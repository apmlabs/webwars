// Hedgewars Engine - Browser IPC Bridge
// Implements message queue for engine IPC protocol

var Module = Module || {};
Module.locateFile = function(path, prefix) {
    if (path.endsWith('.data') || path.endsWith('.wasm')) return path;
    return prefix + path;
};

Module.preRun = Module.preRun || [];
Module.preRun.push(function() {
    try { FS.stat('/Data'); } catch(e) { console.error('[DATA] /Data NOT FOUND:', e.message); }
});

var HWEngine = {
    messageQueue: [],
    outputBuffer: [],
    stderrBuffer: [],

    readIPC: function(bufPtr, maxLen) {
        var count = 0;
        while (count < maxLen && this.messageQueue.length > 0) {
            Module.HEAPU8[bufPtr + count] = this.messageQueue.shift();
            count++;
        }
        return count;
    },

    writeIPC: function(bufPtr, len) {
        var bytes = new Uint8Array(Module.HEAPU8.buffer, bufPtr, len);

        // Auto-respond to pings
        if (len >= 2 && bytes[1] === 0x3f) {
            Array.prototype.unshift.apply(this.messageQueue, [0x03, 0x21, 0x00, 0x00]);
        }

        // Auto-respond to config request 'C'
        if (len >= 2 && bytes[1] === 0x43) {
            if (this.mpConfig) this.startMultiplayerGame();
            else if (this.missionConfig) this.startMissionGame();
            else this.startHotseatGame();
        }

        // Mission/campaign variable storage (V=campaign, v=mission → localStorage)
        if (len >= 4 && (bytes[1] === 0x56 || bytes[1] === 0x76)) {
            var prefix = bytes[1] === 0x56 ? 'V' : 'v';
            var op = String.fromCharCode(bytes[2]);
            var payload = new TextDecoder().decode(bytes.slice(3, len));
            var storageKey = 'hw_' + prefix + '_' + (this.missionConfig ? this.missionConfig.name : 'unknown');
            if (op === '?') {
                var val = localStorage.getItem(storageKey + '_' + payload) || '';
                this.sendMessage(prefix + '.' + val);
            } else if (op === '!') {
                var sp = payload.indexOf(' ');
                if (sp > 0) localStorage.setItem(storageKey + '_' + payload.substring(0, sp), payload.substring(sp + 1));
            }
        }

        // Game stats (i messages) — store for post-game display
        if (len >= 3 && bytes[1] === 0x69) {
            var statType = String.fromCharCode(bytes[2]);
            var statData = new TextDecoder().decode(bytes.slice(3, len));
            if (!this._gameStats) this._gameStats = [];
            this._gameStats.push({type: statType, data: statData});
        }

        // Game finished
        if (len >= 2 && bytes[1] === 0x71) {
            if (typeof window._webwars_gameStats === 'function' && this._gameStats)
                window._webwars_gameStats(this._gameStats);
        }

        // In multiplayer, relay engine messages to lobby
        if (this.mpConfig && len >= 2) {
            var msgType = bytes[1];
            // Engine game messages that need relaying (same set as checkNetCmd legalMessages)
            var relay = 'M#+LlRrUuDdZzAaSjJ,NpPwtgfhbc12345';
            if (relay.indexOf(String.fromCharCode(msgType)) !== -1) {
                var raw = new Uint8Array(len);
                for (var i = 0; i < len; i++) raw[i] = bytes[i];
                var b64 = btoa(String.fromCharCode.apply(null, raw));
                // Direct function call — lobby is in the same page
                if (typeof window._webwars_emRelay === 'function') window._webwars_emRelay(b64);
            }
            if (msgType === 0x71) {
                if (typeof window._webwars_roundFinished === 'function') window._webwars_roundFinished();
            }
        }
    },

    sendMessage: function(msg) {
        if (typeof msg === 'string') msg = new TextEncoder().encode(msg);
        if (msg.length > 254) { console.error('Message too long:', msg.length); return; }
        this.messageQueue.push(msg.length);
        for (var i = 0; i < msg.length; i++) this.messageQueue.push(msg[i]);
    },

    readByte: function() {
        return this.messageQueue.length > 0 ? this.messageQueue.shift() : -1;
    },

    onStdoutByte: function(ch) { this.outputBuffer.push(ch); },

    onStderrByte: function(ch) {
        this.stderrBuffer.push(ch);
        if (ch === 10) {
            var msg = new TextDecoder().decode(new Uint8Array(this.stderrBuffer)).trim();
            // Suppress IPC debug spam
            if (msg.indexOf('[IPC LEVEL') === -1 && msg.indexOf('[Cmd]') === -1)
                console.log('[HW]', msg);
            this.stderrBuffer = [];
        }
    },

    // Ammo string: exactly 60 digits (one per TAmmoType 1..60, amNothing excluded)
    // 9=infinite, 0=disabled. Default scheme based on real Hedgewars:
    // Positions: Grenade Cluster Bazooka Bee Shotgun PickHammer Skip Rope Mine Deagle
    //            Dynamite FirePunch Whip BaseballBat Parachute Airstrike MineStrike
    //            BlowTorch Girder Teleport Switch Mortar Kamikaze Cake Seduction
    //            Watermelon HellishBomb Napalm Drill Ballgun RCPlane LowGravity
    //            ExtraDamage Invulnerable ExtraTime LaserSight Vampiric SniperRifle
    //            Jetpack Molotov Birdy PortalGun Piano GasBomb SineGun Flamethrower
    //            SMine Hammer Resurrector DrillStrike Snowball Tardis LandGun IceGun
    //            Knife Rubber AirMine Creeper Minigun Sentry
    defaultAmmo: '939192919291929192919191919191919191919191919191919191919191',
    zeroAmmo:    '000000000000000000000000000000000000000000000000000000000000',
    defaultProb: '040504050405040504050404040404040404040404040404040404040404',
    defaultDelay:'000000000000020000000000000000000000000000000000000000000000',
    defaultReinf:'000000000000000000000000000000000000000000000000000000000000',

    // Map → theme mapping (from each map's map.cfg line 1)
    mapThemes: {
        'Cake':'Cake','Castle':'Nature','Cave':'Island','Islands':'Deepspace',
        'Mushrooms':'Nature','Tree':'Halloween','Cheese':'Cheese','Bath':'Bath',
        'Bamboo':'Bamboo','Battlefield':'Nature','Blox':'Blox','Cogs':'EarthRise',
        'EarthRise':'EarthRise','Hammock':'Nature','Hedgelove':'Nature',
        'Hogville':'Nature','Lonely_Island':'Island','Plane':'Planes',
        'Sticks':'Bamboo','Trash':'Compost'
    },

    // Theme → music filename (from each theme's theme.cfg)
    themeMusic: {
        'Art':'Art.ogg','Bamboo':'oriental.ogg','Bath':'bath.ogg','Beach':'Beach.ogg',
        'Blox':'Nature.ogg','Brick':'Brick.ogg','Cake':'snow.ogg','Castle':'Castle.ogg',
        'Cave':'snow.ogg','Cheese':'EarthRise.ogg','Christmas':'snow.ogg','City':'City.ogg',
        'Compost':'Compost.ogg','CrazyMission':'snow.ogg','Deepspace':'hell.ogg',
        'Desert':'Desert.ogg','Digital':'Freeway.ogg','EarthRise':'EarthRise.ogg',
        'Eyes':'hell.ogg','Freeway':'Freeway.ogg','Fruit':'Fruit.ogg','Golf':'Golf.ogg',
        'Halloween':'Halloween.ogg','Hell':'hell.ogg','Hoggywood':'Rock.ogg',
        'Island':'pirate.ogg','Jungle':'Jungle.ogg','Nature':'Nature.ogg',
        'Olympics':'Olympics.ogg','Planes':'City.ogg','Sheep':'Sheep.ogg','Snow':'snow.ogg',
        'Stage':'Rock.ogg','Underwater':'underwater.ogg'
    },

    // All available themes (non-hidden ones suitable for random selection)
    allThemes: [
        'Art','Bamboo','Bath','Beach','Brick','Cake','Castle','Cave','Cheese',
        'Christmas','City','Compost','Desert','Digital','EarthRise','Freeway',
        'Fruit','Golf','Halloween','Hell','Hoggywood','Island','Jungle','Nature',
        'Olympics','Sheep','Snow','Stage','Underwater'
    ],

    // Per-theme file manifest (all png + cfg files needed by engine)
    themeFiles: {
        'Art':["BlueWater.png","Border.png","Chunk.png","Droplet.png","Girder.png","LandBackTex.png","LandTex.png","Mona.png","SDDroplet.png","SDFlake.png","SDSplash.png","SDWater.png","Schrei.png","Sky.png","Soup.png","Splash.png","Zeit.png","horizont.png","theme.cfg"],
        'Bamboo':["Bamboo.png","Bamboo2.png","Bamboo3.png","Border.png","Chunk.png","Clouds.png","Flake.png","Flower.png","Girder.png","LandBackTex.png","LandTex.png","Sky.png","SkyL.png","horizont.png","theme.cfg"],
        'Bath':["Border.png","Bubble.png","Chunk.png","Clouds.png","Duck.png","Duck2.png","Dust.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","SDClouds.png","SDFlake.png","Sky.png","Toothbrush.png","Toothbrush_b.png","Toothbrush_g.png","horizont.png","horizontL.png","horizontR.png","theme.cfg"],
        'Beach':["BeachBall.png","BlueWater.png","Boat.png","Border.png","Clouds.png","Droplet.png","Dust.png","Flake.png","Girder.png","LandBackTex.png","LandObject3.png","LandObject38.png","LandObject3_mask.png","LandObject4.png","LandObject5.png","LandTex.png","Object.png","Pier.png","Shell.png","Sky.png","Splash.png","SprayObject29.png","SprayObject36.png","Surfboard.png","horizont.png","kite_base.png","kite_overlay.png","theme.cfg"],
        'Blox':["Border.png","LandBackTex.png","LandTex.png","horizont.png","theme.cfg","tmp.png"],
        'Brick':["BlueWater.png","Border.png","Chunk.png","Clouds.png","Droplet.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","SDDroplet.png","SDSplash.png","SDWater.png","Sky.png","Splash.png","horizont.png","plant1.png","plant2.png","plant3.png","plant4.png","plant5.png","plant6.png","plant7.png","plant8.png","plant9.png","spray1.png","spray2.png","spray3.png","theme.cfg"],
        'Cake':["BlueWater.png","Border.png","CandyCane.png","Cherry.png","Chunk.png","Clouds.png","CupCake.png","Droplet.png","Flake.png","Gingerbread.png","Girder.png","IceCream.png","LandBackTex.png","LandTex.png","Lollipop.png","Oreo.png","Oreo2.png","SDDroplet.png","SDSplash.png","SDWater.png","Sky.png","Snowball.png","Splash.png","amSnowball.png","horizont.png","plant1.png","plant2.png","plant3.png","theme.cfg"],
        'Castle':["Axe.png","BlueWater.png","Border.png","Chunk.png","Clouds.png","Droplet.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","SDClouds.png","SDDroplet.png","SDSplash.png","SDWater.png","Shield.png","Sky.png","SkyL.png","SkyR.png","Spear.png","Splash.png","Sword.png","horizont.png","theme.cfg"],
        'Cave':["Border.png","Chunk.png","Crystal01.png","Crystal02.png","CrystalSpray01.png","CrystalSpray02.png","CrystalSpray03.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","Sky.png","SkyL.png","Stalactite.png","Stalactite_mask.png","Stalagmite01.png","Stalagmite01_mask.png","Stalagmite02.png","Stalagmite02_mask.png","horizont.png","theme.cfg"],
        'Cheese':["Border.png","Chunk.png","Flake.png","LandBackTex.png","LandTex.png","Sky.png","cheese.png","cheese_mask.png","fork.png","horizont.png","knife.png","mouseleft.png","mouseright.png","theme.cfg"],
        'Christmas':["Ball.png","Border.png","CandyCane.png","Chunk.png","Dust.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","Sky.png","Skytrees.png","Snowball.png","Snowman.png","amGirder.png","amSnowball.png","holly.png","holly2.png","horizont.png","plant2.png","plant3.png","plant4.png","reindeer.png","theme.cfg","tree.png"],
        'City':["Border.png","Chunk.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","Sky.png","horizont.png","plant1.png","plant2.png","plant3.png","plant4.png","theme.cfg"],
        'Compost':["BlueWater.png","Border.png","Carrot1.png","Carrot2.png","Carrot3.png","Carrot4.png","Chunk.png","Clouds.png","Cucumber1.png","Cucumber2.png","Cucumber3.png","Cucumber4.png","Droplet.png","Eggshell1.png","Eggshell2.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","Onion1.png","Onion2.png","SDClouds.png","SDDroplet.png","SDSplash.png","SDWater.png","Sky.png","Snowball.png","Splash.png","amSnowball.png","horizont.png","theme.cfg"],
        'CrazyMission':["BlueWater.png","Border.png","Droplet.png","Flake.png","LandTex.png","SDDroplet.png","SDSplash.png","SDWater.png","Sky.png","SkyL.png","Splash.png","theme.cfg"],
        'Deepspace':["BlueWater.png","Border.png","Droplet.png","Flake.png","LandTex.png","SDDroplet.png","SDFlake.png","SDSplash.png","SDWater.png","Sky.png","Splash.png","theme.cfg"],
        'Desert':["BlueWater.png","Border.png","Chunk.png","Clouds.png","Droplet.png","Dust.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","SDClouds.png","SDDroplet.png","SDSplash.png","SDWater.png","Sky.png","Smoke.png","Splash.png","buzzard.png","cactus.png","cobra.png","cowskull.png","horizont.png","rock1.png","rock2.png","sand.png","sandR.png","theme.cfg"],
        'Digital':["BlueWater.png","Border.png","Chunk.png","Clouds.png","Droplet.png","Dust.png","FileA.png","FileHello.png","FileHi.png","FileImg.png","FileMusic.png","FileOmega.png","Flake.png","Flash.png","Folder.png","FolderDoc.png","FolderImg.png","FolderMusic.png","Girder.png","LandBackTex.png","LandTex.png","Mouse.png","Notebook.png","Sky.png","Splash.png","horizont.png","theme.cfg"],
        'EarthRise':["Border.png","Chunk.png","Flake.png","LandBackTex.png","LandTex.png","Rock.png","RockShort.png","RockShort_mask.png","Rock_mask.png","Sky.png","SkyL.png","horizont.png","horizontL.png","horizontR.png","theme.cfg"],
        'Eyes':["BlueWater.png","Border.png","Clouds.png","Droplet.png","Flake.png","LandTex.png","SDClouds.png","SDDroplet.png","SDFlake.png","SDSplash.png","SDWater.png","Sky.png","Splash.png","horizont.png","theme.cfg"],
        'Freeway':["AppleDirt.png","AppleSmall.png","Border.png","BottleDirt.png","Chunk.png","Clouds.png","FishDirt.png","Flake.png","LandBackTex.png","LandTex.png","SDClouds.png","Sky.png","Tire.png","TireDirt.png","horizont.png","theme.cfg"],
        'Fruit':["Banana1.png","Banana2.png","BlueWater.png","Border.png","Chunk.png","Clouds.png","Droplet.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","Orange1.png","Orange2.png","SDClouds.png","SDDroplet.png","SDSplash.png","SDWater.png","Sky.png","SkyL.png","Snowball.png","Splash.png","Watermelon.png","Watermelon_mask.png","amSnowball.png","horizont.png","theme.cfg"],
        'Golf':["Bag.png","Ball.png","Balldirt.png","BlueWater.png","Border.png","Car.png","Chunk.png","Clouds.png","Club.png","Club2.png","Droplet.png","Flag1.png","Flag2.png","Flag3.png","Flag4.png","Flake.png","Girder.png","Hole.png","LandBackTex.png","LandTex.png","SDDroplet.png","SDSplash.png","SDWater.png","Sky.png","SkyL.png","Splash.png","Tee.png","horizont.png","theme.cfg"],
        'Halloween':["BlueWater.png","Border.png","Chunk.png","Clouds.png","Droplet.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","Rock.png","RockShort.png","SDClouds.png","SDDroplet.png","SDSplash.png","SDWater.png","Sky.png","SkyL.png","Splash.png","horizont.png","theme.cfg"],
        'Hell':["BlueWater.png","Border.png","Chunk.png","Clouds.png","Droplet.png","Flake.png","LandBackTex.png","LandTex.png","SDClouds.png","SDDroplet.png","SDSplash.png","SDWater.png","Sky.png","Splash.png","horizont.png","plant1.png","plant2.png","plant3.png","plant4.png","theme.cfg"],
        'Hoggywood':["Border.png","Clouds.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","SDClouds.png","SignL.png","SignR.png","Sky.png","SkyL.png","camera.png","clapper.png","hogscar.png","horizont.png","horizontL.png","palm.png","reel.png","reel2.png","star1.png","star2.png","star3.png","star4.png","star5.png","theme.cfg"],
        'Island':["Border.png","Chunk.png","Flake.png","LandBackTex.png","LandTex.png","Sky.png","SkyL.png","anchor.png","horizont.png","plant1.png","plant2.png","plant3.png","plant4.png","theme.cfg"],
        'Jungle':["BlueWater.png","Border.png","Clouds.png","Droplet.png","FernLeft.png","FernRight.png","Flake.png","FlowerBlue.png","FlowerRed.png","Flowers.png","Girder.png","LandBackTex.png","LandTex.png","Liana.png","Monkey.png","PalmTree.png","Sky.png","SkyL.png","Snake.png","Spider.png","Splash.png","horizont.png","theme.cfg"],
        'Nature':["Border.png","Chunk.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","Sky.png","butterfly.png","horizont.png","mole.png","mole2.png","mole3.png","mushroom.png","mushroom2.png","plant1.png","plant2.png","plant3.png","plant4.png","snail.png","theme.cfg"],
        'Olympics':["Border.png","Chunk.png","Column01.png","Column02.png","Column03.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","Sky.png","SkyL.png","Statue.png","horizont.png","theme.cfg"],
        'Planes':["Border.png","LandTex.png","Sky.png","horizont.png","theme.cfg"],
        'Sheep':["Border.png","Chunk.png","Clouds.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","Sky.png","SkyL.png","barriere.png","fleur.png","fleurland.png","fleurland2.png","fleurland3.png","fleurland4.png","grass.png","grass2.png","grassp.png","grassp2.png","horizont.png","mouton1.png","mouton2.png","mouton3.png","mouton4.png","rocher.png","theme.cfg"],
        'Snow':["Border.png","Chunk.png","Dust.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","Sky.png","Snowball.png","amGirder.png","amSnowball.png","horizont.png","plant1.png","plant2.png","plant3.png","plant4.png","theme.cfg"],
        'Stage':["Bass.png","BlueWater.png","Border.png","Box.png","Chunk.png","Droplet.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","Light.png","MicL.png","MicR.png","SDDroplet.png","SDSplash.png","SDWater.png","Sky.png","SkyL.png","Splash.png","drum.png","horizont.png","poster1.png","poster2.png","poster3.png","poster4.png","theme.cfg"],
        'Underwater':["BlueWater.png","Border.png","Clouds.png","Droplet.png","Dust.png","Flake.png","Girder.png","LandBackTex.png","LandTex.png","SDClouds.png","SDDroplet.png","SDFlake.png","SDSplash.png","SDWater.png","Sky.png","Snowball.png","Splash.png","amSnowball.png","anchor.png","clam.png","coral.png","coral2.png","crab.png","horizont.png","theme.cfg"]
    },

    // Fetch theme assets + music into Emscripten FS before engine needs them
    // Returns a Promise that resolves when all files are written
    fetchThemeAssets: function(theme) {
        var basePath = (window._webwars_assetBase || 'assets');
        var promises = [];

        // Fetch theme directory (skip Nature — already in core.data)
        if (theme !== 'Nature') {
            var themeUrl = basePath + '/Themes/' + theme + '/';
            var files = this.themeFiles[theme] || [];
            var fsDir = '/Data/Themes/' + theme;
            promises.push(this._fetchFilesIntoFS(themeUrl, files, fsDir));
        }

        // Fetch music file
        var musicFN = this.themeMusic[theme] || 'Nature.ogg';
        promises.push(this._fetchFileIntoFS(
            basePath + '/Music/' + musicFN, '/Data/Music/' + musicFN));

        return Promise.all(promises);
    },

    _fetchFileIntoFS: function(url, fsPath) {
        return fetch(url).then(function(r) {
            if (!r.ok) { console.log('[Assets] Not found: ' + url); return; }
            return r.arrayBuffer().then(function(buf) {
                var parts = fsPath.split('/');
                for (var i = 1; i < parts.length - 1; i++) {
                    try { FS.mkdir(parts.slice(0, i + 1).join('/')); } catch(e) {}
                }
                FS.writeFile(fsPath, new Uint8Array(buf));
                console.log('[Assets] Loaded ' + fsPath + ' (' + (buf.byteLength/1024|0) + 'KB)');
            });
        }).catch(function(e) { console.log('[Assets] Failed: ' + url, e.message); });
    },

    _fetchFilesIntoFS: function(baseUrl, files, fsDir) {
        var self = this;
        try { FS.mkdir(fsDir); } catch(e) {}
        return Promise.all(files.map(function(f) {
            return self._fetchFileIntoFS(baseUrl + f, fsDir + '/' + f);
        }));
    },

    sendAmmoAndTeam: function(hash, color, name, hogs) {
        // Sanity check: engine expects exactly 60 chars per ammo string
        if (this.defaultAmmo.length !== 60 || this.zeroAmmo.length !== 60) {
            console.error('[HW] FATAL: ammo string length wrong! default=' + this.defaultAmmo.length + ' zero=' + this.zeroAmmo.length);
        }
        // Ammo store MUST be sent before each team (per Hedgewars protocol)
        this.sendMessage('eammloadt ' + this.defaultAmmo);
        this.sendMessage('eammprob ' + this.defaultProb);
        this.sendMessage('eammdelay ' + this.defaultDelay);
        this.sendMessage('eammreinf ' + this.defaultReinf);
        this.sendMessage('eammstore');

        // addteam format: "eaddteam <hash> <color_decimal> <name>"
        this.sendMessage('eaddteam ' + hash + ' ' + color + ' ' + name);
        this.sendMessage('efort Earth');

        // addhh format: "eaddhh <botlevel> <health> <name>"
        for (var i = 0; i < hogs.length; i++) {
            this.sendMessage('eaddhh 0 100 ' + hogs[i]);
            this.sendMessage('ehat NoHat');
        }
    },

    startHotseatGame: function() {
        console.log('[HW] Starting hotseat game...');

        var seed = '{' + Math.random().toString(36).substring(2, 10) + '}';
        var theme = this._chosenTheme || 'Nature';
        console.log('[HW] Selected random map, theme: ' + theme);

        // Read config from UI dropdowns if available
        var cfg = (typeof window._webwars_hotseatConfig === 'function') ? window._webwars_hotseatConfig() : null;
        var scheme = (cfg && cfg.scheme) ? cfg.scheme : ((typeof GameConfig !== 'undefined') ? GameConfig.SCHEMES[0] : null);
        var weapon = (cfg && cfg.weapon) ? cfg.weapon : null;
        var style = (cfg && cfg.style && cfg.style !== 'Normal') ? cfg.style : null;

        // Order matches real Hedgewars server (EngineInteraction.hs)
        this.sendMessage('etheme ' + theme);

        // Script (must be before seed for some game styles)
        if (style) {
            this.sendMessage('escript Scripts/Multiplayer/' + style.replace(/ /g, '_') + '.lua');
        }

        this.sendMessage('eseed ' + seed);

        // Scheme
        if (scheme && typeof GameConfig !== 'undefined') {
            GameConfig.sendSchemeIPC(this, scheme);
        } else {
            this.sendMessage('e$gmflags 0');
            this.sendMessage('e$damagepct 100');
            this.sendMessage('e$turntime 45000');
            this.sendMessage('e$sd_turns 15');
            this.sendMessage('e$casefreq 5');
            this.sendMessage('e$minestime 3000');
            this.sendMessage('e$minesnum 4');
            this.sendMessage('e$minedudpct 0');
            this.sendMessage('e$explosives 2');
            this.sendMessage('e$airmines 0');
            this.sendMessage('e$healthprob 35');
            this.sendMessage('e$hcaseamount 25');
            this.sendMessage('e$waterrise 47');
            this.sendMessage('e$healthdec 5');
            this.sendMessage('e$ropepct 100');
            this.sendMessage('e$getawaytime 100');
            this.sendMessage('e$worldedge 0');
        }
        this.sendMessage('e$template_filter 0');
        this.sendMessage('e$feature_size 12');
        this.sendMessage('e$mapgen 0');

        // Teams with selected weapon set
        var ammoStr = (weapon && weapon.ammo) ? weapon.ammo : null;
        var initHealth = scheme ? (scheme.params[2] || 100) : 100;
        this._sendHotseatTeam('x', '4980735', 'Red Team', ['Hog A1','Hog A2','Hog A3','Hog A4'], initHealth, ammoStr);
        this._sendHotseatTeam('x', '16776960', 'Blue Team', ['Hog B1','Hog B2','Hog B3','Hog B4'], initHealth, ammoStr);

        // Start
        this.sendMessage('TL');
        this.sendMessage('!');
    },

    _sendHotseatTeam: function(hash, color, name, hogs, health, ammoStr) {
        if (ammoStr && ammoStr.length >= 240 && typeof GameConfig !== 'undefined') {
            GameConfig.sendAmmoIPC(this, ammoStr);
        } else {
            this.sendMessage('eammloadt ' + this.defaultAmmo);
            this.sendMessage('eammprob ' + this.defaultProb);
            this.sendMessage('eammdelay ' + this.defaultDelay);
            this.sendMessage('eammreinf ' + this.defaultReinf);
            this.sendMessage('eammstore');
        }
        this.sendMessage('eaddteam ' + hash + ' ' + color + ' ' + name);
        this.sendMessage('efort Earth');
        for (var i = 0; i < hogs.length; i++) {
            this.sendMessage('eaddhh 0 ' + health + ' ' + hogs[i]);
            this.sendMessage('ehat NoHat');
        }
    },

    startMissionGame: function() {
        var cfg = this.missionConfig;
        console.log('[HW] Starting mission: ' + cfg.script);
        var seed = '{' + Math.random().toString(36).substring(2, 10) + '}';
        this.sendMessage('TL');
        // One team, 8 hedgehogs (mission script controls actual count)
        var teamName = cfg.team || 'Player';
        this.sendMessage('eaddteam 16776960 ' + teamName);
        for (var i = 0; i < 8; i++) this.sendMessage('ename hog' + (i+1));
        for (var i = 0; i < 8; i++) this.sendMessage('ehat NoHat');
        this.sendMessage('eammloadt 9391929422199121032235111001201000000211110101011');
        this.sendMessage('eammprob 0405040541600655546554464776576666666155510101115');
        this.sendMessage('eammdelay 0000000000000205500000040007004000000000220000000');
        this.sendMessage('eammreinf 1311110312111111123114111111111111111211111111111');
        this.sendMessage('eammstore');
        this.sendMessage('eseed ' + seed);
        this.sendMessage('escript ' + cfg.script);
    },

    startMultiplayerGame: function() {
        var cfg = this.mpConfig;
        console.log('[HW] Starting multiplayer game...', cfg);

        // TN for network game (must be first, before config)
        this.sendMessage('TN');

        // Map
        var mapgen = cfg.mapgen || '0';
        var mapGenTypes = ['+rnd+', '+maze+', '+drawn+', '+perlin+'];
        var mapName = cfg.map || mapGenTypes[parseInt(mapgen)] || '+rnd+';
        if (mapGenTypes.indexOf(mapName) === -1) this.sendMessage('emap ' + mapName);

        this.sendMessage('etheme ' + (cfg.theme || 'Nature'));

        // Script
        if (cfg.script && cfg.script !== 'Normal') {
            this.sendMessage('escript Scripts/Multiplayer/' + cfg.script.replace(/ /g, '_') + '.lua');
        }

        this.sendMessage('eseed ' + (cfg.seed || String(Date.now())));
        this.sendMessage('e$mapgen ' + mapgen);
        this.sendMessage('e$template_filter ' + (cfg.template || '0'));
        this.sendMessage('e$feature_size ' + (cfg.featureSize || '12'));

        // Scheme — cfg.scheme is now a scheme object {name, flags, params, scriptparam}
        var scheme = cfg.scheme;
        if (scheme && scheme.flags && typeof GameConfig !== 'undefined') {
            GameConfig.sendSchemeIPC(this, scheme);
        } else {
            // Fallback defaults
            this.sendMessage('e$gmflags 0');
            this.sendMessage('e$damagepct 100');
            this.sendMessage('e$turntime 45000');
            this.sendMessage('e$sd_turns 15');
            this.sendMessage('e$casefreq 5');
            this.sendMessage('e$minestime 3000');
            this.sendMessage('e$minesnum 4');
            this.sendMessage('e$minedudpct 0');
            this.sendMessage('e$explosives 2');
            this.sendMessage('e$airmines 0');
            this.sendMessage('e$healthprob 35');
            this.sendMessage('e$hcaseamount 25');
            this.sendMessage('e$waterrise 47');
            this.sendMessage('e$healthdec 5');
            this.sendMessage('e$ropepct 100');
            this.sendMessage('e$getawaytime 100');
            this.sendMessage('e$worldedge 0');
        }

        // Teams — ammo per team
        var ammo = cfg.ammo || '';
        var initHealth = (scheme && scheme.params) ? (scheme.params[2] || 100) : 100;
        var teams = cfg.teams || [];
        for (var k = 0; k < teams.length; k++) {
            var t = teams[k];
            if (ammo.length >= 240 && typeof GameConfig !== 'undefined') {
                GameConfig.sendAmmoIPC(this, ammo);
            } else {
                this.sendMessage('eammloadt ' + this.defaultAmmo);
                this.sendMessage('eammprob ' + this.defaultProb);
                this.sendMessage('eammdelay ' + this.defaultDelay);
                this.sendMessage('eammreinf ' + this.defaultReinf);
                this.sendMessage('eammstore');
            }

            var colorDecimal = (1 + parseInt(t.color || '0')) * 2113696;
            this.sendMessage('eaddteam <hash> ' + colorDecimal + ' ' + t.name);
            if (t.owner !== cfg.myNick) this.sendMessage('erdriven');
            this.sendMessage('efort ' + (t.fort || 'Plane'));

            var hhnum = t.hhnum || 4;
            var hogs = t.hogs || [];
            for (var h = 0; h < hhnum && h < hogs.length; h++) {
                this.sendMessage('eaddhh ' + (t.diff || '0') + ' ' + initHealth + ' ' + hogs[h].name);
                this.sendMessage('ehat ' + (hogs[h].hat || 'NoHat'));
            }
        }

        this.sendMessage('!');
    }
};

Module.HWEngine = HWEngine;

// Load multiplayer config from sessionStorage if ?mp=1
if (typeof window !== 'undefined' && window.location.search.indexOf('mp=1') !== -1) {
    try {
        var cfg = JSON.parse(sessionStorage.getItem('webwars_game'));
        if (cfg) { HWEngine.mpConfig = cfg; console.log('[HW] Multiplayer mode, config loaded from sessionStorage'); }
    } catch(e) { console.error('[HW] Failed to load MP config:', e); }
}
// Also check for mpConfig injected directly by lobby page (dynamic load)
if (typeof window !== 'undefined' && window._webwars_mpConfig && !HWEngine.mpConfig) {
    HWEngine.mpConfig = window._webwars_mpConfig;
    console.log('[HW] Multiplayer mode, config injected by lobby');
}
// Check for mission config
if (typeof window !== 'undefined' && typeof window._webwars_missionConfig === 'function') {
    HWEngine.missionConfig = window._webwars_missionConfig();
    console.log('[HW] Mission mode: ' + HWEngine.missionConfig.script);
}
Module.noInitialRun = false;
Module.arguments = ['--prefix', '/Data', '--user-prefix', '/Data', 'test.hwd'];
Module.preRun = Module.preRun || [];
Module.postRun = Module.postRun || [];

Module.preRun.push(function() {
    FS.init(
        function() { var b = HWEngine.readByte(); return (b === -1) ? null : (b & 0xFF); },
        function(ch) { HWEngine.onStdoutByte(ch); },
        function(ch) { HWEngine.onStderrByte(ch); }
    );

    // Choose theme now and fetch assets before engine starts
    var theme;
    if (HWEngine.mpConfig) {
        theme = HWEngine.mpConfig.theme || 'Nature';
    } else {
        var cfg = (typeof window._webwars_hotseatConfig === 'function') ? window._webwars_hotseatConfig() : null;
        if (cfg && cfg.theme && cfg.theme !== 'Random') {
            theme = cfg.theme;
        } else {
            theme = HWEngine.allThemes[Math.floor(Math.random() * HWEngine.allThemes.length)];
        }
    }
    HWEngine._chosenTheme = theme;
    console.log('[Assets] Pre-fetching theme: ' + theme);

    Module.addRunDependency('theme-assets');
    HWEngine.fetchThemeAssets(theme).then(function() {
        console.log('[Assets] Theme assets ready');
        Module.removeRunDependency('theme-assets');
    }).catch(function(e) {
        console.error('[Assets] Fetch failed, continuing anyway:', e);
        Module.removeRunDependency('theme-assets');
    });
});

Module.print = function(text) { if (text) console.log('[Engine]', text); };
Module.printErr = function(text) {
    if (!text) return;
    if (text.indexOf('dependency: fp') !== -1) return;
    if (text.indexOf('still waiting') !== -1) return;
    if (text.indexOf('Aborted(Assertion') !== -1) return;
    if (text.indexOf('user callback triggered') !== -1) return;
    console.error('[Engine Error]', text);
};

// setStatus and canvas are defined in hwengine.html before this script loads.
// Do NOT redefine them here — the HTML versions handle the progress bar UI.

// WebWars Game Configuration Data
// Extracted from Qt frontend: gameSchemeModel.cpp, weapons.h, hwconsts.cpp.in
// Used by both index.html (hotseat) and lobby.html (multiplayer)

var GameConfig = (function() {
'use strict';

// ── Game Flag Constants (from EngineInteraction.hs) ──
// Indices 1-25 in scheme arrays map to these bit flags for e$gmflags
var FLAG_BITS = [
    0x1000,    //  1 switchhog
    0x10,      //  2 divteams
    0x4,       //  3 solidland
    0x8,       //  4 border
    0x20,      //  5 lowgrav
    0x40,      //  6 laser
    0x80,      //  7 invulnerability
    0x100,     //  8 resethealth
    0x200,     //  9 vampiric
    0x400,     // 10 karma
    0x800,     // 11 artillery
    0x2000,    // 12 randomorder
    0x4000,    // 13 king
    0x8000,    // 14 placehog
    0x10000,   // 15 sharedammo
    0x20000,   // 16 disablegirders
    0x40000,   // 17 disablelandobjects
    0x80000,   // 18 aisurvival
    0x100000,  // 19 infattack
    0x200000,  // 20 resetweps
    0x400000,  // 21 perhogammo
    0x800000,  // 22 disablewind
    0x1000000, // 23 morewind
    0x2000000, // 24 tagteam
    0x4000000  // 25 bottomborder
];

// Scheme parameter names sent to engine (indices 26-43 in scheme array)
// Multiplier converts UI value to engine value (e.g. turntime seconds → ms)
var SCHEME_PARAMS = [
    {cmd: 'e$damagepct',   mult: 1},    // 26
    {cmd: 'e$turntime',    mult: 1000}, // 27
    {cmd: '',              mult: 0},    // 28 (init health — used for eaddhh, not sent as e$ cmd)
    {cmd: 'e$sd_turns',    mult: 1},    // 29
    {cmd: 'e$casefreq',    mult: 1},    // 30
    {cmd: 'e$minestime',   mult: 1000}, // 31
    {cmd: 'e$minesnum',    mult: 1},    // 32
    {cmd: 'e$minedudpct',  mult: 1},    // 33
    {cmd: 'e$explosives',  mult: 1},    // 34
    {cmd: 'e$airmines',    mult: 1},    // 35
    {cmd: 'e$sentries',    mult: 1},    // 36 — NOTE: not in EngineInteraction.hs schemeParams, but engine accepts it
    {cmd: 'e$healthprob',  mult: 1},    // 37
    {cmd: 'e$hcaseamount', mult: 1},    // 38
    {cmd: 'e$waterrise',   mult: 1},    // 39
    {cmd: 'e$healthdec',   mult: 1},    // 40
    {cmd: 'e$ropepct',     mult: 1},    // 41
    {cmd: 'e$getawaytime', mult: 1},    // 42
    {cmd: 'e$worldedge',   mult: 1}     // 43
];

// ── 16 Scheme Presets ──
// Each: [name, 25 booleans (flags 1-25), 19 numbers (params 26-44)]
// Index 44 = scriptparam (string or null)
var SCHEMES = [
    {name:'Default', desc:'Standard rules. 45s turns, 100 health, random order.',
     flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0],
     params:[100,45,100,15,5,3,4,0,2,0,0,35,25,47,5,100,100,0], scriptparam:null},
    {name:'Pro Mode', desc:'Fast & competitive. 15s turns, no crates, no mines, shared ammo.',
     flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0],
     params:[100,15,100,15,0,3,0,0,2,0,0,35,25,47,5,100,100,0], scriptparam:null},
    {name:'Shoppa', desc:'Rope-only combat. Solid indestructible land, no girders, weapon crates only.',
     flags:[0,0,1,1,0,0,0,0,0,0,0,1,0,0,1,1,1,0,0,1,0,0,0,0,0],
     params:[100,30,100,50,1,0,0,0,0,0,0,0,25,0,0,100,100,0], scriptparam:null},
    {name:'Clean Slate', desc:'Start invulnerable. Weapons reset each turn, AI survival mode.',
     flags:[0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0],
     params:[100,45,100,15,5,3,4,0,2,0,0,35,25,47,5,100,100,0], scriptparam:null},
    {name:'Minefield', desc:'200 mines everywhere! 50 health, shared ammo. Watch your step.',
     flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0],
     params:[100,30,50,15,0,0,200,0,0,0,0,35,25,47,5,100,100,0], scriptparam:null},
    {name:'Barrel Mayhem', desc:'200 explosive barrels scattered across the map. Chain reactions galore.',
     flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0],
     params:[100,30,100,15,0,0,0,0,200,0,0,35,25,47,5,100,100,0], scriptparam:null},
    {name:'Tunnel Hogs', desc:'Border walls, lots of mines and barrels. Dig tunnels to survive.',
     flags:[0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0],
     params:[100,30,100,15,5,3,10,10,10,4,0,35,25,47,5,100,100,0], scriptparam:null},
    {name:'Timeless', desc:'Unlimited turn time. No water rise, no health decay. Take your time.',
     flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0],
     params:[100,9999,100,15,5,3,5,10,2,0,0,35,30,0,0,100,100,0], scriptparam:null},
    {name:'Thinking with Portals', desc:'Karma mode — damage you deal is reflected back. Portal gun emphasis.',
     flags:[0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0],
     params:[100,45,100,15,2,3,5,0,5,4,0,25,25,47,5,100,100,0], scriptparam:null},
    {name:'King Mode', desc:'Each team has a king. If the king dies, the whole team loses.',
     flags:[0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0],
     params:[100,45,100,15,5,3,4,0,2,0,0,35,25,47,5,100,100,0], scriptparam:null},
    {name:'Mutant', desc:'20s turns, infinite attacks, no health crates. Fast and deadly.',
     flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0],
     params:[100,20,100,15,2,1,4,0,2,0,0,0,25,0,0,100,100,0], scriptparam:null},
    {name:'Construction Mode', desc:'Build structures, generate power, buy crates. Strategy-heavy.',
     flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,1,0,1,0,0,0,0],
     params:[100,45,100,15,5,3,0,0,0,0,0,35,25,47,5,100,100,0],
     scriptparam:'initialenergy=550, energyperround=50, maxenergy=1000, cratesperround=5'},
    {name:'The Specialists', desc:'Each hedgehog has a unique role and weapon. Place hogs manually.',
     flags:[1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,0,0],
     params:[100,45,100,15,5,3,0,0,0,0,0,100,25,47,5,100,100,0],
     scriptparam:'t=SENDXHPL'},
    {name:'Space Invasion', desc:'Arcade shooter — destroy invaders for points. 3 rounds.',
     flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0],
     params:[100,45,100,50,0,3,0,0,0,0,0,0,25,0,0,100,100,0],
     scriptparam:'rounds=3, shield=30, barrels=5, pings=2, barrelbonus=3, shieldbonus=30, timebonus=4'},
    {name:'HedgeEditor', desc:'Map editor mode. Unlimited time, place objects freely.',
     flags:[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0],
     params:[100,9999,100,50,0,3,0,0,0,0,0,35,25,0,0,100,100,0], scriptparam:null},
    {name:'Racer', desc:'Race through waypoints. Solid land, laser sight, 90s turns.',
     flags:[0,0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,1,0,1,1,0,0,0,0,0],
     params:[100,90,100,50,0,0,0,0,0,0,0,0,25,0,0,100,100,0], scriptparam:null}
];

// ── 13 Weapon Presets ──
// Each ammo string = 4 × 60 chars: init + prob + delay + crate
var WEAPONS = [
    {name:'Default', desc:'Balanced loadout. Most weapons available with standard ammo counts.',
     ammo:'939192942219912103223511100120000000021110010101111100010001' +
          '040504054160065554655446477657666666615551010111541111111073' +
          '000000000000020550000004000700400000000022000000060002000000' +
          '131111031211111112311411111111111111121111111111111111111111'},
    {name:'Crazy', desc:'Everything maxed out. Infinite ammo for all weapons.',
     ammo:'999999999999999999299999999999999929999999999999999299919099' +
          '111111011111111111111111111111111111111111111111111111111011' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '131111031211111112311411111111111111121111111111111111111111'},
    {name:'Pro Mode', desc:'Minimal weapons. Bazooka and grenade only — pure skill.',
     ammo:'909000900000000000000900000000000000000000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '000000000000020550000004000700400000000020000000000002000000' +
          '111111011111111111111111111111111111111111111111111111111111'},
    {name:'Shoppa', desc:'Rope and crates only. Swing to collect weapon crates.',
     ammo:'000000990000000000000000000000000000000000000000000000000000' +
          '444441004424440221011212122242200000000200040001001100101010' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '111111011111111111111111111111111111111111111111111111111111'},
    {name:'Clean Slate', desc:'Light starting loadout. Weapons come from crates.',
     ammo:'101000900001000001100000000000000000000000000000100000000000' +
          '040504054160065554655446477657666666615551010111541112111040' +
          '000000000000000000000000000000000000000000000000000002000000' +
          '131111031211111112311411111111111111121111111111111111111111'},
    {name:'Minefield', desc:'Shotgun and rope to navigate the mines. No starting weapons.',
     ammo:'000000990009000000030000000000000000000000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '000000000000020550000004000700400000000020000000060002000000' +
          '111111011111111111111111111111111111111111111111111111111111'},
    {name:'Thinking with Portals', desc:'Portal gun plus a mix of weapons. Teleport shots through portals.',
     ammo:'900000900200000000210000000000000011000009000000000000000000' +
          '040504054160065554655446477657666666615551010111541112111020' +
          '000000000000020550000004000700400000000020000000060002000000' +
          '131111031211111112311411111111111111121111111111111111111111'},
    {name:'One of Everything', desc:'Exactly one of every weapon. Use them wisely.',
     ammo:'111111911111111111111111111111111111111111111111111111111011' +
          '111111011111111111111111111111111111111111111111111111111011' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '111111011111111111111111111111111111111111111111111111111111'},
    {name:'Highlander', desc:'Kill to collect weapons. There can be only one.',
     ammo:'111111911111111111110191111111111001011111011110010010111010' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000001'},
    {name:'Balanced Random Weapon', desc:'Random weapons each turn, weighted by ammo probability.',
     ammo:'333233923323323223232331311221130000032322030220222000203010' +
          '000000000000000000000000000000001111100000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '111111011111111111111111111111111111111111111111111111111111'},
    {name:'Construction Mode', desc:'Building-focused loadout for Construction Mode style.',
     ammo:'110001900000001001009000000000000000000000000000000000000000' +
          '111111011111111001000111111011111111111111011111001011101010' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '111111011111111111111111111111111111111111111111111111111111'},
    {name:'Shoppa Pro', desc:'Hardcore Shoppa. Fewer crate types, rope mastery required.',
     ammo:'000000990000000000000000000000000000000000000000000000000000' +
          '444440004404440000000000000040000000000000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '111111011111111111111111111111111111111111111111111112111111'},
    {name:'HedgeEditor', desc:'No starting weapons. For use with the HedgeEditor style.',
     ammo:'000000900000000000000000000000000000000000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '111111011111111111111111111111111111111111111111111111111111'}
];

// ── 29 Themes ──
var THEMES = [
    {name:'Random', desc:'A random theme each game.'},
    {name:'Art', desc:'Famous paintings and art supplies. Soup water.'},
    {name:'Bamboo', desc:'Asian bamboo forest with flowers and butterflies.'},
    {name:'Bath', desc:'Giant bathtub with rubber ducks and toothbrushes.'},
    {name:'Beach', desc:'Sandy beach with surfboards, boats, and kites.'},
    {name:'Brick', desc:'Red brick walls with climbing plants.'},
    {name:'Cake', desc:'Candy land with cupcakes, lollipops, and gingerbread.'},
    {name:'Castle', desc:'Medieval castle with swords, shields, and spears.'},
    {name:'Cave', desc:'Underground cave with crystals and stalactites.'},
    {name:'Cheese', desc:'Swiss cheese landscape with mice and cutlery.'},
    {name:'Christmas', desc:'Snowy winter with candy canes, snowmen, and reindeer.'},
    {name:'City', desc:'Urban rooftops and buildings.'},
    {name:'Compost', desc:'Garden compost heap with vegetables and eggshells.'},
    {name:'Desert', desc:'Arid desert with cacti, cobras, and cow skulls.'},
    {name:'Digital', desc:'Inside a computer — files, folders, and circuit boards.'},
    {name:'EarthRise', desc:'Moon surface with Earth rising on the horizon.'},
    {name:'Freeway', desc:'Highway roadside with tires and litter.'},
    {name:'Fruit', desc:'Tropical fruit paradise with bananas and watermelons.'},
    {name:'Golf', desc:'Golf course with clubs, flags, and golf carts.'},
    {name:'Halloween', desc:'Spooky graveyard with dark skies.'},
    {name:'Hell', desc:'Fiery underworld with lava and dark plants.'},
    {name:'Hoggywood', desc:'Movie studio with cameras, reels, and star signs.'},
    {name:'Island', desc:'Pirate island with anchors and tropical plants.'},
    {name:'Jungle', desc:'Dense jungle with monkeys, snakes, and spiders.'},
    {name:'Nature', desc:'Green meadow with mushrooms, snails, and butterflies.'},
    {name:'Olympics', desc:'Ancient Greek arena with columns and statues.'},
    {name:'Sheep', desc:'French countryside with sheep and flowers.'},
    {name:'Snow', desc:'Snowy landscape with snowballs and pine trees.'},
    {name:'Stage', desc:'Rock concert stage with drums, lights, and speakers.'},
    {name:'Underwater', desc:'Ocean floor with corals, crabs, and clams.'}
];

// ── 21 Game Styles (Lua scripts in Scripts/Multiplayer/) ──
var STYLES = [
    {name:'Normal', desc:'Standard game. No special rules.', script:null, lock:null},
    {name:'Balanced Random Weapon', desc:'1-3 random weapons each turn, weighted by ammo settings.', script:'Balanced_Random_Weapon', lock:{weapons:'Balanced Random Weapon'}},
    {name:'Battalion', desc:'Each hedgehog has different stats and abilities.', script:'Battalion', lock:{weapons:true}},
    {name:'Capture the Flag', desc:'Capture the enemy flag and bring it to your base.', script:'Capture_the_Flag', lock:null},
    {name:'Construction Mode', desc:'Build structures, generate power, buy crates and defenses.', script:'Construction_Mode', lock:{scheme:'Construction Mode', weapons:'Construction Mode'}},
    {name:'Continental supplies', desc:'Choose a continent — each has unique weapons and specials.', script:'Continental_supplies', lock:{weapons:true}},
    {name:'DiagonalMaze', desc:'Fight in a randomly generated diagonal maze.', script:'DiagonalMaze', lock:null},
    {name:'Frenzy', desc:'Rapid-fire chaos. Weapons cycle automatically.', script:'Frenzy', lock:{weapons:true}},
    {name:'Gravity', desc:'Gravity changes throughout the game. Adapt or fall.', script:'Gravity', lock:null},
    {name:'HedgeEditor', desc:'Place gears and objects freely. A map/scenario editor.', script:'HedgeEditor', lock:{scheme:'HedgeEditor', weapons:'HedgeEditor'}},
    {name:'Highlander', desc:'Kill enemies to steal their weapons. Last hog standing.', script:'Highlander', lock:{weapons:'Highlander'}},
    {name:'Mutant', desc:'Kill to become the Mutant — gain health and powers. Everyone hunts the Mutant.', script:'Mutant', lock:{weapons:true}},
    {name:'No Jumping', desc:'Jumping is disabled. Use utilities to get around.', script:'No_Jumping', lock:null},
    {name:'Racer', desc:'Race through waypoints as fast as possible. Best time wins.', script:'Racer', lock:{scheme:'Racer', weapons:'Shoppa'}},
    {name:'Random Weapon', desc:'Get a completely random weapon each turn.', script:'Random_Weapon', lock:{weapons:true}},
    {name:'ShoppaMap', desc:'Auto-generated Shoppa-friendly map with roping terrain.', script:'ShoppaMap', lock:null},
    {name:'Space Invasion', desc:'Arcade shooter — destroy alien invaders for points.', script:'Space_Invasion', lock:{weapons:true}},
    {name:'TechRacer', desc:'Technical racing with Shoppa rules. Official time records.', script:'TechRacer', lock:{weapons:true}},
    {name:'The Specialists', desc:'Each hedgehog has a unique role: Sniper, Engineer, Demoman, etc.', script:'The_Specialists', lock:{weapons:true}},
    {name:'Tumbler', desc:'Fly with a jetpack, dodge mines and barrels raining from above.', script:'Tumbler', lock:{weapons:true}},
    {name:'Tunnels', desc:'Fight in randomly generated tunnels. Close-quarters combat.', script:'Tunnels', lock:null},
    {name:'WxW', desc:'Wall-to-Wall Shoppa. Walls appear between turns for cover.', script:'WxW', lock:{weapons:true}}
];

// ── 25 Quick Game Maps ──
var QUICK_MAPS = [
    'Bamboo','Bath','Battlefield','Blox','Bubbleflow','Cake','Castle','Cheese',
    'Cogs','CrazyMission','EarthRise','Eyes','Hammock','HedgeFortress','Hedgelove',
    'Hedgewars','Hydrant','Lonely_Island','Mushrooms','Octorama','PirateFlag',
    'Plane','Sheep','Trash','Tree'
];

// ── Team Colors (from hwconsts.cpp.in HW_TEAMCOLOR_ARRAY) ──
var TEAM_COLORS = [
    0x4C0000FF, 0x4C00FF00, 0x4CFF0000, 0x4CFF00FF,
    0x4C00FFFF, 0x4CFFFF00, 0x4C7F7F7F, 0x4C000000
];
// Decimal colors for engine: (1 + index) * 2113696
var TEAM_COLORS_DEC = [2113696, 4227392, 6341088, 8454784, 10568480, 12682176, 14795872, 16909568];

// ── Helpers ──

// Compute e$gmflags from a scheme's boolean flags array
function computeGmflags(flags) {
    var v = 0;
    for (var i = 0; i < flags.length && i < FLAG_BITS.length; i++) {
        if (flags[i]) v |= FLAG_BITS[i];
    }
    return v;
}

// Send all scheme IPC commands to HWEngine
function sendSchemeIPC(hw, scheme) {
    hw.sendMessage('e$gmflags ' + computeGmflags(scheme.flags));
    for (var i = 0; i < SCHEME_PARAMS.length && i < scheme.params.length; i++) {
        var p = SCHEME_PARAMS[i];
        if (p.cmd) hw.sendMessage(p.cmd + ' ' + (scheme.params[i] * p.mult));
    }
    if (scheme.scriptparam) {
        hw.sendMessage('e$scriptparam ' + scheme.scriptparam);
    }
}

// Send ammo IPC for one team
function sendAmmoIPC(hw, ammoStr) {
    var n = ammoStr.length / 4; // should be 60
    hw.sendMessage('eammloadt ' + ammoStr.substring(0, n));
    hw.sendMessage('eammprob ' + ammoStr.substring(n, n*2));
    hw.sendMessage('eammdelay ' + ammoStr.substring(n*2, n*3));
    hw.sendMessage('eammreinf ' + ammoStr.substring(n*3, n*4));
    hw.sendMessage('eammstore');
}

// Get init health from scheme (index 28 = params[2])
function getInitHealth(scheme) {
    return scheme.params[2] || 100;
}

// Build CFG SCHEME array for server protocol (each value is a separate protocol line)
// Returns array: [flag1, flag2, ..., flag25, param26, ..., param43, !scriptparam]
function buildSchemeArray(scheme) {
    var parts = [];
    for (var i = 0; i < scheme.flags.length; i++) parts.push(scheme.flags[i] ? 'true' : 'false');
    for (var j = 0; j < scheme.params.length; j++) parts.push(String(scheme.params[j]));
    // Qt prepends '!' to scriptparam (last element) — server does B.tail to strip it
    parts.push('!' + (scheme.scriptparam || ''));
    return parts;
}

// Parse CFG SCHEME values (array of strings) back into a scheme object
function parseSchemeArray(arr) {
    var flags = [];
    for (var i = 0; i < 25 && i < arr.length; i++) flags.push(arr[i] === 'true' ? 1 : 0);
    var params = [];
    for (var j = 25; j < 43 && j < arr.length; j++) params.push(parseInt(arr[j]) || 0);
    var sp = (arr.length > 43 && arr[43]) ? arr[43].replace(/^!/, '') : null;
    return {name:'Custom', flags:flags, params:params, scriptparam:sp || null};
}

// Find scheme by name
function findScheme(name) {
    for (var i = 0; i < SCHEMES.length; i++) {
        if (SCHEMES[i].name === name) return SCHEMES[i];
    }
    return SCHEMES[0];
}

// Find weapon set by name
function findWeapon(name) {
    for (var i = 0; i < WEAPONS.length; i++) {
        if (WEAPONS[i].name === name) return WEAPONS[i];
    }
    return WEAPONS[0];
}

// Find style by name
function findStyle(name) {
    for (var i = 0; i < STYLES.length; i++) {
        if (STYLES[i].name === name) return STYLES[i];
    }
    return STYLES[0];
}

// Find theme by name
function findTheme(name) {
    for (var i = 0; i < THEMES.length; i++) {
        if (THEMES[i].name === name) return THEMES[i];
    }
    return THEMES[0];
}

return {
    FLAG_BITS: FLAG_BITS,
    SCHEME_PARAMS: SCHEME_PARAMS,
    SCHEMES: SCHEMES,
    WEAPONS: WEAPONS,
    THEMES: THEMES,
    STYLES: STYLES,
    QUICK_MAPS: QUICK_MAPS,
    TEAM_COLORS: TEAM_COLORS,
    TEAM_COLORS_DEC: TEAM_COLORS_DEC,
    computeGmflags: computeGmflags,
    sendSchemeIPC: sendSchemeIPC,
    sendAmmoIPC: sendAmmoIPC,
    getInitHealth: getInitHealth,
    buildSchemeArray: buildSchemeArray,
    parseSchemeArray: parseSchemeArray,
    findScheme: findScheme,
    findWeapon: findWeapon,
    findStyle: findStyle,
    findTheme: findTheme
};
})();

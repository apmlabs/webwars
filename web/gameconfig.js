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
    {name:'Default', flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0],
     params:[100,45,100,15,5,3,4,0,2,0,0,35,25,47,5,100,100,0], scriptparam:null},
    {name:'Pro Mode', flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0],
     params:[100,15,100,15,0,3,0,0,2,0,0,35,25,47,5,100,100,0], scriptparam:null},
    {name:'Shoppa', flags:[0,0,1,1,0,0,0,0,0,0,0,1,0,0,1,1,1,0,0,1,0,0,0,0,0],
     params:[100,30,100,50,1,0,0,0,0,0,0,0,25,0,0,100,100,0], scriptparam:null},
    {name:'Clean Slate', flags:[0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0],
     params:[100,45,100,15,5,3,4,0,2,0,0,35,25,47,5,100,100,0], scriptparam:null},
    {name:'Minefield', flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0],
     params:[100,30,50,15,0,0,200,0,0,0,0,35,25,47,5,100,100,0], scriptparam:null},
    {name:'Barrel Mayhem', flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0],
     params:[100,30,100,15,0,0,0,0,200,0,0,35,25,47,5,100,100,0], scriptparam:null},
    {name:'Tunnel Hogs', flags:[0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0],
     params:[100,30,100,15,5,3,10,10,10,4,0,35,25,47,5,100,100,0], scriptparam:null},
    {name:'Timeless', flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0],
     params:[100,9999,100,15,5,3,5,10,2,0,0,35,30,0,0,100,100,0], scriptparam:null},
    {name:'Thinking with Portals', flags:[0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0],
     params:[100,45,100,15,2,3,5,0,5,4,0,25,25,47,5,100,100,0], scriptparam:null},
    {name:'King Mode', flags:[0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0],
     params:[100,45,100,15,5,3,4,0,2,0,0,35,25,47,5,100,100,0], scriptparam:null},
    {name:'Mutant', flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0],
     params:[100,20,100,15,2,1,4,0,2,0,0,0,25,0,0,100,100,0], scriptparam:null},
    {name:'Construction Mode', flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,1,0,1,0,0,0,0],
     params:[100,45,100,15,5,3,0,0,0,0,0,35,25,47,5,100,100,0],
     scriptparam:'initialenergy=550, energyperround=50, maxenergy=1000, cratesperround=5'},
    {name:'The Specialists', flags:[1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,0,0],
     params:[100,45,100,15,5,3,0,0,0,0,0,100,25,47,5,100,100,0],
     scriptparam:'t=SENDXHPL'},
    {name:'Space Invasion', flags:[0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0],
     params:[100,45,100,50,0,3,0,0,0,0,0,0,25,0,0,100,100,0],
     scriptparam:'rounds=3, shield=30, barrels=5, pings=2, barrelbonus=3, shieldbonus=30, timebonus=4'},
    {name:'HedgeEditor', flags:[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0],
     params:[100,9999,100,50,0,3,0,0,0,0,0,35,25,0,0,100,100,0], scriptparam:null},
    {name:'Racer', flags:[0,0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,1,0,1,1,0,0,0,0,0],
     params:[100,90,100,50,0,0,0,0,0,0,0,0,25,0,0,100,100,0], scriptparam:null}
];

// ── 13 Weapon Presets ──
// Each ammo string = 4 × 60 chars: init + prob + delay + crate
var WEAPONS = [
    {name:'Default',
     ammo:'939192942219912103223511100120000000021110010101111100010001' +
          '040504054160065554655446477657666666615551010111541111111073' +
          '000000000000020550000004000700400000000022000000060002000000' +
          '131111031211111112311411111111111111121111111111111111111111'},
    {name:'Crazy',
     ammo:'999999999999999999299999999999999929999999999999999299919099' +
          '111111011111111111111111111111111111111111111111111111111011' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '131111031211111112311411111111111111121111111111111111111111'},
    {name:'Pro Mode',
     ammo:'909000900000000000000900000000000000000000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '000000000000020550000004000700400000000020000000000002000000' +
          '111111011111111111111111111111111111111111111111111111111111'},
    {name:'Shoppa',
     ammo:'000000990000000000000000000000000000000000000000000000000000' +
          '444441004424440221011212122242200000000200040001001100101010' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '111111011111111111111111111111111111111111111111111111111111'},
    {name:'Clean Slate',
     ammo:'101000900001000001100000000000000000000000000000100000000000' +
          '040504054160065554655446477657666666615551010111541112111040' +
          '000000000000000000000000000000000000000000000000000002000000' +
          '131111031211111112311411111111111111121111111111111111111111'},
    {name:'Minefield',
     ammo:'000000990009000000030000000000000000000000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '000000000000020550000004000700400000000020000000060002000000' +
          '111111011111111111111111111111111111111111111111111111111111'},
    {name:'Thinking with Portals',
     ammo:'900000900200000000210000000000000011000009000000000000000000' +
          '040504054160065554655446477657666666615551010111541112111020' +
          '000000000000020550000004000700400000000020000000060002000000' +
          '131111031211111112311411111111111111121111111111111111111111'},
    {name:'One of Everything',
     ammo:'111111911111111111111111111111111111111111111111111111111011' +
          '111111011111111111111111111111111111111111111111111111111011' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '111111011111111111111111111111111111111111111111111111111111'},
    {name:'Highlander',
     ammo:'111111911111111111110191111111111001011111011110010010111010' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000001'},
    {name:'Balanced Random Weapon',
     ammo:'333233923323323223232331311221130000032322030220222000203010' +
          '000000000000000000000000000000001111100000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '111111011111111111111111111111111111111111111111111111111111'},
    {name:'Construction Mode',
     ammo:'110001900000001001009000000000000000000000000000000000000000' +
          '111111011111111001000111111011111111111111011111001011101010' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '111111011111111111111111111111111111111111111111111111111111'},
    {name:'Shoppa Pro',
     ammo:'000000990000000000000000000000000000000000000000000000000000' +
          '444440004404440000000000000040000000000000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '111111011111111111111111111111111111111111111111111112111111'},
    {name:'HedgeEditor',
     ammo:'000000900000000000000000000000000000000000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '000000000000000000000000000000000000000000000000000000000000' +
          '111111011111111111111111111111111111111111111111111111111111'}
];

// ── 21 Game Styles (Lua scripts in Scripts/Multiplayer/) ──
var STYLES = [
    'Normal', 'Balanced Random Weapon', 'Battalion', 'Capture the Flag',
    'Construction Mode', 'Continental supplies', 'DiagonalMaze', 'Frenzy',
    'Gravity', 'HedgeEditor', 'Highlander', 'Mutant', 'No Jumping',
    'Racer', 'Random Weapon', 'ShoppaMap', 'Space Invasion', 'TechRacer',
    'The Specialists', 'Tumbler', 'Tunnels', 'WxW'
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

// Build CFG SCHEME string for server protocol (comma-separated: 25 bools + 18 params + scriptparam)
function buildSchemeString(scheme) {
    var parts = [];
    for (var i = 0; i < scheme.flags.length; i++) parts.push(scheme.flags[i] ? 'true' : 'false');
    for (var j = 0; j < scheme.params.length; j++) parts.push(String(scheme.params[j]));
    parts.push(scheme.scriptparam || '');
    return parts.join(',');
}

// Parse CFG SCHEME string back into a scheme object
function parseSchemeString(str) {
    var parts = str.split(',');
    var flags = [];
    for (var i = 0; i < 25 && i < parts.length; i++) flags.push(parts[i] === 'true' ? 1 : 0);
    var params = [];
    for (var j = 25; j < 43 && j < parts.length; j++) params.push(parseInt(parts[j]) || 0);
    var sp = parts.length > 43 ? parts.slice(43).join(',') : null;
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

return {
    FLAG_BITS: FLAG_BITS,
    SCHEME_PARAMS: SCHEME_PARAMS,
    SCHEMES: SCHEMES,
    WEAPONS: WEAPONS,
    STYLES: STYLES,
    QUICK_MAPS: QUICK_MAPS,
    TEAM_COLORS: TEAM_COLORS,
    TEAM_COLORS_DEC: TEAM_COLORS_DEC,
    computeGmflags: computeGmflags,
    sendSchemeIPC: sendSchemeIPC,
    sendAmmoIPC: sendAmmoIPC,
    getInitHealth: getInitHealth,
    buildSchemeString: buildSchemeString,
    parseSchemeString: parseSchemeString,
    findScheme: findScheme,
    findWeapon: findWeapon
};
})();

let hsModePins = {
    PICO: {
        SPIA: {pins:["GPIO58"]},
        SPIB: {pins:["GPIO63"]},
        SPIC: {pins:["GPIO69"]},
        SPID: {pins:["GPIO91"]},
        SPIE: {pins:["GPIO8"]},
    },
    POCI: {
        SPIA: {pins:["GPIO59"]},
        SPIB: {pins:["GPIO64"]},
        SPIC: {pins:["GPIO70"]},
        SPID: {pins:["GPIO92"]},
        SPIE: {pins:["GPIO9"]},
    },
    CLK: {
        SPIA: {pins:["GPIO60"]},
        SPIB: {pins:["GPIO65"]},
        SPIC: {pins:["GPIO71"]},
        SPID: {pins:["GPIO93"]},
        SPIE: {pins:["GPIO12"]},
    },
    PTE: {
        SPIA: {pins:["GPIO61"]},
        SPIB: {pins:["GPIO66"]},
        SPIC: {pins:["GPIO72"]},
        SPID: {pins:["GPIO94"]},
        SPIE: {pins:["GPIO11"]},
    }
}

module.exports = {
	hsModePins: hsModePins,
}
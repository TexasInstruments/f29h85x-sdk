let fastPlusModePins = {
    SDA: {
        PMBUSA: {pins: ["GPIO13", "GPIO22", "GPIO25", "GPIO29"]},
    },
    SCL: {
        PMBUSA: {pins: ["GPIO10", "GPIO14", "GPIO23"]},
    },
    ALERT: {
        PMBUSA: {pins: ["GPIO11", "GPIO18", "GPIO19"]},
    },
    CTL: {
        PMBUSA: {pins: ["GPIO12", "GPIO15", "GPIO26"]},
    },
}

module.exports = {
    fastPlusModePins: fastPlusModePins,
}
/* Stucture for ADC Internal Connections with VREFLO*/
// TODO: Verify if need to add individual package support
let ADC_internalSignals = {
    F29H85x: {
        A8: "VREFLOA",
        A9: "VREFLOA",
        A13: "TempSensor",
        B8: "VREFLOB",
        B9: "VREFLOB",
        C8: "VREFLOC",
        C9: "VREFLOC",
    }
}

exports = {
    ADC_internalSignals: ADC_internalSignals,
}

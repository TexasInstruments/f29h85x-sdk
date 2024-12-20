/* Stucture for comparator input signals per device and CMPSS Instance*/
let CMPSS_comparatorInputSignals = {
    F29H85x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A4"},
            {name: "1", displayName: "A2"},
            {name: "2", displayName: "A3"},
            {name: "3", displayName: "B3"},
            {name: "4", displayName: "D6"},
            {name: "5", displayName: "A12"},
            {name: "6", displayName: "B0/VDAC"},
        ],
        CMPSS2_BASE: [
            {name: "0", displayName: "A6"},
            {name: "1", displayName: "E8"},
            {name: "2", displayName: "E9"},
            {name: "3", displayName: "D13"},
            {name: "4", displayName: "D7"},
            {name: "5", displayName: "A13"},
            {name: "6", displayName: "B2"},
        ],
        CMPSS3_BASE: [
            {name: "0", displayName: "B2"},
            {name: "1", displayName: "B0/VDAC"},
            {name: "2", displayName: "B1/DACC_OUT"},
            {name: "3", displayName: "TempSensor"}, // NOT FOUND IN THE FILE
            {name: "4", displayName: "E2"},
            {name: "5", displayName: "A14/B14/C14/D14/E14"},
            {name: "6", displayName: "D1"},
        ],
        CMPSS4_BASE: [
            {name: "0", displayName: "A0/DACA_OUT"},
            {name: "1", displayName: "D5"},
            {name: "2", displayName: "D0"},
            {name: "3", displayName: "D2"},
            {name: "4", displayName: "E3"},
            {name: "5", displayName: "A15/B15/C15/D15/E15"},
            {name: "6", displayName: "B8"},
        ],
        CMPSS5_BASE: [
            {name: "0", displayName: "D12"},
            {name: "1", displayName: "E6"},
            {name: "2", displayName: "E7"},
            {name: "3", displayName: "TempSensor"}, // NOT FOUND IN THE FILE
            {name: "4", displayName: "A8"},
            {name: "5", displayName: "C7"},
            {name: "6", displayName: "C0"},
        ],
        CMPSS6_BASE: [
            {name: "0", displayName: "D8"},
            {name: "1", displayName: "E17"},
            {name: "2", displayName: "E16"},
            {name: "3", displayName: "0.9*VREFHIAB"}, // NOT FOUND IN THE FILE
            {name: "4", displayName: "A9"},
            {name: "5", displayName: "C8"},//
            {name: "6", displayName: "E0"},
        ],
        CMPSS7_BASE: [
            {name: "0", displayName: "D1"},
            {name: "1", displayName: "B4"},
            {name: "2", displayName: "B5"},
            {name: "3", displayName: "0.9*VREFHICDE"}, // NOT FOUND IN THE FILE
            {name: "4", displayName: "A10"},
            {name: "5", displayName: "C9"},//
            {name: "6", displayName: "A1"},
        ],
        CMPSS8_BASE: [
            {name: "0", displayName: "D3"},
            {name: "1", displayName: "E4"},
            {name: "2", displayName: "E5"},
            {name: "3", displayName: "A8"}, // FOUND IN THE FILE (0.9*VREFHIC)
            {name: "4", displayName: "A11"},
            {name: "5", displayName: "C10"},
            {name: "6", displayName: "B9"},
        ],
        CMPSS9_BASE: [
            {name: "0", displayName: "C1"},
            {name: "1", displayName: "C2"},
            {name: "2", displayName: "A7"},
            {name: "3", displayName: "C9"}, 
            {name: "4", displayName: "B6"},
            {name: "5", displayName: "B16"},
            {name: "6", displayName: "A0/DACA_OUT"},
        ],
        CMPSS10_BASE: [
            {name: "0", displayName: "C0"},
            {name: "1", displayName: "E10"},
            {name: "2", displayName: "E12"},
            {name: "3", displayName: "D3"}, 
            {name: "4", displayName: "B7"},
            {name: "5", displayName: "B17"},
            {name: "6", displayName: "D0"},
        ],
        CMPSS11_BASE: [
            {name: "0", displayName: "C1"},
            {name: "1", displayName: "E11"},
            {name: "2", displayName: "E13"},
            {name: "3", displayName: "E1"}, 
            {name: "4", displayName: "B8"},
            {name: "5", displayName: "C11"},
            {name: "6", displayName: "A14/B14/C14/D14/E14"},
        ],
        CMPSS12_BASE: [
            {name: "0", displayName: "C8"},
            {name: "1", displayName: "E1"},
            {name: "2", displayName: "E13"}, // NOT FOUND IN THE FILE
            {name: "3", displayName: "E1"},  // NOT FOUND IN THE FILE
            {name: "4", displayName: "B9"},
            {name: "5", displayName: "C12"},
            {name: "6", displayName: "A15/B15/C15/D15/E15"},
        ],
    },
}

/* Stucture for comparator negative input signals per device & CMPSS Instance*/
let CMPSS_comparatorNegInputSignals = {
    F29H85x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A5"},
            {name: "1", displayName: "A3"},
        ],
        CMPSS2_BASE: [
            {name: "0", displayName: "A7"},
            {name: "1", displayName: "A4"},
        ],
        CMPSS3_BASE: [
            {name: "0", displayName: "B3"},
            {name: "1", displayName: "B5"},
        ],
        CMPSS4_BASE: [
            {name: "0", displayName: "A1"},
            {name: "1", displayName: "D5"},
        ],
        CMPSS5_BASE: [
            {name: "0", displayName: "D13"},
            {name: "1", displayName: "E6"},
        ],
        CMPSS6_BASE: [
            {name: "0", displayName: "D9"},
            {name: "1", displayName: "E17"},
        ],
        CMPSS7_BASE: [
            {name: "0", displayName: "D2"},
            {name: "1", displayName: "B4"},
        ],
        CMPSS8_BASE: [
            {name: "0", displayName: "D4"},
            {name: "1", displayName: "E4"},
        ],
        CMPSS9_BASE: [
            {name: "0", displayName: "A2"},
            {name: "1", displayName: "E9"},
        ],
        CMPSS10_BASE: [
            {name: "0", displayName: "E8"},
            {name: "1", displayName: "D12"},
        ],
        CMPSS11_BASE: [
            {name: "0", displayName: "B6"},
            {name: "1", displayName: "C2"},
        ],
        CMPSS12_BASE: [
            {name: "0", displayName: "A6"},
            {name: "1", displayName: "B1/DACC_OUT"},
        ],
    },

}

/* Stucture for comparator low positive input signals per device & CMPSS Instance (currently only for F28P65x)*/
let CMPSS_comparatorLowPositiveInputSignals = {
    F29H85x: {
            CMPSS1_BASE: [
                {name: "0", displayName: "A4"},
                {name: "1", displayName: "A2"},
                {name: "2", displayName: "A3"},
                {name: "3", displayName: "B3"},
                {name: "4", displayName: "D6"},
                {name: "5", displayName: "A12"},
                {name: "6", displayName: "B0/VDAC"},
            ],
            CMPSS2_BASE: [
                {name: "0", displayName: "A6"},
                {name: "1", displayName: "E8"},
                {name: "2", displayName: "E9"},
                {name: "3", displayName: "D13"},
                {name: "4", displayName: "D7"},
                {name: "5", displayName: "A13"},
                {name: "6", displayName: "B2"},
            ],
            CMPSS3_BASE: [
                {name: "0", displayName: "B2"},
                {name: "1", displayName: "B0/VDAC"},
                {name: "2", displayName: "B1/DACC_OUT"},
                {name: "3", displayName: "D9"}, 
                {name: "4", displayName: "E2"},
                {name: "5", displayName: "A14/B14/C14/D14/E14"},
                {name: "6", displayName: "D1"},
            ],
            CMPSS4_BASE: [
                {name: "0", displayName: "A0/DACA_OUT"},
                {name: "1", displayName: "D5"},
                {name: "2", displayName: "D0"},
                {name: "3", displayName: "D2"},
                {name: "4", displayName: "E3"},
                {name: "5", displayName: "A15/B15/C15/D15/E15"},
                {name: "6", displayName: "B8"},
            ],
            CMPSS5_BASE: [
                {name: "0", displayName: "D12"},
                {name: "1", displayName: "E6"},
                {name: "2", displayName: "E7"},
                {name: "3", displayName: "D4"}, 
                {name: "4", displayName: "B10"},
                {name: "5", displayName: "C13"},
                {name: "6", displayName: "C0"},
            ],
            CMPSS6_BASE: [
                {name: "0", displayName: "D8"},
                {name: "1", displayName: "E17"},
                {name: "2", displayName: "E16"},
                {name: "3", displayName: "0.9*VREFHIAB"}, // NOT FOUND IN THE FILE
                {name: "4", displayName: "B11"},
                {name: "5", displayName: "C16"},
                {name: "6", displayName: "E0"},
            ],
            CMPSS7_BASE: [
                {name: "0", displayName: "D1"},
                {name: "1", displayName: "B4"},
                {name: "2", displayName: "B5"},
                {name: "3", displayName: "0.9*VREFHICDE"}, // NOT FOUND IN THE FILE
                {name: "4", displayName: "B12"},
                {name: "5", displayName: "C17"},
                {name: "6", displayName: "A1"},
            ],
            CMPSS8_BASE: [
                {name: "0", displayName: "D3"},
                {name: "1", displayName: "E4"},
                {name: "2", displayName: "E5"},
                {name: "3", displayName: "A8"}, // FOUND IN THE FILE (0.9*VREFHIC)
                {name: "4", displayName: "B13"},
                {name: "5", displayName: "D10"},
                {name: "6", displayName: "B9"},
            ],
            CMPSS9_BASE: [
                {name: "0", displayName: "C1"},
                {name: "1", displayName: "C2"},
                {name: "2", displayName: "A7"},
                {name: "3", displayName: "C9"}, 
                {name: "4", displayName: "C3"},
                {name: "5", displayName: "D11"},
                {name: "6", displayName: "A0/DACA_OUT"},
            ],
            CMPSS10_BASE: [
                {name: "0", displayName: "C0"},
                {name: "1", displayName: "E10"},
                {name: "2", displayName: "E12"},
                {name: "3", displayName: "D3"}, 
                {name: "4", displayName: "C4"},
                {name: "5", displayName: "D16"},
                {name: "6", displayName: "D0"},
            ],
            CMPSS11_BASE: [
                {name: "0", displayName: "C1"},
                {name: "1", displayName: "E11"},
                {name: "2", displayName: "E13"},
                {name: "3", displayName: "E1"}, 
                {name: "4", displayName: "C4"},
                {name: "5", displayName: "D17"},
                {name: "6", displayName: "A14/B14/C14/D14/E14"},
            ],
            CMPSS12_BASE: [
                {name: "0", displayName: "C8"},
                {name: "1", displayName: "E1"},
                {name: "2", displayName: "E13"}, // NOT FOUND IN THE FILE
                {name: "3", displayName: "E1"},  // NOT FOUND IN THE FILE
                {name: "4", displayName: "C6"},
                {name: "5", displayName: "E0"},
                {name: "6", displayName: "A15/B15/C15/D15/E15"},
            ],
        },
}

exports = {
    CMPSS_comparatorInputSignals: CMPSS_comparatorInputSignals,
    CMPSS_comparatorNegInputSignals: CMPSS_comparatorNegInputSignals,
    CMPSS_comparatorLowPositiveInputSignals: CMPSS_comparatorLowPositiveInputSignals,
}

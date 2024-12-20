// Source data will change based on total available flash in device

let flash_code_sets = [
    {
        name: "flc1set1",
        size: 1024
    },
    {
        name: "flc1set2",
        size: 1024
    },
    {
        name: "flc2set1",
        size: 1024
    },
    {
        name: "flc2set2",
        size: 1024
    },
]

let flash_data_sets = [
    {
        name: "flc3setDATA1",   // Actually comes under FLC1, naming only for programming simplicity
        size: 256
    },
]
exports = {
    flash_code_sets,
    flash_data_sets
};






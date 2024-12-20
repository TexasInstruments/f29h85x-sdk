const memTypes = [
    {name: "RAM"},
    {name: "Flash"},
    //{name: "ExtMemory"},
]

let ram_memories = [];
[
    "LDA7.0", "LDA7.1", "LDA7.2", "LDA7.3",
    "LDA6.0", "LDA6.1", "LDA6.2", "LDA6.3",
    "LDA5.0", "LDA5.1", "LDA5.2", "LDA5.3",
    "LDA4.0", "LDA4.1", "LDA4.2", "LDA4.3",
    "LDA3.0", "LDA3.1", "LDA3.2", "LDA3.3",
    "LDA2.0", "LDA2.1", "LDA2.2", "LDA2.3",
    "LDA1.0", "LDA1.1", "LDA1.2", "LDA1.3",
    "LDA0.0", "LDA0.1", "LDA0.2", "LDA0.3",
    "LPA0.0", "LPA0.1", "LPA0.2", "LPA0.3", "LPA0.4", "LPA0.5", "LPA0.6", "LPA0.7",
    "LPA1.0", "LPA1.1", "LPA1.2", "LPA1.3", "LPA1.4", "LPA1.5", "LPA1.6", "LPA1.7",
    "CPA0.0", "CPA0.1", "CPA0.2", "CPA0.3", "CPA0.4", "CPA0.5", "CPA0.6", "CPA0.7",
    "CPA1.0", "CPA1.1", "CPA1.2", "CPA1.3", "CPA1.4", "CPA1.5", "CPA1.6", "CPA1.7",
    "CDA0.0", "CDA0.1", "CDA0.2", "CDA0.3",
    "CDA1.0", "CDA1.1", "CDA1.2", "CDA1.3",
    "CDA2.0", "CDA2.1", "CDA2.2", "CDA2.3",
    "CDA3.0", "CDA3.1", "CDA3.2", "CDA3.3",
    "CDA4.0", "CDA4.1", "CDA4.2", "CDA4.3",
    "CDA5.0", "CDA5.1", "CDA5.2", "CDA5.3",
    "CDA6.0", "CDA6.1", "CDA6.2", "CDA6.3",
    "CDA7.0", "CDA7.1", "CDA7.2", "CDA7.3",
    "CDA8.0", "CDA8.1", "CDA8.2", "CDA8.3",
    "CDA9.0", "CDA9.1", "CDA9.2", "CDA9.3",
    "CDA10.0", "CDA10.1", "CDA10.2", "CDA10.3",
    "CDA11.0", "CDA11.1", "CDA11.2", "CDA11.3"
].forEach((x, i) => {
    ram_memories.push({ name  : x,
                        used  : 0,
                        unitIndex: i,
                        start : 0x200E0000 +  i*0x1000,
                        size  : 0x1000,
                        end   : 0x200E1000 +  i*0x1000})
})

const ram_mem = ram_memories

const ramPlacementPreference = {
    CPU1 : {
        "Code": [{region:"LPA", order: "U"}, {region:"CPA", order: "D"}],
        "Data": [{region:"CDA", order: "U"}, {region:"LDA", order: "D"}]
    },
    CPU2: {
        "Code": [{region:"LPA", order: "D"}, {region:"LDA", order: "U"}],
        "Data": [{region:"LDA", order: "U"}]
    },
    CPU3: {
        "Code": [{region:"CPA", order: "U"}, {region:"CDA", order: "D"}],
        "Data": [{region:"CDA", order: "D"}]
    }
}

const ramInaccessibleRegions = {
    "TMS320F29H859TU8" : {
        
    }
}

const flashMemories = {
    flash_code_sets:    [
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
    ],
    flash_data_sets:    [
        {
            name: "flc3setDATA1",   // Actually comes under FLC1, naming only for programming simplicity
            size: 256
        },
    ]
}

exports = {
    memTypes,
    //ramMemories,
    ram_mem,
    flashMemories,
    ramPlacementPreference
}
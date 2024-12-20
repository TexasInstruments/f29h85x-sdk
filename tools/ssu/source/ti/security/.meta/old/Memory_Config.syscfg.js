const Common = system.getScript('/ti/security/Common.js');
const APR = system.getScript('/ti/security/APR.syscfg.js');
let c29x     = system.getScript('/ti/security/c29x_device.js');

let LPA_List = [0,1,2]
let LDA_List = [0,1,2,3,4,5,6,7,8]
let CPA_List = [0,1,2]
let CDA_List = [0,1,2,3,4,5,6,7,8,9,10,11,12]
let LPA_CPA_List = [0,1,2,3,4]
let LDA_CDA_List = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]

let LPA_Max = 2
let LDA_Max = 8
let CPA_Max = 2
let CDA_Max = 12
let LPA_CPA_Max = 4
let LDA_CDA_Max = 20
function updateCPU1Mem(inst)
{
    inst.CPU1RAMCode = LPA_CPA_Max  - inst.CPU2RAMCode - inst.CPU3RAMCode
    inst.CPU1RAMData = LDA_CDA_Max - inst.CPU2RAMData - inst.CPU3RAMData

    if((inst.CPU2LPRAM + inst.CPU3LPRAM) <= LPA_Max)
        inst.CPU1LPRAM = LPA_Max  - inst.CPU2LPRAM - inst.CPU3LPRAM
    if((inst.CPU2LDRAM + inst.CPU3LDRAM) <= LDA_Max)
        inst.CPU1LDRAM = LDA_Max  - inst.CPU2LDRAM - inst.CPU3LDRAM
    if((inst.CPU2CPRAM + inst.CPU3CPRAM) <= CPA_Max)
        inst.CPU1CPRAM = CPA_Max  - inst.CPU2CPRAM - inst.CPU3CPRAM
    if((inst.CPU2CDRAM + inst.CPU3CDRAM) <= CDA_Max)
        inst.CPU1CDRAM = CDA_Max  - inst.CPU2CDRAM - inst.CPU3CDRAM
}

let CPUs =  [{name:"CPU1"}, {name:"CPU2"}, {name:"CPU3"}];

let RAMs = [
    {name: "LDA7",  displayName : "LDA7  (16 KB, Optimized for CPU1 and CPU2 Data)"},
    {name: "LDA6",  displayName : "LDA6  (16 KB, Optimized for CPU1 and CPU2 Data)"},
    {name: "LDA5",  displayName : "LDA5  (16 KB, Optimized for CPU1 and CPU2 Data)"},
    {name: "LDA4",  displayName : "LDA4  (16 KB, Optimized for CPU1 and CPU2 Data)"},
    {name: "LDA3",  displayName : "LDA3  (16 KB, Optimized for CPU1 and CPU2 Data)"},
    {name: "LDA2",  displayName : "LDA2  (16 KB, Optimized for CPU1 and CPU2 Data)"},
    {name: "LDA1",  displayName : "LDA1  (16 KB, Optimized for CPU1 and CPU2 Data)"},
    {name: "LDA0",  displayName : "LDA0  (16 KB, Optimized for CPU1 and CPU2 Data)"},
    {name: "LPA0",  displayName : "LPA0  (32 KB, Optimized for CPU1 and CPU2 Code)"},
    {name: "LPA1",  displayName : "LPA1  (32 KB, Optimized for CPU1 and CPU2 Code)"},
    {name: "CPA0",  displayName : "CPA0  (32 KB, Optimized for CPU1 and CPU3 Code)"},
    {name: "CPA1",  displayName : "CPA1  (32 KB, Optimized for CPU1 and CPU3 Code)"},
    {name: "CDA0",  displayName : "CDA0  (16 KB, Optimized for CPU1 and CPU3 Data)"},
    {name: "CDA1",  displayName : "CDA1  (16 KB, Optimized for CPU1 and CPU3 Data)"},
    {name: "CDA2",  displayName : "CDA2  (16 KB, Optimized for CPU1 and CPU3 Data)"},
    {name: "CDA3",  displayName : "CDA3  (16 KB, Optimized for CPU1 and CPU3 Data)"},
    {name: "CDA4",  displayName : "CDA4  (16 KB, Optimized for CPU1 and CPU3 Data)"},
    {name: "CDA5",  displayName : "CDA5  (16 KB, Optimized for CPU1 and CPU3 Data)"},
    {name: "CDA6",  displayName : "CDA6  (16 KB, Optimized for CPU1 and CPU3 Data)"},
    {name: "CDA7",  displayName : "CDA7  (16 KB, Optimized for CPU1 and CPU3 Data)"},
    {name: "CDA8",  displayName : "CDA8  (16 KB, Optimized for CPU1 and CPU3 Data)"},
    {name: "CDA9",  displayName : "CDA9  (16 KB, Optimized for CPU1 and CPU3 Data)"},
    {name: "CDA10", displayName : "CDA10 (16 KB, Optimized for CPU1 and CPU3 Data)"},
    {name: "CDA11", displayName : "CDA11 (16 KB, Optimized for CPU1 and CPU3 Data)"},
]


let config = [
    {
        name       : "bankmode",
        displayName: "Bank Mode",
        default    : 0,
        options    : [
            {name : 0, displayName : "MODE0 : All CPU1, no FOTA"},
            {name : 1, displayName : "MODE1 : All CPU1, FOTA enabled"},
            {name : 2, displayName : "MODE2 : CPU1/CPU3 split, no FOTA"},
            {name : 3, displayName : "MODE3 : CPU1/CPU3 split, FOTA enabled"}
        ],
        onChange   : (inst) => {
            if(inst.bankmode == 0) {
                inst.CPU1Flash = 4
                inst.CPU3Flash = 0
            }
            if(inst.bankmode == 1) {
                inst.CPU1Flash = 2
                inst.CPU3Flash = 0
            }
            if(inst.bankmode == 2) {
                inst.CPU1Flash = 2
                inst.CPU3Flash = 2
            }
            if(inst.bankmode == 3) {
                inst.CPU1Flash = 1
                inst.CPU3Flash = 1
            }
        }
    },
    {
        name       : "advanced",
        displayName: "Advanced configuration",
        default    : false,
        onChange   : (inst, ui) => {
            // RAMs.forEach(ram=> {
            //     ui[ram.name].hidden = !inst.advanced
            // })
            ui.CPU1RAMCode.hidden = inst.advanced
            ui.CPU1RAMData.hidden = inst.advanced
            ui.CPU2RAMCode.hidden = inst.advanced
            ui.CPU2RAMData.hidden = inst.advanced
            ui.CPU3RAMCode.hidden = inst.advanced
            ui.CPU3RAMData.hidden = inst.advanced

            ui.CPU1LPRAM.hidden = !inst.advanced
            ui.CPU1LDRAM.hidden = !inst.advanced
            ui.CPU1CDRAM.hidden = !inst.advanced
            ui.CPU1CPRAM.hidden = !inst.advanced
            ui.CPU2LPRAM.hidden = !inst.advanced
            ui.CPU2LDRAM.hidden = !inst.advanced
            ui.CPU2CDRAM.hidden = !inst.advanced
            ui.CPU2CPRAM.hidden = !inst.advanced
            ui.CPU3LPRAM.hidden = !inst.advanced
            ui.CPU3LDRAM.hidden = !inst.advanced
            ui.CPU3CDRAM.hidden = !inst.advanced
            ui.CPU3CPRAM.hidden = !inst.advanced

            APR.ramMemSelect.hidden = !inst.advanced
        }
    },
    // {
    //     name       : "advancedConfig",
    //     displayName: "Advanced configuration",
    //     collapsed  : false,
    //     config     : RAMs.map (x=> {return {name : x.name, displayName : x.displayName, options : CPUs, default : "CPU1", hidden : true}})
    // },
    {
        name       : "CPU1Mem",
        displayName: "CPU1 Memory Configuration",
        collapsed  : false,
        config     : [
            {
                name       : "CPU1RAMCode",
                displayName: "RAM size for CPU1 Code",
                default    : LPA_CPA_Max,
                options    : LPA_CPA_List.map(x => {return {name:x, displayName:(x*32).toString()+"KB"}}),
                readOnly   : true
            },
            {
                name       : "CPU1RAMData",
                displayName: "RAM size for CPU1 Data",
                default    : LDA_CDA_Max,
                options    : LDA_CDA_List.map(x => {return {name:x, displayName:(x*16).toString()+"KB"}}),
                readOnly   : true
            },
            {
                name       : "CPU1LPRAM",
                displayName: "LP RAM size for CPU1 (Fetch:0WS, Data:1WS)",
                default    : LPA_Max,
                options    : LPA_List.map(x => {return {name:x, displayName:(x*32).toString()+"KB"}}),
                readOnly   : true,
                hidden     : true
            },
            {
                name       : "CPU1LDRAM",
                displayName: "LD RAM size for CPU1 (Fetch:1WS, Data:0WS)",
                default    : LDA_Max,
                options    : LDA_List.map(x => {return {name:x, displayName:(x*32).toString()+"KB"}}),
                readOnly   : true,
                hidden     : true
            },
            {
                name       : "CPU1CPRAM",
                displayName: "CP RAM size for CPU1 (Fetch:0WS, Data:1WS)",
                default    : CPA_Max,
                options    : CPA_List.map(x => {return {name:x, displayName:(x*32).toString()+"KB"}}),
                readOnly   : true,
                hidden     : true
            },
            {
                name       : "CPU1CDRAM",
                displayName: "CD RAM size for CPU1 (Fetch:1WS, Data:0WS)",
                default    : CDA_Max,
                options    : CDA_List.map(x => {return {name:x, displayName:(x*32).toString()+"KB"}}),
                readOnly   : true,
                hidden     : true
            },
            {
                name       : "CPU1Flash",
                displayName: "Flash size for CPU1",
                default    : 4,
                options    : [1,2,4].map(x => {return {name:x, displayName:(x).toString()+"MB"}}),
                readOnly   : true
            }
        ]
    },
    {
        name       : "CPU2Mem",
        displayName: "CPU2 Memory Configuration",
        collapsed  : false,
        config     : [
            {
                name       : "CPU2RAMCode",
                displayName: "RAM size for CPU2 Code",
                default    : 0,
                options    : LPA_List.map(x => {return {name:x, displayName:(x*32).toString()+"KB"}}),
                onChange   : (inst)=>updateCPU1Mem(inst)
            },
            {
                name       : "CPU2RAMData",
                displayName: "RAM size for CPU2 Data",
                default    : 0,
                options    : LDA_List.map(x => {return {name:x, displayName:(x*16).toString()+"KB"}}),
                onChange   : (inst)=>updateCPU1Mem(inst)
            },
            {
                name       : "CPU2LPRAM",
                displayName: "LP RAM size for CPU2 (Fetch:0WS, Data:1WS)",
                default    : 0,
                options    : LPA_List.map(x => {return {name:x, displayName:(x*32).toString()+"KB"}}),
                onChange   : (inst)=>updateCPU1Mem(inst),
                hidden     : true
            },
            {
                name       : "CPU2LDRAM",
                displayName: "LD RAM size for CPU2 (Fetch:1WS, Data:0WS)",
                default    : 0,
                options    : LDA_List.map(x => {return {name:x, displayName:(x*32).toString()+"KB"}}),
                onChange   : (inst)=>updateCPU1Mem(inst),
                hidden     : true
            },
            {
                name       : "CPU2CPRAM",
                displayName: "CP RAM size for CPU2 (Fetch:X, Data:3WS)",
                default    : 0,
                options    : CPA_List.map(x => {return {name:x, displayName:(x*32).toString()+"KB"}}),
                onChange   : (inst)=>updateCPU1Mem(inst),
                hidden     : true
            },
            {
                name       : "CPU2CDRAM",
                displayName: "CD RAM size for CPU2 (Fetch:X, Data:3WS)",
                default    : 0,
                options    : CDA_List.map(x => {return {name:x, displayName:(x*32).toString()+"KB"}}),
                onChange   : (inst)=>updateCPU1Mem(inst),
                hidden     : true
            },
                        {
                name       : "CPU2Flash",
                displayName: "Flash size for CPU2",
                default    : 0,
                options    : [0].map(x => {return {name:x, displayName:(x).toString()+"MB"}}),
                readOnly   : true
            }
        ]
    },
    {
        name       : "CPU3Mem",
        displayName: "CPU3 Memory Configuration",
        collapsed  : false,
        config     : [
            {
                name       : "CPU3RAMCode",
                displayName: "RAM size for CPU3 Code",
                default    : 0,
                options    : CPA_List.map(x => {return {name:x, displayName:(x*32).toString()+"KB"}}),
                onChange   : (inst)=>updateCPU1Mem(inst)
            },
            {
                name       : "CPU3RAMData",
                displayName: "RAM size for CPU3 Data",
                default    : 0,
                options    : CDA_List.map(x => {return {name:x, displayName:(x*16).toString()+"KB"}}),
                onChange   : (inst)=>updateCPU1Mem(inst)
            },
            {
                name       : "CPU3LPRAM",
                displayName: "LP RAM size for CPU3 (Fetch:X, Data:3WS)",
                default    : 0,
                options    : LPA_List.map(x => {return {name:x, displayName:(x*32).toString()+"KB"}}),
                onChange   : (inst)=>updateCPU1Mem(inst),
                hidden     : true
            },
            {
                name       : "CPU3LDRAM",
                displayName: "LD RAM size for CPU3 (Fetch:X, Data:3WS)",
                default    : 0,
                options    : LDA_List.map(x => {return {name:x, displayName:(x*32).toString()+"KB"}}),
                onChange   : (inst)=>updateCPU1Mem(inst),
                hidden     : true
            },
            {
                name       : "CPU3CPRAM",
                displayName: "CP RAM size for CPU3 (Fetch:0WS, Data:1WS)",
                default    : 0,
                options    : CPA_List.map(x => {return {name:x, displayName:(x*32).toString()+"KB"}}),
                onChange   : (inst)=>updateCPU1Mem(inst),
                hidden     : true
            },
            {
                name       : "CPU3CDRAM",
                displayName: "CD RAM size for CPU3 (Fetch:1WS, Data:0WS)",
                default    : 0,
                options    : CDA_List.map(x => {return {name:x, displayName:(x*32).toString()+"KB"}}),
                onChange   : (inst)=>updateCPU1Mem(inst),
                hidden     : true
            },
            {
                name       : "CPU3Flash",
                displayName: "Flash size for CPU3",
                default    : 0,
                options    : [0,1,2].map(x => {return {name:x, displayName:(x).toString()+"MB"}}),
                onChange   : (inst)=>updateCPU1Mem(inst),
                readOnly   : true
            }
        ]
    },
    {
        name            : "flashMem",
        displayName     : "Flash Memory Configuration",
        longDescription : "Allocate Flash memory used for sections Loaded to Flash and run from RAM.\n - Sections from CPU1 and CPU2 applications are loaded to CPU1 Flash.\n - Sections from CPU3 application are loaded to CPU1 or CPU3 Flash based on Bank mode settings.  ",
        collapsed       : false,
        config          : [

            {
                name          : "FlashCPU1Load",
                displayName   : "Size for CPU1 Load sections",
                description   : "This section will be part of CPU1 Flash",
                default       : 0x1000,
                displayFormat : "hex"
            },
            {
                name          : "FlashCPU2Load",
                displayName   : "Size for CPU2 Load sections",
                description   : "This section will be part of CPU1 Flash",
                default       : 0,
                displayFormat : "hex"
            },
            {
                name          : "FlashCPU3Load",
                displayName   : "Size for CPU3 Load sections",
                description   : "This section will be part of CPU1 Flash in bank modes 0 and 1, or CPU3 Flash in bank modes 2 and 3",
                default       : 0,
                displayFormat : "hex"
            },
        ]
    },
];

function validate(inst, vo)
{
    if((inst.bankmode == 0) || (inst.bankmode == 1))
    {
        if(((inst.FlashCPU1Load + inst.FlashCPU2Load + inst.FlashCPU3Load) & 0xFFF) != 0)
            vo.logError("Total size allocated for CPU1, CPU2 and CPU3 should be a multiple of 0x1000", inst, 'FlashCPU1Load');
    }
    else
    {
        if(((inst.FlashCPU1Load + inst.FlashCPU2Load) & 0xFFF) !=0)
            vo.logError("Total size allocated for CPU1 and CPU2 should be a multiple of 0x1000", inst, 'FlashCPU1Load');
        if((inst.FlashCPU3Load & 0xFFF) !=0)
            vo.logError("Size should be multiple of 0x1000", inst, 'FlashCPU3Load');

    }
    if((inst.CPU2LPRAM + inst.CPU3LPRAM) > LPA_Max)
    {
        vo.logError("Total size of LPA RAM exceeded", inst, 'CPU2LPRAM',);
        vo.logError("Total size of LPA RAM exceeded", inst, 'CPU3LPRAM',);
    }
    if((inst.CPU2LDRAM + inst.CPU3LDRAM) > LDA_Max)
    {
        vo.logError("Total size of LDA RAM exceeded", inst, 'CPU2LDRAM');
        vo.logError("Total size of LDA RAM exceeded", inst, 'CPU3LDRAM');
    }
    if((inst.CPU2CPRAM + inst.CPU3CPRAM) > CPA_Max)
    {
        vo.logError("Total size of CPA RAM exceeded", inst, 'CPU2CPRAM');
        vo.logError("Total size of CPA RAM exceeded", inst, 'CPU3CPRAM');
    }
    if((inst.CPU2CDRAM + inst.CPU3CDRAM) > CDA_Max)
    {
        vo.logError("Total size of CDA RAM exceeded", inst, 'CPU2CDRAM');
        vo.logError("Total size of CDA RAM exceeded", inst, 'CPU3CDRAM');
    }
}

exports = {
    displayName  : 'Memory Configuration',
    moduleStatic : {
        validate,
        config,

    }
};
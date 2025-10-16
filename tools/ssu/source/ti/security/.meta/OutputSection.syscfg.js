const Common            = system.getScript('/ti/security/Common.js');
const currentContext    = system.context;

let config =
[
    {
        name            : "$name",
        hidden          : false,
        isCIdentifier   : false
    },
    {
        name        : "sectionMemory",
        displayName : "Load Memory",
        default     : "None",
        options     : () => 
        {
            let list = Common.allocateAllMemoryRegions()[currentContext]
            if(list)
            {
                return  list
                        .map(x => { return { name: x.name } })
                        .concat({ name: "None" })
            }
            return []
        },
    },
    {
        name            : "sectionRunFromDifferentAddr",
        displayName     : "Run From Different Address",
        longDescription : "- If this option is selected, then the Output Section will be loaded to the region specified in 'Load Memory', and run from the region specified in 'Run Memory'. \n - Note that this copy is likely done as part of application",
        default         : false,
        onChange        : (inst, ui) =>
        {
            let hidden = !inst["sectionRunFromDifferentAddr"]

            ui["sectionRun"].hidden     = hidden
            ui["sectionBinit"].hidden   = hidden
        }
    },
    {
        name        : "sectionRun",
        displayName : "Run Memory",
        hidden      : true,
        default     : "None",
        options     : () =>
        {
            return  Common.allocateAllMemoryRegions()[currentContext]
                    .map(x => {return {name: x.name}})
                    .concat({name: "None"})
        }
    },
    {
        name            : "sectionBinit",
        displayName     : "Place copy table in BINIT section",
        longDescription : "- If this option is enabled, the copy tables are placed in .binit (boot-time initialization) section. Target will automatically perform the copying at auto-initialization time. \n - If this option is disabled, the copy table is placed in .ovly section and application need to perform the copy. Sysconfig generates the function CMD_init which performs the copy for all copy tables other that boot time copy tables ",
        default         : true,
        hidden          : true,
    },
    {
        name        : "sectionAlignEnable",
        displayName : "Enable Alignment",
        default     : false,
        onChange    : (inst, ui) =>
        {
            ui["sectionAlign"].hidden = !inst["sectionAlignEnable"]
        }
    },
    {
        name        : "sectionAlign",
        displayName : "Alignment in bytes (must be power of 2)",
        default     : 8,
        hidden      : true
    },
    {
        name        : "sectionFillEnable",
        displayName : "Fill section with constant",
        default     : false,
        onChange    : (inst, ui) =>
        {
            ui["sectionFill"].hidden = !inst["sectionFillEnable"]
        }
    },
    {
        name            : "sectionFill",
        displayName     : "Fill value",
        default         : 0x0,
        hidden          : true,
        displayFormat   : "hex"
    },
    {
        name            : "sectionSymbols",
        displayName     : "Add linker symbols",
        default         : [],
        minSelections   : 0,
        options         :
        [
            {name : "LOAD_START", displayName : "LOAD_START"},
            {name : "LOAD_END",   displayName : "LOAD_END"},
            {name : "LOAD_SIZE",  displayName : "LOAD_SIZE"},
            {name : "RUN_START",  displayName : "RUN_START"},
            {name : "RUN_END",    displayName : "RUN_END"},
            {name : "RUN_SIZE",   displayName : "RUN_SIZE"}
        ]
    },
    {
        name        : "sectionType",
        displayName : "Type",
        default     : "None",
        options     :
        [
            { name: "None",     displayName: "None"},
            { name: "DSECT",    displayName: "DSECT"},
            { name: "COPY",     displayName: "COPY"},
            { name: "NOLOAD",   displayName: "NOLOAD"},
            { name: "NOINIT",   displayName: "NOINIT"},
        ]
    },
    {
        name        : "addInputSections",
        displayName : "Add Input Sections",
        description : "Specify Input Sections that will be a part of this Output Section",
        default     : false,
    },
];

let moduleInstances = (inst) =>
{
    let mods = []

    if(inst.addInputSections)
    {
        mods.push
        ({
            name        : "inputSection",
            displayName : "Input Sections",
            moduleName  : "/ti/security/inputSection.syscfg.js",
            useArray    : true,
            collapsed   : false,
        })
    }

    return mods
}

function validate(inst, vo)
{
    let aprList = Common.allocateAllMemoryRegions()[currentContext]

    if(!aprList)
        return; 

    let runMem = inst.sectionRunFromDifferentAddr ? inst.sectionRun : inst.sectionMemory

    if(runMem != "None")
    {
        let currRegion  = aprList.find(apr => {return (apr.name == runMem)})

        // CHECK: Section in FLASH must be 8 byte aligned
        if(currRegion && currRegion.memType == "Flash" && !(inst.sectionAlignEnable && inst.sectionAlign == 8))
        {
            vo.logWarning("Flash sections must be 8 byte aligned", inst, "sectionAlignEnable")
        }
    }
}

exports =
{
    displayName         : "Sections",
    defaultInstanceName : "outputSection",
    config              : config,
    moduleInstances     : moduleInstances,
    validate            : validate
};
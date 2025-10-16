/*
 *  ======== security.component.js ========
 */

"use strict";
const Common        = system.getScript('/ti/security/Common.js');
const displayName   = "C29 Security";
let export_final    = {}

if(Common.isAllocationSetupMode())
{
    const topModules =
    [
        {
            displayName     : "Memory Configuration",
            modules         :
            [
                "/ti/security/CPU1_APR",
                "/ti/security/CPU2_APR",
                "/ti/security/CPU3_APR",
            ],
            alreadySorted   : true
        },
        {
            displayName     : "System Security Configuration",
            categories      :
            [
                {
                    displayName: "CPU1",
                    modules:
                    [
                        "/ti/security/CPU1_System_Security",
                        "/ti/security/CPU1_Link",
                        "/ti/security/CPU1_Stack",
                    ],
                    alreadySorted   : true
                },
                {
                    displayName: "CPU2",
                    modules:
                    [
                        "/ti/security/CPU2_System_Security",
                        "/ti/security/CPU2_Link",
                        "/ti/security/CPU2_Stack",
                    ],
                    alreadySorted   : true
                },
                {
                    displayName: "CPU3",
                    modules:
                    [
                        "/ti/security/CPU3_System_Security",
                        "/ti/security/CPU3_Link",
                        "/ti/security/CPU3_Stack",
                    ],
                    alreadySorted   : true
                }
            ],
            alreadySorted   : true
        }
    ];

    const views =
    [
        {
            name        : "/ti/security/templates/mem_summary.xdt",
            displayName : "Memory Region Summary",
            viewType    : "markdown",
            icon        : "table-large",
        },
        {
            name        : "/ti/security/templates/ssu_summary.xdt",
            displayName : "SSU Summary",
            viewType    : "markdown",
            icon        : "table-large",
        },
    ]

    export_final =
    {
        displayName : displayName,
        topModules  : topModules,
        //views       : views
    }; 
}
else if(Common.isAllocationConfigureMode())
{
    const ctx           = system.context
    const raDataCtx     = system.resourceAllocation.data.contexts
                            .find(a => a["contextName"] == ctx);
    
    let checkAPR        =  raDataCtx ? raDataCtx
                        ["modules"]
                        .find(a => (a["moduleName"] == `/ti/security/${ctx}_APR`))
                        : false

    let checkSystemSecurity = raDataCtx ? raDataCtx
                        ["modules"]
                        .find(a => (a["moduleName"] == `/ti/security/${ctx}_System_Security`))
                        : false
    
    const topModules =
    [
        {
            displayName     : "Memory Configuration",
            modules         :
            [
                "/ti/security/OutputSectionConfigure"
            ],
            alreadySorted   : true
        },
    ];

    const templates =
    [
        {
            name        : "/ti/security/templates_configure/linker.security.cmd.xdt",
            outputPath  : "linker.cmd",
            alwaysRun   : (checkAPR) ? true : false,         //!!!! conditional on that module existing
        },
        {
            name        : "/ti/security/templates_configure/ssu_config.c.xdt",
            outputPath  : "ssu_config.c",
            alwaysRun   : (checkSystemSecurity) ? true : false,
        },
        {
            name        : "/ti/security/templates_configure/ssu_config.h.xdt",
            outputPath  : "ssu_config.h",
            alwaysRun   : (checkSystemSecurity) ? true : false,
        },
        {
            name        : "/ti/security/templates_configure/seccfg_old.c.xdt",
            outputPath  : "seccfg.c",
            alwaysRun   : (checkSystemSecurity) ? true : false,
        },
    ];

    const views =
    [
        {
            name        : "/ti/security/templates_configure/mem_summary.xdt",
            displayName : "Memory Region Summary",
            viewType    : "markdown",
            icon        : "table-large",
        },
        {
            name        : "/ti/security/templates_configure/ssu_summary.xdt",
            displayName : "SSU Summary",
            viewType    : "markdown",
            icon        : "table-large",
        },
    ]
    export_final =
    {
        displayName : displayName,
        topModules  : checkAPR ? topModules : [],
        templates   : templates,
        views       : views
    };
}
else
{
    const topModules =
    [
        {
            displayName     : "Memory Configuration",
            modules         :
            [
                "/ti/security/APR",
                "/ti/security/OutputSection"
            ],
            alreadySorted   : true
        },
        {
            displayName     : "System Security Configuration",
            modules         :
            [
                "/ti/security/System_Security",
                "/ti/security/Link",
                "/ti/security/Stack"
            ],
            alreadySorted   : true
        }
    ];

    const templates =
    [
        {
            name        : "/ti/security/templates/linker.security.cmd.xdt",
            outputPath  : "linker.cmd",
            alwaysRun   : false,
        },
        {
            name        : "/ti/security/templates/ssu_config.c.xdt",
            outputPath  : "ssu_config.c",
            alwaysRun   : false,
        },
        {
            name        : "/ti/security/templates/ssu_config.h.xdt",
            outputPath  : "ssu_config.h",
            alwaysRun   : false,
        },
        {
            name        : "/ti/security/templates/seccfg_old.c.xdt",
            outputPath  : "seccfg.c",
            alwaysRun   : false,
        },
    ];

    const views =
    [
        {
            name        : "/ti/security/templates/mem_summary.xdt",
            displayName : "Memory Region Summary",
            viewType    : "markdown",
            icon        : "table-large",
        },
        {
            name        : "/ti/security/templates/ssu_summary.xdt",
            displayName : "SSU Summary",
            viewType    : "markdown",
            icon        : "table-large",
        },
    ]

    export_final =
    {
        displayName : displayName,
        topModules  : topModules,
        templates   : templates,
        views       : views
    };
}

exports = export_final
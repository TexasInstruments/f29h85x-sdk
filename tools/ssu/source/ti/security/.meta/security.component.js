/*
 *  ======== security.component.js ========
 */

"use strict";

const displayName =  "C29 Security";

const topModules = [
    {
        "displayName": "Memory Configuration",
        "modules": [
            "/ti/security/APR",
            "/ti/security/OutputSection"
        ]
    },
    {
        "displayName": "System Security Configuration",
        "modules": [
            "/ti/security/System_Security",
            "/ti/security/Link",
            "/ti/security/Stack",
            // "/ti/security/Zone",
        ],
        alreadySorted: true
    }
];

const templates =  [
    {
        "name"        : "/ti/security/templates/linker.security.cmd.xdt",
        "outputPath"  : "linker.cmd",
        "alwaysRun"   : false,
    },
    {
        "name"        : "/ti/security/templates/ssu_config.c.xdt",
        "outputPath"  : "ssu_config.c",
        "alwaysRun"   : false,
    },
    {
        "name"        : "/ti/security/templates/ssu_config.h.xdt",
        "outputPath"  : "ssu_config.h",
        "alwaysRun"   : false,
    },
    {
        "name"        : "/ti/security/templates/seccfg_old.c.xdt",
        "outputPath"  : "seccfg.c",
        "alwaysRun"   : false,
    },
];

const views = [
    {
        name: "/ti/security/templates/mem_summary.xdt",
        displayName: "Memory Region Summary",
        viewType: "markdown",
        icon: "table-large",
    },
    {
        name: "/ti/security/templates/ssu_summary.xdt",
        displayName: "SSU Summary",
        viewType: "markdown",
        icon: "table-large",
    },
]

exports = { displayName, topModules, templates, views };
const Common = system.getScript("/ti/security/Common.js");

exports = {
    displayName  : "Create Security Context",
    moduleStatic : {
        config: [
            { name: "$name", isCIdentifier: false },
            {
                name           : "createContext",
                displayName    : "",
                buttonText     : "Create Security Context",
                displayTerminal: true,
                onLaunch       : (inst) => {
                    return {
                        command     : system.getNodePath(),
                        args        : [Common.productPath('tools/name'), '$comFile'],
                        initialData : '',
                        inSystemPath: true
                    };
                },
                scriptingOnComplete: (inst, ui, result) => {
                    const ctxName = result.data.trim();

                    let Stack = scripting.addModule("/ti/security/Stack");
                    let Link  = scripting.addModule("/ti/security/Link");
                    let APR   = scripting.addModule("/ti/security/APR");

                    let stk  = Stack.addInstance({'$name':`${ctxName}_ssu_stack`});
                    let lnk  = Link.addInstance({'$name':`${ctxName}_ssu_link`});

                    let text   = APR.addInstance({'$name':`${ctxName}_text`,     type: "Code", memType:'Flash'});
                    let bss    = APR.addInstance({'$name':`${ctxName}_bss_data`, type: "Data", memType:'RAM'});
                    let stkmem = APR.addInstance({'$name':`${ctxName}_stack`,    type: "Data", memType:'RAM'});
                    let rodata = APR.addInstance({'$name':`${ctxName}_rodata`,   type: "Data", memType:'Flash'});

                    text.userSection.create(1);
                    text.userSection[0].sectionName = ".text";
                    text.userSection[0].objectName = ctxName + ".o";

                    bss.userSection.create(2);
                    bss.userSection[0].sectionName = ".bss";
                    bss.userSection[0].objectName = ctxName + ".o";
                    bss.userSection[1].sectionName = ".data";
                    bss.userSection[1].objectName = ctxName + ".o";

                    rodata.userSection.create(1);
                    rodata.userSection[0].sectionName = ".rodata";
                    rodata.userSection[0].objectName = ctxName + ".o";

                    lnk.codeAPRs        = [text];
                    lnk.readwriteAPRs   = [bss, stkmem, rodata];

                    stk.links = [lnk];
                    stk.apr   = stkmem;
                }
            },
            {
                name           : "createSafetyContext",
                displayName    : "",
                buttonText     : "Create Safety Context",
                displayTerminal: true,
                onLaunch       : (inst) => {
                    return {
                        command     : system.getNodePath(),
                        args        : [Common.productPath('tools/name'), '$comFile'],
                        initialData : '',
                        inSystemPath: true
                    };
                },
                scriptingOnComplete: (inst, ui, result) => {
                    const ctxName = result.data.trim();

                    let Link  = scripting.addModule("/ti/security/Link");
                    let APR   = scripting.addModule("/ti/security/APR");

                    let lnk  = Link.addInstance({'$name':`${ctxName}_ssu_link`});

                    let text   = APR.addInstance({'$name':`${ctxName}_text`,     type: "Code", memType:'Flash'});
                    let bss    = APR.addInstance({'$name':`${ctxName}_bss_data`, type: "Data", memType:'RAM'});
                    let rodata = APR.addInstance({'$name':`${ctxName}_rodata`,   type: "Data", memType:'Flash'});

                    text.userSection.create(1);
                    text.userSection[0].sectionName = ".text";
                    text.userSection[0].objectName = ctxName + ".o";;

                    bss.userSection.create(2);
                    bss.userSection[0].sectionName = ".bss";
                    bss.userSection[0].objectName = ctxName + ".o";;
                    bss.userSection[1].sectionName = ".data";
                    bss.userSection[1].objectName = ctxName + ".o";;

                    rodata.userSection.create(1);
                    rodata.userSection[0].sectionName = ".rodata";
                    rodata.userSection[0].objectName = ctxName + ".o";;

                    lnk.codeAPRs        = [text];
                    lnk.readwriteAPRs   = [bss, rodata];
                }
            }
        ]
    }
};

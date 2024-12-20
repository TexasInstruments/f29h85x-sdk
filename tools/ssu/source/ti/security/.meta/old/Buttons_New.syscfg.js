const Common = system.getScript('/ti/security/Common.js');
let c29x     = system.getScript('/ti/security/c29x_device.js');
let sysSec   = system.getScript('/ti/security/System_Security');

function contextCreateHandler (inst, ui, result)
{

}
let config = [
    {
        name        : "group_context",
        displayName : "Define Context Name",
        collapsed   : false,
        config      : [
            {
                name        : "contextName",
                displayName : "Context Name",
                default     : "",
            },
            {
                name        : "isLink2",
                displayName : "Is this Context Secure Root?",
                default     : false,
                onChange    : (inst, ui) => {
                    if(inst.isLink2)
                        inst.contextName = "LINK_2"
                    else
                        inst.contextName = ""
                    ui.contextName.readOnly     = inst.isLink2
                    ui.fileNames_link2.hidden   = !inst.isLink2
                    ui.newStack.hidden          = inst.isLink2
                    ui.stack.hidden             = inst.isLink2 || inst.newStack
                    ui.newStackName.hidden      = inst.isLink2 || !inst.newStack
                }
            },
            {
                name       : "fileNames_link2",
                displayName: "Default Sections included in Secure Root",
                default    : "libc.a<boot.c.obj>(.text), libc.a<autoinit.c.obj>(.text), codestart",
                hidden     : true,
                readOnly   : true
            },
        ]
    },
    {
        name        : "group_stack",
        displayName : "Stack Association",
        collapsed   : false,
        config      : [
            {
                name       : "newStack",
                displayName: "Do you want to create a new stack?",
                default    : false,
                onChange   : (inst, ui) => {
                    ui.stack.hidden = inst.newStack
                    ui.newStackName.hidden = !inst.newStack
                }
            },
            {
                name        : "stack",
                displayName : "Stack to be included",
                options     : () => Common.modInstances('/ti/security/Stack'),
                getDefault  : () => Common.findDefault('/ti/security/Stack'),
                hideNoneOption : true,
            },
            {
                name        : "newStackName",
                displayName : "New Stack Name",
                default     : "",
                hidden      : true
            },
        ]
    },
    {
        name        : "group_files",
        displayName : "Add source files to the context",
        collapsed   : false,
        config      : [
            {
                name        : "addFiles",
                displayName : "Do you want to add source files to this context?",
                default     : false,
                onChange    : (inst, ui) => {
                    ui.fileNames.hidden = !inst.addFiles
                }
            },
            {
                name       : "fileNames",
                displayName: "File Names (comma separated)",
                default    : "",
                hidden     : true
            },
        ]
    },
    {
        name        : "group_libs",
        displayName : "Add Libraries to the context",
        collapsed   : false,
        config      : [
            {
                name        : "addLibs",
                displayName : "Do you want to add any libraries to this context?",
                default     : false,
                onChange    : (inst, ui) => {
                    ui.libs.hidden = !inst.addLibs
                }
            },
            {
                name       : "libs",
                displayName: "Libraries (comma separated)",
                default    : "",
                hidden     : true
            },
        ]
    },
    {
        name        : "group_size",
        displayName : "Define Code and Data sizes",
        collapsed   : false,
        config      : [
            {
                name        : "codeMemType",
                displayName : "Do you want to run the context run from Flash or RAM?",
                default     : "Flash",
                options     : [
                    {name : "Flash",    displayName : "Flash Only"},
                    {name : "RAM",      displayName : "RAM Only"},
                    {name : "FlashRAM", displayName : "Flash and RAM"},
                ],
                onChange    : (inst, ui) => {
                    ui.codesizeFlash.hidden = inst.codeMemType == "RAM"
                    ui.codesizeRAM.hidden = inst.codeMemType == "Flash"
                }
            },
            {
                name        : "group_size1",
                displayName : "",
                collapsed   : false,
                config      : [
                    {
                        name       : "codesizeFlash",
                        displayName: "Code size in Flash (in kB)",
                        default    : 4,
                    },
                    {
                        name       : "codesizeRAM",
                        displayName: "Code size in RAM (in kB)",
                        default    : 4,
                        hidden     : true
                    },
                    {
                        name       : "rwdatasize",
                        displayName: "RW Data size in RAM (in kB)",
                        default    : 4
                    },
                    {
                        name       : "rodatasize",
                        displayName: "RO Data size in Flash(in kB)",
                        default    : 4
                    },
                ]
            }
        ]
    },
    {
        name: "createContext",
        displayName: "",
        description : '',
        buttonText: "Create New Context",
        scriptingOnComplete: (inst, ui, result) => {

            const ctxName = inst.contextName.trim();

            var Stack = scripting.addModule("/ti/security/Stack");
            var Link  = scripting.addModule("/ti/security/Link");
            var APR   = scripting.addModule("/ti/security/APR");

            var stk               = ""
            var lnk               = ""
            var apr_code_flash    = ""
            var apr_code_ram      = ""
            var apr_rwdata_ram    = ""
            var apr_rodata_flash  = ""

            // Create new stack if enabled
            if(inst.newStack)
            {
                var stackName = inst.newStackName
                if(stackName == "")
                    stackName = ctxName + "_stack"
                stk  = Stack.addInstance({'$name': stackName});
            }
            else
                stk = inst.stack

            // Create a new link if not already added
            var temp = Common.modInstances("/ti/security/Link").filter(x=> x.$name == ctxName)
            if(temp.length == 0)
                lnk  = Link.addInstance({'$name': ctxName})
            else
                lnk = temp[0]

            // Create APRs
            if(inst.codeMemType != "RAM")   apr_code_flash    = APR.addInstance({'$name':`${ctxName}_text`,     type: "Code", memType:'Flash',   memSize: inst.codesizeFlash});
            if(inst.codeMemType != "Flash") apr_code_ram      = APR.addInstance({'$name':`${ctxName}_ramfunc`,  type: "Code", memType:'LoadRun', memSize: inst.codesizeRAM});
            if(inst.rwdatasize != 0)        apr_rwdata_ram    = APR.addInstance({'$name':`${ctxName}_rwdata`, type: "Data", memType:'RAM',     memSize: inst.rwdatasize});
            if(inst.rodatasize != 0)        apr_rodata_flash  = APR.addInstance({'$name':`${ctxName}_rodata`,   type: "Data", memType:'Flash',   memSize: inst.rodatasize});

            // Count the number of files / libraries to be added
            var fileList = []
            var libList = []
            if(inst.addFiles)
                fileList = inst.fileNames.split(",")
            if(inst.addLibs)
                libList  = inst.libs.split(",")
            if(inst.isLink2)
                libList = libList.concat(inst.fileNames_link2.split(","))

            var fileCount = fileList.length + libList.length

            // Add sections from each of the files listed to respective APRs
            if(fileCount > 0)
            {
                // Create user sections
                if(apr_code_flash)   apr_code_flash.userSection.create(fileCount);      // .text
                if(apr_code_ram)     apr_code_ram.userSection.create(fileCount);        // .TI.ramfunc
                if(apr_rwdata_ram)   apr_rwdata_ram.userSection.create(2 * fileCount);  // .bss, .data
                if(apr_rodata_flash) apr_rodata_flash.userSection.create(2* fileCount); // .const, .rodata

                var i=0
                fileList.forEach(file=>{
                    file = file.trim()

                    if(apr_code_flash)
                    {
                        apr_code_flash.userSection[i].$name         = "file_" + file + "_text";
                        apr_code_flash.userSection[i].sectionName   = ".text";
                        apr_code_flash.userSection[i].objectName    = file + ".o";
                    }
                    if(apr_code_ram)
                    {
                        apr_code_ram.userSection[i].$name           = "file_" + file + "_ramfunc";
                        apr_code_ram.userSection[i].sectionName     = ".TI.ramfunc";
                        apr_code_ram.userSection[i].objectName      = file + ".o";
                    }
                    if(apr_rwdata_ram)
                    {
                        apr_rwdata_ram.userSection[2*i].$name           = "file_" + file + "_bss";
                        apr_rwdata_ram.userSection[2*i].sectionName     = ".bss";
                        apr_rwdata_ram.userSection[2*i].objectName      = file + ".o";
                        apr_rwdata_ram.userSection[2*i+1].$name         = "file_" + file + "_data";
                        apr_rwdata_ram.userSection[2*i+1].sectionName   = ".data";
                        apr_rwdata_ram.userSection[2*i+1].objectName    = file + ".o";
                    }
                    if(apr_rodata_flash)
                    {
                        apr_rodata_flash.userSection[2*i].$name         = "file_" + file + "_rodata";
                        apr_rodata_flash.userSection[2*i].sectionName   = ".rodata";
                        apr_rodata_flash.userSection[2*i].objectName    = file + ".o";
                        apr_rodata_flash.userSection[2*i+1].$name       = "file_" + file + "_const";
                        apr_rodata_flash.userSection[2*i+1].sectionName = ".const";
                        apr_rodata_flash.userSection[2*i+1].objectName  = file + ".o";
                    }
                    i+=1
                })
                libList.forEach(file=>{
                    var LibName = file.trim()
                    var ObjName = ""
                    if(file.includes("<")) {
                        ObjName = LibName.split("<")[1].replace(">", "")
                        LibName = LibName.split("<")[0]
                    }
                    file = LibName.split(".")[0] + "_" + ObjName.split(".")[0]

                    if(apr_code_flash) {
                        if(file == "codestart_")
                        {
                            apr_code_flash.userSection[i].$name         = "codestart";
                            apr_code_flash.userSection[i].sectionName   = ".codestart";
                        }
                        else
                        {
                            apr_code_flash.userSection[i].$name         = "lib_" + file +  "_text";
                            apr_code_flash.userSection[i].sectionName   = ".text";
                            apr_code_flash.userSection[i].libraryName   = LibName;
                            apr_code_flash.userSection[i].objectName    = ObjName;
                        }
                    }
                    if(apr_code_ram)
                    {
                        apr_code_ram.userSection[i].$name           = "lib_" + file + "_ramfunc";
                        apr_code_ram.userSection[i].sectionName     = ".TI.ramfunc";
                        apr_code_ram.userSection[i].libraryName     = LibName;
                        apr_code_ram.userSection[i].objectName      = ObjName;
                    }
                    if(apr_rwdata_ram)
                    {
                        apr_rwdata_ram.userSection[2*i].$name           = "lib_" + file + "_bss";
                        apr_rwdata_ram.userSection[2*i].sectionName     = ".bss";
                        apr_rwdata_ram.userSection[2*i].libraryName     = LibName;
                        apr_rwdata_ram.userSection[2*i].objectName      = ObjName;
                        apr_rwdata_ram.userSection[2*i+1].$name         = "lib_" + file + "_data";
                        apr_rwdata_ram.userSection[2*i+1].sectionName   = ".data";
                        apr_rwdata_ram.userSection[2*i+1].libraryName   = LibName;
                        apr_rwdata_ram.userSection[2*i+1].objectName    = ObjName;
                    }
                    if(apr_rodata_flash)
                    {
                        apr_rodata_flash.userSection[2*i].$name         = "lib_" + file + "_rodata";
                        apr_rodata_flash.userSection[2*i].sectionName   = ".rodata";
                        apr_rodata_flash.userSection[2*i].libraryName   = LibName;
                        apr_rodata_flash.userSection[2*i].objectName    = ObjName;
                        apr_rodata_flash.userSection[2*i+1].$name       = "lib_" + file + "_const";
                        apr_rodata_flash.userSection[2*i+1].sectionName = ".const";
                        apr_rodata_flash.userSection[2*i+1].libraryName = LibName;
                        apr_rodata_flash.userSection[2*i+1].objectName  = ObjName;
                    }
                    i+=1
                })

            }

            if(apr_code_flash)   lnk.codeAPRs.push(apr_code_flash)
            if(apr_code_ram)     lnk.codeAPRs.push(apr_code_ram)
            if(apr_rwdata_ram)   lnk.readwriteAPRs.push(apr_rwdata_ram)
            if(apr_rodata_flash) lnk.readAPRs.push(apr_rodata_flash)
            if(stk) stk.links.push(lnk);
        }
    },
];

function validate(inst, vo)
{
    if((inst.codeMemType != "RAM") && (inst.codesizeFlash == 0))
        vo.logError("Memory Size cannot be 0" , inst, 'codesizeFlash');

    if((inst.codeMemType != "Flash") && (inst.codesizeRAM == 0))
        vo.logError("Memory Size cannot be 0" , inst, 'codesizeRAM');

    if((inst.codesizeFlash %4) != 0)
        vo.logError("Memory Size should be multiple of 4kB" , inst, 'codesizeFlash');

    if((inst.codesizeRAM %4) != 0)
        vo.logError("Memory Size should be multiple of 4kB" , inst, 'codesizeRAM');

    if((inst.rwdatasize %4) != 0)
        vo.logError("Memory Size should be multiple of 4kB" , inst, 'rwdatasize');

    if((inst.rodatasize %4) != 0)
        vo.logError("Memory Size should be multiple of 4kB" , inst, 'rodatasize');
}

exports = {
    displayName  : 'Create Security Context',
    moduleStatic : {
        validate,
        config,

    }
};
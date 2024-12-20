let Common          = system.getScript("/driverlib/Common.js");
let hwi             = system.getScript("/kernel/dpl/hwi_c29_sdk.js");
let soc             = system.getScript(`/driverlib/hsmclient/soc/hsmclient_${Common.getDeviceName().toLowerCase()}`);
let gHideIntrPri    = !hwi.getPriorityConfigSupported();

let hsmclient_module_name = "/driverlib/hsmclient/hsmclient";

function getInterfaceName(inst) {
    return inst.instance;
}

function getInstanceConfig(moduleInstance) {
    let config = moduleInstance.instance;

     return {
        ...config,
        ...moduleInstance,
     };
};

let hsmclient_module = {

    displayName: "HSMCLIENT",
    templates: {
        "/driverlib/system/system_config.c.xdt": {
            driver_config:  "/driverlib/hsmclient/templates/hsmclient_config.c.xdt",
            driver_init:    "/driverlib/hsmclient/templates/hsmclient_init.c.xdt",
            driver_deinit:  "/driverlib/hsmclient/templates/hsmclient_deinit.c.xdt",
        },
        "/driverlib/system/system_config.h.xdt": {
            driver_config:  "/driverlib/hsmclient/templates/hsmclient.h.xdt",
        },
    },
	defaultInstanceName: "CONFIG_HSMCLIENT",
    maxInstances: 1,
	config: [
		{
			name: "en_hsmclient",
            displayName:"Description",
            description:"Adding and instance of HSMCLIENT enables hsmclient for current core.",
            default: "HSMCLIENT added for current R5 core",
            readOnly:true
        },
		{
			name: "sipc_que_depth",
			displayName:"SIPC Message Queue Depth",
			description: "At any given time maximum number of messages that can be in an SIPC queue. Make sure this field matches with HSM server SIPC message queue depth configuration.",
			default: 32,
			displayFormat: "dec",
		},
        {
            name: "intrPriority",
            displayName: "Interrupt Priority",
            default: 7,
            hidden: gHideIntrPri,
            description: `Interrupt Priority: (RTINT_Threshold + 1) (highest) to ${hwi.getHwiMaxPriority()} (lowest)`,
        },
		{
			name: "sipc_c29cores",
			displayName:"Number Of Secure Hosts",
			description: "Total number of secure hosts. The can be at least 1 and atmost 2 secure hosts at a time. Make sure this field matches with HSM server configurations. ",
			default: 2,
			displayFormat: "dec",
		},
		{
			name: "sec_core_option",
			displayName:"Select Secure Host Id",
			longDescription: "Select secure_host_id for current core. Secure_host_id_0is the primary secure core. HSMRt will send a bootnotify message to a primary secure core once it completes the initialization sequence and ready to accept requests.",
			default: "secure_host_id_0",
            options: [
                {
                    name:"secure_host_id_0"
                },
                {
                    name:"secure_host_id_1"
                }]
		},
	],
    longDescription:
    "The objective of HSM client is to provide APIs for accessing HSM services. It uses Secure IPC Notify driver as a low level message passing mechanism to talk to HSM M4 core. HSM client APIs can be used with either FreeRTOS or NoRTOS application.",
    validate: validate,
    getInterfaceName,
    getInstanceConfig
}

function validate(inst,report)
{
    if(inst.sipc_que_depth < 2 || inst.sipc_que_depth > 77)
    {
        report.logError("SIPC Queue depth should be between 2 and 77 ",inst);
    }
    if(inst.sipc_c29cores < 1 || inst.sipc_c29cores > 2)
    {
        report.logError("There can be at least 1 and atmost 2 secure hosts at a time.",inst);
    }

    let coreNames       = Common.getSysCfgCoreNames();
    let selfCoreName    = Common.getSelfSysCfgCoreName();

    let remoteCoreInstArr = new Array();

    /* populate all hsmclient instances */
    for(let remoteCoreName of coreNames)
    {
        let remote_core_instance = Common.getModuleForCore('/driverlib/hsmclient/hsmclient',remoteCoreName);
        if (!_.isEmpty(remote_core_instance))
        {
            remoteCoreInstArr.push(remote_core_instance);
        }
    }

    let interrupt       = system.modules["/driverlib/interrupt.js"];
    let rtIntThreshold  = 1;

    if(interrupt != null)
    {
        rtIntThreshold = interrupt.$static.RTINT_Threshold + 1;
    }

    if(inst.intrPriority > hwi.getHwiMaxPriority() || inst.intrPriority < rtIntThreshold)
    {
        report.logError(`Interrupt priority must be between ${rtIntThreshold} and ${hwi.getHwiMaxPriority()}.`,inst);
    }

    /* if more than two hsmclient modules are instansiated then throw error */
    if(remoteCoreInstArr.length > 2)
    {
        report.logError("Max number of secure cores is 2",inst);
    }
    else
    {
        for(let remoteCoreName of coreNames)
        {
            if(remoteCoreName != selfCoreName)
            {
                let remote_core_instance = common.getModuleForCore('/driverlib/hsmclient/hsmclient',remoteCoreName);
                if(!_.isEmpty(remote_core_instance))
                {
                    if(remote_core_instance.$instances[0].sec_core_option == inst.sec_core_option )
                    {
                        report.logError(`Please give different secure host id to hsmclient instanciated for different R5F cores.`,inst);
                    }
                    if(remote_core_instance.$instances[0].sipc_que_depth != inst.sipc_que_depth)
                    {
                        report.logError(`Please make sure that sipc queue depth for all the instance is same. Note that sipc queue depth should be equal to sipc queue depth set for hsm server.`, inst);
                    }
                    if(remote_core_instance.$instances[0].sipc_c29cores != inst.sipc_c29cores)
                    {
                        report.logError("Please make sure that sipc queue depth for all the instance is same. Note that sipc queue depth should be equal to sipc queue depth set for hsm server", inst);
                    }
                }
            }
        }
    }

}
exports = hsmclient_module;

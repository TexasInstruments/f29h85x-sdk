const Common                = system.getScript('/ti/security/Common.js');
const currentContext        = "CPU1";
const config_systemSecurity = system.getScript('/ti/security/configCommon/systemSecurity.js');

let check = Common.isAllocationSetupMode()

let moduleStaticResources =
{
    config                      : config_systemSecurity.config_resources(currentContext),
    shouldBeAllocatedAsResource : true
}

exports =
{
    displayName         : 'CPU1 System Security',
    validate            : config_systemSecurity.validate,
    config              : config_systemSecurity.config_main_core,
    moduleInstances     : config_systemSecurity.moduleInstances,
    moduleStatic        : check ? moduleStaticResources : {},                        
    totalMaxInstances   : 1,
    templates   :
    {
        '/ti/security/templates/ssu_config.c.xdt'   : true,
        '/ti/security/templates/ssu_config.h.xdt'   : true,
        '/ti/security/templates/seccfg_old.c.xdt'   : true
    },
    shouldBeAllocatedAsResource : true
};
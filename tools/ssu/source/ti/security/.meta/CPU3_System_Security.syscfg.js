const Common                = system.getScript('/ti/security/Common.js');
const currentContext        = "CPU3";
const config_systemSecurity = system.getScript('/ti/security/configCommon/systemSecurity_non_main_core.js');

let check = Common.isAllocationSetupMode()

let moduleStaticResources =
{
    config                      : config_systemSecurity.config_resources(currentContext),
    shouldBeAllocatedAsResource : true
}

exports =
{
    displayName         : 'CPU3 System Security',
    validate            : config_systemSecurity.validate,
    config              : config_systemSecurity.config_non_main_core_with_flash,
    moduleStatic        : check ? moduleStaticResources : {},      
    moduleInstances     : config_systemSecurity.moduleInstances,
    totalMaxInstances   : 1,
    templates   :
    {
        '/ti/security/templates/ssu_config.c.xdt'   : true,
        '/ti/security/templates/ssu_config.h.xdt'   : true,
        '/ti/security/templates/seccfg_old.c.xdt'   : true
    },
    shouldBeAllocatedAsResource : true
};
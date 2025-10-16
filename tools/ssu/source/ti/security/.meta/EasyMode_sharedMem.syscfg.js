const Common            = system.getScript('/ti/security/Common.js');
const config_sharedmem  = system.getScript('/ti/security/configCommon/easy_sharedmem.js');
const currentContext    = system.context;

exports =
{
    displayName         : 'SharedMem',
    defaultInstanceName : currentContext + "_SharedMem",
    validate            : config_sharedmem.validate,
    config              : config_sharedmem.config,
    moduleInstances     : config_sharedmem.moduleInstances,
};
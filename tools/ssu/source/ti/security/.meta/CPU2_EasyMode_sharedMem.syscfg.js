const Common            = system.getScript('/ti/security/Common.js');
const config_sharedmem  = system.getScript('/ti/security/configCommon/easy_sharedmem.js');

exports =
{
    displayName         : 'CPU2 Shared Memory Region',
    defaultInstanceName : "CPU2_SharedMem",
    validate            : config_sharedmem.validate,
    config              : config_sharedmem.config,
    moduleInstances     : config_sharedmem.moduleInstances,
};
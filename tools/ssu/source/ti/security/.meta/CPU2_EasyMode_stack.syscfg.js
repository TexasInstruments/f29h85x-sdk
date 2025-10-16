const Common        = system.getScript('/ti/security/Common.js');
const config_stack  = system.getScript('/ti/security/configCommon/easy_stack.js');

exports =
{
    displayName         : 'CPU2 Sandbox',
    defaultInstanceName : 'CPU2_Sandbox',
    validate            : config_stack.validate,
    config              : config_stack.config,
    moduleInstances     : config_stack.moduleInstances
};
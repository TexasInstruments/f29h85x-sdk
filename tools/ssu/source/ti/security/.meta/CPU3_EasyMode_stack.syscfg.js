const Common        = system.getScript('/ti/security/Common.js');
const config_stack  = system.getScript('/ti/security/configCommon/easy_stack.js');

exports =
{
    displayName         : 'CPU3 Sandbox',
    defaultInstanceName : 'CPU3_Sandbox',
    validate            : config_stack.validate,
    config              : config_stack.config,
    moduleInstances     : config_stack.moduleInstances
};
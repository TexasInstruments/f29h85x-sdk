const Common            = system.getScript('/ti/security/Common.js');
const config_stack      = system.getScript('/ti/security/configCommon/easy_stack.js');
const currentContext    = system.context;

exports =
{
    displayName         : 'EasyMode',
    defaultInstanceName : currentContext + '_Sandbox',
    validate            : config_stack.validate,
    config              : config_stack.config,
    moduleInstances     : config_stack.moduleInstances
};
const Common            = system.getScript('/ti/security/Common.js');
const config_stack      = system.getScript('/ti/security/configCommon/stack.js');
const currentContext    = system.context;

exports =
{
    displayName         : 'STACK',
    defaultInstanceName : currentContext +  '_STACK_10',
    maxInstances        : 7,
    validate            : config_stack.validate,
    config              : config_stack.config,
    moduleInstances     : config_stack.moduleInstances
};

const Common        = system.getScript('/ti/security/Common.js');
const config_stack  = system.getScript('/ti/security/configCommon/stack.js');

exports =
{
    displayName         : 'CPU1 STACK',
    defaultInstanceName : 'CPU1_STACK_10',
    maxInstances        : 7,
    validate            : config_stack.validate,
    config              : config_stack.config,
    moduleInstances     : config_stack.moduleInstances
};

const Common        = system.getScript('/ti/security/Common.js');
const config_stack  = system.getScript('/ti/security/configCommon/stack.js');

exports =
{
    displayName         : 'CPU2 STACK',
    defaultInstanceName : 'CPU2_STACK_10',
    maxInstances        : 7,
    validate            : config_stack.validate,
    config              : config_stack.config,
    moduleInstances     : config_stack.moduleInstances
};

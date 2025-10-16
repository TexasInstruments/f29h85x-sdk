const Common            = system.getScript('/ti/security/Common.js');
const config_apr        = system.getScript('/ti/security/configCommon/apr.js');
const currentContext    = system.context;

exports =
{
    displayName         : 'Memory Region',
    defaultInstanceName : currentContext + '_Mem_',
    config              : config_apr.config,
    moduleStatic        :
    {
        validateStatic  : config_apr.validateStatic,
        config          : config_apr.config_static,
    },
    moduleInstances     : config_apr.moduleInstances,
    templates           :
    {
        '/ti/security/templates/linker.security.cmd.xdt': true,
    },
    validate            : config_apr.validate,
};

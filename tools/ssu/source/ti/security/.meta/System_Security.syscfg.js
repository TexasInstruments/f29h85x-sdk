const Common                = system.getScript('/ti/security/Common.js');
const currentContext        = system.context;
const config_systemSecurity = system.getScript('/ti/security/configCommon/systemSecurity.js');

exports =
{
    displayName : 'System Security',
    moduleStatic:
    {
        validate            : config_systemSecurity.validate,
        config              : config_systemSecurity.configStatic,
        moduleInstances     : config_systemSecurity.moduleInstances,
    },
    templates   :
    {
        '/ti/security/templates/ssu_config.c.xdt'   : true,
        '/ti/security/templates/ssu_config.h.xdt'   : true,
        '/ti/security/templates/seccfg_old.c.xdt'   : true
    }
};
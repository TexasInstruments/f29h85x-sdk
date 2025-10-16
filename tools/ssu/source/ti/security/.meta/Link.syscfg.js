const Common            = system.getScript('/ti/security/Common.js');
const config_link       = system.getScript('/ti/security/configCommon/link.js');
const currentContext    = system.context;

exports =
{
    displayName         : 'LINK',
    defaultInstanceName : currentContext + '_LINK_10',
    maxInstances        : 15,
    validate            : config_link.validate,
    config              : config_link.config,
    moduleStatic        :
    {
        validate    : config_link.validateGlobal
    }
};

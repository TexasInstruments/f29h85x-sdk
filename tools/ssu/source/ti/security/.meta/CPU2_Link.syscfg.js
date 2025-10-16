const Common            = system.getScript('/ti/security/Common.js');
const config_link       = system.getScript('/ti/security/configCommon/link.js');

exports =
{
    displayName         : 'CPU2 LINK',
    defaultInstanceName : 'CPU2_LINK_10',
    maxInstances        : 15,
    validate            : config_link.validate,
    config              : config_link.config,
    moduleStatic        :
    {
        validate    : config_link.validateGlobal
    }
};

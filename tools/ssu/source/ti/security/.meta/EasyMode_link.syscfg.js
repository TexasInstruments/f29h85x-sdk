const Common            = system.getScript('/ti/security/Common.js');
const config_easy_link  = system.getScript('/ti/security/configCommon/easy_link.js');
const currentContext    = system.context;

exports =
{
    displayName         : 'Link',
    defaultInstanceName : currentContext + "_AppModule",
    config              : config_easy_link.config_common,
    validate            : config_easy_link.validate,
    moduleInstances     : config_easy_link.moduleInstances,
};
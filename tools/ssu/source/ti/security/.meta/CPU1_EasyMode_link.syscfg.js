const Common            = system.getScript('/ti/security/Common.js');
const config_easy_link  = system.getScript('/ti/security/configCommon/easy_link.js');

exports =
{
    displayName         : 'CPU1 Application Module',
    defaultInstanceName : "CPU1_AppModule",
    config              : config_easy_link.config_main,
    validate            : config_easy_link.validate,
    moduleInstances     : config_easy_link.moduleInstances,
};
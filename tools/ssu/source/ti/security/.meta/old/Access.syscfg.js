const Common = system.getScript('/ti/security/Common.js');
let c29x     = system.getScript('/ti/security/c29x_device.js');

let config = [
    { name : 'read',  displayName: 'Readable',  default : false },
    { name : 'write', displayName: 'Writeable', default : false },
];

function validate(inst, vo)
{
}

function sharedModuleInstances(inst)
{
    return [
        {
            name            : 'link',
            displayName     : 'Link',
            moduleName      : '/ti/security/ssu/Link',
            collapsed       : true
        }
    ];
}

exports = {
    displayName        : 'Access',
    defaultInstanceName: 'acc_',
    sharedModuleInstances,
    validate,
    config
};

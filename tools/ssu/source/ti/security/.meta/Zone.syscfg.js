const Common = system.getScript('/ti/security/Common.js');
//!! Config not exposed currently

let config = [
    { name: '$name', startingIndex:2},
    {
        name             : 'stacks',
        displayName      : 'STACKs',
        options          : () => Common.modInstances('/ti/security/Stack'),
        isArray          : true,
        disableSelectAll : true,
    },
    {
        name       : 'FWU',
        displayName: "ZONE Firmware Update",
        collapsed  : false,
        config     : [
            {
                name         : 'UPDATE_EN',
                displayName  : 'ZONE Update Enable',
                default      : false,
            },
            {
                name         : 'FWU_CPU',
                displayName  : 'Firmware Update Owner CPU',
                default      : 0,
                options      : [
                    { name: 0, displayName :"CPU-HSM"},
                    { name: 1, displayName :"CPU1"},
                    { name: 2, displayName :"CPU2"},
                    { name: 3, displayName :"CPU3"},
                ]
            },
            {
                name         : 'FWU_LINK',
                displayName  : 'Firmware Update Owner LINK',
                options      : () => Common.modInstances('/ti/security/Link'),
                hideNoneOption : true
            },
        ]
    },
    {
        name       : 'Debug',
        displayName: "Debug Access (SSU MODE 3 Only)",
        collapsed  : false,
        config     : [
            {
                name         : 'DEBUG_CFG',
                displayName  : 'ZONE Debug Configuration',
                default      : 2,
                options      : [
                    { name: 1, displayName: "CPU based"},
                    { name: 2, displayName: "Password based"},
                    { name: 4, displayName: "Disable debug"},
                ],
                onChange   : (inst, ui) => {
                    ui.FDBGPSWD.hidden = inst.DEBUG_CFG != 2;
                    ui.PDBGPSWD.hidden = inst.DEBUG_CFG != 2;
                }
            },
            {
                name       : 'PDBGPSWD',
                displayName: 'Partial debug password',
                default    : "0x55555555555555555555555555555555",
            },
            {
                name       : 'FDBGPSWD',
                displayName: 'Full debug password',
                default    : "0x55555555555555555555555555555555",
            },
        ]
    }
];

function validate(inst, vo)
{
    // Check if stacks selected are used in other zones
    _.without(Common.modInstances('/ti/security/Zone'), inst).forEach(zone => {
        inst.stacks.forEach(s =>  {
            if(zone.stacks.includes(s)) {
                vo.logError(s.$name + " is already added in " + zone.$name, inst, 'stacks');
            }
        });
    });

    var format32Hex = new RegExp(/^0x[A-F0-9]{32}$/i);
    if(!format32Hex.test(inst.FDBGPSWD))
        vo.logError("Invalid 32 digit hex value.", inst, 'FDBGPSWD');
    if(!format32Hex.test(inst.PDBGPSWD))
        vo.logError("Invalid 32 digit hex value.", inst, 'PDBGPSWD');
}

exports = {
    displayName         : 'ZONE',
    defaultInstanceName : 'ZONE_',
    maxInstances        : 3,
    validate,
    config,
};
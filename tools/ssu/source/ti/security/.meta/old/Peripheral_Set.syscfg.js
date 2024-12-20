"use strict";
let Common   = system.getScript('/ti/security/Common.js');
let c29x     = system.getScript('/ti/security/c29x_device.js');
let logError = Common.logError;

/* Array of configurables */
let config = [
    {
        name         : "peripherals",
        displayName  : "Peripherals",
        minSelections: 0,
        default      : [],
        options      : c29x.periphSelector()
    },
    {
        name       : 'readable',
        displayName: 'Readable',
        default    : 'Exclusively Yes',
        options    : [
            {name: 'No'},
            {name: 'Yes'},
            {name: 'Exclusively Yes'},
        ]
    },
    {
        name       : 'writeable',
        displayName: 'Writeable',
        default    : 'Exclusively Yes',
        options    : [
            {name: 'No'},
            {name: 'Yes'},
            {name: 'Exclusively Yes'},
        ]
    },
];

/**
 * Validate this module's configuration
 *
 * @param {object} inst - Watchdog instance to be validated
 * @param {object} vo   - Issue reporting object
 */
function validate(inst, vo)
{
    Common.validateNames(inst, vo);

    if (inst.peripherals.length == 0) {
        logError(vo,inst,'peripherals', 'Must select at least one peripheral.');
    }
}

exports = {
    displayName         : 'Peripheral Set',
    defaultInstanceName : 'periph_set_',
    config              : config,
    validate            : validate
};


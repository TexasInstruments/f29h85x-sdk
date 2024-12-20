let references = system.getScript("/kernel/dpl/dpl_c29_sdk_references.js");

exports = {
    displayName:    'freertos_dpl',
    moduleStatic:   {},
    config:         [],
    references: [
        references.getReferencePath("CACHEP_NORTOS"),
        references.getReferencePath("CPUID_C29"),
        references.getReferencePath("CYCLECOUNTERP_NORTOS"),
        references.getReferencePath("DEBUGP_LOG"),
        references.getReferencePath("PRINTF"),
        references.getReferencePath("TIMERP"),
        references.getReferencePath("CLOCKP_FREERTOS_C29"),
        references.getReferencePath("HWIP_FREERTOS_C29"),
        references.getReferencePath("HWIP_FREERTOS_C29_ASM"),
        references.getReferencePath("HWIP_FREERTOS_C29_HANDLERS"),
        references.getReferencePath("CLOCKP_FREERTOS"),
        references.getReferencePath("DEBUGP_FREERTOS"),
        references.getReferencePath("EVENTP_FREERTOS"),
        references.getReferencePath("HEAPP_FREERTOS"),
        references.getReferencePath("SEMP_FREERTOS"),
        references.getReferencePath("TASKP_FREERTOS"),
    ]
};
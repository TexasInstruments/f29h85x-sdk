let references = system.getScript("/kernel/dpl/dpl_c29_sdk_references.js");

exports = {
    displayName:    'nortos_dpl',
    moduleStatic:   {},
    config:         [],
    references: [
        references.getReferencePath("CACHEP_NORTOS"),
        references.getReferencePath("CLOCKP_NORTOS_C29"),
        references.getReferencePath("CPUID_C29"),
        references.getReferencePath("HWIP_NORTOS_C29"),
        references.getReferencePath("HWIP_NORTOS_C29_ASM"),
        references.getReferencePath("HWIP_NORTOS_C29_HANDLERS"),
        references.getReferencePath("CLOCKP_NORTOS"),
        references.getReferencePath("CYCLECOUNTERP_NORTOS"),
        references.getReferencePath("DEBUGP_LOG"),
        references.getReferencePath("DEBUGP_NORTOS"),
        references.getReferencePath("PRINTF"),
        references.getReferencePath("SEMP_NORTOS"),
        references.getReferencePath("TIMERP"),
    ]
};
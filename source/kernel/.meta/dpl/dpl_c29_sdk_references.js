var references = [
    /* NORTOS */
    {
        name:           "CLOCKP_NORTOS_C29",
        path:           "../source/kernel/nortos/dpl/c29/ClockP_nortos_c29.c",
        alwaysInclude:  false,
    },
    {
        name:           "CPUID_C29",
        path:           "../source/kernel/nortos/dpl/c29/CpuIdP_c29.c",
        alwaysInclude:  false,
    },
    {
        name:           "HWIP_NORTOS_C29",
        path:           "../source/kernel/nortos/dpl/c29/HwiP_c29_pipe.c",
        alwaysInclude:  false,
    },
    {
        name:           "HWIP_NORTOS_C29_ASM",
        path:           "../source/kernel/nortos/dpl/c29/HwiP_c29_pipe_asm.S",
        alwaysInclude:  false,
    },
    {
        name:           "HWIP_NORTOS_C29_HANDLERS",
        path:           "../source/kernel/nortos/dpl/c29/HwiP_c29_pipe_handlers_nortos.c",
        alwaysInclude:  false,
    },
    {
        name:           "CACHEP_NORTOS",
        path:           "../source/kernel/nortos/dpl/common/CacheP_null.c",
        alwaysInclude:  false,
    },
    {
        name:           "CLOCKP_NORTOS",
        path:           "../source/kernel/nortos/dpl/common/ClockP_nortos.c",
        alwaysInclude:  false,
    },
    {
        name:           "CYCLECOUNTERP_NORTOS",
        path:           "../source/kernel/nortos/dpl/common/CycleCounterP.c",
        alwaysInclude:  false,
    },
    {
        name:           "DEBUGP_LOG",
        path:           "../source/kernel/nortos/dpl/common/DebugP_log.c",
        alwaysInclude:  false,
    },
    {
        name:           "DEBUGP_NORTOS",
        path:           "../source/kernel/nortos/dpl/common/DebugP_nortos.c",
        alwaysInclude:  false,
    },
    {
        name:           "PRINTF",
        path:           "../source/kernel/nortos/dpl/common/printf.c",
        alwaysInclude:  false,
    },
    {
        name:           "SEMP_NORTOS",
        path:           "../source/kernel/nortos/dpl/common/SemaphoreP_nortos.c",
        alwaysInclude:  false,
    },
    {
        name:           "TIMERP",
        path:           "../source/kernel/nortos/dpl/common/TimerP.c",
        alwaysInclude:  false,
    },

    /* FREERTOS */
    {
        name:           "CLOCKP_FREERTOS_C29",
        path:           "../source/kernel/freertos/dpl/c29/ClockP_freertos_c29.c",
        alwaysInclude:  false,
    },
    {
        name:           "HWIP_FREERTOS_C29",
        path:           "../source/kernel/freertos/dpl/c29/HwiP_c29_pipe.c",
        alwaysInclude:  false,
    },
    {
        name:           "HWIP_FREERTOS_C29_ASM",
        path:           "../source/kernel/freertos/dpl/c29/HwiP_c29_pipe_asm.S",
        alwaysInclude:  false,
    },
    {
        name:           "HWIP_FREERTOS_C29_HANDLERS",
        path:           "../source/kernel/freertos/dpl/c29/HwiP_c29_pipe_handlers_freertos.c",
        alwaysInclude:  false,
    },
    {
        name:           "CLOCKP_FREERTOS",
        path:           "../source/kernel/freertos/dpl/common/ClockP_freertos.c",
        alwaysInclude:  false,
    },
    {
        name:           "DEBUGP_FREERTOS",
        path:           "../source/kernel/freertos/dpl/common/DebugP_freertos.c",
        alwaysInclude:  false,
    },
    {
        name:           "EVENTP_FREERTOS",
        path:           "../source/kernel/freertos/dpl/common/EventP_freertos.c",
        alwaysInclude:  false,
    },
    {
        name:           "HEAPP_FREERTOS",
        path:           "../source/kernel/freertos/dpl/common/HeapP_freertos.c",
        alwaysInclude:  false,
    },
    {
        name:           "SEMP_FREERTOS",
        path:           "../source/kernel/freertos/dpl/common/SemaphoreP_freertos.c",
        alwaysInclude:  false,
    },
    {
        name:           "TASKP_FREERTOS",
        path:           "../source/kernel/freertos/dpl/common/TaskP_freertos.c",
        alwaysInclude:  false,
    },
]

function getReferencePath(name)
{
    for (var ref of references)
    {
        if (ref.name == name)
        {
            return ref.path
        }
    }
}

var componentReferences = []
for (var ref of references)
{
    componentReferences.push({
        path: ref.path,
        alwaysInclude: ref.alwaysInclude
    })
}

exports = {
    references:             references,
    getReferencePath :      getReferencePath,
    componentReferences :   componentReferences
}
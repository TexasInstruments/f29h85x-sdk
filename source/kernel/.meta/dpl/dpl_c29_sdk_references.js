var references = [
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
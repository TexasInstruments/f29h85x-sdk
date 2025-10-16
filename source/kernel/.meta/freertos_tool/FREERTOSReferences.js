var references = [
        {
            name: "TASK",
            path: "../source/kernel/freertos/Source/tasks.c",
            alwaysInclude: false,
        },
        {
            name: "QUEUE",
            path: "../source/kernel/freertos/Source/queue.c",
            alwaysInclude: false,
        },
        {
            name: "LIST",
            path: "../source/kernel/freertos/Source/list.c",
            alwaysInclude: false,
        },
        {
            name: "TIMER",
            path: "../source/kernel/freertos/Source/timers.c",
            alwaysInclude: false,
        },
        {
            name: "EVENTS",
            path: "../source/kernel/freertos/Source/event_groups.c",
            alwaysInclude: false,
        },
        {
            name: "SBUFFER",
            path: "../source/kernel/freertos/Source/stream_buffer.c",
            alwaysInclude: false,
        },
        {
            name: "PORT",
            path: "../source/kernel/freertos/Source/portable/CCS/C2000_C29x/port.c",
            alwaysInclude: false,
        },
        {
            name: "PORTASM",
            path: "../source/kernel/freertos/Source/portable/CCS/C2000_C29x/portasm.S",
            alwaysInclude: false,
        },
        {
            name: "HEAP1",
            path: "../source/kernel/freertos/Source/portable/MemMang/heap_1.c",
            alwaysInclude: false,
        },
        {
            name: "HEAP2",
            path: "../source/kernel/freertos/Source/portable/MemMang/heap_2.c",
            alwaysInclude: false,
        },
        {
            name: "HEAP3",
            path: "../source/kernel/freertos/Source/portable/MemMang/heap_3.c",
            alwaysInclude: false,
        },
        {
            name: "HEAP4",
            path: "../source/kernel/freertos/Source/portable/MemMang/heap_4.c",
            alwaysInclude: false,
        },
        {
            name: "HEAP5",
            path: "../source/kernel/freertos/Source/portable/MemMang/heap_5.c",
            alwaysInclude: false,
        },
        //
        // H files are not really necessary as they can be included with a -I in the opt file
        //
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
    references: references,
    getReferencePath : getReferencePath,
    componentReferences : componentReferences
}
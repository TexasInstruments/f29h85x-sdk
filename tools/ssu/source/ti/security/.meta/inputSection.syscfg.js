
let config =
[
    {
        name            : "$name",
        hidden          : false,
        isCIdentifier   : false,
    },
    {
        name            : "sectionName",
        displayName     : "Section Name",
        default         : "",
        longDescription : "If Section name is not specified, all the sections specified in the library and .obj will be used."
    },
    {
        name            : "objectName",
        displayName     : "Obj Name",
        longDescription : "If Obj name is specified, only the sections present in the selected .obj file are used. Can be left blank if not applicable",
        default         : ""
    },
    {
        name            : "libraryName",
        displayName     : "Library Name",
        longDescription : "If Library name is specified, only the sections present in the selected library are used. Can be left blank if not applicable",
        default         : ""
    },
];

exports =
{
    displayName         : "Input Section",
    defaultInstanceName : "inputSection",
    config              : config
};

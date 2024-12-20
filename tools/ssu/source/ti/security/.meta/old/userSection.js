
var config = [
    {
        name: "$name",
        hidden: false,
    },
    {
        name: "sectionName",
        displayName: "Section Name",
        default: "",
        longDescription: "If Section Name is not specified, all the sections specified in the library and obj is used."
    },
    {
        name: "objectName",
        displayName: "Obj Name",
        longDescription : "If Obj name is specified, only the section present in the selected .obj file is used. Can be left blank if not applicable",
        default: ""
    },
    {
        name: "libraryName",
        displayName: "Library Name",
        longDescription : "If Library name is specified, only the section present in the selected library is used. Can be left blank if not applicable",
        default: ""
    },
];



// Define the common/portable base Watchdog
exports = {
    displayName         : "Input Section",
    defaultInstanceName : "inputSection",
    config              : config
};

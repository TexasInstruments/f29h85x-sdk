let Common  = system.getScript("/driverlib/Common.js");

function getSelfCoreId(){
    if (Common.isContextCPU1()) {
        return "C29_CPU_1";
    }
    else if (Common.isContextCPU2()) {
        return "C29_CPU_2";
    }
    else {
        return "C29_CPU_3";
    }
}

exports =
{
    getSelfCoreId,
}

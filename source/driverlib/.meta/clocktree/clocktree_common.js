var TriCore 	= system.getTemplate('triCore/triCore.xdt');
var TriCore_CPU2 	= system.getTemplate('triCore/triCore_CPU2.xdt');
var TriCore_CPU3 	= system.getTemplate('triCore/triCore_CPU3.xdt');
var DualCore 	= system.getTemplate('dualCore/dualCore.xdt');
var DualCore_CPU2 	= system.getTemplate('dualCore/dualCore_CPU2.xdt');
var SingleCore  = system.getTemplate('singleCore/singleCore.xdt');

const multi_core = ["F29H85x"]
const dual_core = []
const tri_core = ["F29H85x"]
const xtal_x1_macro = []

const PLL_type1  = []					            //FMULT available 	| REFDIV unavailable
const PLL_type2  = ["F29H85x"]	                    //FMULT unavailable	| REFDIV available

const AUXPLL_Support 		= []
const EPWM_div_support 		= ["F29H85x"]           //ePWM clock divider support

const device  = system.deviceData.device
var XTAL_OR_X1 		= system.clockTree.XTAL_OR_X1

exports = {
    TriCore  : TriCore,
    TriCore_CPU2  : TriCore_CPU2,
    TriCore_CPU3  : TriCore_CPU3,
    DualCore : DualCore,
    DualCore_CPU2 : DualCore_CPU2,
    SingleCore : SingleCore,
    multi_core : multi_core,
    dual_core  : dual_core,
    tri_core   : tri_core,
    PLL_type1 : PLL_type1,
    PLL_type2 : PLL_type2,
    device : device,
    AUXPLL_Support : AUXPLL_Support,
    EPWM_div_support : EPWM_div_support,
    XTAL_OR_X1 : XTAL_OR_X1,
    xtal_x1_macro : xtal_x1_macro
}
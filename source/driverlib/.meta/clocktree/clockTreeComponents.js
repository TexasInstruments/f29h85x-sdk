let Common   = system.getScript("/driverlib/Common.js");
if (("system" === system.context || "CPU1" === system.context) && system.deviceData.clockTree)
{

	let Support = system.getScript("./support.js");

	const typeMap = {
		Oscillator: "/driverlib/clocktree/oscillators.js",
		PinFunction: "/driverlib/clocktree/pinFunction.js",
		Mux: "/driverlib/clocktree/mux.js",
		Divider: "/driverlib/clocktree/divider.js",
		Multiplier: "/driverlib/clocktree/multiplier.js",
		Adder: "/driverlib/clocktree/adder.js",
		Gate: "/driverlib/clocktree/unknown.js",
		NamedConnection: "/driverlib/clocktree/namedConnection.js",
		unknown: "/driverlib/clocktree/unknown.js",
	};

	let FreqLabels = _.chain(system.deviceData.clockTree.connectivity).filter((c)=>!_.isEmpty(c.displayName)).map((c)=>c.name).value()

	let namedConnection = _.chain(system.deviceData.clockTree.ipInstances).filter((c) => (c.shape === "NamedConnection")).map((c)=>c.name).value()

	let InputClock = _.chain(system.deviceData.clockTree.ipInstances).filter((c) => (c.displayName === "OSCCLK")).map((c)=>c.name).value()

	FreqLabels = FreqLabels.concat(namedConnection)

	function defaultView(ipInstance) {
		// MCAN - include all MCAN clock sources inclduing PLLCLK
		if (ipInstance.name == "MCANA_CLOCK_domain" || ipInstance.name == "MCANB_CLOCK_domain" || ipInstance.name == "MCANC_CLOCK_domain" || ipInstance.name == "MCAND_CLOCK_domain" || ipInstance.name == "MCANE_CLOCK_domain" ||ipInstance.name == "MCANF_CLOCK_domain") {
			return {
				displayName: (ipInstance.description ?? ipInstance.name).replace(/domain/ig,''),
				ipInstances: ["AUXCLK","AUXCLKIN","PLLCLK",ipInstance.name],
				algorithm: "everythingBetween",
				frequencyLabels: FreqLabels,
			}
		}

		//PLLSYSCLK + WD - include complete domain
		if (ipInstance.name == "PLLSYSCLK_domain" || ipInstance.name == "Watchdog_domain" ) {
			return {
				displayName: (ipInstance.description ?? ipInstance.name).replace(/domain/ig,''),
				ipInstances: [ipInstance.name],
				algorithm: "fanIn",
				frequencyLabels: FreqLabels,
			}
		}

		// OTHER - from PLLCLK
		else {
			return {
				displayName: (ipInstance.description ?? ipInstance.name).replace(/domain/ig,''),
				ipInstances: ["PLLCLK",ipInstance.name],
				algorithm: "everythingBetween",
				frequencyLabels: FreqLabels,
			}
		}
	}

	let All_Instances = _.map(system.deviceData.clockTree.ipInstances, (i) => i.name)

	let CPUCLK_Entries = ["PLLSYSCLK", "CPU", "CPUCLK", "SYSCLK", "CPUCLK_domain"]

	var device = system.deviceData.device

	var brokenConnection1

	switch(device)
	{
		case 'F29H85x':
			brokenConnection1 = Support.F29H85x_bc
			break
	}

	if(device == "F29H85x")
	{
		var myipInstance1 = ["CPU1_CPUCLK_domain", "CPU2_CPUCLK_domain", "CPU3_CPUCLK_domain"]
		var myipInstance2 = ["CPU1_CPUCLK", "CPU2_CPUCLK", "CPU3_CPUCLK"]
	}
	else
	{
		var myipInstance1 = ["CPUCLK"]
		var myipInstance2 = ["CPUCLK"]
	}


	All_Instances = All_Instances.concat(FreqLabels)

	//Beta version: reasonableLayout is not used in beta version of clocktree tool
	//Purpose: Used for customized Layout. 
	const reasonableLayout = {
		"INTOSC1"			: { layer: 0, position: 1 },
		"INTOSC2"			: { layer: 0, position: 2 },
		"XTAL"				: { layer: 0, position: 3 },
		"OSCCLKSRCSEL"		: { layer: 1, position: 0 },
		"PLL_IMULT"			: { layer: 4, position: 1 },
		"PLL_FMULT"			: { layer: 4, position: 2 },
		"PLL_ADD"			: { layer: 5, position: 2 },
		"PLL_ODIV"			: { layer: 6, position: 2 },
		"PLL_Group"			: { layer: 3, position: 3 },
	};

	
		
	var tree = [
		{
			displayName: "Complete ClockTree",
			entries: [
				{
					displayName: "ClockTree",
					ipInstances: All_Instances,
					frequencyLabels: FreqLabels,
					brokenConnections: brokenConnection1,
				},
			],
		}, 
	]
	// checking the deviceData to see if the device has AUXPLL 
	var AUXPLLDevice = (system.deviceData.clockTree.ipInstances).filter(function(ipInst) {
		return ipInst.name === "AUXCLKDIVSEL";
	  });
	if(AUXPLLDevice.length > 0){
			tree = tree.concat ([
				{
					displayName: "PLLs",
					entries: [
						{
							displayName: "System PLL",
							ipInstances: ["CPU1CLK", "CPU2CLK", "CPU3CLK"],
							frequencyLabels: FreqLabels,
							algorithm: "fanIn"
						},
						{
							displayName: "Auxillary PLL",
							ipInstances: ["AUXPLLCLK"],
							frequencyLabels: FreqLabels,
							algorithm: "fanIn"
						},
					],
				}
			])
	}
		
	tree = tree.concat ([
		{
		displayName: "Clock domain view",
		entries: _.chain(system.deviceData.clockTree.ipInstances)
			.filter((ipInstance) => _.endsWith(ipInstance.name, "domain"))
			.map(defaultView)
			.value(),
		}
	]);

	const views = [
		{
			name: "/driverlib/clocktree/summaryView.xdt",
			displayName: "Clock Tree Summary",
			viewType: "markdown"
		}
	];

	exports = {
		// topModules: [{
		// 	displayName: "Modules",
		// 	modules: ["/modules/basic.js"],
		// }],
		displayName: "ClockTree Tool",
		clockTree: {
			typeMap,
			tree,
		},
		views,
		templates: [
			{
				name: "/driverlib/clocktree/clocktree.h.xdt",
		     	outputPath: "clocktree.h",
				// alwaysRun: true,
			 	alwaysRun: !(Common.isAllocationSetupMode()),
			 	ignoreErrors: false 
			},
		],
	};
}
else if ("CPU2" === system.context) //"CPU2" === system.context
{
	exports = {
		displayName: "ClockTree Tool",
		templates: [
			{
				name: "/driverlib/clocktree/clocktree_cpu2.h.xdt",
		     	outputPath: "clocktree.h",
			 	alwaysRun: true,
			 	ignoreErrors: false 
			},
		]
	};
}
else if ("CPU3" === system.context) //"CPU3" === system.context
{
	exports = {
		displayName: "ClockTree Tool",
		templates: [
			{
				name: "/driverlib/clocktree/clocktree_cpu3.h.xdt",
		     	outputPath: "clocktree.h",
			 	alwaysRun: true,
			 	ignoreErrors: false 
			},
		]
	};
}
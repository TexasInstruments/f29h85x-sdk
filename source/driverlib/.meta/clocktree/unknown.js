const { getDefaultValue } = system.getScript("./defaultValue.js");

exports = {
	displayName: "Unknown",
	//longDescription: "Here is the long description",
	config: [],
	extendConfig: ({ $ipInstance }) => 
	{
		const source = _.first($ipInstance.inPins);
		var names = ''
		//console.log($ipInstance)
		//console.log($ipInstance.modulePins)
		const pinConfig = _.map($ipInstance.outPins, (pin) => 
		({
			name: pin.name,
			displayName: pin.displayName,
			description: pin.description,
			longDescription: $ipInstance.inPins.toString(),
			default: 0,
			getValue: (inst) => source ? inst[source.name] : getDefaultValue(inst),
			hidden: true
			// shape: "MediumSquare",
		}));
		for(var pin of $ipInstance.modulePins){
			names += pin.name +', '
		}

		if (names.endsWith(", "))
		{
			names = names.slice(0, -2);
		}

		if (names != "in")
		{
			pinConfig.push({
				name: "modules", 
				displayName: "Modules", 
				longDescription: "Connected modules to this signal: " + names,
				default: names, 
				getValue: (inst) => { return names },
			})
		}

		// if ($ipInstance.name == "CPU1")
		// {
		// 		pinConfig.push({
		// 		shape: "MediumSquare"
		// 	})
		// }

		if ($ipInstance.name == "PERx_CPU1CLK_GATE")
		{
				pinConfig.push({
				name: "cpu1clk_gate", 
				displayName: "CPU1CLK GATE", 
				default: "Click the hyper link for CPUCLK GATES", 
				getValue: (inst) => { return "Click the hyper link for CPUCLK GATES" },
			})
		}
		if ($ipInstance.name == "PERx_CPU2CLK_GATE")
		{
				pinConfig.push({
				name: "cpu2clk_gate", 
				displayName: "CPU2CLK GATE", 
				default: "Click the hyper link for CPUCLK GATES", 
				getValue: (inst) => { return "Click the hyper link for CPUCLK GATES" },
			})
		}
		if ($ipInstance.name == "PERx_CPU3CLK_GATE")
		{
				pinConfig.push({
				name: "cpu3clk_gate", 
				displayName: "CPU3CLK GATE", 
				default: "Click the hyper link for CPUCLK GATES", 
				getValue: (inst) => { return "Click the hyper link for CPUCLK GATES" },
			})
		}
		return pinConfig;
	},

	validate: (inst, { logInfo }) => {
		var sysctl = system.modules['/driverlib/sysctl.js']
		if (sysctl)
		{
			if (inst.cpu1clk_gate)
			{
				logInfo("For enabling peripherals, use the " + system.getReference(sysctl.$static, "enable_SYSCTL_PERIPH_CLK_TIMER0"), inst, "cpu1clk_gate")
			}
			if (inst.cpu2clk_gate)
			{
				logInfo("For enabling peripherals, use the " + system.getReference(sysctl.$static, "enable_SYSCTL_PERIPH_CLK_TIMER0"), inst, "cpu2clk_gate")
			}
			if (inst.cpu3clk_gate)
			{
				logInfo("For enabling peripherals, use the " + system.getReference(sysctl.$static, "enable_SYSCTL_PERIPH_CLK_TIMER0"), inst, "cpu3clk_gate")
			}
		}
	}
};
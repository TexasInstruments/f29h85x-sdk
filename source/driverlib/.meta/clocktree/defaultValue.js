exports = {
	displayName: "Default Clock Value",
	moduleStatic: {
		config: [{
			name: "valueType",
			default: "arrayRange",
			options: [{ name: "singleValue" }, { name: "arraySame" }, { name: "arrayRange" }],
			shouldBeAllocatedAsResource : true,
		},
		{
			name: "$assignedContext",
			hidden: true,
			options: [{name: "CPU1"}],
			default: "CPU1",
			readOnly: true
		}]
	},
	getDefaultValue: (inst) => {
		const valueType = system.modules["/clockTree/defaultValue.js"]?.$static.valueType ?? "arrayRange";
		if (inst.disable) {
			return valueType === "singleValue" ? 0 : [0, 0];
		}
		const name = inst.$name;
		switch (valueType) {
			case "singleValue":
				return _.size(name);
			case "arraySame":
				return [_.size(name), _.size(name)];
			case "arrayRange":
				return [_.size(name), _.size(name) + 1];
		}
	},
	shouldBeAllocatedAsResource : true,
}
exports = {
	displayName: "Multiplier",
	config: [
		{
			name: "$assignedContext",
			hidden: true,
			options: [{name: "CPU1"}],
			default: "CPU1",
			readOnly: true
		}
	],
	extendConfig: ({ $ipInstance }) => [
	{
		name: "Description",
		displayName: "Description",
		default: $ipInstance.description,
		readOnly: true,
	},
	{
		name: "InputValue",
		displayName: "Input Clock (MHz)",
		default: '',
		getValue: (inst) => {
			const value = inst[$ipInstance.inPins[0].name] + ' MHz';
			return value;
		}
	},
	{
		name: "multiplyValue",
		displayName: "Multiply Value",
		default: $ipInstance.resetValue,
		options: _.map($ipInstance.multiplyValues, (v) => ({ name: v, displayName: `X ${v}` })),
		shouldBeAllocatedAsResource : true
	},
	{
		name: $ipInstance.outPins[0].name,
		displayName: "Output Clock",
		default: 0,
		getValue: (inst) => {
			const value = inst[$ipInstance.inPins[0].name];
			return value * inst.multiplyValue;
		},
	}],
	shouldBeAllocatedAsResource : true
};

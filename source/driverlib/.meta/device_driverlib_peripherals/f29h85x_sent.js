let SENT_CRCType = [
	{ name: "SENT_CRC_RECOMMENDED", displayName: "Recommended CRC (J2716 2010 or newer spec)" },
	{ name: "SENT_CRC_ORIGINAL", displayName: "Original Legacy CRC (J2716 2007 spec)" },
]
let SENT_CRCWidth = [
	{ name: "SENT_CRC_4BIT", displayName: "4 bit CRC" },
	{ name: "SENT_CRC_6BIT", displayName: "6 bit CRC" },
	{ name: "SENT_CRC_8BIT", displayName: "8 bit CRC" },
]
let SENT_FIFOMode = [
	{ name: "SENT_FIFOMODE_MEMMAPPED", displayName: "The Timestamp, data0 and data1 data will be mapped directly to a memory." },
	{ name: "SENT_FIFOMODE_FIFO", displayName: "Receivers memory is in FIFO mode" },
]
let SENT_DataNibble = [
	{ name: "SENT_RX_DNIB1", displayName: "1 data nibble per-frame" },
	{ name: "SENT_RX_DNIB2", displayName: "2 data nibble per-frame" },
	{ name: "SENT_RX_DNIB3", displayName: "3 data nibble per-frame" },
	{ name: "SENT_RX_DNIB4", displayName: "4 data nibble per-frame" },
	{ name: "SENT_RX_DNIB5", displayName: "5 data nibble per-frame" },
	{ name: "SENT_RX_DNIB6", displayName: "6 data nibble per-frame" },
	{ name: "SENT_RX_DNIB7", displayName: "7 data nibble per-frame" },
	{ name: "SENT_RX_DNIB8", displayName: "8 data nibble per-frame" },
]
let SENT_RxCRC = [
	{ name: "SENT_RX_CRC_WITHOUT_STATUS", displayName: "CRC calculation without status" },
	{ name: "SENT_RX_CRC_WITH_STATUS", displayName: "CRC calculatin with status" },
]
let SENT_TriggerLevel = [
	{ name: "SENT_TRIGDISABLE", displayName: "Trigger disable" },
	{ name: "SENT_TRIGLEV1", displayName: "Trigger level 1" },
	{ name: "SENT_TRIGLEV2", displayName: "Trigger level 2" },
	{ name: "SENT_TRIGLEV3", displayName: "Trigger level 3" },
	{ name: "SENT_TRIGLEV4", displayName: "Trigger level 4" },
	{ name: "SENT_TRIGLEV5", displayName: "Trigger level 5" },
	{ name: "SENT_TRIGLEV6", displayName: "Trigger level 6" },
	{ name: "SENT_TRIGLEV7", displayName: "Trigger level 7" },
	{ name: "SENT_TRIGLEV8", displayName: "Trigger level 8" },
	{ name: "SENT_TRIGLEV9", displayName: "Trigger level 9" },
	{ name: "SENT_TRIGLEV10", displayName: "Trigger level 10" },
	{ name: "SENT_TRIGLEV11", displayName: "Trigger level 11" },
	{ name: "SENT_TRIGLEV12", displayName: "Trigger level 12" },
	{ name: "SENT_TRIGLEV13", displayName: "Trigger level 13" },
	{ name: "SENT_TRIGLEV14", displayName: "Trigger level 14" },
	{ name: "SENT_TRIGLEV15", displayName: "Trigger level 15" },
	{ name: "SENT_TRIGLEV16", displayName: "Trigger level 16" },
]
let SENT_Trigger = [
	{ name: "SENT_TRIGGER_DISABLE", displayName: "Trigger is disable" },
	{ name: "SENT_TRIGGER_BROADCAST", displayName: "Broadcast Channel Trigger Source" },
	{ name: "SENT_TRIGGER_SENSOR1", displayName: "Sensor 1 Trigger Source" },
	{ name: "SENT_TRIGGER_SENSOR2", displayName: "Sensor 2 Trigger Source" },
	{ name: "SENT_TRIGGER_SENSOR3", displayName: "Sensor 3 Trigger Source" },
	{ name: "SENT_TRIGGER_SENSOR4", displayName: "Sensor 4 Trigger Source" },
]
let SENT_DataNumber = [
	{ name: "SENT_RECEIVER_DATA0", displayName: "Receiver Data 0" },
	{ name: "SENT_RECEIVER_DATA1", displayName: "Receiver Data 1" },
]
let SENT_NibbleNumber = [
	{ name: "SENT_DATAX_NIB0", displayName: "DataX Nibble Number 0" },
	{ name: "SENT_DATAX_NIB1", displayName: "DataX Nibble Number 1" },
	{ name: "SENT_DATAX_NIB2", displayName: "DataX Nibble Number 2" },
	{ name: "SENT_DATAX_NIB3", displayName: "DataX Nibble Number 3" },
	{ name: "SENT_DATAX_NIB4", displayName: "DataX Nibble Number 4" },
	{ name: "SENT_DATAX_NIB5", displayName: "DataX Nibble Number 5" },
	{ name: "SENT_DATAX_NIB6", displayName: "DataX Nibble Number 6" },
	{ name: "SENT_DATAX_NIB7", displayName: "DataX Nibble Number 7" },
]
let SENT_Nibble = [
	{ name: "SENT_NO_NIBBLE", displayName: "No Nibble Selected" },
	{ name: "SENT_DATA_NIBBLE1", displayName: "Data Nibble 1" },
	{ name: "SENT_DATA_NIBBLE2", displayName: "Data Nibble 2" },
	{ name: "SENT_DATA_NIBBLE3", displayName: "Data Nibble 3" },
	{ name: "SENT_DATA_NIBBLE4", displayName: "Data Nibble 4" },
	{ name: "SENT_DATA_NIBBLE5", displayName: "Data Nibble 5" },
	{ name: "SENT_DATA_NIBBLE6", displayName: "Data Nibble 6" },
	{ name: "SENT_DATA_NIBBLE7", displayName: "Data Nibble 7" },
	{ name: "SENT_DATA_NIBBLE8", displayName: "Data Nibble 8" },
	{ name: "SENT_CRC_NIBBLE1", displayName: "CRC Nibble 1" },
	{ name: "SENT_CRC_NIBBLE2", displayName: "CRC Nibble 2" },
	{ name: "SENT_STATUS_NIBBLE", displayName: "Status Nibble" },
]
let SENT_Channel = [
	{ name: "SENT_BROADCAST_CHANNEL", displayName: "Broadcase Channel" },
	{ name: "SENT_SENSOR_1_CHANNEL", displayName: "Sensor 1" },
	{ name: "SENT_SENSOR_2_CHANNEL", displayName: "Sensor 2" },
	{ name: "SENT_SENSOR_3_CHANNEL", displayName: "Sensor 3" },
	{ name: "SENT_SENSOR_4_CHANNEL", displayName: "Sensor 4" },
]
let SENT_SensorNumber = [
	{ name: "SENT_SENSOR_1", displayName: "Sensor 1" },
	{ name: "SENT_SENSOR_2", displayName: "Sensor 2" },
	{ name: "SENT_SENSOR_3", displayName: "Sensor 3" },
	{ name: "SENT_SENSOR_4", displayName: "Sensor 4" },
]
let SENT_CompareNumber = [
	{ name: "SENT_MTP_CMP_1", displayName: "MTP Compare 1" },
	{ name: "SENT_MTP_CMP_2", displayName: "MTP Compare 2" },
	{ name: "SENT_MTP_CMP_3", displayName: "MTP Compare 3" },
	{ name: "SENT_MTP_CMP_4", displayName: "MTP Compare 4" },
	{ name: "SENT_MTP_CMP_5", displayName: "MTP Compare 5" },
	{ name: "SENT_MTP_CMP_6", displayName: "MTP Compare 6" },
	{ name: "SENT_MTP_CMP_7", displayName: "MTP Compare 7" },
	{ name: "SENT_MTP_CMP_8", displayName: "MTP Compare 8" },
	{ name: "SENT_MTP_CMP_9", displayName: "MTP Compare 9" },
]
let SENT_INT = [
	{ name: "SENT_INT_RFAST_S1DV", displayName: "Sensor 1 Fast channel" },
	{ name: "SENT_INT_RFAST_S2DV", displayName: "Sensor 2 Fast channel" },
	{ name: "SENT_INT_RFAST_S3DV", displayName: "Sensor 3 Fast channel" },
	{ name: "SENT_INT_RFAST_S4DV", displayName: "Sensor 4 Fast channel" },
	{ name: "SENT_INT_RSLOW_DV", displayName: "Slow channel data with" },
	{ name: "SENT_INT_RSLOW_CRCERR", displayName: "Slow channel data with" },
	{ name: "SENT_INT_RSLOW_FORMATERR", displayName: "Slow channel data with" },
	{ name: "SENT_INT_RFAST_S1CRCE", displayName: "Sensor 1 Fast channel data" },
	{ name: "SENT_INT_RFAST_S2CRCE", displayName: "Sensor 2 Fast channel data" },
	{ name: "SENT_INT_RFAST_S3CRCE", displayName: "Sensor 3 Fast channel data" },
	{ name: "SENT_INT_RFAST_S4CRCE", displayName: "Sensor 4 Fast channel data" },
	{ name: "SENT_INT_RFAST_S1FRME", displayName: "Sensor 1 Fast channel data" },
	{ name: "SENT_INT_RFAST_S2FRME", displayName: "Sensor 2 Fast channel data" },
	{ name: "SENT_INT_RFAST_S3FRME", displayName: "Sensor 3 Fast channel data" },
	{ name: "SENT_INT_RFAST_S4FRME", displayName: "Sensor 4 Fast channel data" },
	{ name: "SENT_INT_RTIMEOUT_S1ERR", displayName: "Sensor 1 timeout error" },
	{ name: "SENT_INT_RTIMEOUT_S2ERR", displayName: "Sensor 2 timeout error" },
	{ name: "SENT_INT_RTIMEOUT_S3ERR", displayName: "Sensor 3 timeout error" },
	{ name: "SENT_INT_RTIMEOUT_S4ERR", displayName: "Sensor 4 timeout error" },
	{ name: "SENT_INT_RFAST_SYNCERR25", displayName: "Fast channel sync pulse" },
	{ name: "SENT_INT_RFAST_SYNCERR", displayName: "Successive calibration" },
	{ name: "SENT_INT_FREQDRIFT_ERR", displayName: "Frequency drift error event" },
	{ name: "SENT_INT_RFIFO_TRIGGER", displayName: "FIFO trigger event" },
	{ name: "SENT_INT_RFIFO_OVFERR", displayName: "FIFO Overflow Error event" },
	{ name: "SENT_INT_RFIFO_UNDFERR", displayName: "FIFO Underflow Error event" },
	{ name: "SENT_INT_OVFTRIG_BCERR", displayName: "Broadcast channel overflow" },
	{ name: "SENT_INT_OVFTRIG_S1ERR", displayName: "Sensor 1 overflow trigger" },
	{ name: "SENT_INT_OVFTRIG_S2ERR", displayName: "Sensor 2 overflow trigger" },
	{ name: "SENT_INT_OVFTRIG_S3ERR", displayName: "Sensor 3 overflow trigger" },
	{ name: "SENT_INT_OVFTRIG_S4ERR", displayName: "Sensor 4 overflow trigger" },
]
module.exports = {
	SENT_CRCType: SENT_CRCType,
	SENT_CRCWidth: SENT_CRCWidth,
	SENT_FIFOMode: SENT_FIFOMode,
	SENT_DataNibble: SENT_DataNibble,
	SENT_RxCRC: SENT_RxCRC,
	SENT_TriggerLevel: SENT_TriggerLevel,
	SENT_Trigger: SENT_Trigger,
	SENT_DataNumber: SENT_DataNumber,
	SENT_NibbleNumber: SENT_NibbleNumber,
	SENT_Nibble: SENT_Nibble,
	SENT_Channel: SENT_Channel,
	SENT_SensorNumber: SENT_SensorNumber,
	SENT_CompareNumber: SENT_CompareNumber,
	SENT_INT: SENT_INT,
}

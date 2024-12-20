let UART_INT = [
	{ name: "UART_INT_DMATX", displayName: "DMA TX interrupt" },
	{ name: "UART_INT_DMARX", displayName: "DMA RX interrupt" },
	{ name: "UART_INT_9BIT", displayName: "9-bit address match interrupt" },
	{ name: "UART_INT_OE", displayName: "Overrun Error Interrupt Mask" },
	{ name: "UART_INT_BE", displayName: "Break Error Interrupt Mask" },
	{ name: "UART_INT_PE", displayName: "Parity Error Interrupt Mask" },
	{ name: "UART_INT_FE", displayName: "Framing Error Interrupt Mask" },
	{ name: "UART_INT_RT", displayName: "Receive Timeout Interrupt Mask" },
	{ name: "UART_INT_TX", displayName: "Transmit Interrupt Mask" },
	{ name: "UART_INT_RX", displayName: "Receive Interrupt Mask" },
]
let UART_CONFIG = [
	{ name: "UART_CONFIG_WLEN_8", displayName: "8 bit data" },
	{ name: "UART_CONFIG_WLEN_7", displayName: "7 bit data" },
	{ name: "UART_CONFIG_WLEN_6", displayName: "6 bit data" },
	{ name: "UART_CONFIG_WLEN_5", displayName: "5 bit data" },
	{ name: "UART_CONFIG_STOP_ONE", displayName: "1 stop bit" },
	{ name: "UART_CONFIG_STOP_TWO", displayName: "2 stop bits" },
	{ name: "UART_CONFIG_PAR_NONE", displayName: "No parity" },
	{ name: "UART_CONFIG_PAR_EVEN", displayName: "Even parity" },
	{ name: "UART_CONFIG_PAR_ODD", displayName: "Odd parity" },
	{ name: "UART_CONFIG_PAR_ONE", displayName: "Parity bit is one" },
	{ name: "UART_CONFIG_PAR_ZERO", displayName: "Parity bit is zero" },
	{ name: "UART_CONFIG_WLEN_MASK", displayName: "Mask for extracting wordlength" },
	{ name: "UART_CONFIG_STOP_MASK", displayName: "Mask for extracting stop bits" },
	{ name: "UART_CONFIG_PAR_MASK", displayName: "Mask for extracting parity" },
]
let UART_FIFO_TX = [
	{ name: "UART_FIFO_TX1_8", displayName: "Transmit interrupt at 1/8 Full" },
	{ name: "UART_FIFO_TX2_8", displayName: "Transmit interrupt at 1/4 Full" },
	{ name: "UART_FIFO_TX4_8", displayName: "Transmit interrupt at 1/2 Full" },
	{ name: "UART_FIFO_TX6_8", displayName: "Transmit interrupt at 3/4 Full" },
	{ name: "UART_FIFO_TX7_8", displayName: "Transmit interrupt at 7/8 Full" },
]
let UART_FIFO_RX = [
	{ name: "UART_FIFO_RX1_8", displayName: "Receive interrupt at 1/8 Full" },
	{ name: "UART_FIFO_RX2_8", displayName: "Receive interrupt at 1/4 Full" },
	{ name: "UART_FIFO_RX4_8", displayName: "Receive interrupt at 1/2 Full" },
	{ name: "UART_FIFO_RX6_8", displayName: "Receive interrupt at 3/4 Full" },
	{ name: "UART_FIFO_RX7_8", displayName: "Receive interrupt at 7/8 Full" },
]
let UART_DMA = [
	{ name: "UART_DMA_ERR_RXSTOP", displayName: "Stop DMA receive if UART error" },
	{ name: "UART_DMA_TX", displayName: "Enable DMA for transmit" },
	{ name: "UART_DMA_RX", displayName: "Enable DMA for receive" },
]
let UART_RXERROR = [
	{ name: "UART_RXERROR_OVERRUN", displayName: "RXERROR OVERRUN" },
	{ name: "UART_RXERROR_BREAK", displayName: "RXERROR BREAK" },
	{ name: "UART_RXERROR_PARITY", displayName: "RXERROR PARITY" },
	{ name: "UART_RXERROR_FRAMING", displayName: "RXERROR FRAMING" },
]
let UART_TXINT_MODE = [
	{ name: "UART_TXINT_MODE_FIFO", displayName: "Trigger based on tx FIFOlevel" },
	{ name: "UART_TXINT_MODE_EOT", displayName: "Trigger when transmitter idle" },
]
let UART_CLK_DIVIDER = [
	{ name: "UART_CLK_DIVIDER", displayName: "DIVIDER" },
]
let UART_CLK_IRLPBAUD16 = [
	{ name: "UART_CLK_IRLPBAUD16", displayName: "IRLPBAUD16" },
]
let UART_SIR_LOWPOWER = [
	{ name: "UART_SIR_LOWPOWER_DISABLE", displayName: "Disable SIR Low-Power mode" },
	{ name: "UART_SIR_LOWPOWER_ENABLE", displayName: "Enable SIR Low-Power mode" },
]
module.exports = {
	UART_INT: UART_INT,
	UART_CONFIG: UART_CONFIG,
	UART_FIFO_TX: UART_FIFO_TX,
	UART_FIFO_RX: UART_FIFO_RX,
	UART_DMA: UART_DMA,
	UART_RXERROR: UART_RXERROR,
	UART_TXINT_MODE: UART_TXINT_MODE,
	UART_CLK_DIVIDER: UART_CLK_DIVIDER,
	UART_CLK_IRLPBAUD16: UART_CLK_IRLPBAUD16,
	UART_SIR_LOWPOWER: UART_SIR_LOWPOWER,
}

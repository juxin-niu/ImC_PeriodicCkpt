
#include <ImC/analysis/uart2target.h>


void uart2target_init()
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(UART_TX_PORT, UART_TX_PIN, UART_TX_FUNCTION);

    EUSCI_A_UART_initParam param = {0};
    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;   /* Use SMCLK in 1MHz */
    param.parity = EUSCI_A_UART_NO_PARITY;                      /* No parity check */
    param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;               /* LSB first */
    param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;         /* 1 stop bit */
    param.uartMode = EUSCI_A_UART_MODE;
    param.clockPrescalar = 8;
    param.firstModReg = 0;
    param.secondModReg = 214;
    param.overSampling = 0;

    EUSCI_A_UART_init(UART_BASEADDR, &param);       // Initialize UART.

    EUSCI_A_UART_enable(UART_BASEADDR);             // Enable UART.
}

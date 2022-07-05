
#include <ImC/analysis/uart2target.h>

void uart2target_init()
{

    EUSCI_A_UART_initParam param = {0};
    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;   /* Use SMCLK */
    param.parity = EUSCI_A_UART_NO_PARITY;                      /* No parity check */
    param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;               /* LSB first */
    param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;         /* 1 stop bit */
    param.uartMode = EUSCI_A_UART_MODE;

    param.clockPrescalar = CLK_PRESCALAR_USED;
    param.firstModReg = FIRST_MODE_REG_USED;
    param.secondModReg = SECOND_MODE_REG_USED;
    param.overSampling = OVER_SAMP_USED;

    if (STATUS_FAIL == EUSCI_A_UART_init(UART_BASEADDR, &param)) {
        while (1){}
    }

    EUSCI_A_UART_enable(UART_BASEADDR);             // Enable UART.
     GPIO_setAsPeripheralModuleFunctionOutputPin(UART_TX_PORT, UART_TX_PIN, UART_TX_FUNCTION);
}

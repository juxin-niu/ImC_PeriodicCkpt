
#include <ImC/target_spec.h>
#include "Imc/analysis/io.h"

#include <stdio.h>
#include <string.h>

int fputc(int _c, register FILE *_fp)
{
  EUSCI_A_UART_transmitData(EUSCI_A0_BASE, (unsigned char) _c );
  return((unsigned char)_c);
}

int fputs(const char *_ptr, register FILE *_fp)
{
  unsigned int i, len;

  len = strlen(_ptr);

  for(i=0 ; i<len ; i++)
  {
    EUSCI_A_UART_transmitData(EUSCI_A0_BASE, (unsigned char) _ptr[i]);
  }

  return len;
}

/*
 * Board will use eZ-FET (backchannel UART) to communication with host.
 * The backchannel UART is the UART on eUSCI_A0.
 *                              ---- LaunchPad Development Kit 2.2.4
 */
void io_uart_init()
{
    EUSCI_A_UART_initParam param = {0};
    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;   /* Use SMCLK */
    param.parity = EUSCI_A_UART_NO_PARITY;                      /* No parity check */
    param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;               /* LSB first */
    param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;         /* 1 stop bit */
    param.uartMode = EUSCI_A_UART_MODE;

    /* http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
     * BAUD-RATE IS SET 115200 BPS. A brief table is as follow:
     *     clockFrequency ||  clockPrescalar | firstModReg | secondModReg | overSampling
     *     1MHz           ||  8              | 0           | 214          | 0
     *     4MHz           ||  2              | 2           | 187          | 1
     *     8MHz           ||  4              | 5           | 85           | 1
     *  */
    param.clockPrescalar = 8;
    param.firstModReg = 0;
    param.secondModReg = 214;
    param.overSampling = 0;

    EUSCI_A_UART_init(EUSCI_A0_BASE, &param);

    /* Selecting UART functions for TXD */
    GPIO_setAsOutputPin(2, 0);
    GPIO_setAsPeripheralModuleFunctionInputPin(2, 0, GPIO_SECONDARY_MODULE_FUNCTION); // TXD
    GPIO_setAsPeripheralModuleFunctionInputPin(2, 1, GPIO_SECONDARY_MODULE_FUNCTION); // TXD

    EUSCI_A_UART_enable(EUSCI_A0_BASE);
}

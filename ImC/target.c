
#include <stdint.h>
#include <ImC/target_spec.h>
#include "Imc/target.h"

void power_on_init()
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watch-dog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    /* Terminate all GPIO pins to Output LOW to minimize power consumption */
    GPIO_setOutputLowOnPin(GPIO_PORT_PA, GPIO_PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_PB, GPIO_PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_PC, GPIO_PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_PD, GPIO_PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_PE, GPIO_PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_PF, GPIO_PIN_ALL16);

    GPIO_setAsOutputPin(GPIO_PORT_PA, GPIO_PIN_ALL16);
    GPIO_setAsOutputPin(GPIO_PORT_PB, GPIO_PIN_ALL16);
    GPIO_setAsOutputPin(GPIO_PORT_PC, GPIO_PIN_ALL16);
    GPIO_setAsOutputPin(GPIO_PORT_PD, GPIO_PIN_ALL16);
    GPIO_setAsOutputPin(GPIO_PORT_PE, GPIO_PIN_ALL16);
    GPIO_setAsOutputPin(GPIO_PORT_PF, GPIO_PIN_ALL16);
}


void clock_sys_init()
{
    CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_0);

    CS_initClockSignal(CS_MCLK,   CS_DCOCLK_SELECT,   CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK,  CS_DCOCLK_SELECT,   CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_ACLK,   CS_VLOCLK_SELECT,   CS_CLOCK_DIVIDER_1);

    CS_turnOffLFXT();
}

void dma_init()
{
    DMA_initParam DMAInitParam = {0};
    DMAInitParam.channelSelect = DMA_CHANNEL_0;
    DMAInitParam.transferModeSelect = DMA_TRANSFER_REPEATED_BLOCK;
    DMAInitParam.transferUnitSelect = DMA_SIZE_SRCWORD_DSTWORD;
    DMAInitParam.triggerSourceSelect = DMA_TRIGGERSOURCE_0;
    DMAInitParam.triggerTypeSelect = DMA_TRIGGER_RISINGEDGE;

    DMA_init(&DMAInitParam);

    /* Source address is incremented */
    HWREG16(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0CTL) &= ~(DMASRCINCR_3);
    HWREG16(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0CTL) |= DMA_DIRECTION_INCREMENT;

    /* Destination address is incremented */
    HWREG16(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0CTL) &= ~(DMADSTINCR_3);
    HWREG16(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0CTL) |= (DMA_DIRECTION_INCREMENT << 2);

}


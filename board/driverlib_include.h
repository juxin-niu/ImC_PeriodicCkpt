
#ifndef BOARD_DRIVERLIB_INCLUDE_H_
#define BOARD_DRIVERLIB_INCLUDE_H_

#if defined(__MSP430FR5969__) || defined(__MSP430FR5994__)
    #include <lib/driverlib_MSP430FR5xx_6xx/driverlib.h>
#elif defined(__MSP430FR2433__)
    #include <lib/driverlib_MSP430FR2xx_4xx/driverlib.h>
#else
#error "ERROR: UNSUPPORTED MSP TARGET!"
#endif

#endif /* BOARD_DRIVERLIB_INCLUDE_H_ */

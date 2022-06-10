
#ifndef IMC_TARGET_SPEC_H_
#define IMC_TARGET_SPEC_H_

#if defined(__MSP430FR5969__) || defined(__MSP430FR5994__)
    #include <lib/driverlib_MSP430FR5xx_6xx/driverlib.h>
#elif defined(__MSP430FR2433__)
    #include <lib/driverlib_MSP430FR2xx_4xx/driverlib.h>
#else
#error "ERROR: UNSUPPORTTED MSP TARGET!"
#endif


#if defined(__MSP430FR5994__) || defined(__MSP430FR2433__)
    #define LED_RED_PORT        GPIO_PORT_P1
    #define LED_RED_PIN         GPIO_PIN0
    #define LED_GREEN_PORT      GPIO_PORT_P1
    #define LED_GREEN_PIN       GPIO_PIN1
#elif defined(__MSP430FR5969__)
    #define LED_RED_PORT        GPIO_PORT_P4
    #define LED_RED_PIN         GPIO_PIN6
    #define LED_GREEN_PORT      GPIO_PORT_P1
    #define LED_GREEN_PIN       GPIO_PIN0
#else
#error "ERROR: UNSUPPORTTED MSP TARGET!"
#endif

#if defined(__MSP430FR5969__)
    #define TESTBENCH_START_PORT    GPIO_PORT_P1
    #define TESTBENCH_START_PIN     GPIO_PIN4
    #define TESTBENCH_FINISH_PORT   GPIO_PORT_P1
    #define TESTBENCH_FINISH_PIN    GPIO_PIN5
#elif defined(__MSP430FR5994__)

#elif defined(__MSP430FR2433__)

#endif

#endif /* IMC_TARGET_SPEC_H_ */

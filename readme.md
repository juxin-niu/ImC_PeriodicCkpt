# ImC_PeriodicCkpt



> `__MSP430FR2433__`, `__MSP430FR5969__` and `__MSP430FR5994__` are macros imported by CCS by default to distinguish different development boards.



**Switch from MSP430FR2433 to MSP430FR5xxx**

1. Exclude `CCS_PROJECT/lib/driverlib_MSP430FR2xx_4xx` from build.
2. Include `CCS_PROJECT/lib/driverlib_MSP430FR5xx_6xx` from build.
3. Change Device to `MSP430FR5xxx` (`Project Explorer -> Properties -> General(Project) -> Device` ).

**Switch from MSP430FR5xxx to MSP430FR2433**

1. Exclude `CCS_PROJECT/lib/driverlib_MSP430FR5xx_6xx` from build.
2. Include `CCS_PROJECT/lib/driverlib_MSP430FR2xx_3xx` from build.
3. Change Device to `MSP430FR2433` (`Project Explorer -> Properties -> General(Project) -> Device` ).



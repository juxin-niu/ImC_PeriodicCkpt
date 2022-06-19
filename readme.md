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

**Change Working Clock Frequency**

At `CCS_PROJECT/ImC/target.h`:

```c
#define WORKING_FREQUENCY_IN_MHZ    8
//!                                -1 (in 1MHz)
//!                                -2 (in 2MHz)
//!                                -4 (in 4MHz)
//!                                -8 (in 8MHz)
```

**Change Backup Scheme**

At `CCS_PROJECT/ImC/scheduler.h`:

```c
#define BACKUP_USE_DMA
//!    -BACKUP_USE_CPU
//!    -BACKUP_USE_DMA
```


###  BETA v0.1  ( только пока  HC32L110 )

###  Библиотека примеров - HC32L110   VSCode + EIDE + PyOCD (JLink,OpenOCD)

Все примеры для контроллеров серии HC32 представлены для  Keil и IAR.<br>
Попытка сделать минимальную настройку для работы.

Для данных контроллеров нет привычных CMSIS как на STM32<br>
Описание регистров и перефирии отличается.<br>
Также нет библиотек LL и HAL, а есть собственная DDL ( здесь не приведена )<br>
Пока только работа на регистрах.

###  HC32L110
```
         Cortex-M0+ 32MHz, 1.8-5.5 V
Comm:    2xUART, LPUART, SPI, I2C
Timers:  Base - 3, Adv - 3, LP - 1, PCA - 1(5ch), RTC, WDT
Analog:  ADC 12bit, Comp - 2, LVD, BGR Vref, TempSensor

выпускается в 7 модификациях
  HC32L110B4PA  - tssop-14;      16K Flash; 2K RAM
  HC32L110C4PA  - tssop-20;      16K Flash; 2K RAM
  HC32L110C4UA  - qfn-20(3x3);   16K Flash; 2K RAM
  HC32L110B6PA  - tssop-14;      32K Flash; 4K RAM
  HC32L110B6YA  - csp-16;        32K Flash; 4K RAM
  HC32L110C6PA  - tssop-20;      32K Flash; 4K RAM
  HC32L110C6PA  - qfn-20(3x3);   32K Flash; 4K RAM

особенности
- нет DMA
- внутренний RCL(LSI) - 2 константы 32.768, 38.4 kHz   (min 19.7)
- внутренний RCH(HSI) - 5 констант  4, 8, 16, 22.12, 24 MHz  (min 2.3)
- 32МГц от внешнего кварца или генератора
- HCLK  от  RCL, XTL(LSE), RCH, XTH(HSE)
- на всех корпусах есть возможность подключения и XTH и XTL
  причем независимо и одновременно (или в виде входа только - настраивается)

потребление
- при LPrun ( while(1) perif - off ) при снижении частоты HCLK - потребление снижается
  от  8-9 мкА  при частоте 19.7 kHz  ( RCL_TRIM=0, RCL=19.7 kHz, HCLK=RCL=19.7 kHz )
  до  1-2 мкА  при частоте 308 Hz  ( RCL_TRIM=0, RCL=19.7 kHz, HCLK=RCL/64=308 Hz )

- при LPrun ( while(1); GPIO - on; HCLK out to pin )  
  25 мкА  при частоте 19.7 kHz  (RLCTRIM=0, RLC=19.7 kHz, HCLK=RLC=19.7 kHz)

- DeepSleep ( LPTIM - on; GPIO - on; HCLK - out to pin )
  1.2 мкА - HCLK = 308 Hz; RCL = 19.7 kHz
  1.5 мкА - HCLK = 616 Hz; RCL = 19.7 kHz  
```

###  Планируется

Также планируется поддержка HC32L130, HC32L072
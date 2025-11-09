        .syntax unified  

        
#ifndef   __SUPPORT_RESET_HALT_AFTER_BTL
  #define __SUPPORT_RESET_HALT_AFTER_BTL  1
#endif
        
/*********************************************************************
*
*       Macros
*
**********************************************************************
*/
//
// Just place a vector (word) in the table
//
.macro VECTOR Name=
        .section .vectors, "a"
        .word \Name
.endm
//
// Declare an interrupt handler
//
.macro ISR_HANDLER Name=
        //
        // Insert vector in vector table
        //
        .section .vectors, "a"
        .word \Name
        //
        // Insert dummy handler in init section
        //
        .section .init.\Name, "ax"
        .thumb_func
        .weak \Name
        .balign 2
\Name:
        1: b 1b   // Endless loop
        END_FUNC \Name
.endm

//
// Place a reserved vector in vector table
//
.macro ISR_RESERVED
        .section .vectors, "a"
        .word 0
.endm

//
// Mark the end of a function and calculate its size
//
.macro END_FUNC name
        .size \name,.-\name
.endm

/***************************Vector Table*****************************/
        .section .vectors, "a"
        .code 16
        .balign 4
        .global _vectors
_vectors:
        VECTOR __stack_end__
        VECTOR Reset_Handler
        ISR_HANDLER NMI_Handler
        VECTOR HardFault_Handler
        ISR_RESERVED
        ISR_RESERVED
        ISR_RESERVED
        ISR_RESERVED
        ISR_RESERVED
        ISR_RESERVED
        ISR_RESERVED
        ISR_HANDLER SVC_Handler
        ISR_RESERVED
        ISR_RESERVED
        ISR_HANDLER PendSV_Handler
        ISR_HANDLER SysTick_Handler

        ISR_HANDLER PORTA_IRQHandler
        ISR_HANDLER PORTB_IRQHandler
        ISR_HANDLER PORTC_IRQHandler
        ISR_HANDLER PORTD_IRQHandler
        ISR_HANDLER DMAC_IRQHandler
        ISR_HANDLER TIM3_IRQHandler
        ISR_HANDLER UART0_IRQHandler
        ISR_HANDLER UART1_IRQHandler
        ISR_HANDLER LPUART0_IRQHandler
        ISR_HANDLER LPUART1_IRQHandler
        ISR_HANDLER SPI0_IRQHandler
        ISR_HANDLER SPI1_IRQHandler
        ISR_HANDLER I2C0_IRQHandler
        ISR_HANDLER I2C1_IRQHandler
        ISR_HANDLER TIM0_IRQHandler
        ISR_HANDLER TIM1_IRQHandler
        ISR_HANDLER TIM2_IRQHandler
        ISR_HANDLER LPTIM_IRQHandler
        ISR_HANDLER TIM4_IRQHandler
        ISR_HANDLER TIM5_IRQHandler
        ISR_HANDLER TIM6_IRQHandler
        ISR_HANDLER PCA_IRQHandler
        ISR_HANDLER WDT_IRQHandler
        ISR_HANDLER RTC_IRQHandler
        ISR_HANDLER ADC_IRQHandler
        ISR_HANDLER PCNT_IRQHandler
        ISR_HANDLER VC0_IRQHandler
        ISR_HANDLER VC1_IRQHandler
        ISR_HANDLER LVD_IRQHandler
        ISR_HANDLER LCD_IRQHandler
        ISR_HANDLER FLASH_RAM_IRQHandler
        ISR_HANDLER CLKTRIM_IRQHandler

        .section .vectors, "a"
        .size _vectors, .-_vectors
_vectors_end:

/*************************Global functions***************************/

/*********************************************************************
*       Reset_Handler
*/
        .global reset_handler
        .global Reset_Handler
        .equ reset_handler, Reset_Handler
        .section .init.Reset_Handler, "ax"
        .balign 2
        .thumb_func
Reset_Handler:
#if __SUPPORT_RESET_HALT_AFTER_BTL != 0
        movs    R0, #8
        ldr     R0, [R0]
        nop
        nop
#endif
IAR_STARTUP_CODE_START:
        // reset NVIC if in rom debug
        ldr     R0, =0x20000000
        ldr     R2, =0x0      // vector offset
        mov     R1, PC
        cmp     R1, R0
        bls     ROMCODE
        
        // ram code base address. 
        add     R2, R0,R2
ROMCODE:
        // reset Vector table address.
        ldr     R0, =0xE000ED08
        str     R2, [R0]
IAR_STARTUP_CODE_END:
        // Call SystemInit
        bl      SystemInit
        // Call runtime initialization, which calls main().
        bl      _start
END_FUNC Reset_Handler

        //
        // Weak only declaration of SystemInit enables Linker to replace bl SystemInit with a NOP,
        // when there is no strong definition of SystemInit.
        //
        .weak SystemInit

/*********************************************************************
*       HardFault_Handler
*/
        .weak HardFault_Handler
        .section .init.HardFault_Handler, "ax"
        .balign 2
        .thumb_func
HardFault_Handler:
        b       .
END_FUNC HardFault_Handler

/*************************** End of file ****************************/

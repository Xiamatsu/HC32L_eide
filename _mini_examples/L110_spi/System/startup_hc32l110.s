/*
;*******************************************************************************
; Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
;
; This software is owned and published by:
; Huada Semiconductor Co.,Ltd ("HDSC").
;
; BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
; BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
;
; This software contains source code for use with HDSC
; components. This software is licensed by HDSC to be adapted only
; for use in systems utilizing HDSC components. HDSC shall not be
; responsible for misuse or illegal use of this software for devices not
; supported herein. HDSC is providing this software "AS IS" and will
; not be responsible for issues arising from incorrect user implementation
; of the software.
;
; Disclaimer:
; HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
; REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
; ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
; WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
; WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
; WARRANTY OF NONINFRINGEMENT.
; HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
; NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
; LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
; LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
; INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
; INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
; SAVINGS OR PROFITS,
; EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
; YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
; INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
; FROM, THE SOFTWARE.
;
; This software may be replicated in part or whole for the licensed use,
; with the restriction that this Disclaimer and Copyright notice must be
; included with each copy of this software, whether used in part or whole,
; at all times.
;/
*/
/*****************************************************************************/
/*  Startup for GCC                                                          */
/*  Version     V1.0                                                         */
/*  Date        2019-03-13                                                   */
/*  Target-mcu  HC32L110                                                     */
/*****************************************************************************/
/*  Version     V2.0                                                         */
/*  Date        2025-11-09                                                   */
/*****************************************************************************/

/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

                .syntax     unified
                .arch       armv6-m
                .cpu        cortex-m0plus
                .thumb


/*
;<h> Interrupt vector table start.
*/
                .section    .vectors, "a", %progbits
                .align      2
                .type       __Vectors, %object
                .globl      __Vectors
                .globl      __Vectors_End
                .globl      __Vectors_Size
__Vectors:
                .word       __StackTop                         /*     Top of Stack */
                .word       Reset_Handler                      /*     Reset Handler */
                .word       NMI_Handler                        /* -14 NMI Handler */
                .word       HardFault_Handler                  /* -13 Hard Fault Handler */
                .word       0                                  /*     Reserved */
                .word       0                                  /*     Reserved */
                .word       0                                  /*     Reserved */
                .word       0                                  /*     Reserved */
                .word       0                                  /*     Reserved */
                .word       0                                  /*     Reserved */
                .word       0                                  /*     Reserved */
                .word       SVC_Handler                        /*  -5 SVCall Handler */
                .word       0                                  /*     Reserved */
                .word       0                                  /*     Reserved */
                .word       PendSV_Handler                     /*  -2 PendSV Handler */
                .word       SysTick_Handler                    /*  -1 SysTick Handler */

                /* Interrupts */
                .word PORT0_IRQHandler
                .word PORT1_IRQHandler
                .word PORT2_IRQHandler
                .word PORT3_IRQHandler
                .word 0
                .word 0
                .word UART0_IRQHandler
                .word UART1_IRQHandler
                .word LPUART_IRQHandler
                .word 0
                .word SPI_IRQHandler
                .word 0
                .word I2C_IRQHandler
                .word 0
                .word TIM0_IRQHandler
                .word TIM1_IRQHandler
                .word TIM2_IRQHandler
                .word LPTIM_IRQHandler
                .word TIM4_IRQHandler
                .word TIM5_IRQHandler
                .word TIM6_IRQHandler
                .word PCA_IRQHandler
                .word WDT_IRQHandler
                .word RTC_IRQHandler
                .word ADC_IRQHandler
                .word 0
                .word VC0_IRQHandler
                .word VC1_IRQHandler
                .word LVD_IRQHandler
                .word 0
                .word EF_RAM_IRQHandler
                .word CLKTRIM_IRQHandler

__Vectors_End:
                .equ        __Vectors_Size, __Vectors_End - __Vectors
                .size       __Vectors, . - __Vectors
/*
;<h> Interrupt vector table end.
*/

/*
;<h> Reset handler start.
*/
                .section    .text.Reset_Handler
                .align      2
                .weak       Reset_Handler
                .type       Reset_Handler, %function
                .globl      Reset_Handler
Reset_Handler:
                /* Set stack top pointer. */
                ldr         r0, =__StackTop
                mov         sp ,r0
/* Single section scheme.
 *
 * The ranges of copy from/to are specified by following symbols
 *   __etext: LMA of start of the section to copy from. Usually end of text
 *   __data_start__: VMA of start of the section to copy to
 *   __data_end__: VMA of end of the section to copy to
 *
 * All addresses must be aligned to 4 bytes boundary.
 */
                /* Copy data from read only memory to RAM. */
CopyData:
                ldr         r1, =__etext
                ldr         r2, =__data_start__
                ldr         r3, =__data_end__

                subs        r3, r2
                ble         CopyLoopExit
CopyLoop:
                subs        r3, #4
                ldr         r0, [r1,r3]
                str         r0, [r2,r3]
                bgt         CopyLoop
CopyLoopExit:

/* This part of work usually is done in C library startup code.
 * Otherwise, define this macro to enable it in this startup.
 *
 * There are two schemes too.
 * One can clear multiple BSS sections. Another can only clear one section.
 * The former is more size expensive than the latter.
 *
 * Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
 * Otherwise define macro __STARTUP_CLEAR_BSS to choose the later.
 */
/* Single BSS section scheme.
 *
 * The BSS section is specified by following symbols
 *   __bss_start__: start of the BSS section.
 *   __bss_end__: end of the BSS section.
 *
 * Both addresses must be aligned to 4 bytes boundary.
 */
                /* Clear BSS section. */
ClearBss:
                ldr         r1, =__bss_start__
                ldr         r2, =__bss_end__

                movs        r0, 0
                subs        r2, r1
                ble         ClearLoopExit
ClearLoop:
                subs        r2, #4
                str         r0, [r1, r2]
                bgt         ClearLoop
ClearLoopExit:
                /* reset NVIC if in rom debug */
                ldr         r0, =0x20000000
                ldr         r2, =0x0
                movs        r1, #0
                add         r1, pc, #0
                cmp         r1, r0
                bls         Rom_Code
                /* ram code base address. */
                add         r2, r0, r2
Rom_Code:
                /* reset vector table address */
                ldr         r0, =0xE000ED08
                str         r2, [r0]
                /* Call the clock system initialization function. */
                bl          SystemInit
                /* Call static constructors */
                //bl          __libc_init_array
                /* Call the application's entry point. */
                bl          main
                bx          lr
                .size       Reset_Handler, . - Reset_Handler
/*
;<h> Reset handler end.
*/

/*
;<h> Default handler start.
*/
                .section    .text.Default_Handler, "ax", %progbits
                .align      2
Default_Handler:
                b           .
                .size       Default_Handler, . - Default_Handler
/*
;<h> Default handler end.
*/

/* Macro to define default exception/interrupt handlers.
 * Default handler are weak symbols with an endless loop.
 * They can be overwritten by real handlers.
 */
                .macro      Set_Default_Handler  Handler_Name
                .weak       \Handler_Name
                .thumb_set  \Handler_Name, Default_Handler
                .endm

/* Default exception/interrupt handler */

                Set_Default_Handler    NMI_Handler
                Set_Default_Handler    HardFault_Handler
                Set_Default_Handler    SVC_Handler
                Set_Default_Handler    PendSV_Handler
                Set_Default_Handler    SysTick_Handler

        		Set_Default_Handler    PORT0_IRQHandler
        		Set_Default_Handler    PORT1_IRQHandler
                Set_Default_Handler    PORT2_IRQHandler
                Set_Default_Handler    PORT3_IRQHandler
                Set_Default_Handler    UART0_IRQHandler
                Set_Default_Handler    UART1_IRQHandler
                Set_Default_Handler    LPUART_IRQHandler
                Set_Default_Handler    SPI_IRQHandler
                Set_Default_Handler    I2C_IRQHandler
                Set_Default_Handler    TIM0_IRQHandler
                Set_Default_Handler    TIM1_IRQHandler
                Set_Default_Handler    TIM2_IRQHandler
                Set_Default_Handler    LPTIM_IRQHandler
                Set_Default_Handler    TIM4_IRQHandler
                Set_Default_Handler    TIM5_IRQHandler
                Set_Default_Handler    TIM6_IRQHandler
                Set_Default_Handler    PCA_IRQHandler
                Set_Default_Handler    WDT_IRQHandler
                Set_Default_Handler    RTC_IRQHandler
                Set_Default_Handler    ADC_IRQHandler
                Set_Default_Handler    VC0_IRQHandler
                Set_Default_Handler    VC1_IRQHandler
                Set_Default_Handler    LVD_IRQHandler
                Set_Default_Handler    EF_RAM_IRQHandler
                Set_Default_Handler    CLKTRIM_IRQHandler

                .end

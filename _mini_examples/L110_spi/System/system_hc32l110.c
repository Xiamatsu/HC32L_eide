/******************************************************************************/
/** \file system_hc32l110.c
 **
 ** System clock initialization.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "base_types.h"
#include "hc32l110.h"
#include "system_hc32l110.h"

/**
 ******************************************************************************
 ** System Clock Frequency (Core Clock) Variable according CMSIS
 ******************************************************************************/
volatile uint32_t SystemCoreClock = 4000000;


//add clock source.
void SystemCoreClockUpdate (void) // Update SystemCoreClock variable
{
	SystemCoreClock = 24000000;
}

/**
 ******************************************************************************
 ** \brief  对MCU未引出IO端口进行默认配置.
 **
 ** \param  none
 ** \return none
 ******************************************************************************/
static void _HidePinInit(void)
{
#if !defined(HC32L110Cxxx)       //20PIN MCU	
    uint32_t tmpReg = M0P_CLOCK->PERI_CLKEN;
	
	M0P_CLOCK->PERI_CLKEN_f.GPIO = 1;
    
  #if defined(HC32L110Bxxx)	     //16PIN MCU
    M0P_GPIO->P0ADS &= 0x07;     ///< P03
	M0P_GPIO->P3ADS &= 0xE3;     ///< P32/P33/P34
	
    M0P_GPIO->P0DIR	|= 0xF8;     ///< P03
    M0P_GPIO->P3DIR	|= 0x1C;     ///< P32/P33/P34
	
	M0P_GPIO->P0PU  |= 0xF8;     ///< P03
	M0P_GPIO->P3PU  |= 0x1C;     ///< P32/P33/P34
    
  #endif
	  M0P_CLOCK->PERI_CLKEN = tmpReg;
#endif
}

/**
 ******************************************************************************
 ** \brief  Setup the microcontroller system. 
 **         Initialize the System and update the SystemCoreClock variable.
 **
 ** \param  none
 ** \return none
 ******************************************************************************/
void SystemInit(void)
{
    //hcr 24MHz manual trim.
	// set RCH = 24MHz
    M0P_CLOCK->RCH_CR_f.TRIM = (*((volatile uint16_t*) (0x00100C00ul)));
    while (!M0P_CLOCK->RCH_CR_f.STABLE);

    SystemCoreClockUpdate();
	  
	_HidePinInit();
}



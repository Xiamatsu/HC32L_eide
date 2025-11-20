#include <hc32l110.h>

void delay(uint32_t nTime);


void enable_GPIO_CLK(void) {
    M0P_CLOCK->PERI_CLKEN_f.GPIO = 1;    //  enable CLK to GPIO
}

void disable_GPIO_CLK(void) {
    M0P_CLOCK->PERI_CLKEN_f.GPIO = 0;    //  enable CLK to GPIO
}

void enable_MSO(void) {
    M0P_GPIO->P2ADS_f.P24 = 0;           //  not analog
    M0P_GPIO->P24_SEL = 3;               //  alternate HCLK_out
    M0P_GPIO->P2DIR_f.P24 = 0;           //  output
    M0P_GPIO->P2OD_f.P24 = 0;            //  PushPull ( not open drain )
    M0P_GPIO->P2PD_f.P24 = 0;            //  no Pull Down
    M0P_GPIO->P2PU_f.P24 = 0;            //  no Pull Up
    M0P_GPIO->P2DR_f.P24 = 0;            //  High speed

    M0P_GPIO->CTRL1_f.HCLK_SEL = 0;
    M0P_GPIO->CTRL1_f.HCLK_EN = 1;
}

void Change_HCLK_PRS(uint32_t k) {
	M0P_CLOCK->SYSCTRL2 = 0x5A5A;
	M0P_CLOCK->SYSCTRL2 = 0xA5A5;
	M0P_CLOCK->SYSCTRL0_f.HCLK_PRS = k;
}

void test_gpio(void) {
    M0P_CLOCK->PERI_CLKEN_f.GPIO = 1;    //  enable CLK to GPIO   

    M0P_GPIO->P3ADS_f.P34 = 0;           //  not analog
    M0P_GPIO->P34_SEL = 0;               //  not alternate  
    M0P_GPIO->P3DIR_f.P34 = 0;           //  output
    M0P_GPIO->P3OD_f.P34 = 0;            //  PushPull ( not open drain )
    M0P_GPIO->P3PD_f.P34 = 0;            //  no Pull Down 
    M0P_GPIO->P3PU_f.P34 = 0;            //  no Pull Up 
    M0P_GPIO->P3DR_f.P34 = 1;            //  Low speed 
    M0P_GPIO->P3OUT_f.P34 = 1;           //  out 1
    
	while (1) {
		delay(0x4000);
        M0P_GPIO->P3OUT_f.P34 = 0;           //  out 0
		delay(0x4000);
        M0P_GPIO->P3OUT_f.P34 = 1;           //  out 0
	}
}	

void delay(uint32_t nTime)  {
	volatile uint32_t count;

	count = nTime;
	while (count--);
}

void Clock_RCH_to_RCL(void) {
	//M0P_CLOCK->RCL_CR_f.TRIM = (*((volatile uint16_t*) (0x00100C22ul)));
	M0P_CLOCK->RCL_CR_f.TRIM = 1;
	M0P_CLOCK->RCL_CR_f.STARTUP = 1;  // 16 cycles
	M0P_CLOCK->SYSCTRL2 = 0x5A5A;
	M0P_CLOCK->SYSCTRL2 = 0xA5A5;
	M0P_CLOCK->SYSCTRL0_f.RCL_EN = 1;
	while (M0P_CLOCK->RCL_CR_f.STABLE == 0);
	M0P_CLOCK->SYSCTRL2 = 0x5A5A;
	M0P_CLOCK->SYSCTRL2 = 0xA5A5;
	M0P_CLOCK->SYSCTRL0_f.CLK_SW4_SEL = 2;
	M0P_CLOCK->SYSCTRL2 = 0x5A5A;
	M0P_CLOCK->SYSCTRL2 = 0xA5A5;
	M0P_CLOCK->SYSCTRL0_f.RCH_EN = 0;
}

void Clock_RCL_to_RCH(void) {
	//M0P_CLOCK->RCH_CR_f.TRIM = (*((volatile uint16_t*) (0x00100C08ul)));
	M0P_CLOCK->RCH_CR_f.TRIM = 1;
	M0P_CLOCK->SYSCTRL2 = 0x5A5A;
	M0P_CLOCK->SYSCTRL2 = 0xA5A5;
	M0P_CLOCK->SYSCTRL0_f.RCH_EN = 1;
	while (M0P_CLOCK->RCH_CR_f.STABLE == 0);
	M0P_CLOCK->SYSCTRL2 = 0x5A5A;
	M0P_CLOCK->SYSCTRL2 = 0xA5A5;
	M0P_CLOCK->SYSCTRL0_f.CLK_SW4_SEL = 0;
	M0P_CLOCK->SYSCTRL2 = 0x5A5A;
	M0P_CLOCK->SYSCTRL2 = 0xA5A5;
	M0P_CLOCK->SYSCTRL0_f.RCL_EN = 0;
}


void Disable_GPIO(void) {
    M0P_CLOCK->PERI_CLKEN_f.GPIO = 1;    //  enable CLK to GPIO

    // digital
    M0P_GPIO->P0ADS = 0x00;
    M0P_GPIO->P1ADS = 0x00;
    M0P_GPIO->P2ADS = 0x00;
	M0P_GPIO->P3ADS = 0x00;

    // output
    M0P_GPIO->P0DIR	= 0x00;
    M0P_GPIO->P1DIR	= 0x00;
    M0P_GPIO->P2DIR	= 0x00;
    M0P_GPIO->P3DIR	= 0x00;

	// push-pull
	M0P_GPIO->P0OD  = 0x00;
	M0P_GPIO->P1OD  = 0x00;
	M0P_GPIO->P2OD  = 0x00;
	M0P_GPIO->P3OD  = 0x00;

	// no pull-up
	M0P_GPIO->P0PU  = 0x00;
	M0P_GPIO->P1PU  = 0x00;
	M0P_GPIO->P2PU  = 0x00;
	M0P_GPIO->P3PU  = 0x00;

	// no pull-down
	M0P_GPIO->P0PD  = 0x00;
	M0P_GPIO->P1PD  = 0x00;
	M0P_GPIO->P2PD  = 0x00;
	M0P_GPIO->P3PD  = 0x00;

	// low speed
	M0P_GPIO->P0DR  = 0xFF;
	M0P_GPIO->P1DR  = 0xFF;
	M0P_GPIO->P2DR  = 0xFF;
	M0P_GPIO->P3DR  = 0xFF;

	// out = 1
	M0P_GPIO->P0OUT  = 0x00;
	M0P_GPIO->P1OUT  = 0x00;
	M0P_GPIO->P2OUT  = 0x00;
	M0P_GPIO->P3OUT  = 0x00;

	M0P_CLOCK->PERI_CLKEN_f.GPIO = 0;    //  disable CLK to GPIO
}

void Enable_LPTIM_CLK(void) {
	M0P_CLOCK->PERI_CLKEN_f.LPTIM = 1;
}

void Disable_LPTIM_CLK(void) {
	M0P_CLOCK->PERI_CLKEN_f.LPTIM = 0;
}

void Config_LPTIM(void) {
	M0P_LPTIMER->CR_f.GATE_P = 0;
	M0P_LPTIMER->CR_f.GATE = 0;
	M0P_LPTIMER->CR_f.TCK_SEL = 0;
	M0P_LPTIMER->CR_f.TOG_EN = 0;
	M0P_LPTIMER->CR_f.CT = 0;
	M0P_LPTIMER->CR_f.MD = 1;

	M0P_LPTIMER->CR_f.IE = 1;  //  enable Interrupt
	NVIC_EnableIRQ(17);

	while (M0P_LPTIMER->CR_f.WT_FLAG == 0);
	M0P_LPTIMER->ARR_f.ARR = 0xE000; //  count from 0xF800 to 0xFFFF  (2048)
	M0P_LPTIMER->CNT = 0xE000;
}

void Run_LPTIM(void) {
	M0P_LPTIMER->CR_f.TR = 1;  //  Run
}

void Stop_LPTIM(void) {
	M0P_LPTIMER->CR_f.TR = 0;  //  Run
}

void Config_SLEEP(void) {
	SCB->SCR = 4;
}

#define  xPrefix  1

int main(void) {
	Disable_GPIO();
	Clock_RCH_to_RCL();
	enable_GPIO_CLK();
	enable_MSO();
	delay(32000*xPrefix);
/*	Change_HCLK_PRS(1);
	delay(8000*xPrefix);
	Change_HCLK_PRS(2);
	delay(4000*xPrefix);
	Change_HCLK_PRS(3);
	delay(2000*xPrefix);
	Change_HCLK_PRS(4);
	delay(1000*xPrefix);
	Change_HCLK_PRS(5);
	delay(500*xPrefix); */
	Change_HCLK_PRS(6);
	//delay(500*xPrefix);

	Enable_LPTIM_CLK();
	Config_LPTIM();
	Config_SLEEP();
	while(1) {
		Enable_LPTIM_CLK();
		Run_LPTIM();
		__WFI();
		Stop_LPTIM();
		Disable_LPTIM_CLK();
		delay(100*xPrefix);
		Change_HCLK_PRS(2);
		delay(8000*xPrefix);
		Change_HCLK_PRS(5);
	}
}

void LPTIM_IRQHandler(void) {
	if (M0P_LPTIMER->IFR_f.TF == 1) {
		// clear interrupt flag
		M0P_LPTIMER->ICLR_f.TFC = 0;
	}
}


#include <hc32l110.h>

void delay(uint32_t nTime);

int main(void)
{
    M0P_CLOCK->PERI_CLKEN_f.GPIO = 1;    //  enable CLK to GPIO   
    M0P_GPIO->P3ADS_f.P34 = 0;           //  not analog
    M0P_GPIO->P34_SEL = 0;               //  not alternate  
    M0P_GPIO->P3DIR_f.P34 = 0;           //  output
    M0P_GPIO->P3OD_f.P34 = 0;            //  PushPull ( not open drain )
    M0P_GPIO->P3PD_f.P34 = 0;            //  no Pull Down 
    M0P_GPIO->P3PU_f.P34 = 0;            //  no Pull Up 
    M0P_GPIO->P3DR_f.P34 = 1;            //  Low speed 
    M0P_GPIO->P3OUT_f.P34 = 1;           //  out 1
    
	while (1)
	{
		delay(0x4000);
        M0P_GPIO->P3OUT_f.P34 = 0;           //  out 0
		delay(0x4000);
        M0P_GPIO->P3OUT_f.P34 = 1;           //  out 0
	}
}	

void delay(uint32_t nTime)
{
    volatile uint32_t count = nTime;
	while (count--);
}





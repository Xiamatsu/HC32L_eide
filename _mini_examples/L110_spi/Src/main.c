#include <hc32l110.h>

void delay(uint32_t nTime);

void SPI_Init() {
    //  Configure GPIO
    //  SCK  - P25  (sel=1)
    //  MOSI - P26  (sel=1)
    //  MISO - not used
    //  CS   - P24  (sel=1) (soft)

    M0P_CLOCK->PERI_CLKEN_f.GPIO = 1;    //  enable CLK to GPIO   
    // P24 - CS  as GPIO
    M0P_GPIO->P2ADS_f.P24 = 0;           //  not analog
    M0P_GPIO->P24_SEL = 0;               //  not alternate  
    M0P_GPIO->P2DIR_f.P24 = 0;           //  output
    M0P_GPIO->P2OD_f.P24 = 0;            //  PushPull ( not open drain )
    M0P_GPIO->P2PD_f.P24 = 0;            //  no Pull Down 
    M0P_GPIO->P2PU_f.P24 = 0;            //  Pull Up 
    M0P_GPIO->P2DR_f.P24 = 0;            //  High drive
    // P25 - SCK
    M0P_GPIO->P2ADS_f.P25 = 0;           //  not analog
    M0P_GPIO->P25_SEL = 1;               //  SPI_SCK  
    M0P_GPIO->P2DIR_f.P25 = 0;           //  output
    M0P_GPIO->P2OD_f.P25 = 0;            //  PushPull ( not open drain )
    M0P_GPIO->P2PD_f.P25 = 0;            //  no Pull Down 
    M0P_GPIO->P2PU_f.P25 = 0;            //  no Pull Up 
    M0P_GPIO->P2DR_f.P25 = 0;            //  High drive 
    // P26 - MOSI
    M0P_GPIO->P2ADS_f.P26 = 0;           //  not analog
    M0P_GPIO->P26_SEL = 1;               //  SPI_MOSI  
    M0P_GPIO->P2DIR_f.P26 = 0;           //  output
    M0P_GPIO->P2OD_f.P26 = 0;            //  PushPull ( not open drain )
    M0P_GPIO->P2PD_f.P26 = 1;            //  no Pull Down 
    M0P_GPIO->P2PU_f.P26 = 0;            //  no Pull Up 
    M0P_GPIO->P2DR_f.P26 = 0;            //  High drive 

    //  Configure SPI
    M0P_CLOCK->PERI_CLKEN_f.SPI = 1;    //  enable CLK to SPI
    M0P_SPI->CR_f.MSTR = 1;             //  master
    M0P_SPI->CR_f.CPHA = 0;
    M0P_SPI->CR_f.CPOL = 0;
    //  divider = 2
    M0P_SPI->CR_f.SPR0 = 0;
    M0P_SPI->CR_f.SPR1 = 0;
    M0P_SPI->CR_f.SPR2 = 0;

}

void SPI_Enable() {
    M0P_SPI->CR_f.SPEN = 1;
}

void SPI_Disable() {
    M0P_SPI->CR_f.SPEN = 0;
}

void SPI_Send(uint8_t data) {
    M0P_SPI->DATA = data;
}

int main(void) {

    uint8_t  rs;
    SPI_Init();
    SPI_Enable();

	while (1)	{
        //M0P_SPI->SSN_f.SSN = 1;
        M0P_GPIO->P2OUT_f.P24 = 0;           //  out 0

        SPI_Send(0xA1);
        while (M0P_SPI->STAT_f.SPIF == 0) {}
        rs = M0P_SPI->DATA;
        SPI_Send(0x52);
        while (M0P_SPI->STAT_f.SPIF == 0) {}
        rs = M0P_SPI->DATA;

        //M0P_SPI->SSN_f.SSN = 0;
        M0P_GPIO->P2OUT_f.P24 = 1;           //  out 1
        delay(200);
	}
    SPI_Disable();

}	

void delay(uint32_t nTime) {

    volatile uint32_t count = nTime;
	while (count--);
}





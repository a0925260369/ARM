#include  "lpc11xx.h"
#include  "LED_ADC.h"
void ADC_Init(int Channel)
{
		if(Channel>7){
				return;
		}
		LPC_SYSCON->PDRUNCFG &= ~(0x1<<4);        // ADC power
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);     // Enables clock for ADC.
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);     // Enables clock for IO configuration block
		switch(Channel)
		{
				case 0: //  set channel 0
						LPC_IOCON->JTAG_TDI_PIO0_11 &= ~0x07;              //
						LPC_IOCON->JTAG_TDI_PIO0_11 |= 0x02;      // set P0.11 forAD0
						LPC_IOCON->JTAG_TDI_PIO0_11 &= ~(3<<3) ;  // no pull-down/pull-up resistor enabled
						LPC_IOCON->JTAG_TDI_PIO0_11 &= ~(1<<7) ;   // Analog input mode.
						break;
				case 1:  //  set channel 1
						LPC_IOCON->JTAG_TMS_PIO1_0 &= ~0x07;              //
						LPC_IOCON->JTAG_TMS_PIO1_0 |= 0x02;               // set P1.0 forAD1
						LPC_IOCON->JTAG_TMS_PIO1_0 &= ~(3<<3) ;           // no pull-down/pull-up resistor enabled
						LPC_IOCON->JTAG_TMS_PIO1_0 &= ~(1<<7) ;           // Analog input mode.
						break;
				case 2:  //  set channel 2
						LPC_IOCON->JTAG_TDO_PIO1_1 &= ~0x07;              //
						LPC_IOCON->JTAG_TDO_PIO1_1 |= 0x02;               // set P1.1 forAD2
						LPC_IOCON->JTAG_TDO_PIO1_1 &= ~(3<<3) ;           // no pull-down/pull-up resistor enabled
						LPC_IOCON->JTAG_TDO_PIO1_1 &= ~(1<<7) ;           // Analog input mode.
						break;
				case 3:  //  set channel 3
						LPC_IOCON->JTAG_nTRST_PIO1_2 &= ~0x07;              //
						LPC_IOCON->JTAG_nTRST_PIO1_2 |= 0x02;               // set P1.2 forAD3
						LPC_IOCON->JTAG_nTRST_PIO1_2 &= ~(3<<3) ;           // no pull-down/pull-up resistor enabled
						LPC_IOCON->JTAG_nTRST_PIO1_2 &= ~(1<<7) ;           // Analog input mode.
						break;
				case 4:  //  set channel 4
						LPC_IOCON->ARM_SWDIO_PIO1_3 &= ~0x07;              //
						LPC_IOCON->ARM_SWDIO_PIO1_3 |= 0x02;    					 // set P1.3 forAD4
						LPC_IOCON->ARM_SWDIO_PIO1_3 &= ~(3<<3) ;           // no pull-down/pull-up resistor enabled
						LPC_IOCON->ARM_SWDIO_PIO1_3 &= ~(1<<7) ;           // Analog input mode.
						break;
				case 5:  //  set channel 5
						LPC_IOCON->PIO1_4 &= ~0x07;              //
						LPC_IOCON->PIO1_4 |= 0x01;               // set P1.4 forAD5
						LPC_IOCON->PIO1_4 &= ~(3<<3) ;           // no pull-down/pull-up resistor enabled
						LPC_IOCON->PIO1_4 &= ~(1<<7) ;           // Analog input mode.
						break;
				case 6:  //  set channel 6
						LPC_IOCON->PIO1_10 &= ~0x07;              //
						LPC_IOCON->PIO1_10 |= 0x01;               // set P1.10 forAD6
						LPC_IOCON->PIO1_10 &= ~(3<<3) ;           // no pull-down/pull-up resistor enabled
						LPC_IOCON->PIO1_10 &= ~(1<<7) ;           // Analog input mode.
						break;
				case 7:  // set channel 7
						LPC_IOCON->PIO1_11 &= ~0x07;              //
						LPC_IOCON->PIO1_11 |= 0x01;               // set P1.11 forAD7
						LPC_IOCON->PIO1_11 &= ~(3<<3) ;           // no pull-down/pull-up resistor enabled
						LPC_IOCON->PIO1_11 &= ~(1<<7) ;           // Analog input mode.
						break;
				default:
						break;
      
		}
		LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);    // disables clock for IO configuration block
		LPC_ADC->CR = (1<<Channel)|(24<<8);   /*select Channel bit0~bit7*//* bit15:bit8  set clock frequency 2MHz 50/(24+1)*/
   
}
uint16_t ADC_Read(int Channel)
{
		float adc_value=0;
		LPC_ADC->CR |= (1<<24); // start transform
		while((LPC_ADC->DR[Channel]&0x80000000)==0);
		adc_value = (LPC_ADC->DR[Channel]>>6)&0x3FF;
		adc_value = (adc_value/1024)*100; // turn into real Voltage
		return adc_value;        // return value
}
uint16_t ADC_Read2(int Channel)
{
		uint16_t adc_value=0;
		LPC_ADC->CR |= (1<<24); // start transform
		while((LPC_ADC->DR[Channel]&0x80000000)==0);
		adc_value = (LPC_ADC->DR[Channel]>>6)&0x3FF;
		//adc_value = (adc_value/1024)*100; // turn into real Voltage
		return adc_value;        // return value
}
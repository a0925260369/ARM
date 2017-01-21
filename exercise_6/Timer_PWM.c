#include  "lpc11xx.h"
#include  "Timer_PWM.h"
uint16_t cycle;   
uint8_t duty;   // range 1~99

void T16B0M0_PWM_Init(void)
{
		if((duty>=100)&&(duty<=0)){
				return;//if duty is not 1~99 return
		}
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);    //enable TIM16B0 clock 
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);  // enable IOCON clock 
		LPC_IOCON->PIO0_8 &= ~0x07;
		LPC_IOCON->PIO0_8 |= 0x02;        //set P0.8 to MAT0
		LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);  // disable IOCON clock
		LPC_TMR16B0->TCR = 0x02;            //reset timer(bit1:1=reset)
		LPC_TMR16B0->PR  = SystemFrequency/1000000-1;            //12M/1M-1=11,11*1/12M about 1us
		LPC_TMR16B0->PWMC= 0x01;                //set MAT0 for PWM output
		LPC_TMR16B0->MCR = 0x02<<9; //set MR3 for cycle register
		LPC_TMR16B0->MR3 = cycle;           //set cycle
		LPC_TMR16B0->MR0 = cycle/100*(100-duty);      //set duty cycle
		LPC_TMR16B0->TCR = 0x01;                 //start timer
}
void T16B0M0_PWM_SET(void)
{
		if((duty>=100)&&(duty<=0)){
				return;//if duty is not 1~99 return
		}
		LPC_TMR16B0->MR0 = cycle/100*(100-duty);      //set duty cycle
}
void TIM32B0_PWM(uint32_t cycle_us, uint8_t duty)
{
		if((duty>=100)&&(duty<=0)){
				return;//if duty is not 1~99 return
		}
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); //enable IOCON clock  
    LPC_IOCON->PIO0_1 &= ~0x07;
    LPC_IOCON->PIO0_1 |= 0x02; //set P0.1 to MAT2
    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // disable IOCON clock
    LPC_TMR32B0->TCR = 0x00;
    LPC_SYSCON->SYSAHBCLKCTRL|=(1<<9); //enable TIM32B0 clock 
    LPC_TMR32B0->TCR = 0x02; //reset timer(bit1:1=reset)
    LPC_TMR32B0->PR = 0x00; //
    LPC_TMR32B0->PWMC= 0x04; //set MAT2 for PWM output
    LPC_TMR32B0->MCR = 0x02<<9; //set MR3 for cycle register
    LPC_TMR32B0->MR3 = cycle_us; //set cycle
    LPC_TMR32B0->MR2 = cycle_us*(100-duty)/100;//set duty cycle
    LPC_TMR32B0->TCR = 0x01; //start timer
}
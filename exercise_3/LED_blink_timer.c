#include "LPC11xx.h"
#include "Timer.h"
#include "setport.h"
extern volatile uint32_t timer_counter;
void LED_blink(int port,int bit,int time_on,int time_off)
{
		uint32_t interval;
		int timer_off=time_on+time_off;
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);/* Enable AHB clock to the GPIO domain. */
		SystemInit();
		interval = SystemAHBFrequency/1000 - 1;
		if ( interval > 0xFFFF )
		{
				interval = 0xFFFF;
		}
		init_timer16(0, interval);//init timer16
		enable_timer16(0);//let timer16 can be used
		SetDir(port,bit,1);/* Set port _bit to output */
		timer_counter = 0;
		while (1) {		
				if ( (timer_counter > 0) && (timer_counter <= time_on) ){
						SetValue( port, bit, 0 );//if timer16 < time_on LED_on
				}
				else if ( (timer_counter > time_on) && (timer_counter <= timer_off) ){
						SetValue( port, bit, 1 );//if time_on <timer16 <timer_off+time_on,LED OFF
				}
				else if ( timer_counter > timer_off ){
						timer_counter = 0;//if timer16>timer_off+time_on, init timer16
				}
		}
}
//LED_blink_timer
int main()
{
		LED_blink(2,7,1000,250);//LED on 1s,off 250ms
}
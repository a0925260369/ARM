#include "setport.h"
#include "LPC11xx.h"
#define TEST_TIMER_NUM  0 
#define btn_push LPC_GPIO2->DATA&(1<<0))==0   //button push
#define btn_nopush LPC_GPIO2->DATA&(1<<0))!=0 //button no push
extern volatile uint32_t timer_counter;
void btn_timer( int port, int bit, int time_push, int time_on, int time_off)
{
		uint32_t interval;
		int timer_off=time_on+time_off;
		int i=0;
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);/* Enable AHB clock to the GPIO domain. */
		SystemInit();
		interval = SystemAHBFrequency/1000 - 1;
		if ( interval > 0xFFFF )
		{
				interval = 0xFFFF;
		}
		init_timer16(TEST_TIMER_NUM, interval);//init timer16
		enable_timer16(TEST_TIMER_NUM);//let timer16 can be used
		SetDir(port,bit,1);/* Set port _bit to output */
		while (1) {
				timer_counter = 0; //init timer16
				i=0;
				if((btn_push) {  
						while((btn_push){//button keep pushing
								if(timer_counter >time_push) { //if timer16 > time_push
										timer_counter = 0;//init timer16
										while (1) {
												if ( (timer_counter > 0) && (timer_counter <= time_on) ){
														SetValue( port, bit, 0 );//if timer16 < time_on LED_on
												}
												if ( (timer_counter > time_on) && (timer_counter <= timer_off) ){
														SetValue( port, bit, 1 );//if time_on <timer16 <timer_off+time_on,LED OFF
												}
												else if ( timer_counter > timer_off ){
														timer_counter = 0;//if timer16>timer_off+time_on, init timer16
												}
												if((btn_nopush){
														i=1;//avoid into next if
														break;
												}
										}
								}
						}
						if((btn_nopush&&timer_counter<time_push&&i==0){//button push time < time_push
								if(port==1) {
										LPC_GPIO1->DATA^=(1<<(bit)); //change LED ON or OFF
								}
								else if(port==2){
										LPC_GPIO2->DATA^=(1<<(bit));//change LED ON or OFF
								}
								else if(port==3){
										LPC_GPIO3->DATA^=(1<<(bit));//change LED ON or OFF
								}
								else if(port==0){
										LPC_GPIO0->DATA^=(1<<(bit));//change LED ON or OFF
								}
								timer_counter = 0;//reset timer
						}
						else if(i==1){
								SetValue( port, bit, 1 );//let LED OFF
								i=0;
						}
				}
		}
}
int main(void)
{
		LPC_GPIO2->IS |= (1<<0);  
		LPC_GPIO2->IE |= (1<<0);//PORT2 IE on  
		NVIC_EnableIRQ(EINT2_IRQn);//enable PORT2 interrupt
		SetDir(2,0,0);/* Set port _bit to input */
		NVIC_SetPriority(EINT2_IRQn, 3);//change Priority PORT2 interrupt the last
		while (1) {
		}
}
void PIOINT2_IRQHandler()//PORT2 interrupt funciton
{	
		LPC_GPIO2->IE |= (0<<0);//PORT2 IE off
		if((LPC_GPIO2->MIS&(1<<0))==(1<<0)){ //PORT2 BIT0 push
				btn_timer(2,7,500,250,250);
		}
		LPC_GPIO2->IC = 0XFFF;
}
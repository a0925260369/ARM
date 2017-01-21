#include "lpc11xx.h"
#include "Timer_PWM.h"
#include "LED_ADC.h"
#include "Timer.h"
#include "UART.h"
#define TEST_TIMER_NUM  0 
extern volatile uint32_t timer_counter;
volatile uint8_t UARTBuffer[0x40];
uint8_t rec_buf;
uint8_t rec_buf2;
uint8_t ConvertDigital ( uint8_t digital )
{
		uint8_t ascii_char;
		if ( (digital >= 0) && (digital <= 9) )
		{
				ascii_char = digital + 0x30;	/* 0~9 */
		}
		else
		{
				ascii_char = digital - 0x0A;
				ascii_char += 0x41;				/* A~F */
		}
		return ( ascii_char );
}
void init(void)
{
		uint32_t interval;
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);/* Enable AHB clock to the GPIO domain. */
		interval = SystemAHBFrequency/1000 - 1;
		if ( interval > 0xFFFF ) {
				interval = 0xFFFF;
		}
		init_timer16(TEST_TIMER_NUM, interval);//init timer16
		enable_timer16(TEST_TIMER_NUM);//let timer16 can be used
		ADC_Init(7);
		UART_init(9600);
}


void UART_IRQHandler(void)
{
		uint32_t IRQ_ID;         // ??????ID???
		uint8_t rec_buf;    // ??????????
		IRQ_ID = LPC_UART->IIR;   // ???ID?
		IRQ_ID =((IRQ_ID>>1)&0x7);// ??bit3:bit1
		if(IRQ_ID == 0x02 ){
				rec_buf = LPC_UART->RBR;
				if(rec_buf=='$'){
						UART_send_byte(rec_buf); // ???????????
						rec_buf2=rec_buf;
				}
				if(rec_buf=='#'){
						UART_send_byte(rec_buf);
						rec_buf2=rec_buf;
				}
		}
}
int main()
{		
		uint16_t adc_value;
		uint16_t adc_PWM;
		int x=0,i=0,y=1;
		timer_counter = 0;
		init();
		LPC_UART->IER = 0x01;  // ??????
		NVIC_EnableIRQ(UART_IRQn); // ?????
		while (1) {
				adc_value = ADC_Read2(7);
				adc_PWM=ADC_Read(7);
				if(rec_buf2=='$'){
						TIM32B0_PWM(1000,adc_PWM);
				}
				x=0;
				y=1;
				for(i=0;i<=10;i++){
						if(i!=0){
								y=y*2;
						}
						if((adc_value>>i)&0x1){
								x=x+y;
						}
				}
				if(timer_counter == 2000){
						UARTBuffer[0] = ConvertDigital( (uint8_t)(x/1000));
						UARTBuffer[1] = ConvertDigital( (uint8_t)(x/100%10));
						UARTBuffer[2] = ConvertDigital( (uint8_t)(x/10%10));
						UARTBuffer[3] = ConvertDigital( (uint8_t)(x%10));
						UARTBuffer[4] = '\r';
						UARTBuffer[5] = '\n';
						UARTSend((uint8_t *)UARTBuffer, 6);
						timer_counter = 0;
				}
		}
}
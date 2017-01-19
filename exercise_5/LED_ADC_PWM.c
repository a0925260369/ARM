#include  "lpc11xx.h"
#include  "LED_ADC.h"
#include  "Timer_PWM.h"
//ADC control LED PWM
int main()
{
		uint16_t adc_value;
		ADC_Init(7);//chose channel 7 P1.11
    while (1) {
				adc_value = ADC_Read(7);
				TIM32B0_PWM(1000,adc_value);
    }
}
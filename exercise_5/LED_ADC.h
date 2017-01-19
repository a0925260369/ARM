#ifndef __LED_ADC_H
#define __LED_ADC_H
#define  Vref   5000
extern void ADC_Init(int Channel);
extern uint16_t ADC_Read(int Channel);
#endif
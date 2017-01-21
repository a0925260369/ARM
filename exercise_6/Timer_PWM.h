#ifndef __Timer_PWM_H
#define __Timer_PWM_H
extern uint16_t cycle;
extern uint32_t cycle_us;
extern uint8_t duty;
extern void T16B0M0_PWM_Init(void);
extern void T16B0M0_PWM_SET(void);
extern void TIM32B0_PWM(uint32_t cycle_us, uint8_t duty);
#endif
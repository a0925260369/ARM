#ifndef __Timer_H
#define __Timer_H
void TIMER16_0_IRQHandler(void);
void enable_timer16(uint8_t timer_num);
void init_timer16(uint8_t timer_num, uint32_t TimerInterval);
#endif
#ifndef   __UART_H__
#define   __UART_H__
extern uint8_t Recived_data;
extern void UART_init(uint32_t baudrate);
extern uint8_t UART_recive(void);
extern void UART_send_byte(uint16_t byte);
extern void UARTSend(uint8_t *BufferPtr, uint32_t Length);
#endif
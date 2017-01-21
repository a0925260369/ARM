#include  "lpc11xx.h"
#include  "UART.h"
void UART_init(uint32_t baudrate)
{
   uint32_t DL_value,Clear=Clear;   // (???????????????Warning)
   LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); //Enables clock for IO configuration block
   LPC_IOCON->PIO1_6 &= ~0x07;
   LPC_IOCON->PIO1_6 |= 0x01; //set P1.6 for RX
   LPC_IOCON->PIO1_7 &= ~0x07;
   LPC_IOCON->PIO1_7 |= 0x01; //set P1.7 for TX
   LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // Disables clock for IO configuration block
   LPC_SYSCON->UARTCLKDIV = 0x1; //UART_PCLK clock divider values.Divide by 1. 
   LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);//Enables clock for UART
   LPC_UART->LCR = 0x83;   //8-bit character length.Enable access to Divisor Latches.
   DL_value = SystemFrequency/16/baudrate ;  //
   LPC_UART->DLM = DL_value / 256;    //?????????
   LPC_UART->DLL = DL_value % 256;   //?????????
   LPC_UART->LCR = 0x03;    //DLAB set 0
   LPC_UART->FCR = 0x07;    //Enable FIFO.clear all bytes in UART TX FIFO and RX.
   Clear = LPC_UART->LSR;   //?UART????????????
}
uint8_t UART_recive(void)
{
   while(!(LPC_UART->LSR & (1<<0)));//wait for the uart data
   return(LPC_UART->RBR);                //return the uart data
}
void UART_send_byte(uint16_t byte)
{
   LPC_UART->THR = byte;
   while ( !(LPC_UART->LSR & (1<<5)) );//wait the data send
}
void UARTSend(uint8_t *BufferPtr, uint32_t Length)
{
  while ( Length != 0 )
  {
	  LPC_UART->THR = *BufferPtr;
      BufferPtr++;
      Length--;
  }
  return;
}
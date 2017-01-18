#include "setport.h"
#include "LPC11xx.h"
volatile uint32_t GPIOShadowPort0;
volatile uint32_t GPIOShadowPort1;
volatile uint32_t GPIOShadowPort2;
volatile uint32_t GPIOShadowPort3;
void SetDir( int port, int bit, int dir )
{
		switch ( port ) {
				case 0:
						if ( !(LPC_GPIO0->DIR & (0x1<<bit)) && (dir == 1) ){
								LPC_GPIO0->DIR |= (0x1<<bit);//set PORT0 BIT? OUTPUT
						}
						else if ( (LPC_GPIO0->DIR & (0x1<<bit)) && (dir == 0) ){
								LPC_GPIO0->DIR &= ~(0x1<<bit);//set PORT0 BIT? INPUT 
						}
						break;
				case 1:
						if ( !(LPC_GPIO1->DIR & (0x1<<bit)) && (dir == 1) ){
								LPC_GPIO1->DIR |= (0x1<<bit);//set PORT1 BIT? OUTPUT
						}
						else if ( (LPC_GPIO1->DIR & (0x1<<bit)) && (dir == 0) ){
								LPC_GPIO1->DIR &= ~(0x1<<bit);//set PORT1 BIT? INPUT
						}							
						break;
				case 2:
						if ( !(LPC_GPIO2->DIR & (0x1<<bit)) && (dir == 1) ){
								LPC_GPIO2->DIR |= (0x1<<bit);//set PORT2 BIT? OUTPUT
						}
						else if ( (LPC_GPIO2->DIR & (0x1<<bit)) && (dir == 0) ){
								LPC_GPIO2->DIR &= ~(0x1<<bit);//set PORT2 BIT? INPUT
						}
						break;
				case 3:
						if ( !(LPC_GPIO3->DIR & (0x1<<bit)) && (dir == 1) ){
								LPC_GPIO3->DIR |= (0x1<<bit);//set PORT3 BIT? OUTPUT
						}
						else if ( (LPC_GPIO3->DIR & (0x1<<bit)) && (dir == 0) ){
								LPC_GPIO3->DIR &= ~(0x1<<bit);//set PORT3 BIT? INPUT
						}
						break;
				default:
						break;
		}
		return;
}
void SetValue( int port, int bit, int bitVal )
{
		switch ( port ) {
				case 0:
						if(bitVal){
								GPIOShadowPort0 |= (1<<bit);//Set Port 0 BIT? OFF	
						}
						else{
								GPIOShadowPort0 &= ~(1<<bit);//Set Port 0 BIT? ON
						}
						LPC_GPIO0->DATA = GPIOShadowPort0;
						break;
				case 1:
						if(bitVal){
								GPIOShadowPort1 |= (1<<bit);//Set Port 1 BIT? OFF
						}
						else{
								GPIOShadowPort1 &= ~(1<<bit);//Set Port 1 BIT? ON
						}
						LPC_GPIO1->DATA = GPIOShadowPort1;
						break;
				case 2:
						if(bitVal){
								GPIOShadowPort2 |= (1<<bit);//Set Port 2 BIT? OFF
						}
						else{
								GPIOShadowPort2 &= ~(1<<bit);//Set Port 2 BIT? ON		
						}
						LPC_GPIO2->DATA = GPIOShadowPort2;
						break;
				case 3:
						if(bitVal){
								GPIOShadowPort3 |= (1<<bit);//Set Port 3 BIT? OFF
						}
						else{
								GPIOShadowPort3 &= ~(1<<bit);//Set Port 3 BIT? ON
						}
						LPC_GPIO3->DATA = GPIOShadowPort3;
						break;
				default:
						break;
		}
		return;
}
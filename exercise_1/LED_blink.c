#include "setport.h"
#include "LPC11xx.h"
#include "delay.h"

void LED_blink(int port,int bit,int t1,int t2)
{
	
		SetDir(port,bit,1);
		while (1) {
				SetValue(port,bit,0);
				delay(t1);
				SetValue(port,bit,1);
				delay(t2);
		}
}
//LED_blink
int main()
{
		LED_blink(1,8,1200000,1200000);
}

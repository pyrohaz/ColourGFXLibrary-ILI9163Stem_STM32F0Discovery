#include <GFXC.h>
#include <math.h>
#include <stm32f0xx_adc.h>

volatile uint32_t MSec = 0;
uint8_t BLLevel = 4;

void SysTick_Handler(void){
	static uint8_t BLCnt = 0;
	/*
	static uint16_t SCnt;

	SCnt++;
	if(SCnt==1999){
		SCnt = 0;
		BLLevel++;
		if(BLLevel>4) BLLevel = 0;
	}
	 */

	BLCnt++;
	BLCnt&=3;
	if(BLCnt<BLLevel) GPIO_ResetBits(GPIOA, BLPin);
	else GPIO_SetBits(GPIOA, BLPin);

	MSec++;
}
int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	ILI9163Init();

	SleepMode(Awake);

	int XPos = 0, Cnt;

	SetScrn(Black);

	while(1)
	{
		for(Cnt = 1; Cnt<100; Cnt++){
			if(Cnt<50) PStr("Text", 0, 0, 1, ColP(100-Cnt, 0, Cnt), Black);
			else PStr("Text", 0, 0, 2, ColP(Cnt-50, 0, 100-Cnt), Black);
			Triangle(96, 64, (Cnt-1)>>1, (Cnt-1)*360/200, Black);
			Triangle(96, 64, Cnt>>1, Cnt*360/200, ColP((Cnt%7)*12, Cnt, Cnt>>2));
			PNum(Cnt, 0, 40, 3, 3, ColP(0, Cnt, (100-Cnt)), ColP(Cnt, (100-Cnt), 0));
			PNumF((200-Cnt)*0.012f, 0, 80, 2, 2, ColP(Cnt, (100-Cnt), 0), ColP(0, Cnt, (100-Cnt)));
		}
		SetScrn(Black);
	}
}

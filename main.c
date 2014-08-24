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

GPIO_InitTypeDef GP;
ADC_InitTypeDef A;

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	ILI9163Init();

	/*
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	GP.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GP.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init(GPIOB, &GP);

	GP.GPIO_Pin = GPIO_Pin_10;
	GP.GPIO_Mode = GPIO_Mode_IN;
	GP.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GP);

	A.ADC_ContinuousConvMode = DISABLE;
	A.ADC_DataAlign = ADC_DataAlign_Right;
	A.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	A.ADC_Resolution = ADC_Resolution_8b;
	ADC_Init(ADC1, &A);
	ADC_Cmd(ADC1, ENABLE);
	*/

	SleepMode(Awake);

	int XPos = 0, Cnt, XR, YR, A = 0;

	SetScrn(Black);

	while(1)
	{
		Triangle(64, 64, 80, A, Green);
		A++;

	}
}

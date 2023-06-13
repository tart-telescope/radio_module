#define SYSCLK_FREQ_48MHZ_HSI 48000000

#include <ch32v00x.h>
#include <debug.h>
#include "hardware.h"
#include "max2769.h"

void TART_Pin_Init() {

	GPIO_InitTypeDef GPIO_InitStructure = {0};

	/* RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TART_SCLK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure); */

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TART_CS_PIN | TART_SDATA_PIN | TART_PGM_PIN | TART_SCLK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TART_CS_PORT, &GPIO_InitStructure); 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
}


void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void Delay_Init(void);
void Delay_Ms(uint32_t n);




int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();

	TART_Pin_Init();


	#if 0
		// Preconfigured States PGM -> Logic Hi
		GPIO_WriteBit(TART_PGM_PORT, TART_PGM_PIN, Bit_SET);

		GPIO_WriteBit(TART_CS_PORT, TART_CS_PIN, Bit_RESET);
		GPIO_WriteBit(TART_SDATA_PORT, TART_SDATA_PIN, Bit_SET);
		GPIO_WriteBit(TART_SCLK_PORT, TART_SCLK_PIN, Bit_RESET);

	#else
		GPIO_WriteBit(TART_PGM_PORT, TART_PGM_PIN, Bit_RESET);
  		GPIO_WriteBit(TART_CS_PORT, TART_CS_PIN, Bit_SET);
		Delay_Ms(1000);
		setupRadioStream(TART_CS_PORT, TART_CS_PIN);
	#endif
	uint8_t ledState = 0;
	while (1)
	{
  		// GPIO_WriteBit(TART_CS_PORT, TART_CS_PIN, ledState);
		GPIO_WriteBit(LED_GPIO_PORT, LED_GPIO_PIN, ledState);
		ledState ^= 1; // invert for the next run
		Delay_Ms(100);
	}
}

void NMI_Handler(void) {}
void HardFault_Handler(void)
{
	while (1)
	{
	}
}

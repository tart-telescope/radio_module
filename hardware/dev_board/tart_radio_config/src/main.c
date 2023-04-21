#if defined(CH32V00X)
#include <ch32v00x.h>
#elif defined(CH32V10X)
#include <ch32v10x.h>
#elif defined(CH32V20X)
#include <ch32v20x.h>
#elif defined(CH32V30X)
#include <ch32v30x.h>
#endif
//#include <debug.h>

#define LED_GPIO_PORT GPIOA
#define LED_GPIO_PIN GPIO_Pin_1
#define LED_CLOCK_ENABLE RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)


// Pins for the programming interface

#define TART_PGM_PORT GPIOC 
#define TART_PGM_PIN GPIO_Pin_4
#define TART_PGM_CLOCK_ENABLE RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE)

#define TART_CS_PORT GPIOD
#define TART_CS_PIN GPIO_Pin_5
#define TART_SDATA_PORT GPIOD
#define TART_SDATA_PIN GPIO_Pin_6
#define TART_CS_CLOCK_ENABLE RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE)

#define TART_SCLK_PORT GPIOA
#define TART_SCLK_PIN GPIO_Pin_2
#define LED_CLOCK_ENABLE RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)


void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void Delay_Init(void);
void Delay_Ms(uint32_t n);

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();

	GPIO_InitTypeDef GPIO_InitStructure = {0};

	LED_CLOCK_ENABLE;
	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

	uint8_t ledState = 0;
	while (1)
	{
		GPIO_WriteBit(LED_GPIO_PORT, LED_GPIO_PIN, ledState);
		ledState ^= 1; // invert for the next run
		Delay_Ms(1000);
	}
}

void NMI_Handler(void) {}
void HardFault_Handler(void)
{
	while (1)
	{
	}
}

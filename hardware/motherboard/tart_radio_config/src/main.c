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
	GPIO_InitStructure.GPIO_Pin = TART_CS_PIN | TART_SDATA_PIN | TART_PGM_PIN | TART_SCLK_PIN | TART_SLOT_ENABLE_PIN;
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

void pulse_led(uint32_t period, float high_percent) {
	if (high_percent < 0.0) high_percent = 0.0;
	if (high_percent > 1.0) high_percent = 1.0;
	uint32_t high_us = (period * high_percent);
	if (high_us > period) high_us = period;
	uint32_t low_us = period - high_us;
	GPIO_WriteBit(LED_GPIO_PORT, LED_GPIO_PIN, Bit_SET);
	Delay_Us(low_us);
	GPIO_WriteBit(LED_GPIO_PORT, LED_GPIO_PIN, Bit_RESET);
	Delay_Us(high_us);
}

float qsin(float x) {
	// http://datagenetics.com/blog/july12019/index.html
	static const float pi = 3.14159265;
	static const float pis = pi*pi;
	static const float p2 = 2.0 * pi;

	// Wrap x to -pi..pi	
	while (x < -pi) x += p2;
	while (x > pi) x -= p2;
    if (x < 0) {
        return -qsin(-x);
	}
	float px = (pi - x);
	float xpx = x*px;
	float y = (16*xpx)/(5*pis - 4*xpx);

	return y;
}

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();

	TART_Pin_Init();

	// SHDN the MAX2769 (Shutdown Mode)
	shutdownRadio();
	Delay_Ms(1500);

	// GPIO_WriteBit(TART_PGM_PORT, TART_PGM_PIN, Bit_RESET);
	/* FIRST go into the preconfigured state */
		// Preconfigured States PGM -> Logic Hi
		GPIO_WriteBit(TART_PGM_PORT, TART_PGM_PIN, Bit_SET);

		GPIO_WriteBit(TART_CS_PORT, TART_CS_PIN, Bit_RESET);
		GPIO_WriteBit(TART_SDATA_PORT, TART_SDATA_PIN, Bit_SET);
		GPIO_WriteBit(TART_SCLK_PORT, TART_SCLK_PIN, Bit_RESET);
		Delay_Ms(100);
		// Enable the MAX2769 (Normal Mode)
		enableRadio();
	#if 1 /* Not enable serial configuration */
		// Serial Configuration States PGM -> Logic Low
		Delay_Ms(2000);
		GPIO_WriteBit(TART_PGM_PORT, TART_PGM_PIN, Bit_RESET);
		// Enable the MAX2769 (Normal Mode)

		Delay_Ms(500);
  		GPIO_WriteBit(TART_CS_PORT, TART_CS_PIN, Bit_SET);
		// setupRadioStream(TART_CS_PORT, TART_CS_PIN);
		setupRadio(TART_CS_PORT, TART_CS_PIN);
	#endif

	while (1)
	{
  		for (int j=-128; j<128;j++) {
			float theta = ((float)(j) / 128.0) * 3.14159265;
			float y = (qsin(theta)+1.0)/2;

			pulse_led(10000, y);
		}
	}
}

void NMI_Handler(void) {}
void HardFault_Handler(void)
{
	while (1)
	{
	}
}

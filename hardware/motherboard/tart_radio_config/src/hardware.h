#ifndef __hardware_h__
#define __hardware_h__
#include <ch32v00x.h>

typedef uint16_t pin_t;

// Board definitions
#define LED_GPIO_PORT GPIOC
#define LED_GPIO_PIN GPIO_Pin_2


// Pins for the programming interface of the MAX2769
// SCLK PD4
// SDATA PD6
// CS# PD5
// PGM PD3

#define TART_SLOT_ENABLE_PORT GPIOD
#define TART_SLOT_ENABLE_PIN GPIO_Pin_2

#define TART_PGM_PORT GPIOD 
#define TART_PGM_PIN GPIO_Pin_3

#define TART_SCLK_PORT GPIOD
#define TART_SCLK_PIN GPIO_Pin_4

#define TART_CS_PORT GPIOD
#define TART_CS_PIN GPIO_Pin_5

#define TART_SDATA_PORT GPIOD
#define TART_SDATA_PIN GPIO_Pin_6


#endif /* __hardware_h__ */
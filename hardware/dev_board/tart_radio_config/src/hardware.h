#ifndef __hardware_h__
#define __hardware_h__
#include <ch32v00x.h>

typedef uint16_t pin_t;

// Board definitions
#define LED_GPIO_PORT GPIOA
#define LED_GPIO_PIN GPIO_Pin_1


// Pins for the programming interface of the MAX2769
// SCLK PA2
// SDATA PD6
// CS# PD5
// PGM PC4

#define TART_PGM_PORT GPIOC 
#define TART_PGM_PIN GPIO_Pin_4

#define TART_CS_PORT GPIOD
#define TART_CS_PIN GPIO_Pin_5
#define TART_SDATA_PORT GPIOD
#define TART_SDATA_PIN GPIO_Pin_6

#define TART_SCLK_PORT GPIOA
#define TART_SCLK_PIN GPIO_Pin_2


#endif /* __hardware_h__ */
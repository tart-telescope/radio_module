#ifndef __hardware_h__
#define __hardware_h__
#include <Arduino.h>

// Board definitions


// LEDs
#define LED_LD_A PIN_PE0 // 30
#define LED_LD_B PIN_PE1 // 31
#define LED_ANT_A PIN_PE2 // 32
#define LED_ANT_B PIN_PE3 // 33

// Radio connections

#define IN_LD_A PIN_PC4 // 16
#define IN_LD_B PIN_PC5 // 17
#define IN_ANT_A PIN_PC6 // 18
#define IN_ANT_B PIN_PC7 // 19


// Enable component power
#define EN_A_NEG PIN_PF0 // 34
#define EN_B_NEG PIN_PF1 // 35
#define EN_FPGA_NEG PIN_PF2 // 36


// Serial Connection to Radio A, B
#define DOUT 48
#define DIN 1 
#define DCLK 2
#define CS_A_NEG PIN_PD3 // 23
#define CS_B_NEG PIN_PD4 // 24

// Button on Board


#define IN_SW_1 PIN_PA3 // 47

#define A0 PIN_PB0  // 4
#define A1 PIN_PB1  // 5
#define A2 PIN_PB2  // 6
#define A3 PIN_PB3  // 7
#define A4 PIN_PB4  // 8

#endif /* __hardware_h__ */
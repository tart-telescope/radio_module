#include <Arduino.h>
#include <SPI.h>

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
#define EN_A PIN_PF0 // 34
#define EN_B PIN_PF1 // 35
#define EN_FPGA PIN_PF2 // 36


// Serial Connection to Radio A, B
#define DOUT 48
#define DIN 1 
#define DCLK 2
#define CS_A_NEG PIN_PD3 // 23
#define CS_B_NEG PIN_PD4 // 24

// Button on Board


#define SW_1 PIN_PA3 // 47

#define A0 PIN_PB0  // 4
#define A1 PIN_PB1  // 5
#define A2 PIN_PB2  // 6
#define A3 PIN_PB3  // 7
#define A4 PIN_PB4  // 8


// SPI mapping


void setupRadio(uint8_t cs_pin) {
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(cs_pin, 0);
  SPI.transfer(0X55);
  SPI.transfer(0X55);
  SPI.transfer(0X55);
  SPI.transfer(0X55);
  SPI.transfer(0X55);
  SPI.transfer(0X55);
  SPI.transfer(0X55);
  SPI.transfer(0X55);
  SPI.transfer(0X55);
  SPI.transfer(0X55);
  digitalWrite(cs_pin, 1);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_LD_A, OUTPUT);
  pinMode(LED_ANT_A, OUTPUT);
  pinMode(IN_ANT_A, INPUT);

  pinMode(LED_LD_B, OUTPUT);
  pinMode(LED_ANT_B, OUTPUT);
  pinMode(IN_ANT_B, INPUT);

  pinMode(CS_A_NEG, 1);
  pinMode(CS_B_NEG, 1);

  setupRadio(CS_A_NEG);
  setupRadio(CS_B_NEG);
}

void loop() {
  // put your main code here, to run repeatedly:

  int ld_a = digitalRead(IN_LD_A);
  int ld_b = digitalRead(IN_LD_B);

  digitalWrite(LED_LD_A, ld_a);
  digitalWrite(LED_LD_B, ld_b);
}
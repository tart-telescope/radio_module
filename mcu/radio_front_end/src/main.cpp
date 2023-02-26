#include <Arduino.h>

// Board definitions

// LEDs
#define LED_LD_A 30
#define LED_LD_B 31
#define LED_ANT_A 32
#define LED_ANT_B 33

// Radio connections

#define IN_LD_A 16
#define IN_LD_B 17
#define IN_ANT_A 18
#define IN_ANT_B 19


#define EN_A 34
#define EN_B 35
#define EN_FPGA 36


// Serial Connection to Radio A, B
#define DOUT 48
#define DIN 1
#define DCLK 2
#define CS_A_NEG 23
#define CS_B_NEG 24

// Button on Board

#define SW_1 47

#define A0 4
#define A1 5
#define A2 6
#define A3 7
#define A4 8



void setup() {
  // put your setup code here, to run once:
  pinMode(LED_LD_A, OUTPUT);
  pinMode(LED_LD_B, OUTPUT);
  pinMode(LED_ANT_A, OUTPUT);
  pinMode(LED_ANT_B, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_LD_A, HIGH);
  digitalWrite(LED_LD_B, LOW);
  delay(3000);
  digitalWrite(LED_LD_A, LOW);
  digitalWrite(LED_LD_B, HIGH);
  delay(1000);
}
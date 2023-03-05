#include <Arduino.h>
#include <SPI.h>

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


// Enable component power
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



void writeRadioA() {
    // Programme The Radios
  // set up 3-wire interface for radio A

  digitalWrite(CS_A_NEG, 0);    // select radio A
  digitalWrite(CS_B_NEG, 1);    // select radio A
  SPISettings radio_a(14000000, MSBFIRST, SPI_MODE0);

  SPI.beginTransaction(radio_a);
}

void setupRadios() {
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);

  pinMode(CS_A_NEG, OUTPUT);
  pinMode(CS_B_NEG, OUTPUT);
  pinMode(DOUT, OUTPUT);
  pinMode(DCLK, OUTPUT);
  
  // power on radios
  digitalWrite(EN_A, 1);
  digitalWrite(EN_B, 1);


  sleep(100); // wait for a little before programming. PGM is held low

  digitalWrite(DOUT, 0);
  digitalWrite(DCLK, 0);
  digitalWrite(CS_A_NEG, 0);
  digitalWrite(CS_B_NEG, 0);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_LD_A, OUTPUT);
  pinMode(LED_LD_B, OUTPUT);
  pinMode(LED_ANT_A, OUTPUT);
  pinMode(LED_ANT_B, OUTPUT);

  setupRadios();
}

void loop() {
  // put your main code here, to run repeatedly:

  int ld_a = digitalRead(IN_LD_A);
  int ld_b = digitalRead(IN_LD_B);

  digitalWrite(LED_LD_A, ld_a);
  digitalWrite(LED_LD_B, ld_b);
}
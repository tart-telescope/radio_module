#include <Arduino.h>

#include "hardware.h"
#include "max2769.h"


// SPI mapping


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_LD_A, OUTPUT);
  pinMode(LED_ANT_A, OUTPUT);
  pinMode(IN_ANT_A, INPUT);

  pinMode(LED_LD_B, OUTPUT);
  pinMode(LED_ANT_B, OUTPUT);
  pinMode(IN_ANT_B, INPUT);

  pinMode(CS_A_NEG, PIN_DIR_OUTPUT);
  pinMode(CS_B_NEG, PIN_DIR_OUTPUT);

  // Power on the FPGA - this gets the clock going for the radios.
  pinMode(EN_FPGA_NEG, OUTPUT);
  digitalWrite(EN_FPGA_NEG, LOW);
  delay(100); // wait 100 ms

  // Power on the radios
  pinMode(EN_A_NEG, OUTPUT);
  pinMode(EN_B_NEG, OUTPUT);

  digitalWrite(EN_A_NEG, LOW);
  digitalWrite(EN_B_NEG, LOW);
  
  delay(100);

  // setupRadio(CS_A_NEG);
  // setupRadio(CS_B_NEG);
}


// LED blink
uint32_t previousMillis = 0;
uint32_t interval = 100;
int ledState = LOW; 


void loop() {
  int ld_a = digitalRead(IN_LD_A);
  int ld_b = digitalRead(IN_LD_B);
  int sw_1 = digitalRead(SW_1);

  digitalWrite(LED_LD_A, ld_a);
  digitalWrite(LED_LD_B, ld_b);

  digitalWrite(LED_ANT_A, sw_1);

  uint32_t currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    if (ledState == LOW) 
      ledState = HIGH; 
    else 
      ledState = LOW;

    digitalWrite(LED_ANT_B, ledState);
  }
}
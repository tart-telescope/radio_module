#include <Arduino.h>
#include <SPI.h>

#include "hardware.h"
#include "max2769.h"


// SPI mapping

void notify_delay(int millisec) {
  int led_state = 0;
  int sub_delay = millisec / 20;
  for (int i=0; i<20;i++) {
    digitalWrite(LED_LD_A, led_state);
    digitalWrite(LED_LD_B, ~led_state);
    digitalWrite(LED_ANT_A, led_state); 
    digitalWrite(LED_ANT_B, ~led_state);
    delay(sub_delay);
    led_state = ~led_state;
  }

}

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
  notify_delay(1000);

  // Power on t0he radios
  pinMode(EN_A_NEG, OUTPUT);
  pinMode(EN_B_NEG, OUTPUT);

  digitalWrite(EN_A_NEG, LOW);
  digitalWrite(EN_B_NEG, LOW);
  notify_delay(1000);

  pinMode(PIN_SPI_MISO, INPUT);
  pinMode(PIN_SPI_MOSI, OUTPUT);
  pinMode(PIN_SPI_SCK, OUTPUT);
  pinMode(CS_A_NEG, OUTPUT);
  pinMode(CS_B_NEG, OUTPUT);

  SPI.begin();

  setupRadio(CS_A_NEG);
  setupRadio(CS_B_NEG);
}


void loop() {
  int ld_a = digitalRead(IN_LD_A);
  int ld_b = digitalRead(IN_LD_B);

  digitalWrite(LED_LD_A, ld_a);
  digitalWrite(LED_LD_B, ld_b);

  int ant_a = digitalRead(IN_ANT_A);
  int ant_b = digitalRead(IN_ANT_B);
  int sw_1 = digitalRead(IN_SW_1);
  
  digitalWrite(LED_ANT_A, IN_ANT_B); 
  digitalWrite(LED_ANT_B, IN_ANT_B);

  delay(1);
}
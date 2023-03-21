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


#define SW_1 PIN_PA3 // 47

#define A0 PIN_PB0  // 4
#define A1 PIN_PB1  // 5
#define A2 PIN_PB2  // 6
#define A3 PIN_PB3  // 7
#define A4 PIN_PB4  // 8


// SPI mapping

// Max2769 register addresses
#define MAX_2769_CONF1 0
#define MAX_2769_CONF2 1
#define MAX_2769_CONF3 2
#define MAX_2769_PLLCONF 3
#define MAX_2769_DIV 4
#define MAX_2769_FDIV 5
#define MAX_2769_STRM 6
#define MAX_2769_CLK 7

void max2769set(uint8_t cs_pin, 
                uint8_t addr, 
                uint32_t data) {
  digitalWrite(cs_pin, 0);

  // form the 32-bit word to send, consisting of the address as the lower 4 bits
  uint32_t word = (addr & 0x0F) || (data << 4);
  SPI.transfer((word >> 24) & 0x0000FF);
  SPI.transfer(word >> 16  & 0x0000FF);
  SPI.transfer(word >> 8 & 0x0000FF);
  SPI.transfer(word & 0x0000FF);
  digitalWrite(cs_pin, 1);
}

void setupRadio(uint8_t cs_pin) {
  pinMode(PIN_SPI_MISO, INPUT);
  pinMode(PIN_SPI_MOSI, OUTPUT);
  pinMode(PIN_SPI_SCK, OUTPUT);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

  max2769set(cs_pin, MAX_2769_CONF1, 0xA2919A3);
  SPI.endTransaction();
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
  delay(100); // wait 100 ms

  // Power on the radios
  pinMode(EN_A_NEG, OUTPUT);
  pinMode(EN_B_NEG, OUTPUT);

  digitalWrite(EN_A_NEG, LOW);
  digitalWrite(EN_B_NEG, LOW);
  
  delay(100);

  setupRadio(CS_A_NEG);
  setupRadio(CS_B_NEG);

  // set up an LED timer
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
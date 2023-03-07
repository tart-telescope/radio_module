#include <Arduino.h>

#include <SIKTEC_SPI.h>

// Brings in SoftSPI

#include "<DigitalIO.h>

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


// SPI mapping

const uint8_t SOFT_SPI_MISO_PIN = DIN;
const uint8_t SOFT_SPI_MOSI_PIN = DOUT;
const uint8_t SOFT_SPI_SCK_PIN  = DCLK;
const uint8_t SPI_MODE = 0;

SoftSPI<SOFT_SPI_MISO_PIN, SOFT_SPI_MOSI_PIN, SOFT_SPI_SCK_PIN, SPI_MODE> spi;

void setupRadio() {
    spi.begin();
    digitalWrite(CS_A_NEG, 1);
    spi.send(0X55);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_LD_A, OUTPUT);
  pinMode(LED_ANT_A, OUTPUT);
  pinMode(IN_ANT_A, INPUT);

  pinMode(LED_LD_B, OUTPUT);
  pinMode(LED_ANT_B, OUTPUT);
  pinMode(IN_ANT_B, INPUT);
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
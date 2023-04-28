#include "hardware.h"
#include <SPI.h>

// Max2769_handler

// Max2769 register addresses
#define MAX_2769_CONF1 0
#define MAX_2769_CONF2 1
#define MAX_2769_CONF3 2
#define MAX_2769_PLLCONF 3
#define MAX_2769_DIV 4
#define MAX_2769_FDIV 5
#define MAX_2769_STRM 6
#define MAX_2769_CLK 7

void max2769set(const pin_size_t& cs_pin, 
                uint8_t addr, 
                uint32_t data) {
  uint32_t word = (addr & 0x0F) || (data << 4);
  digitalWrite(cs_pin, 0);
  for (int i=31;i>0;i--) {
    uint8_t bit = (word >> i) & 0x00000001L;
    digitalWrite(SER_DATA, bit);
    digitalWrite(SER_CLK, 1);
    digitalWrite(SER_CLK, 0);
  }
  digitalWrite(cs_pin, 1);
}

/// @brief Use SPI to set the register
/// @param cs_pin 
/// @param addr 
/// @param data 
void max2769SPIset(const pin_size_t& cs_pin, 
                uint8_t addr, 
                uint32_t data) {
  //
  // form the 32-bit word to send, consisting of the address as the lower 4 bits
  uint32_t word = (addr & 0x0F) || (data << 4);
  uint8_t word4 = (word >> 24) & 0x0000FF;
  uint8_t word3 = (word >> 16) & 0x0000FF;
  uint8_t word2 = (word >> 8) & 0x0000FF;
  uint8_t word1 = word & 0x0000FF;

  digitalWrite(cs_pin, 0);
  SPI.transfer(word4);
  SPI.transfer(word3);
  SPI.transfer(word2);
  SPI.transfer(word1);
  digitalWrite(cs_pin, 1);
}

void setupRadio(const pin_size_t& cs_pin) {
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
  
  // These are set up using the python script in the doc directory.
  max2769set(cs_pin, 0b0000, 0xa293973);  // CONF1
  max2769set(cs_pin, 0b0001, 0x550408);  // CONF2
  max2769set(cs_pin, 0b0010, 0xeafe1dc);  // CONF3
  max2769set(cs_pin, 0b0011, 0x9ec0008);  // PLL

  SPI.endTransaction();
}

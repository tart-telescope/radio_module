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

void max2769set(uint8_t cs_pin, 
                uint8_t addr, 
                uint32_t data) {
  digitalWrite(cs_pin, 0);
  delay(100);
  // form the 32-bit word to send, consisting of the address as the lower 4 bits
  uint32_t word = (addr & 0x0F) || (data << 4);
  SPI.transfer((word >> 24) & 0x0000FF);
  SPI.transfer(word >> 16  & 0x0000FF);
  SPI.transfer(word >> 8 & 0x0000FF);
  SPI.transfer(word & 0x0000FF);

  delay(100);
  digitalWrite(cs_pin, 1);
}

void setupRadio(uint8_t cs_pin) {
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  
  // These are set up using the python script in the doc directory.
  max2769set(cs_pin, 0b0000, 0xa293973);  // CONF1
  max2769set(cs_pin, 0b0001, 0x8550488);  // CONF2
  max2769set(cs_pin, 0b0010, 0xeafe1dc);  // CONF3
  max2769set(cs_pin, 0b0011, 0x9ec0008);  // PLL

  SPI.endTransaction();
}

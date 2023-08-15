#include <ch32v00x.h>
#include <debug.h>
#include "hardware.h"

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


void max2769set(GPIO_TypeDef *cs_port, pin_t cs_pin,
                uint8_t addr,
                uint32_t data)
{

    int i;
    uint32_t word = (addr & 0x0F) | (data << 4);
    GPIO_WriteBit(cs_port, cs_pin, Bit_RESET);
    GPIO_WriteBit(TART_SCLK_PORT, TART_SCLK_PIN, Bit_RESET);

    // Timing parameters from the Max2769 datasheet.
    // These are in microseconds.
    int t_CSS = 10;
    int t_DS = 10;
    int t_DH = 10;
    int t_CH = 25;
    int t_CL = 25;
    int t_CSH = 10;
    int t_CSW = t_CH + t_CL;

    Delay_Us(t_CSS); // t_CSS

    for (i = 31; i >= 0; i--)
    {
        uint8_t bit = (word >> i) & 0x00000001L;

        if (0 == bit)
            GPIO_WriteBit(TART_SDATA_PORT, TART_SDATA_PIN, Bit_RESET);
        else
            GPIO_WriteBit(TART_SDATA_PORT, TART_SDATA_PIN, Bit_SET);

        Delay_Us(t_DS); // t_DS = 10
        GPIO_WriteBit(TART_SCLK_PORT, TART_SCLK_PIN, Bit_SET);
        Delay_Us(t_CH); // t_CH = 25
        GPIO_WriteBit(TART_SCLK_PORT, TART_SCLK_PIN, Bit_RESET);
        Delay_Us(t_CL); // t_CL
    }
    GPIO_WriteBit(cs_port, cs_pin, Bit_SET);
    Delay_Ms(1);
}

void setupRadioStream(GPIO_TypeDef *cs_port, pin_t cs_pin)
{
  max2769set(cs_port, cs_pin, 0b0000, 0xa293973);  // CONF1
  max2769set(cs_port, cs_pin, 0b0001, 0x855028c);  // CONF2
  max2769set(cs_port, cs_pin, 0b0010, 0xeaff827);  // CONF 3 Streaming: reset 
  max2769set(cs_port, cs_pin, 0b0010, 0xeaff826);  // CONF 3 Streaming: 
  max2769set(cs_port, cs_pin, 0b0011, 0x9ec0008);  // PLL
  max2769set(cs_port, cs_pin, 0b0111, 0x10061b5);  // CLK
  max2769set(cs_port, cs_pin, 0b0010, 0xeaffc26);  // CONF 3 Streaming: start 
  // max2769set(cs_port, cs_pin, 0b0010, 0xeaff827);  // CONF 3 Streaming: reset 
}

void setupRadio(GPIO_TypeDef *cs_port, pin_t cs_pin)
{
  max2769set(cs_port, cs_pin, 0b0000, 0xa293973);  // max2769setCONF1
  max2769set(cs_port, cs_pin, 0b0001, 0x855020c);  // CONF2
  max2769set(cs_port, cs_pin, 0b0010, 0xeaff1dc);  // CONF3
  max2769set(cs_port, cs_pin, 0b0011, 0x9ec0008);  // PLL
}

void shutdownRadio(void) {
  GPIO_WriteBit(TART_SLOT_ENABLE_PORT, TART_SLOT_ENABLE_PIN, Bit_RESET);
}

void enableRadio(void) {
  GPIO_WriteBit(TART_SLOT_ENABLE_PORT, TART_SLOT_ENABLE_PIN, Bit_SET);
}
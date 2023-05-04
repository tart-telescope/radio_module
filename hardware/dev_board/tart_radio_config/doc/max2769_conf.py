
class Register:
    def __init__(self, name, address):
        self.name = name
        self.address = address
        self.val = [0] * 28
        
        
    def setBits(self, msb, lsb, value):
        if len(value) != (msb - lsb + 1):
            print(f" len(value) = {len(value)}: expected {(msb - lsb + 1)}")
        for i, b in enumerate(value):
            self.setBit(msb - i, b)

    def setBit(self, msb, b):
        self.val[msb] = b
        
    def getValue(self):
        ret = 0;
        for i,b in enumerate(self.val):
            ret += int(b) * 2**i
        
        return ret
    
    def disp(self):
        print(f"  max2769set(cs_port, cs_pin, 0b{self.address}, 0x{self.getValue() :x});  // {self.name}")

def getConf1():
    reg = Register("CONF1", "0000")
    reg.setBit(27, "1");   # ret[27] = 1; enable
    reg.setBit(26, "0");   # IDLE Idle enable. Set 1 to put the chip in the idle mode and 0 for operating mode.
    reg.setBits(25, 22, "1000");   # Reserved
    reg.setBits(21, 20, "10");   # Reserved
    reg.setBits(19, 18, "10");   # Reserved
    reg.setBits(17, 16, "01");   # Reserved
    reg.setBit(15, "0");   # MIXPOLE
    reg.setBits(14, 13, "01");   # ret[14:13] = '01': LNA2 on, '00': Choose with ant bias
    reg.setBit(12, "1");   # MIXEN enable mixer
    reg.setBit(11, "1");   # ANTEN enable antenna bias
    reg.setBits(10, 5, "001011"); # FCEN 
                                  #  IF center frequency programming.
                                  #     '001101' = 3.092MHz, 
                                  #     '001011' = 4.092MHz
                                  #     '010011' = 10.0MHz
    reg.setBits(4, 3, "10");      # RBW = '00': 2.5MHz, '10': 4.2 MHz, '01': 9.66MHz
    reg.setBit(2, "0"); # 0: 3rd order, 1: 5th order Butterworth
    reg.setBit(1, "1"); # Complex bandpass filter mode
    reg.setBit(0, "1"); # Keep filter gain
    return reg


def getConf2():
    reg = Register("CONF2", "0001")
    reg.setBit(27, "1");   # IQEN enable (I channel only is 0)
    reg.setBits(26, 15, "000010101010");   # GAINREF
    reg.setBits(14, 13, "00");   # Reserved
    reg.setBits(12, 11, "00");   # AGC Mode INDEPENDENT I/Q
    reg.setBits(10, 9, "01");   # FORMAT '01': Sign Magnitude, 
    reg.setBits(8, 6, "010");   # 1 bits ADC ('000': 1-bit, '010': 2-bits, '100': 3-bits)0
    reg.setBits(5, 4, "00");   # DRVCFG '00': CMOS logic, '01': Differential?, '1x': Analog
    reg.setBit(3, "1");   # Reserved
    reg.setBit(2, "1");   # Reserved
    reg.setBits(1, 0, "00");   # DIEID
    return reg

def getConf3Normal():
    reg = Register("CONF3", "0010")
    reg.setBits(27, 22, "111010");   # GAININ 57 dB
    reg.setBit(21, "1");   # RESERVED
    reg.setBit(20, "0");   # HIGHLOADEN # TODO
    reg.setBit(19, "1");   # RESERVED
    reg.setBit(18, "1");   # RESERVED
    reg.setBit(17, "1");   # RESERVED
    reg.setBit(16, "1");   # RESERVED
    reg.setBit(15, "1");   # FHIPEN Highpass coupling
    reg.setBit(14, "1");   # RESERVED
    reg.setBit(13, "1");   # PGAIEN I channel PGA Enable
    reg.setBit(12, "1");   # PGAQEN Q channel PGA Enable
    reg.setBit(11, "0");   # STRMEN
    reg.setBit(10, "0");   # STRMSTART
    reg.setBit(9, "0");   # STRMSTOP
    reg.setBits(8, 6, "111");   # STRM_COUNT 111 -> 16384 000->128
    reg.setBits(5, 4, "01");   # NUMBER of bits streamed STRMBITS
    reg.setBit(3, "1");   # STAMPEN
    reg.setBit(2, "1");   # TIMESYNCEN
    reg.setBit(1, "0");   # DATASYNCEN
    reg.setBit(0, "0");   # STRMRST Reset all counters
    return reg


def getConf3Stream(start=0, reset=0):
    title = "CONF 3 Streaming: "
    if start == 1:
        title += "start "
    if reset == 1:
        title += "reset "
        
    reg = Register(title, "0010")
    reg.setBits(27, 22, "111010");   # GAININ 57 dB
    reg.setBit(21, "1");   # RESERVED
    reg.setBit(20, "0");   # HIGHLOADEN
    reg.setBit(19, "1");   # RESERVED
    reg.setBit(18, "1");   # RESERVED
    reg.setBit(17, "1");   # RESERVED
    reg.setBit(16, "1");   # RESERVED
    reg.setBit(15, "1");   # FHIPEN Highpass coupling
    reg.setBit(14, "1");   # RESERVED
    reg.setBit(13, "1");   # PGAIEN I channel PGA Enable
    reg.setBit(12, "1");   # PGAQEN Q channel PGA Enable
    reg.setBit(11, "1");   # STRMEN
    reg.setBit(10, start);   # STRMSTART
    reg.setBit(9, "0");   # STRMSTOP
    reg.setBits(8, 6, "000");    # STRM_COUNT 111 -> 16384 000->128
    reg.setBits(5, 4, "11");   # NUMBER of bits streamed STRMBITS 
                            #       00: I MSB
                            #       01: I MSB, I LSB,
                            #       10: I MSB, Q MSB,
                            #       11: I MSB, I LSB, Q MSB, Q LSB,
    reg.setBit(3, "0");   # STAMPEN Stream the time stamp
    reg.setBit(2, "0");   # TIMESYNCEN
    reg.setBit(1, "1");   # DATASYNCEN
    reg.setBit(0,  reset);    # STRMRST Reset all counters
    return reg


def getPLL():
    reg = Register("PLL", "0011")
    reg.setBit(27, 1);   # RESERVED
    reg.setBit(26, 0);   # RESERVED
    reg.setBit(25, 0);   # RESERVED
    reg.setBit(24, 1);   # REFOUTEN Clock buffer enable
    reg.setBit(23, 1);   # RESERVED
    reg.setBits(22, 21, "00");   # REFDIV clock frequency = XTAL
    reg.setBits(20, 19, "01");   # IXTAL Current programming
    reg.setBits(18, 14, "10000");   # RESERVED
    reg.setBits(13, 10, "0000");   # LDMUX PLL lock detect enable
    reg.setBit(9, 0);   # ICP Charge pump current
    reg.setBit(8, 0);   # PFDEN
    reg.setBit(7, 0);   # RESERVED
    reg.setBits(6, 4, "000");   # RESERVED
    reg.setBit(3, 1);   # INT_PLL
    reg.setBit(2, 0);   # PWRSAV
    reg.setBit(1, 0);   # RESERVED
    reg.setBit(0, 0);   # RESERVED
    return reg


def getCLK(L_CNT=256, M_CNT=1563):
    reg = Register("CLK", "0111")
    reg.setBits(27, 16, f"{L_CNT:>012b}")  # L_CNT Sets the value for the L counter. 
                                        # 000100000000 = 256 fractional clock divider,
                                        # 100000000000 = 2048 fractional clock divider.
    reg.setBits(15,4, f"{M_CNT:>012b}")  # M_CNT Sets the value for the M counter
    reg.setBit(3, 0)    # FCLKIN Fractional clock divider. (REFDIV in PLL register)
                        # Set 1 to select the ADC clock to come from the fractional clock divider, 
                        # or 0 to bypass the ADC clock from the fractional clock divider.
    reg.setBit(2, 1)    # ADCCLK ADC clock selection. 
                        # Set 0 to select the ADC and fractional divider clocks to come from
                        # the reference divider/multiplier.
    reg.setBit(1, 0)    # SERCLK_SEL. 0 selects the serializer clock to come from the reference divider.
    reg.setBit(0, 1)    # MODE. DSP interface mode selection
                        # Set to 1 for standard mode operation.
    return reg


import argparse

if __name__=="__main__":
    parser = argparse.ArgumentParser(description='Configure Max2769 Registers radio telescope.',
                                     formatter_class=argparse.ArgumentDefaultsHelpFormatter)

    parser.add_argument('--stream', '-s', action="store_true",
                        help="Enable streaming")
    ARGS = parser.parse_args()

    LCOUNT = 256
    MCOUNT = 1563
    fIn = 16.368e6
    fOUT_fIN = LCOUNT/(4096 - MCOUNT + LCOUNT)
    print(fOUT_fIN)
    print(f"fractional clk = {fOUT_fIN*fIn}")
    getConf1().disp()
    getConf2().disp()
    if ARGS.stream:
        getConf3Stream(reset=1).disp()
        getConf3Stream(start=0, reset=0).disp()
    else:
        getConf3Normal().disp()
    getPLL().disp()

    if ARGS.stream:
        getCLK(L_CNT=LCOUNT, M_CNT=MCOUNT).disp()
        getConf3Stream(start=1).disp()


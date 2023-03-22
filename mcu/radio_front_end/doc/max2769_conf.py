
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
        print(f"  max2769set(cs_pin, 0b{self.address}, 0x{self.getValue() :x});  // {self.name}")

def getConf1():
    reg = Register("CONF1", "0000")
    reg.setBits(27, 27, "1");   # ret[27] = 1; enable
    reg.setBits(26, 26, "0");   # IDLE off
    reg.setBits(25, 22, "1000");   # Reserved
    reg.setBits(21, 20, "10");   # Reserved
    reg.setBits(19, 18, "10");   # Reserved
    reg.setBits(17, 16, "01");   # Reserved
    reg.setBits(15, 15, "0");   # MIXPOLE
    reg.setBits(14, 13, "01");   # ret[14:13] = 01 LNA2 on
    reg.setBits(12, 12, "1");   # MIXEN enable mixer
    reg.setBits(11, 11, "1");   # ANTEN enable antenna
    reg.setBits(10, 5, "001011"); # FCEN = 4.092 MHz
    reg.setBits(4, 3, "10"); # RBW = 4.2 MHz
    reg.setBits(2, 2, "0"); # 5th order Butterworth
    reg.setBits(1, 1, "1"); # Complex bandpass filter mode
    reg.setBits(0, 0, "1"); # Keep filter gain
    return reg


def getConf2():
    reg = Register("CONF2", "0001")
    reg.setBits(27, 27, "1");   # IQEN enable
    reg.setBits(26, 15, "000010101010");   # GAINREF
    reg.setBits(14, 13, "00");   # Reserved
    reg.setBits(12, 11, "00");   # AGC Mode INDEPENDENT I/Q
    reg.setBits(10, 9, "10");   # FORMAT Sign Magnitude
    reg.setBits(8, 6, "010");   # 2 bits ADC
    reg.setBits(5, 4, "00");   # DRVCFG CMOS logic
    reg.setBits(3, 3, "1");   # Reserved
    reg.setBits(2, 2, "0");   # Reserved
    reg.setBits(1, 0, "00");   # DIEID
    return reg

def getConf3():
    reg = Register("CONF3", "0010")
    reg.setBits(27, 22, "111010");   # GAININ 57 dB
    reg.setBits(21, 21, "1");   # RESERVED
    reg.setBits(20, 20, "0");   # HIGHLOADEN
    reg.setBits(19, 19, "1");   # RESERVED
    reg.setBits(18, 18, "1");   # RESERVED
    reg.setBits(17, 17, "1");   # RESERVED
    reg.setBits(16, 16, "1");   # RESERVED
    reg.setBits(15, 15, "1");   # FHIPEN Highpass coupling
    reg.setBits(14, 14, "1");   # RESERVED
    reg.setBits(13, 13, "1");   # RESERVED
    reg.setBits(12, 12, "0");   # RESERVED
    reg.setBits(11, 11, "0");   # STRMEN
    reg.setBits(10, 10, "0");   # STRMSTART
    reg.setBits(9, 9, "0");   # STRMSTOP
    reg.setBits(8, 6, "111");   # RESERVED
    reg.setBits(5, 4, "01");   # NUMBER of bits streamed STRMBITS
    reg.setBits(3, 3, "1");   # STAMPEN
    reg.setBits(2, 2, "1");   # TIMESYNCEN
    reg.setBits(1, 1, "0");   # DATASYNCEN
    reg.setBits(0, 0, "0");   # STRMRST Reset all counters
    return reg


def getPLL():
    reg = Register("PLL", "0011")
    reg.setBit(27, 1);   # RESERVED
    reg.setBit(26, 0);   # RESERVED
    reg.setBit(25, 0);   # RESERVED
    reg.setBit(24, 1);   # REFOUTEN Clock buffer enable
    reg.setBit(23, 1);   # RESERVED
    reg.setBits(22, 21, "11");   # REFDIV clock frequency = XTAL
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
    return reg

if __name__=="__main__":
    getConf1().disp()
    getConf2().disp()
    getConf3().disp()
    getPLL().disp()

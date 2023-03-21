YOSYS ?= yowasp-yosys
NEXTPNR ?= yowasp-nextpnr-gowin
PROGRAMMER ?= /usr/local/bin/openFPGALoader
DEVICE ?= GW1N-LV1QN48C6/I5
DEVICE_FAMILY ?= GW1N-1
CST ?= radio_module.cst
BOARD ?= tangnano
#
# The tang nano 4k is
# DEVICE = GW1NSR-LV4CQN48PC7/I6
# LED = 8

all:
	make radio_module-prog
	
clean:
	rm -f *.json *.fs *-unpacked.v
	
.PHONY: all clean 4k

%-synth.json: %.v
	$(YOSYS) -p "read_verilog $^; synth_gowin -json $@" $^

%.json: %-synth.json ${CST}
	$(NEXTPNR) --json $< --write $@ --device ${DEVICE} --cst ${CST}

%.fs: %.json
	gowin_pack -d ${DEVICE_FAMILY} -o $@ $^

%-default-flags.json: %-synth.json
	$(NEXTPNR) --json $^ --write $@ --device ${DEVICE} \
		--cst iob/tangnano-default.cst

%-prog: %.fs
	$(PROGRAMMER) -f --cable ft2232_b -b ${BOARD} $^
	
%-unpacked.v: %.fs
	gowin_unpack -d ${DEVICE_FAMILY} -o $@ $^

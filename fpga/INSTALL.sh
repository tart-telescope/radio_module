#!/bin/sh
# Install the tools required to build the FPGA
#
pip3 install yowasp-yosys --upgrade --break-system-packages
pip3 install yowasp-nextpnr-gowin --upgrade --break-system-packages

#!/bin/sh
# Install the tools required to build the FPGA
#
pipx install yowasp-yosys 
pipx install yowasp-nextpnr-gowin
pipx upgrade yowasp-yosys 
pipx upgrade yowasp-nextpnr-gowin

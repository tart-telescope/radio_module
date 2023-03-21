# f_clkout = f_clkin * FBDIV / IDIV
# f_vco  = f_clkout * ODIV
# f_clkoutd = f_clkout / SDIV

# Desired behaviour clkin = 16
#     clkoutd = 8
#     clkout = clkin * 4 
#     
# FBDIV / IDIV = 4
# FBDIV / (IDIV * SDIV) = 0.5
# 
# VCO = FCLKIN*(FBDIV_SEL+1)*ODIV_SEL/(IDIV_SEL+1) = 1024.0MHz not in range 400 - 900MHz
f_clkin = 16
f_radio = 8

for fbdiv_sel in range(0,63):
    for idiv_sel in range(0,63):
        for sdiv in range(2,128,2):
            for ODIV in [2,4,8,16,32,48,64,80,96,112,128]:

                FBDIV = fbdiv_sel + 1
                IDIV = idiv_sel + 1
                SDIV = sdiv
                
                f_clkout = f_clkin * FBDIV / IDIV
                f_vco  = f_clkout * ODIV
                f_clkoutd = f_clkout / SDIV    

                if f_vco < 400 or f_vco > 900:
                    continue
                
                if f_clkoutd != 8:
                    continue

                if f_clkout != 4*f_radio:
                    continue
                
                print(f" fbdiv_sel = {fbdiv_sel}, idiv_sel = {idiv_sel}, sdiv={sdiv} odiv={ODIV} f_vco={f_vco}")

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


def get_pll(f_clkin, f_radio, multiplier):
    print(f"// PLL configuration for f_clkin={f_clkin}, f_radio={f_radio}, multiplier={multiplier}")
    for fbdiv_sel in range(1,63):
        for idiv_sel in range(1,63):
            for sdiv in range(2,128,2):
                for ODIV in [2,4,8,16,32,48,64,80,96,112,128]:

                    FBDIV = fbdiv_sel + 1
                    IDIV = idiv_sel + 1
                    SDIV = sdiv
                    
                    f_clkout = f_clkin * FBDIV / IDIV
                    f_vco  = f_clkout * ODIV
                    f_clkoutd = f_clkout / SDIV    

                    if f_vco < 400:
                        continue
                    
                    if f_vco > 900:
                        continue
                    
                    if f_clkoutd != f_radio:
                        continue

                    if f_clkout != multiplier*f_radio:
                        continue
                    
                    print(f" fbdiv_sel = {fbdiv_sel}, idiv_sel = {idiv_sel}, sdiv={sdiv} odiv={ODIV} f_vco={f_vco}")
                    return {'f_clkin': f_clkin, 'fbdiv_sel': fbdiv_sel,  'idiv_sel': idiv_sel, 'sdiv': sdiv, 'odiv': ODIV}
    
res = get_pll(f_clkin = 16, f_radio = 8, multiplier=2)
print(f"`define PLL_FCLKIN {res['f_clkin']}");
print(f"`define PLL_FBDIV_SEL {res['fbdiv_sel']}");
print(f"`define PLL_IDIV_SEL  {res['idiv_sel']}");
print(f"`define PLL_ODIV_SEL  {res['odiv']}");
print(f"`define DYN_SDIV_SEL  {res['sdiv']}");

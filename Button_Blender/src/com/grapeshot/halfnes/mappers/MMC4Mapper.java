package com.grapeshot.halfnes.mappers;

import com.grapeshot.halfnes.*;

public class MMC4Mapper extends Mapper {

    boolean chrlatchL = true;
    boolean chrlatchR = false;
    int chrbankL1 = 0;
    int chrbankR1 = 0;
    int chrbankL2 = 0;
    int chrbankR2 = 0;

    @Override
    public void loadrom() throws BadMapperException {
        //needs to be in every mapper. Fill with initial cfg
        super.loadrom();
        //on startup:
        for (int i = 1; i <= 32; ++i) {
            prg_map[32 - i] = prgsize - (1024 * i);
        }
        for (int i = 0; i < 8; ++i) {
            chr_map[i] = 0;
        }
    }

    @Override
    public final void cartWrite(int addr, int data) {
        if (addr < 0x8000 || addr > 0xffff) {
            super.cartWrite(addr, data);
            return;
        } else if (addr >= 0x8000 && addr <= 0xafff) {
            //remap prg
            for (int i = 0; i < 16; ++i) {
                prg_map[i] = (1024 * (i + 16 * data)) & (prgsize - 1);
            }
        } else if (addr >= 0xb000 && addr <= 0xbfff) {
            chrbankL1 = data & 0x1f;
            setupPPUBanks();
        } else if (addr >= 0xc000 && addr <= 0xcfff) {
            chrbankL2 = data & 0x1f;
            setupPPUBanks();
        } else if (addr >= 0xd000 && addr <= 0xdfff) {
            chrbankR1 = data & 0x1f;
            setupPPUBanks();
        } else if (addr >= 0xe000 && addr <= 0xefff) {
            chrbankR2 = data & 0x1f;
            setupPPUBanks();
        } else if (addr >= 0xf000 && addr <= 0xffff) {
            setmirroring((utils.getbit(data, 0)) ? MirrorType.H_MIRROR : MirrorType.V_MIRROR);
        }
    }

    @Override
    public int ppuRead(final int addr) {
        int retval = super.ppuRead(addr);
        if (utils.getbit(addr,3)) {
            //latch fires after 2nd read from pattern table
            //A3 will be on for 2nd read b/c it's tile low bytes
            if (addr >> 4 == 0xfd) {
                chrlatchL = false;
                setupPPUBanks();
            } else if (addr >> 4 == 0xfe) {
                chrlatchL = true;
                setupPPUBanks();
            } else if (addr >= 0x1fd0 && addr <= 0x1fdf) {
                chrlatchR = false;
                setupPPUBanks();
            } else if (addr >= 0x1fe0 && addr <= 0x1fef) {
                chrlatchR = true;
                setupPPUBanks();
            }
        }
        return retval;
    }

    private void setupPPUBanks() {
        if (chrlatchL) {
            setppubank(4, 0, chrbankL2);
        } else {
            setppubank(4, 0, chrbankL1);
        }
        if (chrlatchR) {
            setppubank(4, 4, chrbankR2);
        } else {
            setppubank(4, 4, chrbankR1);
        }
    }

    private void setppubank(int banksize, int bankpos, int banknum) {
        for (int i = 0; i < banksize; ++i) {
            chr_map[i + bankpos] = (1024 * ((banksize * banknum) + i)) % chrsize;
        }
    }
}

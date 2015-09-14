#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

void init_ppu() {
    *REGIST_PPU_CTRL1 = 0x00;
    *REGIST_PPU_CTRL2 = 0x00;
}

void set_ppu(unsigned char flag1, unsigned char flag2) {
    *REGIST_PPU_CTRL1 = flag1;
    *REGIST_PPU_CTRL2 = flag2;
}

void set_scroll(unsigned char x, unsigned char y) {
    *REGIST_SCROLL = x;
    *REGIST_SCROLL = y;
}

void fill_background(unsigned char address1, unsigned char address2, unsigned char val, unsigned char cnt) {
    char i;

    *REGIST_ADR = address1;
    *REGIST_ADR = address2;

    for (i = 0; i < cnt; i++) {
        *REGIST_GRA = val;
    }
}

void set_background(unsigned char address1, unsigned char address2, unsigned char *bg, unsigned char cnt) {
    char i;

    *REGIST_ADR = address1;
    *REGIST_ADR = address2;

    for (i = 0; i < cnt; i++) {
        *REGIST_GRA = *(bg + i);
    }
}

void get_background_address(unsigned char screen, unsigned char x, unsigned char y, char *ret) {
    unsigned int pos;

    switch (screen) {
        case 0:
            pos = 0x2000;
            break;
        case 1:
            pos = 0x2800;
            break;
        case 2:
            pos = 0x2400;
            break;
        case 3:
            pos = 0x2c00;
            break;
    }

    pos += y * 0x20 + x;
    *(ret + 0) = (pos & 0xff00) >> 8;
    *(ret + 1) = pos & 0x00ff;
}

void fill_attribute(unsigned char address1, unsigned char address2, unsigned char val, unsigned char cnt) {
    fill_background(address1, address2, val, cnt);
}

void set_attribute(unsigned char address1, unsigned char address2, unsigned char *atr, unsigned char cnt) {
    set_background(address1, address2, atr, cnt);
}

void set_palette(unsigned char *palette, unsigned char sprite) {
    char i;

    *REGIST_ADR = 0x3f;
    if (sprite) {
        *REGIST_ADR = 0x10;
    } else {
        *REGIST_ADR = 0x00;
    }

    for (i = 0; i < 16; i++) {
        *REGIST_GRA = *(palette + i);
    }
}

void set_palette_bg(unsigned char *palette) {
    set_palette(palette, 0);
}

void set_palette_spr(unsigned char *palette) {
    set_palette(palette, 1);
}

void set_sprite(unsigned char first, unsigned char x, unsigned char y, unsigned char index, unsigned char flag) {
    if (first) {
        *REGIST_SPR_ADR = 0x00;
    }
    *REGIST_SPR_GRA = y;
    *REGIST_SPR_GRA = index;
    *REGIST_SPR_GRA = flag;
    *REGIST_SPR_ADR = x;
}

void init_dma(unsigned char *address) {
    unsigned char i;
    for (i = 0; i < 256; i++) {
        *(address + i) = 0;
    }
}

void set_dma(unsigned char *address, unsigned char first, unsigned char x, unsigned char y, unsigned char index, unsigned char flag) {
    static unsigned char cnt;

    if (first) {
        cnt = 0;
    }

    *(address + cnt + 0) = y;
    *(address + cnt + 1) = index;
    *(address + cnt + 2) = flag;
    *(address + cnt + 3) = x;
    cnt += 4;
}

void send_dma(unsigned char address) {
    *REGIST_DMA = address;
}

void vblank() {
    while (!(*REGIST_PPU_STS & 0x80));
}

void zero_sprite() {
    while ((*REGIST_PPU_STS & 0x40));
    while (!(*REGIST_PPU_STS & 0x40));
}

#endif


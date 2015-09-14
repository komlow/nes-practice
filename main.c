#include "registers.h"
#include "graphic.h"

void NesMain(void) {
    unsigned char bgy = 0;
    const char palettebg[] = {
        0x0f, 0x11, 0x21, 0x30,
        0x0f, 0x11, 0x21, 0x30,
        0x0f, 0x11, 0x21, 0x30,
        0x0f, 0x11, 0x21, 0x30
    };

    const char palettespr[] = {
        0x0f, 0x00, 0x10, 0x21,
        0x0f, 0x0f, 0x10, 0x21,
        0x0f, 0x09, 0x19, 0x21,
        0x0f, 0x15, 0x27, 0x30
    };

    init_ppu();

    set_palette((char *)palettebg, 0);
    set_palette((char *)palettespr, 1);

    set_background(0x21, 0xc9, "HELLO, WORLD!", 13);

    set_scroll(0, 0);
    set_ppu(0x08, 0x1e);

    while (1) {
        vblank();

        bgy++;

        if (bgy == 240) { bgy == 0; }
        set_scroll(0, bgy);
        frame++;
    }
}

void NMIProc(void) {
}

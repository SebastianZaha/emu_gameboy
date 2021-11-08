
// https://problemkaputt.de/pandocs.htm

// 20x18 8x8 tiles
const uint SCREEN_W = 160;
const uint SCREEN_H = 144;


// Cartridge header

const uint CH_LOGO      = 0x0104; // upto 0x0133
const uint CH_TITLE     = 0x0134;
const uint CH_TITLE_END = 0x0143;
const uint CH_SGB_FLAG  = 0x0146;
const uint CH_TYPE      = 0x0147;
/* 0147 - Cartridge Type
    Specifies which Memory Bank Controller (if any) is used in the cartridge, and if further external hardware exists in the cartridge.
    00h  ROM ONLY                 13h  MBC3+RAM+BATTERY
    01h  MBC1                     15h  MBC4
    02h  MBC1+RAM                 16h  MBC4+RAM
    03h  MBC1+RAM+BATTERY         17h  MBC4+RAM+BATTERY
    05h  MBC2                     19h  MBC5
    06h  MBC2+BATTERY             1Ah  MBC5+RAM
    08h  ROM+RAM                  1Bh  MBC5+RAM+BATTERY
    09h  ROM+RAM+BATTERY          1Ch  MBC5+RUMBLE
    0Bh  MMM01                    1Dh  MBC5+RUMBLE+RAM
    0Ch  MMM01+RAM                1Eh  MBC5+RUMBLE+RAM+BATTERY
    0Dh  MMM01+RAM+BATTERY        FCh  POCKET CAMERA
    0Fh  MBC3+TIMER+BATTERY       FDh  BANDAI TAMA5
    10h  MBC3+TIMER+RAM+BATTERY   FEh  HuC3
    11h  MBC3                     FFh  HuC1+RAM+BATTERY
    12h  MBC3+RAM */

uint const CH_ROM_SIZE = 0x0148;
/* 0148 - ROM Size
    Specifies the ROM Size of the cartridge. Typically calculated as "32KB shl N".
      00h -  32KByte (no ROM banking)
      01h -  64KByte (4 banks)
      02h - 128KByte (8 banks)
      03h - 256KByte (16 banks)
      04h - 512KByte (32 banks)
      05h -   1MByte (64 banks)  - only 63 banks used by MBC1
      06h -   2MByte (128 banks) - only 125 banks used by MBC1
      07h -   4MByte (256 banks)
      52h - 1.1MByte (72 banks)
      53h - 1.2MByte (80 banks)
      54h - 1.5MByte (96 banks) */

uint const CH_RAM_SIZE = 0x0149;
/*0149 - RAM Size
    Specifies the size of the external RAM in the cartridge (if any).
      00h - None
      01h - 2 KBytes
      02h - 8 Kbytes
      03h - 32 KBytes (4 banks of 8KBytes each)
    When using a MBC2 chip 00h must be specified in this entry, even though the MBC2 includes a built-in RAM of 512 x 4 bits. */

uint const CH_DESTINATION_CODE = 0x014A;
/* 014A - Destination Code
    Specifies if this version of the game is supposed to be sold in japan, or anywhere else. Only two values are defined.
    00h - Japanese
    01h - Non-Japanese */

const uint8_t LOGO[] {
    0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
    0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
    0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E};
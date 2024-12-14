/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --no-compress --font Roboto-Regular.ttf --symbols
 *AĄBCĆDEĘFGHIJKLŁMNOÓPQRSŚTUVWXYZŹŻZQVXaąbcćdeęfghijklłmnoópqrsśtuvwxyzźżzqvx
 *--format lvgl -o lv_font_roboto_16.c
 ******************************************************************************/

#include "screens/fonts.h"

#if LV_FONT_ROBOTO_16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0041 "A" */
    0xc, 0x3, 0x0, 0xe0, 0x68, 0x13, 0x4, 0xc3, 0x10, 0x86, 0x7f, 0x98, 0x24,
    0xf, 0x3,

    /* U+0042 "B" */
    0xfd, 0xe, 0xc, 0x18, 0x7f, 0xa1, 0xc1, 0x83, 0x6, 0x1f, 0xe0,

    /* U+0043 "C" */
    0x3c, 0x42, 0x43, 0x81, 0x80, 0x80, 0x80, 0x80, 0x81, 0x43, 0x42, 0x3c,

    /* U+0044 "D" */
    0xf8, 0x86, 0x82, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x82, 0x86, 0xf8,

    /* U+0045 "E" */
    0xff, 0x2, 0x4, 0x8, 0x1f, 0xa0, 0x40, 0x81, 0x2, 0x7, 0xf0,

    /* U+0046 "F" */
    0xff, 0x2, 0x4, 0x8, 0x10, 0x3f, 0x40, 0x81, 0x2, 0x4, 0x0,

    /* U+0047 "G" */
    0x3e, 0x30, 0x90, 0x30, 0x8, 0x4, 0x2, 0x1f, 0x1, 0x80, 0xa0, 0x58, 0x63,
    0xe0,

    /* U+0048 "H" */
    0x81, 0x81, 0x81, 0x81, 0x81, 0xff, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,

    /* U+0049 "I" */
    0xff, 0xf0,

    /* U+004A "J" */
    0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x81, 0x3, 0x7, 0x13, 0xc0,

    /* U+004B "K" */
    0x82, 0x86, 0x8c, 0x98, 0xb0, 0xf0, 0xf0, 0x98, 0x8c, 0x84, 0x86, 0x83,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x82, 0x8, 0x3f,

    /* U+004D "M" */
    0xc0, 0x78, 0xf, 0x83, 0xf0, 0x7a, 0xb, 0x63, 0x64, 0x4c, 0xd9, 0x9b, 0x31,
    0x46, 0x38, 0xc2, 0x10,

    /* U+004E "N" */
    0x81, 0xc1, 0xe1, 0xe1, 0xb1, 0x99, 0x99, 0x8d, 0x85, 0x87, 0x83, 0x81,

    /* U+004F "O" */
    0x3e, 0x31, 0x90, 0x50, 0x18, 0xc, 0x6, 0x3, 0x1, 0x80, 0xa0, 0x98, 0xc7,
    0xc0,

    /* U+0050 "P" */
    0xfc, 0x82, 0x81, 0x81, 0x81, 0x82, 0xfc, 0x80, 0x80, 0x80, 0x80, 0x80,

    /* U+0051 "Q" */
    0x3e, 0x31, 0x90, 0x50, 0x18, 0xc, 0x6, 0x3, 0x1, 0x80, 0xa0, 0xd8, 0xc7,
    0xe0, 0x18, 0x4,

    /* U+0052 "R" */
    0xfc, 0x41, 0x20, 0x50, 0x28, 0x14, 0x1b, 0xf9, 0xc, 0x86, 0x41, 0x20, 0xd0,
    0x20,

    /* U+0053 "S" */
    0x1c, 0x62, 0x41, 0x40, 0x60, 0x38, 0xe, 0x3, 0x1, 0x81, 0x43, 0x3c,

    /* U+0054 "T" */
    0xff, 0x84, 0x2, 0x1, 0x0, 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1, 0x0,

    /* U+0055 "U" */
    0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3c,

    /* U+0056 "V" */
    0xc0, 0xd0, 0x26, 0x9, 0x86, 0x21, 0xc, 0x41, 0x30, 0x48, 0x1a, 0x3, 0x80,
    0xc0, 0x30,

    /* U+0057 "W" */
    0x43, 0xd, 0xc, 0x36, 0x30, 0x98, 0xe2, 0x26, 0x98, 0x92, 0x62, 0x4d, 0xd,
    0x14, 0x3c, 0x50, 0x61, 0xc1, 0x86, 0x6, 0x8,

    /* U+0058 "X" */
    0x61, 0x98, 0x63, 0x30, 0x48, 0x1e, 0x3, 0x0, 0xc0, 0x78, 0x12, 0xc, 0xc6,
    0x19, 0x82,

    /* U+0059 "Y" */
    0xc1, 0xa0, 0x98, 0xc4, 0x43, 0x60, 0xa0, 0x70, 0x10, 0x8, 0x4, 0x2, 0x1,
    0x0,

    /* U+005A "Z" */
    0xff, 0x3, 0x6, 0x4, 0xc, 0x18, 0x18, 0x30, 0x20, 0x60, 0xc0, 0xff,

    /* U+0061 "a" */
    0x7b, 0x38, 0x41, 0x7f, 0x18, 0x63, 0x7c,

    /* U+0062 "b" */
    0x81, 0x2, 0x5, 0xcc, 0x50, 0x60, 0xc1, 0x83, 0x7, 0x17, 0xc0,

    /* U+0063 "c" */
    0x3c, 0x8e, 0x1c, 0x8, 0x10, 0x20, 0xa3, 0x3c,

    /* U+0064 "d" */
    0x2, 0x4, 0x9, 0xf4, 0x70, 0x60, 0xc1, 0x83, 0x5, 0x19, 0xf0,

    /* U+0065 "e" */
    0x38, 0x8a, 0xc, 0x1f, 0xf0, 0x20, 0x21, 0x3c,

    /* U+0066 "f" */
    0x19, 0x8, 0x4f, 0x90, 0x84, 0x21, 0x8, 0x42, 0x0,

    /* U+0067 "g" */
    0x3e, 0x8e, 0xc, 0x18, 0x30, 0x60, 0xa3, 0x3e, 0x7, 0x13, 0xc0,

    /* U+0068 "h" */
    0x82, 0x8, 0x2e, 0xc6, 0x18, 0x61, 0x86, 0x18, 0x61,

    /* U+0069 "i" */
    0x9f, 0xf0,

    /* U+006A "j" */
    0x20, 0x12, 0x49, 0x24, 0x92, 0x70,

    /* U+006B "k" */
    0x81, 0x2, 0x4, 0x69, 0x96, 0x38, 0x70, 0xb1, 0x32, 0x34, 0x60,

    /* U+006C "l" */
    0xff, 0xf0,

    /* U+006D "m" */
    0xfb, 0xd8, 0xc6, 0x10, 0xc2, 0x18, 0x43, 0x8, 0x61, 0xc, 0x21, 0x84, 0x20,

    /* U+006E "n" */
    0xbb, 0x18, 0x61, 0x86, 0x18, 0x61, 0x84,

    /* U+006F "o" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xa2, 0x38,

    /* U+0070 "p" */
    0xf9, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xe2, 0xf9, 0x2, 0x4, 0x0,

    /* U+0071 "q" */
    0x3e, 0x8e, 0xc, 0x18, 0x30, 0x60, 0xa3, 0x3e, 0x4, 0x8, 0x10,

    /* U+0072 "r" */
    0xfc, 0x88, 0x88, 0x88, 0x80,

    /* U+0073 "s" */
    0x39, 0x14, 0x58, 0x38, 0x38, 0x71, 0x78,

    /* U+0074 "t" */
    0x21, 0x3e, 0x42, 0x10, 0x84, 0x21, 0x6,

    /* U+0075 "u" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x63, 0x7c,

    /* U+0076 "v" */
    0xc2, 0x85, 0x9b, 0x22, 0x45, 0x8e, 0xc, 0x18,

    /* U+0077 "w" */
    0xc6, 0x34, 0x62, 0x46, 0x26, 0xf6, 0x29, 0x42, 0x94, 0x39, 0xc3, 0xc, 0x10,
    0x80,

    /* U+0078 "x" */
    0x42, 0x66, 0x3c, 0x18, 0x18, 0x18, 0x2c, 0x66, 0x42,

    /* U+0079 "y" */
    0x87, 0x8b, 0x32, 0x66, 0x8d, 0xe, 0x18, 0x30, 0x40, 0x86, 0x0,

    /* U+007A "z" */
    0xfe, 0xc, 0x30, 0xc3, 0x6, 0x18, 0x60, 0xfe,

    /* U+00D3 "Ó" */
    0x6, 0x2, 0x2, 0x0, 0x3, 0xe3, 0x19, 0x5, 0x1, 0x80, 0xc0, 0x60, 0x30, 0x18,
    0xa, 0x9, 0x8c, 0x7c,

    /* U+00F3 "ó" */
    0x8, 0x20, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x83, 0x5, 0x11, 0xc0,

    /* U+0104 "Ą" */
    0xc, 0x3, 0x1, 0xc0, 0x48, 0x12, 0xc, 0x82, 0x11, 0xfc, 0x41, 0x10, 0x2c,
    0xb, 0x2, 0x1, 0x80, 0x40, 0x18,

    /* U+0105 "ą" */
    0x7b, 0x10, 0x5f, 0xc6, 0x18, 0x63, 0x7c, 0x20, 0x83,

    /* U+0106 "Ć" */
    0x4, 0xc, 0x18, 0x0, 0x3c, 0x42, 0x43, 0x81, 0x80, 0x80, 0x80, 0x80, 0x81,
    0x43, 0x42, 0x3c,

    /* U+0107 "ć" */
    0x18, 0x20, 0x1, 0xe4, 0x70, 0xe0, 0x40, 0x81, 0x5, 0x19, 0xe0,

    /* U+0118 "Ę" */
    0xff, 0x2, 0x4, 0x8, 0x1f, 0xa0, 0x40, 0x81, 0x2, 0x7, 0xf0, 0xc1, 0x3, 0x0,

    /* U+0119 "ę" */
    0x38, 0x8a, 0xc, 0x1f, 0xf0, 0x20, 0x21, 0x3c, 0x30, 0x40, 0xe0,

    /* U+0141 "Ł" */
    0x40, 0x81, 0x2, 0x4, 0xe, 0x30, 0x20, 0x40, 0x81, 0x3, 0xf0,

    /* U+0142 "ł" */
    0x49, 0x24, 0xf2, 0x49, 0x20,

    /* U+015A "Ś" */
    0x6, 0x4, 0x8, 0x0, 0x1c, 0x62, 0x41, 0x40, 0x60, 0x38, 0xe, 0x3, 0x1, 0x81,
    0x43, 0x3c,

    /* U+015B "ś" */
    0x8, 0x40, 0xe, 0x4d, 0x16, 0xe, 0xe, 0x1c, 0x5e,

    /* U+0179 "Ź" */
    0x4, 0x8, 0x10, 0xff, 0x3, 0x6, 0x4, 0xc, 0x18, 0x18, 0x30, 0x20, 0x60,
    0xc0, 0xff,

    /* U+017A "ź" */
    0x8, 0x20, 0x7, 0xf0, 0x61, 0x86, 0x18, 0x30, 0xc3, 0x7, 0xf0,

    /* U+017B "Ż" */
    0x8, 0x0, 0xff, 0x3, 0x6, 0x6, 0xc, 0x18, 0x18, 0x30, 0x30, 0x60, 0xc0,
    0xff,

    /* U+017C "ż" */
    0x10, 0x0, 0x7, 0xf0, 0xe1, 0x86, 0x1c, 0x30, 0xc3, 0x7, 0xf0};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0,
     .adv_w = 0,
     .box_w = 0,
     .box_h = 0,
     .ofs_x = 0,
     .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0,
     .adv_w = 167,
     .box_w = 10,
     .box_h = 12,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 15,
     .adv_w = 159,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 26,
     .adv_w = 167,
     .box_w = 8,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 38,
     .adv_w = 168,
     .box_w = 8,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 50,
     .adv_w = 146,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 61,
     .adv_w = 142,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 72,
     .adv_w = 174,
     .box_w = 9,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 86,
     .adv_w = 183,
     .box_w = 8,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 98,
     .adv_w = 70,
     .box_w = 1,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 100,
     .adv_w = 141,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 111,
     .adv_w = 161,
     .box_w = 8,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 123,
     .adv_w = 138,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 132,
     .adv_w = 224,
     .box_w = 11,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 149,
     .adv_w = 183,
     .box_w = 8,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 161,
     .adv_w = 176,
     .box_w = 9,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 175,
     .adv_w = 162,
     .box_w = 8,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 187,
     .adv_w = 176,
     .box_w = 9,
     .box_h = 14,
     .ofs_x = 1,
     .ofs_y = -2},
    {.bitmap_index = 203,
     .adv_w = 158,
     .box_w = 9,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 217,
     .adv_w = 152,
     .box_w = 8,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 229,
     .adv_w = 153,
     .box_w = 9,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 243,
     .adv_w = 166,
     .box_w = 8,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 255,
     .adv_w = 163,
     .box_w = 10,
     .box_h = 12,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 270,
     .adv_w = 227,
     .box_w = 14,
     .box_h = 12,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 291,
     .adv_w = 161,
     .box_w = 10,
     .box_h = 12,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 306,
     .adv_w = 154,
     .box_w = 9,
     .box_h = 12,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 320,
     .adv_w = 153,
     .box_w = 8,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 332,
     .adv_w = 139,
     .box_w = 6,
     .box_h = 9,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 339,
     .adv_w = 144,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 350,
     .adv_w = 134,
     .box_w = 7,
     .box_h = 9,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 358,
     .adv_w = 144,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 369,
     .adv_w = 136,
     .box_w = 7,
     .box_h = 9,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 377,
     .adv_w = 89,
     .box_w = 5,
     .box_h = 13,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 386,
     .adv_w = 144,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 397,
     .adv_w = 141,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 406,
     .adv_w = 62,
     .box_w = 1,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 408,
     .adv_w = 61,
     .box_w = 3,
     .box_h = 15,
     .ofs_x = -1,
     .ofs_y = -3},
    {.bitmap_index = 414,
     .adv_w = 130,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 425,
     .adv_w = 62,
     .box_w = 1,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 427,
     .adv_w = 224,
     .box_w = 11,
     .box_h = 9,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 440,
     .adv_w = 141,
     .box_w = 6,
     .box_h = 9,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 447,
     .adv_w = 146,
     .box_w = 7,
     .box_h = 9,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 455,
     .adv_w = 144,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 466,
     .adv_w = 146,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 477,
     .adv_w = 87,
     .box_w = 4,
     .box_h = 9,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 482,
     .adv_w = 132,
     .box_w = 6,
     .box_h = 9,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 489,
     .adv_w = 84,
     .box_w = 5,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 496,
     .adv_w = 141,
     .box_w = 6,
     .box_h = 9,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 503,
     .adv_w = 124,
     .box_w = 7,
     .box_h = 9,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 511,
     .adv_w = 192,
     .box_w = 12,
     .box_h = 9,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 525,
     .adv_w = 127,
     .box_w = 8,
     .box_h = 9,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 534,
     .adv_w = 121,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 545,
     .adv_w = 127,
     .box_w = 7,
     .box_h = 9,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 553,
     .adv_w = 176,
     .box_w = 9,
     .box_h = 16,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 571,
     .adv_w = 146,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 582,
     .adv_w = 167,
     .box_w = 10,
     .box_h = 15,
     .ofs_x = 0,
     .ofs_y = -3},
    {.bitmap_index = 601,
     .adv_w = 139,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 610,
     .adv_w = 167,
     .box_w = 8,
     .box_h = 16,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 626,
     .adv_w = 134,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 637,
     .adv_w = 146,
     .box_w = 7,
     .box_h = 15,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 651,
     .adv_w = 136,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = -3},
    {.bitmap_index = 662,
     .adv_w = 138,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 673,
     .adv_w = 69,
     .box_w = 3,
     .box_h = 12,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 678,
     .adv_w = 152,
     .box_w = 8,
     .box_h = 16,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 694,
     .adv_w = 132,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 703,
     .adv_w = 153,
     .box_w = 8,
     .box_h = 15,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 718,
     .adv_w = 127,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 729,
     .adv_w = 153,
     .box_w = 8,
     .box_h = 14,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 743,
     .adv_w = 127,
     .box_w = 7,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0}};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_2[] = {0x0,  0x20, 0x31, 0x32, 0x33, 0x34,
                                          0x45, 0x46, 0x6e, 0x6f, 0x87, 0x88,
                                          0xa6, 0xa7, 0xa8, 0xa9};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {.range_start = 65,
     .range_length = 26,
     .glyph_id_start = 1,
     .unicode_list = NULL,
     .glyph_id_ofs_list = NULL,
     .list_length = 0,
     .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY},
    {.range_start = 97,
     .range_length = 26,
     .glyph_id_start = 27,
     .unicode_list = NULL,
     .glyph_id_ofs_list = NULL,
     .list_length = 0,
     .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY},
    {.range_start = 211,
     .range_length = 170,
     .glyph_id_start = 53,
     .unicode_list = unicode_list_2,
     .glyph_id_ofs_list = NULL,
     .list_length = 16,
     .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY}};

/*-----------------
 *    KERNING
 *----------------*/

/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] = {
    0,  1,  2,  3, 4,  5,  6,  0,  7,  7,  8,  9,  10, 7,  7,  4,  11, 12,
    13, 0,  14, 8, 15, 16, 17, 18, 19, 20, 21, 0,  0,  22, 23, 0,  0,  0,
    0,  24, 0,  0, 0,  25, 21, 0,  26, 0,  27, 0,  28, 0,  29, 28, 30, 4,
    25, 1,  20, 3, 0,  5,  22, 0,  0,  0,  0,  19, 30, 19, 30};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] = {
    0,  1, 0,  2,  0,  0,  0,  2,  0,  0,  3,  0,  0,  0,  0,  2,  0,  2,
    0,  4, 5,  6,  7,  8,  9,  10, 11, 12, 0,  13, 13, 13, 14, 13, 0,  0,
    0,  0, 0,  15, 15, 16, 15, 13, 17, 18, 19, 20, 21, 22, 23, 21, 24, 2,
    16, 1, 12, 2,  13, 0,  13, 0,  0,  4,  18, 11, 24, 11, 24};

/*Kern values between classes*/
static const int8_t kern_class_values[] = {
    0,   -1,  0,   0,   -16, -2,  -11, -9,  0,   -12, 0,   0,   0,   0,   0,
    -1,  0,   0,   -2,  -1,  -6,  -4,  0,   2,   0,   0,   0,   0,   -3,  0,
    -3,  0,   0,   -7,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   -4,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -3,  0,   0,
    0,   -3,  0,   -3,  0,   -3,  -5,  -3,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   0,   0,   0,   0,
    0,   0,   0,   -2,  -2,  0,   -2,  0,   0,   0,   -2,  -3,  -3,  0,   0,
    -21, 0,   -33, 0,   3,   0,   0,   0,   0,   0,   0,   -4,  -3,  0,   0,
    -3,  -3,  0,   0,   -3,  -3,  0,   0,   0,   2,   0,   0,   0,   -4,  0,
    0,   0,   2,   -3,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   -3,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -4,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   -3,  0,   -3,  -3,  0,   0,
    0,   -3,  -5,  -8,  0,   0,   2,   -8,  0,   0,   -34, -7,  -22, -18, 0,
    -30, 0,   0,   0,   0,   0,   0,   0,   0,   0,   -5,  -17, -11, 0,   0,
    -17, 0,   -25, 0,   0,   0,   0,   0,   -4,  0,   -3,  -1,  -2,  0,   0,
    -2,  0,   0,   2,   0,   2,   0,   0,   0,   0,   0,   0,   0,   -5,  0,
    -3,  -2,  0,   -4,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   -10, 0,   -2,  0,   0,   -6,  0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -10, -3,  -30,
    -2,  2,   0,   2,   2,   0,   2,   0,   -14, -12, 0,   -14, -12, -9,  -14,
    0,   -12, -9,  -7,  -10, -7,  -9,  -2,  0,   0,   0,   0,   0,   0,   0,
    0,   0,   -6,  -5,  0,   0,   -6,  -4,  0,   0,   -3,  -1,  0,   0,   0,
    -5,  0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   -4,  -4,  0,   0,
    -4,  -3,  0,   0,   -2,  0,   0,   0,   0,   0,   -3,  0,   0,   0,   0,
    2,   0,   0,   0,   0,   0,   -3,  0,   0,   -3,  0,   0,   0,   -3,  -4,
    0,   0,   0,   -12, -4,  -12, -2,  2,   -12, 2,   2,   2,   2,   0,   -9,
    -8,  -3,  -5,  -8,  -5,  -7,  -3,  -5,  -2,  0,   -3,  -4,  2,   -3,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   -3,  0,   0,   -3,  0,   0,
    0,   -2,  -3,  -3,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -2,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   -1,  0,   -2,  -2,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -2,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    -3,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   -2,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -2,  0,   -3,  -2,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -5,  -2,  2,   0,
    -2,  0,   0,   6,   0,   2,   2,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   -2,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -2,
    -2,  2,   0,   -2,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   -2,  0,   0,   -2,  0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   -2,  0,   0,   -2,  0,   0,   0,   0,   0,   0,   0,   0};

/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes = {
    .class_pair_values = kern_class_values,
    .left_class_mapping = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt = 30,
    .right_class_cnt = 24,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 3,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};

extern const lv_font_t lv_font_montserrat_16;

/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t lv_font_roboto_16 = {
#else
lv_font_t lv_font_roboto_16 = {
#endif
    .get_glyph_dsc =
        lv_font_get_glyph_dsc_fmt_txt, /*Function pointer to get glyph's data*/
    .get_glyph_bitmap =
        lv_font_get_bitmap_fmt_txt, /*Function pointer to get glyph's bitmap*/
    .line_height = 19, /*The maximum line height required by the font*/
    .base_line = 3,    /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc, /*The custom font data. Will be accessed by
                         `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &lv_font_montserrat_16,
#endif
    .user_data = NULL,
};

#endif /*#if LV_FONT_ROBOTO_16*/

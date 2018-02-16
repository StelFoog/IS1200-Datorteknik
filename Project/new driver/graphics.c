#include "graphics.h"

const word cursor = {
    8, 8,{
        0x00, 0x18, 0x24, 0x42, 0xe7, 0x24, 0x24, 0x3c
  }
};

const word MysticFire = {
    8, 2, {
        0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
        0x00, 0x07, 0x08, 0x70, 0x08, 0x07, // Y
        0x00, 0x46, 0x49, 0x49, 0x49, 0x31, // S
        0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, // T
        0x00, 0x00, 0x41, 0x7F, 0x41, 0x00, // I
        0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, // C
        0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C, // A
        0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, // L
        0x00, 0x7F, 0x09, 0x09, 0x09, 0x01, // F
        0x00, 0x00, 0x41, 0x7F, 0x41, 0x00, // I
        0x00, 0x7F, 0x09, 0x19, 0x29, 0x46, // R
        0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, // E
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
    }
};

const word Slam = {
    4, 1, {
        0x00, 0x46, 0x49, 0x49, 0x49, 0x31,   // S
        0x00, 0x7F, 0x40, 0x40, 0x40, 0x40,   // L
        0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C,   // A
        0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F,   // M
    }
};

const word WingAttack = {
    6,2, {
        0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F,   // W
        0x00, 0x00, 0x41, 0x7F, 0x41, 0x00,   // I
        0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F,   // N
        0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A,   // G
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   //
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   //
        0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C,   // A
        0x00, 0x01, 0x01, 0x7F, 0x01, 0x01,   // T
        0x00, 0x01, 0x01, 0x7F, 0x01, 0x01,   // T
        0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C,   // A
        0x00, 0x3E, 0x41, 0x41, 0x41, 0x22,   // C
        0x00, 0x7F, 0x08, 0x14, 0x22, 0x41,   // K
    }
};


const sprite qminx = {
    {
        /*
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x30, 0x00, 0x00,
        0x00, 0x4c, 0x00, 0x00,
        0x00, 0x42, 0x00, 0x00,
        0x00, 0x82, 0x00, 0x00,
        0x00, 0x81, 0x00, 0x00,
        0x00, 0x81, 0x00, 0x70,
        0x01, 0x01, 0x07, 0x88,
        0x03, 0x0f, 0x78, 0x48,
        0x05, 0x11, 0x90, 0x48,
        0x19, 0x24, 0x90, 0x48,
        0x25, 0x24, 0x48, 0x88,
        0x2b, 0x21, 0x47, 0x08,
        0x25, 0x24, 0x40, 0x48,
        0x21, 0x24, 0x40, 0xa8,
        0x21, 0x10, 0x80, 0x48,
        0x11, 0x11, 0x86, 0x08,
        0x0d, 0x0f, 0x69, 0x08,
        0x03, 0x01, 0x1f, 0x08,
        0x01, 0x81, 0x00, 0xf0,
        0x00, 0x82, 0x00, 0x00,
        0x00, 0x82, 0x00, 0x00,
        0x00, 0x44, 0x00, 0x00,
        0x00, 0x38, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
        */
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x0c, 0x00,
        0x00, 0x00, 0x32, 0x00,
        0x00, 0x00, 0x42, 0x00,
        0x00, 0x00, 0x41, 0x00,
        0x00, 0x00, 0x81, 0x00,
        0x0e, 0x00, 0x81, 0x00,
        0x11, 0xe0, 0x80, 0x80,
        0x12, 0x1e, 0xf0, 0xc0,
        0x12, 0x09, 0x88, 0xa0,
        0x12, 0x09, 0x24, 0x98,
        0x11, 0x12, 0x24, 0xa4,
        0x10, 0xe2, 0x84, 0xd4,
        0x12, 0x02, 0x24, 0xa4,
        0x15, 0x02, 0x24, 0x84,
        0x12, 0x01, 0x08, 0x84,
        0x10, 0x61, 0x88, 0x88,
        0x10, 0x96, 0xf0, 0xb0,
        0x10, 0xf8, 0x80, 0xc0,
        0x0f, 0x00, 0x81, 0x80,
        0x00, 0x00, 0x41, 0x00,
        0x00, 0x00, 0x41, 0x00,
        0x00, 0x00, 0x22, 0x00,
        0x00, 0x00, 0x1c, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    }, {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x03, 0x05, 0x19, 0x25,
        0x2b, 0x25, 0x21, 0x21, 0x11, 0x0d, 0x03, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

        0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x4c, 0x42,
        0x82, 0x81, 0x81, 0x01, 0x0f, 0x11, 0x24, 0x24,
        0x21, 0x24, 0x24, 0x10, 0x11, 0x0f, 0x01, 0x01,
        0x82, 0x82, 0x44, 0x38, 0x00, 0x00, 0x00, 0x00,

        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x07, 0x78, 0x90, 0x90, 0x48,
        0x47, 0x40, 0x40, 0x80, 0x85, 0x59, 0x1f, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x70, 0x78, 0x90, 0x90, 0x48,
        0x08, 0x48, 0xa8, 0x48, 0x08, 0x08, 0x08, 0xf0,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    }
};

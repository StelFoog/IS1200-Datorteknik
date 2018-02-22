#include "graphics.h"

const unsigned char cursor[8] = {
  0x18,
  0x24,
  0x42,
  0x81,
  0xe7,
  0x24,
  0x24,
  0x3c
};

const unsigned char pkmnSelectCursor[4] = {
    0x0f, 0x0f, 0x0f, 0x0f
};

const sprite qminxSprite = {
    {
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
    }, {
      0x00, 0x10, 0x08, 0x00,
      0x00, 0x10, 0x04, 0x00,
      0x00, 0x21, 0x24, 0x00,
      0x00, 0x21, 0x52, 0x00,
      0x00, 0x2e, 0x23, 0x83,
      0x00, 0x72, 0x02, 0x64,
      0x00, 0x85, 0x02, 0x18,
      0x01, 0x02, 0x02, 0x08,
      0x01, 0x80, 0x01, 0x08,
      0x01, 0x40, 0x01, 0x04,
      0x02, 0x80, 0x01, 0x04,
      0x02, 0x10, 0x01, 0x04,
      0x02, 0x28, 0x01, 0x04,
      0x01, 0x10, 0x11, 0x04,
      0x01, 0x02, 0x2a, 0x08,
      0x01, 0x05, 0x12, 0x88,
      0x00, 0xe2, 0x02, 0xb8,
      0x00, 0x38, 0x04, 0xc7,
      0x00, 0x26, 0x07, 0x00,
      0x00, 0x11, 0x04, 0x00,
      0x00, 0x11, 0x08, 0x00,
      0x00, 0x10, 0x08, 0x00,
      0x00, 0x08, 0x10, 0x00,
      0x00, 0x08, 0x20, 0x00,
      0x00, 0x04, 0xc0, 0x00,
      0x00, 0x03, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00
    }
};

const sprite temitSprite = {
  {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x24, 0x80, 0x00,
    0x00, 0x15, 0x00, 0x00,
    0x00, 0x3f, 0x80, 0x00,
    0x0f, 0xc0, 0x40, 0x00,
    0x30, 0x00, 0x7f, 0xf8,
    0x66, 0x03, 0xff, 0xf8,
    0x7c, 0x63, 0xff, 0xf8,
    0x3c, 0xf7, 0xff, 0xf8,
    0x1c, 0xf5, 0xff, 0x80,
    0x0c, 0x66, 0xff, 0x00,
    0x0c, 0x06, 0xff, 0xf8,
    0x06, 0x05, 0xff, 0xf8,
    0x07, 0xfe, 0xff, 0xf8,
    0x07, 0x9e, 0xff, 0xf8,
    0x0f, 0x0d, 0xff, 0xf8,
    0x0f, 0x0f, 0xff, 0xf0,
    0x1f, 0x9f, 0xff, 0xf8,
    0x3f, 0xff, 0xff, 0xf8,
    0x7f, 0xff, 0xff, 0xf9,
    0x7f, 0xff, 0xff, 0xfb,
    0x3f, 0xff, 0xff, 0xfb,
    0x00, 0x3f, 0x3f, 0xfb,
    0x00, 0x15, 0x3f, 0xfb,
    0x00, 0x24, 0x9f, 0xfb,
    0x00, 0x00, 0x0f, 0xfb,
    0x00, 0x00, 0x0f, 0xf3,
    0x00, 0x00, 0x0f, 0xf3,
    0x00, 0x00, 0x07, 0xe7,
    0x00, 0x00, 0x00, 0xf7,
    0x00, 0x00, 0x00, 0x7f,
    0x00, 0x00, 0x00, 0x3e
  },{
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x42, 0x00,
    0x00, 0x04, 0x44, 0x00,
    0x00, 0x02, 0x48, 0x01,
    0x00, 0x07, 0xfe, 0x03,
    0x00, 0x3f, 0xff, 0x0f,
    0x07, 0xff, 0xff, 0xff,
    0x1f, 0xff, 0xff, 0xff,
    0x3f, 0xff, 0xff, 0xff,
    0x3f, 0xff, 0xff, 0xff,
    0x1f, 0xff, 0xff, 0xff,
    0x0f, 0xff, 0xff, 0xff,
    0x07, 0xff, 0xff, 0xff,
    0x03, 0xff, 0xff, 0xff,
    0x03, 0xff, 0xff, 0xff,
    0x01, 0xff, 0xff, 0xff,
    0x01, 0xff, 0xff, 0xff,
    0x01, 0xff, 0xff, 0xff,
    0x03, 0xff, 0xff, 0xff,
    0x03, 0xff, 0xff, 0xff,
    0x07, 0xff, 0xff, 0xff,
    0x0f, 0xff, 0xfe, 0x1f,
    0x1f, 0xfc, 0x00, 0x1f,
    0x3f, 0xe0, 0x00, 0x7e,
    0x30, 0x00, 0x00, 0x40,
    0x1f, 0xc0, 0x00, 0x80,
    0x00, 0x20, 0x01, 0x00,
    0x00, 0x1f, 0xfe, 0x00,
    0x00, 0x04, 0x44, 0x00,
    0x00, 0x08, 0x42, 0x00,
    0x00, 0x10, 0x41, 0x00,
    0x00, 0x00, 0x00, 0x00
  }
};

const sprite nullSprite = {
    {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x01, 0xc0, 0x00, 0x00,
        0x03, 0xc0, 0x00, 0x00,
        0x0f, 0x80, 0x00, 0x00,
        0x0e, 0x00, 0x00, 0x00,
        0x1c, 0x00, 0x00, 0x00,
        0x18, 0x00, 0x00, 0x00,
        0x38, 0x00, 0x00, 0x00,
        0x38, 0x00, 0x00, 0x00,
        0x30, 0x00, 0x0f, 0xe6,
        0x30, 0x00, 0x3f, 0xe6,
        0x30, 0x00, 0x78, 0x00,
        0x30, 0x00, 0x70, 0x00,
        0x30, 0x00, 0xe0, 0x00,
        0x38, 0x00, 0xc0, 0x00,
        0x1c, 0x01, 0xc0, 0x00,
        0x1e, 0x03, 0x80, 0x00,
        0x0f, 0x87, 0x80, 0x00,
        0x07, 0xff, 0x00, 0x00,
        0x00, 0xfe, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    } , {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x01, 0xc0, 0x00, 0x00,
        0x03, 0xc0, 0x00, 0x00,
        0x0f, 0x80, 0x00, 0x00,
        0x0e, 0x00, 0x00, 0x00,
        0x1c, 0x00, 0x00, 0x00,
        0x18, 0x00, 0x00, 0x00,
        0x38, 0x00, 0x00, 0x00,
        0x38, 0x00, 0x00, 0x00,
        0x30, 0x00, 0x0f, 0xe6,
        0x30, 0x00, 0x3f, 0xe6,
        0x30, 0x00, 0x78, 0x00,
        0x30, 0x00, 0x70, 0x00,
        0x30, 0x00, 0xe0, 0x00,
        0x38, 0x00, 0xc0, 0x00,
        0x1c, 0x01, 0xc0, 0x00,
        0x1e, 0x03, 0x80, 0x00,
        0x0f, 0x87, 0x80, 0x00,
        0x07, 0xff, 0x00, 0x00,
        0x00, 0xfe, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    }
};

const unsigned char startScreen[1024] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
  0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00,
  0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
  0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x38, 0x00, 0x38, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
  0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0xe0,
  0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x40,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x07, 0xe0, 0x00, 0x01, 0xe0, 0x00, 0x00,
  0x00, 0x07, 0xf0, 0x00, 0x01, 0xf0, 0x00, 0x00,
  0x00, 0x00, 0x60, 0x00, 0x00, 0x10, 0x00, 0x00,
  0x00, 0x07, 0xc0, 0x00, 0x00, 0x10, 0x00, 0x00,
  0x00, 0x00, 0x60, 0x00, 0x00, 0x10, 0x00, 0x00,
  0x00, 0x07, 0xf0, 0x00, 0x01, 0xf0, 0x00, 0x00,
  0x00, 0x07, 0xe0, 0x00, 0x01, 0xf0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xe0, 0x07, 0xf0, 0x00, 0x90, 0x00,
  0x00, 0x01, 0xf0, 0x07, 0xf1, 0x01, 0xd0, 0x00,
  0x00, 0x01, 0x50, 0x04, 0x41, 0x01, 0x50, 0x00,
  0x00, 0x01, 0x50, 0x04, 0x47, 0xf1, 0x50, 0x10,
  0x00, 0x01, 0x50, 0x04, 0x47, 0xf1, 0x50, 0x38,
  0x00, 0x01, 0xd0, 0x07, 0xc1, 0x01, 0x70, 0x10,
  0x00, 0x00, 0xc0, 0x83, 0x81, 0x00, 0x20, 0x00,
  0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x10, 0x01, 0xf1, 0x01, 0x00, 0x00,
  0x00, 0x04, 0x10, 0x01, 0xf1, 0x01, 0x00, 0x00,
  0x00, 0x07, 0xf0, 0x00, 0x87, 0xf7, 0xf0, 0x00,
  0x00, 0x07, 0xf0, 0x01, 0x07, 0xf7, 0xf0, 0x00,
  0x00, 0x00, 0x10, 0x01, 0x01, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x10, 0x01, 0x01, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xe0, 0x00, 0xe0, 0xe0, 0x20, 0x00,
  0x00, 0x01, 0xf0, 0x01, 0xf1, 0xf1, 0x70, 0x00,
  0x00, 0x01, 0x10, 0x01, 0x51, 0x11, 0x50, 0x00,
  0x00, 0x01, 0x10, 0x01, 0x51, 0x11, 0x50, 0x00,
  0x00, 0x01, 0x10, 0x01, 0x51, 0x11, 0x50, 0x00,
  0x00, 0x01, 0x10, 0x01, 0xd1, 0xf1, 0xf0, 0x00,
  0x00, 0x01, 0x10, 0x00, 0xc0, 0xe0, 0xf0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xe0, 0x00, 0x91, 0xf0, 0x00, 0x00,
  0x08, 0x01, 0xf0, 0x01, 0xd1, 0xf1, 0xf0, 0x00,
  0x1c, 0x01, 0x10, 0x01, 0x51, 0x01, 0xf0, 0x00,
  0x08, 0x01, 0x10, 0x01, 0x51, 0x00, 0x80, 0x00,
  0x00, 0x01, 0x10, 0x01, 0x51, 0x01, 0x00, 0x00,
  0x00, 0x01, 0xf0, 0x01, 0x71, 0xf1, 0x00, 0x00,
  0x00, 0x00, 0xe0, 0x00, 0x20, 0xf1, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0xf0, 0x00, 0x90, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x01, 0xd0, 0x01, 0x00, 0x00,
  0x00, 0x01, 0xf0, 0x01, 0x50, 0x01, 0x00, 0x00,
  0x00, 0x01, 0xf0, 0x01, 0x50, 0x07, 0xf0, 0x00,
  0x00, 0x01, 0x00, 0x01, 0x50, 0x07, 0xf0, 0x00,
  0x00, 0x01, 0xf0, 0x01, 0x70, 0x01, 0x00, 0x00,
  0x00, 0x00, 0xf0, 0x00, 0x20, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0xf0, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x50, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x51, 0x00, 0x07, 0xf0, 0x00, 0x00,
  0x00, 0x01, 0x53, 0x80, 0x07, 0xf0, 0x00, 0x00,
  0x00, 0x01, 0xd1, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x20,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x70,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x20,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00,
  0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

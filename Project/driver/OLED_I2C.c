#include "OLED_I2C.h"
#include "pic32mx.h"  /* Declarations of system-specific addresses etc */

#include "font.h"
// #pragma message("Compiling for PIC32 Architecture...") Yes we know...
#include "pic32/HW_PIC32.h"

void begin()
{
  _scl_pin = 19;
  _sda_pin = 18;

  _initTWI();

	_sendTWIcommand(SH1106_DISPLAY_OFF);
    _sendTWIcommand(SH1106_SET_DISPLAY_CLOCK_DIV_RATIO);
    _sendTWIcommand(0x80);
    _sendTWIcommand(SH1106_SET_MULTIPLEX_RATIO);
    _sendTWIcommand(0x3F);
    _sendTWIcommand(SH1106_SET_DISPLAY_OFFSET);
    _sendTWIcommand(0x0);
    _sendTWIcommand(SH1106_SET_START_LINE | 0x0);
    _sendTWIcommand(SH1106_CHARGE_PUMP);
	_sendTWIcommand(0x14);
    _sendTWIcommand(SH1106_MEMORY_ADDR_MODE);
    _sendTWIcommand(0x00);
    _sendTWIcommand(SH1106_SET_SEGMENT_REMAP | 0x1);
    _sendTWIcommand(SH1106_COM_SCAN_DIR_DEC);
    _sendTWIcommand(SH1106_SET_COM_PINS);
    _sendTWIcommand(0x12);
    _sendTWIcommand(SH1106_SET_CONTRAST_CONTROL);
	_sendTWIcommand(0xCF);
    _sendTWIcommand(SH1106_SET_PRECHARGE_PERIOD);
	_sendTWIcommand(0xF1);
    _sendTWIcommand(SH1106_SET_VCOM_DESELECT);
    _sendTWIcommand(0x40);
    _sendTWIcommand(SH1106_DISPLAY_ALL_ON_RESUME);
    _sendTWIcommand(SH1106_NORMAL_DISPLAY);
	_sendTWIcommand(SH1106_DISPLAY_ON);

	clrScr();
	update();
}

void clrScr(){
  int i;
  for(i=0;i<1024;i++){
    scrbuf[i] = 0;
  }
}

void setBrightness(uint8_t value)
{
	_sendTWIcommand(SH1106_SET_CONTRAST_CONTROL);
	_sendTWIcommand(value);
}

void setPixel(uint16_t x, uint16_t y)
{
	int by, bi;

	if ((x>=0) && (x<128) && (y>=0) && (y<64))
	{
		by = ((y/8)*128)+x;
		bi = y % 8;
		scrbuf[by]=scrbuf[by] | (1<<bi);
	}
}

void clrPixel(uint16_t x, uint16_t y)
{
	int by, bi;
	if ((x>=0) && (x<128) && (y>=0) && (y<64))
	{
		by=((y/8)*128)+x;
		bi=y % 8;
		scrbuf[by]=scrbuf[by] & ~(1<<bi);
	}
}

void invert(char mode)
{
	if (mode)
		_sendTWIcommand(SH1106_INVERT_DISPLAY);
	else
		_sendTWIcommand(SH1106_NORMAL_DISPLAY);
}

void drawSprite(uint8_t x, uint8_t y, const unsigned char bitmap[], uint8_t sx, uint8_t sy){
  unsigned char data;
  uint8_t cx, cy, bit;
  for(cx = 0; cx < sx; cx++){
    for(cy= 0; cy < sy; cy++){
      bit = cy % 8;                           // Which bit of chunk that is chosen
      data = bitmap[(cx * (sy/8)) + cy/8];    // Get the chunck
      if((data & (0x80>>bit))>0)              // Choose correct bit of the chick
        setPixel(x+cx, y+cy);                 // Set correct pixel
      else
        clrPixel(x+cx, y+cy);
    }
  }
}

void DrawChar(char c, uint8_t x, uint8_t y, uint8_t row) {
    uint8_t cy,cx;
    unsigned char data;
    // Convert the character to an index
    c = c & 0x7F;
    if (c < ' ') {
        c = 0;
    } else {
        c -= ' ';
    }
    // 'font' is a multidimensional array of [96][char_width]
    // which is really just a 1D array of size 96*char_width.
    // Draw pixels
    for (cx=0; cx<charWidth; cx++) {
      data = font[c][cx];
        for (cy=0; cy<charHeight; cy++) {
            if (data & (1<<cy))
              setPixel(x+cx , y+cy + row * 8);
            else
              clrPixel(x+cx, y+cy + row * 8);
        }
    }
}

void drawString(const char* str, uint8_t x, uint8_t y) {
    uint8_t cache = x;
    while (*str) {
        DrawChar(*str++, x, y, row);
        x += charWidth;
    }
}


void drawMoves(const char* str, uint8_t x, uint8_t y) {
    uint8_t row = 0;
    uint8_t cache = x;
    while (*str) {
        DrawChar(*str++, x, y, row);
        x += charWidth;
        if(*str == ' '){
          row++;
          x = cache;
          *str++;
        }
    }
}

#include "OLED_I2C.h"
#include "pic32mx.h"  /* Declarations of system-specific addresses etc */

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

void delay (unsigned int t) {
  int c, d;
  for (c = 1; c <= t; c++){
    for (d = 1; d <= 3400; d++)
    {}
  }
}

void clrScr(){
  int i;
  for(i=0;i<1024;i++){
    scrbuf[i] = 0;
  }
}

void fillScr()
{
  int i;
  for(i=0;i<1024;i++){
    scrbuf[i] = 255;
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

void invert(bool mode)
{
	if (mode==true)
		_sendTWIcommand(SH1106_INVERT_DISPLAY);
	else
		_sendTWIcommand(SH1106_NORMAL_DISPLAY);
}

void drawBitmap(int x, int y, unsigned char bitmap[], int sx, int sy)
{
	int bit;
	unsigned char data; // byte = unsigned char
  int cy;
	for (cy=0; cy<sy; cy++) {
	  bit = cy % 8;
    int cx;
		for(cx=0; cx<sx; cx++) {
      data = bitmap[cx+((cy/8)*sx)];
      if ((data & (1<<bit))>0)
				setPixel(x+cx, y+cy);
			else
				clrPixel(x+cx, y+cy);
		}
	}
}
void drawSprite(int x, int y, unsigned char bitmap[]){
  unsigned char data;
  int cx;
  int cy;
  int bit;
  for(cx = 0; cx < 32; cx++){
    for(cy= 0; cy < 32; cy++){
      bit = cy % 8;                       // Which bit of chunk that is chosen
      data = bitmap[(cx * 4) + cy/8];     // Get the chunck
      if((data & (0x80>>bit))>0)          // Choose correct bit of the chick
        setPixel(x+cx, y+cy);             // Set correct pixel
      else
        clrPixel(x+cx, y+cy);
    }
  }
}

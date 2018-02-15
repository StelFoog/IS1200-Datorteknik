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
	//cfont.font=0; Dont know what this do
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
		by=((y/8)*128)+x;
		bi=y % 8;

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
	for (cy=0; cy<sy; cy++)
	{
		bit= cy % 8;
    int cx;
		for(cx=0; cx<sx; cx++)
		{
      data = bitmap[cx+((cy/8)*sx)];
      if ((data & (1<<bit))>0)
				setPixel(x+cx, y+cy);
			else
				clrPixel(x+cx, y+cy);
		}
	}
}

// Private

/*
void i2c_idle() {
	while(I2C1CON & 0x1F || I2C1STAT & (1 << 14)); //TRSTAT
}

void _sendStart(unsigned char addr)
{
  i2c_idle();
	I2C1CONSET = 1 << 0; //SEN
	i2c_idle();
}

void _sendStop()
{
  i2c_idle();
	I2C1CONSET = 1 << 2; //PEN
	i2c_idle();
}

void _sendNack()
{
  i2c_idle();
	I2C1CONSET = 1 << 5; //ACKDT = 1
	I2C1CONSET = 1 << 4; //ACKEN = 1
}

void _sendAck()
{
  i2c_idle();
	I2C1CONCLR = 1 << 5; //ACKDT = 0
	I2C1CONSET = 1 << 4; //ACKEN = 1
}

 Hopefully we can mange without this
void _waitForAck()
{
	pinMode(_sda_pin, INPUT);
	digitalWrite(_scl_pin, HIGH);
	while (digitalRead(_sda_pin)==HIGH) {}
	digitalWrite(_scl_pin, LOW);
}

void _writeByte(uint8_t value)
{
  i2c_idle();
	I2C1TRN = value;
  i2c_idle();
	//return !(I2C1STAT & (1 << 15)); //ACKSTAT
}
*/

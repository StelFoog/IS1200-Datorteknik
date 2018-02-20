#ifndef OLED_I2C_h
#define OLED_I2C_h

#define charWidth		6
#define charHeight		8

#define SH1106_ADDR		0x3C

// Defines from libaries
#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1

#define MSBFIRST 1

#define LEFT	0
#define RIGHT	9999
#define CENTER	9998

#define SH1106_COMMAND			0x00
#define SH1106_DATA			0xC0
#define SH1106_DATA_CONTINUE	0x40

#define RST_NOT_IN_USE	255

// SH1106 Commandset
// ------------------
// Fundamental Commands
#define SH1106_SET_CONTRAST_CONTROL					0x81
#define SH1106_DISPLAY_ALL_ON_RESUME					0xA4
#define SH1106_DISPLAY_ALL_ON							0xA5
#define SH1106_NORMAL_DISPLAY							0xA6
#define SH1106_INVERT_DISPLAY							0xA7
#define SH1106_DISPLAY_OFF								0xAE
#define SH1106_DISPLAY_ON								0xAF
#define SH1106_NOP										0xE3
// Scrolling Commands
#define SH1106_HORIZONTAL_SCROLL_RIGHT					0x26
#define SH1106_HORIZONTAL_SCROLL_LEFT					0x27
#define SH1106_HORIZONTAL_SCROLL_VERTICAL_AND_RIGHT	0x29
#define SH1106_HORIZONTAL_SCROLL_VERTICAL_AND_LEFT		0x2A
#define SH1106_DEACTIVATE_SCROLL						0x2E
#define SH1106_ACTIVATE_SCROLL							0x2F
#define SH1106_SET_VERTICAL_SCROLL_AREA				0xA3
// Addressing Setting Commands
#define SH1106_SET_LOWER_COLUMN						0x02     //Starts at 2 for some reason
#define SH1106_SET_HIGHER_COLUMN						0x10
#define SH1106_SETSTARTPAGE               0xB0     // For some reason page start at 0xB0
#define SH1106_MEMORY_ADDR_MODE						0x20
#define SH1106_SET_COLUMN_ADDR							0x21
#define SH1106_SET_PAGE_ADDR							0x22
// Hardware Configuration Commands
#define SH1106_SET_START_LINE							0x40
#define SH1106_SET_SEGMENT_REMAP						0xA0
#define SH1106_SET_MULTIPLEX_RATIO						0xA8
#define SH1106_COM_SCAN_DIR_INC						0xC0
#define SH1106_COM_SCAN_DIR_DEC						0xC8
#define SH1106_SET_DISPLAY_OFFSET						0xD3
#define SH1106_SET_COM_PINS							0xDA
#define SH1106_CHARGE_PUMP								0x8D
// Timing & Driving Scheme Setting Commands
#define SH1106_SET_DISPLAY_CLOCK_DIV_RATIO				0xD5
#define SH1106_SET_PRECHARGE_PERIOD					0xD9
#define SH1106_SET_VCOM_DESELECT						0xDB

#include "pic32/HW_PIC32_defines.h"
#include <stdbool.h>
#include <stdint.h>

void	begin();
void	update();
void  delay(unsigned int t);
void	setBrightness(uint8_t value);
void	clrScr();
void	invert(bool mode);
void	setPixel(uint16_t x, uint16_t y);
void	clrPixel(uint16_t x, uint16_t y);

void DrawChar(char c, uint8_t x, uint8_t y, uint8_t row);
void DrawString(const char* str, uint8_t x, uint8_t y);
void drawBitmap(uint8_t x, uint8_t y, const unsigned char * bitmap, uint8_t sx, uint8_t sy);
void drawSprite(uint8_t x, uint8_t y, const unsigned char bitmap[], uint8_t sx, uint8_t sy);
uint8_t			_scl_pin, _sda_pin;
uint8_t			scrbuf[1024];
void	_initTWI();
void	_sendTWIstart();
void	_sendTWIstop();
void	_sendTWIcommand(uint8_t value);

#endif

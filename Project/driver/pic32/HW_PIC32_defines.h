// *** Hardwarespecific defines ***
#define __cbi(reg, bitmask) (*(reg + 1)) = bitmask
#define __sbi(reg, bitmask) (*(reg + 2)) = bitmask
#define pulseClock digitalWrite(SCK_Pin, LOW); digitalWrite(SCK_Pin, HIGH)

#define bitmapbyte(x) bitmap[x]

#define PROGMEM
#define bitmapdatatype unsigned char*

#define SDA	18					// A4 (Remeber to set the jumper correctly)
#define SCL	19					// A5 (Remeber to set the jumper correctly)

#ifndef TWI_FREQ
	#define TWI_FREQ 400000L
#endif

#ifndef HEADER_HW_PIC32_DEFINES
#define HEADER_HW_PIC32_DEFINES

// *** Hardwarespecific defines ***
#define bitmapbyte(x) bitmap[x]

#define PROGMEM
#define bitmapdatatype unsigned char*

#define SDA	18					// A4 (Remeber to set the jumper correctly)
#define SCL	19					// A5 (Remeber to set the jumper correctly)

#ifndef TWI_FREQ
	#define TWI_FREQ 400000L

#endif

#endif

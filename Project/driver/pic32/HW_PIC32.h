
#include <stdint.h>

#define _I2CCON_ON 15
#define _I2CCON_STREN 6
#define _I2CSTAT_BCL 10
#define _I2CCON_SEN 0
#define _I2CSTAT_IWCOL 7
#define _I2CSTAT_TRSTAT 14
#define _I2CSTAT_ACKSTAT 15
#define _I2CCON_PEN 2


inline void _waitForIdleBus() { while (I2C1CON & 0x1f) {} }

void _initTWI()
{
	uint32_t	tpgd;
	IFSCLR(0) = 0xE0000000;									// Clear Interrupt Flag
	IECCLR(0) = 0xE0000000;									// Disable Interrupt
	I2C1CONCLR = (1 << _I2CCON_ON);							// Disable I2C interface
	//tpgd = ((F_CPU / 8) * 104) / 125000000;
	//I2C1BRG = (F_CPU / (2 * TWI_FREQ) - tpgd) - 2;			// Set I2C Speed
	I2C1BRG = 0x0C2; // Test speed, might want to change later
	I2C1ADD = SH1106_ADDR;									// Set I2C device address
	I2C1CONSET = (1 << _I2CCON_ON) | (1 << _I2CCON_STREN);	// Enable I2C Interface
}

void update()
{
	IECCLR(0) = 0xE0000000;
	int i;
    for(i = 0 ; i < 8; i++){
        _sendTWIcommand(SH1106_SETSTARTPAGE + i);
        _sendTWIcommand(2);
        _sendTWIcommand(0x10);
				int pixel;
        for(pixel = 0; pixel < 128; pixel++){
            _waitForIdleBus();									// Wait for I2C bus to be Idle before starting
            I2C1CONSET = (1 << _I2CCON_SEN);					// Send start condition
            if (I2C1STAT & (1 << _I2CSTAT_BCL)) { return; }		// Check if there is a bus collision
            while (I2C1CON & (1 << _I2CCON_SEN)) {}				// Wait for start condition to finish
            I2C1TRN = (SH1106_ADDR<<1);						// Send device Write address
            while (I2C1STAT & (1 << _I2CSTAT_IWCOL))			// Check if there is a Write collision
            {
                I2C1STATCLR = (1 << _I2CSTAT_IWCOL);			// Clear Write collision flag
                I2C1TRN = (SH1106_ADDR<<1);					// Retry send device Write address
            }
            while (I2C1STAT & (1 << _I2CSTAT_TRSTAT)) {}		// Wait for transmit to finish
            while (I2C1STAT & (1 << _I2CSTAT_ACKSTAT)) {}		// Wait for ACK
            I2C1TRN = SH1106_DATA_CONTINUE;					// Send the command for continous data
            while (I2C1STAT & (1 << _I2CSTAT_TRSTAT)) {}		// Wait for transmit to finish
            while (I2C1STAT & (1 << _I2CSTAT_ACKSTAT)) {}		// Wait for ACK
						int b;
					for (b=0; b<16; b++){	// Send data
                I2C1TRN = scrbuf[i * 128 + pixel];
                while (I2C1STAT & (1 << _I2CSTAT_TRSTAT)) {}
                while (I2C1STAT & (1 << _I2CSTAT_ACKSTAT)) {}
                ++pixel;
            }
            --pixel;
            I2C1CONSET = (1 << _I2CCON_PEN);					// Send stop condition
            while (I2C1CON & (1 << _I2CCON_PEN)) {}				// Wait for stop condition
        }
    }
	IECSET(0) = 0xE0000000; // set interuppt
}

void _sendTWIcommand(uint8_t value)
{
	_waitForIdleBus();									// Wait for I2C bus to be Idle before starting
	I2C1CONSET = (1 << _I2CCON_SEN);					// Send start condition
	if (I2C1STAT & (1 << _I2CSTAT_BCL)) { return; }		// Check if there is a bus collision
	while (I2C1CON & (1 << _I2CCON_SEN)) {}				// Wait for start condition to finish
	I2C1TRN = (SH1106_ADDR<<1);						// Send device Write address
	while (I2C1STAT & (1 << _I2CSTAT_IWCOL))			// Check if there is a Write collision
	{
		I2C1STATCLR = (1 << _I2CSTAT_IWCOL);			// Clear Write collision flag
		I2C1TRN = (SH1106_ADDR<<1);					// Retry send device Write address
	}
	while (I2C1STAT & (1 << _I2CSTAT_TRSTAT)) {}		// Wait for transmit to finish
	while (I2C1STAT & (1 << _I2CSTAT_ACKSTAT)) {}		// Wait for ACK
	I2C1TRN = SH1106_COMMAND;							// Send the 1st data byte
	while (I2C1STAT & (1 << _I2CSTAT_TRSTAT)) {}		// Wait for transmit to finish
	while (I2C1STAT & (1 << _I2CSTAT_ACKSTAT)) {}		// Wait for ACK
	I2C1TRN = value;									// Send the 2nd data byte
	while (I2C1STAT & (1 << _I2CSTAT_TRSTAT)) {}		// Wait for transmit to finish
	while (I2C1STAT & (1 << _I2CSTAT_ACKSTAT)) {}		// Wait for ACK
	I2C1CONSET = (1 << _I2CCON_PEN);					// Send stop condition
	while (I2C1CON & (1 << _I2CCON_PEN)) {}				// Wait for stop condition to finish
}

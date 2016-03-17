/******************************************************************************
MMA8491Q.h

******************************************************************************/

#ifndef MMA8491Q_h
#define MMA8491Q_h

#include <Arduino.h>

///////////////////////////////////
// MMA8491Q Register Definitions  //
///////////////////////////////////

#define	STATE					(uint8_t)0x00
#define	GPIO_ADDRESS			(uint8_t)0x20
#define	GPIO_READ				(uint8_t)0x00
#define	GPIO_WRITE_PORT0		(uint8_t)0x02
#define	ADDRESS					(uint8_t)0x55	

////////////////////////////////
// MMA8491Q Class Declaration  //
////////////////////////////////
class MMA8491Q
{
public:	
	MMA8491Q(uint8_t addr = ADDRESS);
	void read();
	float x;
	float y;
	float z;

private:
	byte address;
	uint8_t data_read;
	//void writeRegister(uint8_t reg, int data);
	void readRegister(int reg);
	float value(int val);
	void enable();
	void disable();
	uint16_t cx;
	uint16_t cy;
	uint16_t cz;
	uint16_t state;

};

extern MMA8491Q mma8491q;

#endif
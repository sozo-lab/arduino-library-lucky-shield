/******************************************************************************
MMA8491Q.cpp
******************************************************************************/

#include <MMA8491Q.h>
#include <Wire.h>

// CONSTRUCTUR
MMA8491Q::MMA8491Q(uint8_t addr)
{
	address = addr; // Store address into private variable
}

void MMA8491Q::read(){
	readRegister(STATE);
}

void MMA8491Q::enable(){

	Wire.beginTransmission(GPIO_ADDRESS); //read the gpio expander value
	Wire.write(GPIO_READ);
	Wire.endTransmission();  
	Wire.requestFrom(GPIO_ADDRESS,(uint8_t)1); 
	if(Wire.available()) {
		data_read = Wire.read();
	}
	data_read = data_read | 0x01; //enable
	Wire.beginTransmission(GPIO_ADDRESS);	
	Wire.write(GPIO_WRITE_PORT0);
	Wire.write(data_read);
	Wire.endTransmission();
}

void MMA8491Q::disable(){

	Wire.beginTransmission(GPIO_ADDRESS);
	Wire.write(GPIO_WRITE_PORT0);
	Wire.write(data_read & 0xFE); //disable
	Wire.endTransmission();

}

float MMA8491Q::value(int val){

	if (val < 0x2000)
		return float(val)/1024;   // read value is between 0 and 8191 (0g 8g)
	else
		return float((0x1FFF & val) - 0x2000)/1024;

}

void MMA8491Q::readRegister(int reg)
{
	enable();
	delay(5);
	Wire.beginTransmission(address);
	Wire.write(reg);
	Wire.endTransmission();  
	Wire.requestFrom(address, (uint8_t)7); 
	state = Wire.read();
	cx = Wire.read(); cx <<= 8; cx |= Wire.read(); cx >>= 2;
	cy = Wire.read(); cy <<= 8; cy |= Wire.read(); cy >>= 2;
	cz = Wire.read(); cz <<= 8; cz |= Wire.read(); cz >>= 2;
	x = value(cx);
	y = value(cy);
	z = value(cz);
	disable();

}

MMA8491Q mma8491q;
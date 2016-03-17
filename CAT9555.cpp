/******************************************************************************
Arduino_CAT9555.cpp
******************************************************************************/

#include <CAT9555.h>
#include <Wire.h>

// CONSTRUCTUR
CAT9555::CAT9555(uint8_t addr)
{
	address = addr; // Store address into private variable
}

void CAT9555::begin(){

	writeRegister(CONFIG_PORT0, 0x0E);	// setup direction register port0
	writeRegister(CONFIG_PORT1, 0x7F);	// setup direction register port1
	writeRegister(OUTPUT_PORT0, 0x3c);	// set all output pin to LOW level

}

void CAT9555::digitalWrite(int PIN, int data){

	uint8_t data_reg = read_8_Register(INPUT_PORT0);
	if (data == HIGH )
		if (PIN == LED1 || PIN == LED2)
      		data_reg = ~PIN >> 8 & data_reg;
    	else
    		data_reg = PIN >> 8 | data_reg;
    else if (data == LOW)
    	if (PIN == LED1 || PIN == LED2)
    		data_reg = PIN >> 8 | data_reg;
    	else
    		data_reg = (0xFF ^ PIN >> 8) &  data_reg;
    writeRegister(OUTPUT_PORT0, data_reg);
    data_reg = read_8_Register(INPUT_PORT0);

}

int CAT9555::digitalRead(int PIN){

	uint16_t data = read_16_Register(INPUT_PORT0);
	//Serial.println(data,BIN);
	int result = (data ^ 0x30FF) & PIN;  //0xFFFF
	if (result)
		return HIGH;
	else
		return result;
	
}
// WRITE REGISTER
void CAT9555::writeRegister(int reg, int data)
{

    Wire.beginTransmission(address);  
    Wire.write(reg); 
    Wire.write(data); 
    Wire.endTransmission(); 
}


uint8_t CAT9555::read_8_Register(int reg)
{
	uint8_t _data0;
	Wire.beginTransmission(address);
	Wire.write(reg);
	Wire.endTransmission();  
	Wire.requestFrom(address, (uint8_t)1); 
	if(Wire.available()) {
		_data0 = Wire.read();
	}
	return _data0;
}
// READ REGISTER
uint16_t CAT9555::read_16_Register(int reg)
{
	uint16_t _data0;
	Wire.beginTransmission(address);
	Wire.write(reg);
	Wire.endTransmission();  
	Wire.requestFrom(address, (uint8_t)2); 
	if(Wire.available()) {
		_data0 = Wire.read() << 8 ;
	}
	if(Wire.available()) {
		_data0 |= Wire.read();
	}

	return _data0;
}

CAT9555 cat9555;

/******************************************************************************
Arduino.h

******************************************************************************/

#ifndef Lucky_h
#define Lucky_h

#include <CAT9555.h>
#include <MMA8491Q.h>
#include <MAG3110.h>
#include <BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "Wire.h"

class Lucky
{
	public:
		
		void init(){ 
			Wire.begin();
		}	
		MMA8491Q& accelerometer(){
		 	return mma8491q;
		}
		MAG3110& magnetometer(){
		 	return mag3110;
		}
		BME280& bosch(){
		 	return bme280;
		}
		CAT9555& gpio(){
		 	return cat9555;
		}
		Adafruit_SSD1306& oled(){
		 	return ssd1306;
		}
};

extern Lucky lucky;

#endif

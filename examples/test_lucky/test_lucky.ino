#include <Lucky.h>
#include <Wire.h>

void setup() {

  lucky.init();
  lucky.gpio().begin();
  lucky.magnetometer().begin();
  lucky.oled().begin();
  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  lucky.oled().setTextSize(2);
  lucky.oled().setTextColor(WHITE);
  lucky.oled().setCursor(3,23);
  lucky.oled().clearDisplay();
  lucky.oled().print("Arduino");
  lucky.oled().display();
  
  lucky.gpio().digitalWrite(LED2,LOW);
  lucky.gpio().digitalWrite(REL1,HIGH);
  lucky.gpio().digitalWrite(REL2,LOW);
  delay(1000);
  lucky.gpio().digitalWrite(LED2,HIGH);
  lucky.gpio().digitalWrite(REL2,HIGH);
  lucky.gpio().digitalWrite(REL1,LOW);
  delay(1000);
  Serial.print("LED1: ");
  Serial.print(lucky.gpio().digitalRead(LED1));
  Serial.print(" LED2: ");
  Serial.print(lucky.gpio().digitalRead(LED2));
  Serial.print(" REL1: ");
  Serial.print(lucky.gpio().digitalRead(REL1));
  Serial.print(" REL2: ");
  Serial.println(lucky.gpio().digitalRead(REL2));
  Serial.print(" joy-D: ");
  Serial.print(lucky.gpio().digitalRead(JOYD));
  Serial.print(" joy-R: ");
  Serial.print(lucky.gpio().digitalRead(JOYR));
  Serial.print(" joy-L: ");
  Serial.print(lucky.gpio().digitalRead(JOYL));
  Serial.print("  joy-U: ");
  Serial.print(lucky.gpio().digitalRead(JOYU));
  Serial.print("  joy-C: "); 
  Serial.println(lucky.gpio().digitalRead(JOYC));
  lucky.accelerometer().read();
  Serial.print("x: ");
  Serial.print(lucky.accelerometer().x);
  Serial.print("  y: ");
  Serial.print(lucky.accelerometer().y);
  Serial.print("  z: ");
  Serial.println(lucky.accelerometer().z);
  Serial.print("Mx: ");
  Serial.print(lucky.magnetometer().readx());
  Serial.print("  My: ");
  Serial.print(lucky.magnetometer().ready());
  Serial.print("  Mz: ");
  Serial.println(lucky.magnetometer().readz());
  
  lucky.bosch().readCompensationParams();
  
  // Need to turn on 1x oversampling, default is os_skipped, which means it doesn't measure anything
  lucky.bosch().writeOversamplingPressure(os1x);  // 1x over sampling (ie, just one sample)
  lucky.bosch().writeOversamplingTemperature(os1x);
  lucky.bosch().writeOversamplingHumidity(os1x);
  lucky.bosch().writeMode(smForced);
  while (lucky.bosch().isMeasuring()) {
    //Serial.println("Measuring...");
    delay(50);
  }
  
  // read out the data - must do this before calling the getxxxxx routines
  lucky.bosch().readMeasurements();
  Serial.print("Temp=");
  Serial.print(lucky.bosch().getTemperature());  // must get temp first
  Serial.print("  Humidity=");
  Serial.print(lucky.bosch().getHumidity());
  Serial.print("  Pressure=");
  Serial.println(lucky.bosch().getPressure());
  
  lucky.oled().clearDisplay();
  lucky.oled().display();
  delay(1000);

}

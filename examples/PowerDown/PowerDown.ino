/***************************************************************************
* Example sketch for the INA219_WE library
*
* This sketch shows how to use the INA219 Power Down mode. 
*  
* Further information can be found on:
* http://wolles-elektronikkiste.de/ina219
* 
***************************************************************************/
#include <Wire.h>
#include <INA219_WE.h>
#define I2C_ADDRESS 0x40

INA219_WE ina219(I2C_ADDRESS);
// INA219_WE ina219 = INA219_WE(); // Alternative: sets default address 0x40

void setup() {
  Serial.begin(9600);
  Wire.begin();
  // default parameters are set - for change check the other examples
  if(!ina219.init()){
    Serial.println("INA219 not connected!");
  }
  Serial.println("INA219 Current Sensor Example Sketch - PowerDown");
  Serial.println("Continuous Sampling starts");
  Serial.println();
}

void loop() {
  for(int i=0; i<5; i++){
    continuousSampling();
    delay(3000);
  }
  
  Serial.println("Power down for 10s");
  ina219.powerDown();
  for(int i=0; i<10; i++){
    Serial.print(".");
    delay(1000);
  }
  
  Serial.println("Power up!");
  Serial.println("");
  ina219.powerUp();
}

void continuousSampling(){
  float shuntVoltage_mV = 0.0;
  float loadVoltage_V = 0.0;
  float busVoltage_V = 0.0;
  float current_mA = 0.0;
  float power_mW = 0.0; 
  bool ina219_overflow = false;
  
  shuntVoltage_mV = ina219.getShuntVoltage_mV();
  busVoltage_V = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getBusPower();
  loadVoltage_V  = busVoltage_V + (shuntVoltage_mV/1000);
  ina219_overflow = ina219.getOverflow();
  
  Serial.print("Shunt Voltage [mV]: "); Serial.println(shuntVoltage_mV);
  Serial.print("Bus Voltage [V]: "); Serial.println(busVoltage_V);
  Serial.print("Load Voltage [V]: "); Serial.println(loadVoltage_V);
  Serial.print("Current[mA]: "); Serial.println(current_mA);
  Serial.print("Bus Power [mW]: "); Serial.println(power_mW);
  if(!ina219_overflow){
    Serial.println("Values OK - no overflow");
  }
  else{
    Serial.println("Overflow! Choose higher PGAIN");
  }
  Serial.println();
}

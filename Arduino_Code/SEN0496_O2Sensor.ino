#include "DFRobot_EOxygenSensor.h"
#define OXYGEN_I2C_ADDRESS E_OXYGEN_ADDRESS_0

DFRobot_EOxygenSensor_I2C oxygen(&Wire, OXYGEN_I2C_ADDRESS);
uint8_t calibrationState = 0;

void setup()  {
  Serial.begin(115200);
  while(!Serial);
  while(!oxygen.begin()){
    Serial.println("No O2 Sensor!");
    delay(1000);
  } Serial.println("Device connected successfully !");
  // if(oxygen.clearCalibration()) Serial.println("Clear calibration success!");
  // if(oxygen.calibration_20_9()) Serial.println("20.9 calibration success!");
  // if(oxygen.calibration_99_5()) Serial.println("99.5 calibration success!");
}

void loop()
{
  calibrationState = oxygen.readCalibrationState();
  // if(calibrationState == 0) Serial.println("No calibration!");
  // if(calibrationState&0x01) Serial.println("20.9 calibration!");
  // if(calibrationState&0x02) Serial.println("99.5 calibration!");
  Serial.print("Oxygen concentration is: ");
  Serial.print(oxygen.readOxygenConcentration());
  Serial.println("% VOL");
  delay(1000);
}

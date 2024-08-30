#include "humid_temp_sensor.h"
#include "pins.h"
void HumidTempSensor::get_readings() {
  ht_sensor.measureHighPrecision(temperature, humidity);
}
void HumidTempSensor::begin() {
  Wire.begin();
  ht_sensor.begin(Wire);
}

#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <stdint.h> // Required for uint8_t

// To store Sensor data
typedef struct Data {
  float light_sensor_value;
  float wind_speed;
  float wind_direction;
  float humidity;
  float temperature;
  float rain_volume;
  float battery_voltage;

} Data;

#endif //!__CONFIG_H_

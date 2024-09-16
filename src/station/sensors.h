#ifndef __SENSOR_H_
#define __SENSOR_H_

#include "battery_monitor.h"
#include "config.h"
#include "humid_temp_sensor.h"
#include "light_sensor.h"
#include "weather_station.h"
// Get all sensors data

// Light sensor object
extern lightSensor Light_Sensor;

// Battery Monitor object
extern BatteryMonitor Battery_Monitor;
// Humidity and temperature
extern HumidTempSensor Humid_Temp_Sensor;

// Weather_Station object
extern weatherStation Weather_Station;

void get_data(Data &new_data);

#endif // !__SENSOR_H_


#include "sensors.h"
#include "config.h"

// Light sensor object
lightSensor Light_Sensor;

// Battery Monitor object
BatteryMonitor Battery_Monitor;
// Humidity and temperature
HumidTempSensor Humid_Temp_Sensor;

// Weather_Station object
weatherStation Weather_Station;

void get_data(Data &new_data) {
  Humid_Temp_Sensor.get_readings();
  new_data.light_sensor_value = Light_Sensor.get_value();
  new_data.temperature = Humid_Temp_Sensor.temperature;
  new_data.humidity = Humid_Temp_Sensor.humidity;
  new_data.wind_speed = Weather_Station.get_speed();
  new_data.wind_direction = Weather_Station.get_direction();
  new_data.rain_volume = Weather_Station.get_rain();
  new_data.battery_voltage = Battery_Monitor.get_voltage(ADC_PIN);
}

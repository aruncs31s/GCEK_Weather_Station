#include "light_sensor.h"
#include "humid_temp_sensor.h"
#include "esp_mesh.h"
#include "weather_station.h"
#include <WiFi.h>

// ########## //
#define DEVICE_ID 1
// ########## //

lightSensor Light_Sensor;

espMesh Wifi_Mesh;

Data Message;

humidTempSensor Humid_Temp_Sensor;

weatherStation Weather_Station;

uint8_t Receiver_mac[6] ={0x08, 0xD1, 0xF9,0xED, 0x30, 0xD8}; 
uint8_t wifi_channel = 6;


// Pins Defenitions Go Here

void setup(){
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  Message.UID=DEVICE_ID;
  Weather_Station.init();
  Wifi_Mesh.Mesh.set_broadcast_address(Receiver_mac);
  Wifi_Mesh.Wifi.begin(wifi_channel);
  Light_Sensor.begin();
  Humid_Temp_Sensor.begin();

  Wifi_Mesh.Mesh.init();

}

void loop(){

// Get readings from humidity and temp sensor
Humid_Temp_Sensor.get_readings();
Message.light_sensor_value = Light_Sensor.get_value();
Message.temperature = Humid_Temp_Sensor.temperature;
Message.humidity = Humid_Temp_Sensor.humidity;
Message.wind_speed = Weather_Station.get_speed();
Message.wind_direction = Weather_Station.get_direction();
Message.rain_volume= Weather_Station.get_rain();
Serial.println("Direction ");
Serial.print(Message.wind_direction);
  esp_err_t result =
      esp_now_send(Receiver_mac, (uint8_t *)&Message, sizeof(Message));
  //Check If the Tx was successful
  if (result == ESP_OK) {
    Serial.println("Success");
  }
  else {
    Serial.println("Failed");
    }

delay(1000);

}

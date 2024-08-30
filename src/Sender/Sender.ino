#include "light_sensor.h"
#include "humid_temp_sensor.h"
#include "esp_mesh.h"

// ########## //
#define DEVICE_ID 1
// ########## //

lightSensor Light_Sensor;

espMesh Wifi_Mesh;

Data Message;

uint8_t Receiver_mac[6] ={0x08, 0xD1, 0xF9,0xED, 0x30, 0xD8}; 
uint8_t wifi_channel = 6;


// Pins Defenitions Go Here

void setup(){
  Serial.begin(9600);
  Message.UID=DEVICE_ID;
  Wifi_Mesh.Mesh.set_broadcast_address(Receiver_mac);
  Wifi_Mesh.Wifi.begin(wifi_channel);
  Light_Sensor.begin();
  Wifi_Mesh.Mesh.init();

}

void loop(){
  strcpy(Message.someChar ,"This is a Message from Node 1");
  Message.light_sensor_value = 10.111; 
  //Light_Sensor.get_value();
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

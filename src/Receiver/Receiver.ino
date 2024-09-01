#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>
#include <ThingSpeak.h>
// #include "lib/sensors.h"
// uint8_t broadcastAddress[] = {0x08, 0xD1, 0xF9, 0xED, 0x30, 0xD8};
const char* ssid     = "802.11";
const char* password = "12345678p";
const int channel = 2642690;
int t_status;
// For Thingspeak
WiFiClient  client;
uint8_t wifiChannel = 6;


typedef struct Data {
  uint8_t UID;
  float light_sensor_value;
  float wind_speed;
  float wind_direction;
  float humidity;
  float temperature;
  float rain_volume;
} Data;
// Create struct same as Sender
Data Message;

// Create struct for different boards
Data from_board_1;
Data from_board_2;

// Pack it together
Data whole_data[2]={from_board_1,from_board_2};

void OnReceive(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  memcpy(&Message, incomingData, sizeof(Message));
  Serial.printf("Board ID %u: %u bytes\n", Message.UID, len);

 
}
void setup(){
Serial.begin(9600);
// Ignore this and get Contant Reboot :)
 WiFi.mode(WIFI_AP_STA);
  
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(wifiChannel, WIFI_SECOND_CHAN_NONE); 
  esp_wifi_set_promiscuous(false); 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

 ThingSpeak.begin(client); 
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnReceive));
}
void loop(){
   // TODO: Implement HTTP Server

  // Update the structures with the new incoming data
  whole_data[Message.UID-1].light_sensor_value = Message.light_sensor_value;
  whole_data[Message.UID-1].temperature = Message.temperature;
  whole_data[Message.UID-1].humidity = Message.humidity;
  whole_data[Message.UID-1].wind_speed = Message.wind_speed;
  whole_data[Message.UID-1].wind_direction = Message.wind_direction;
  whole_data[Message.UID-1].rain_volume = Message.rain_volume;

t_status = 
  ThingSpeak.writeField(channel,1,Message.light_sensor_value,apiKey);
  delay(100);
 t_status = 
  ThingSpeak.writeField(channel,2,Message.humidity,apiKey);
  delay(100);

 t_status = 
  ThingSpeak.writeField(channel,3,Message.temperature,apiKey);
  delay(100);
 t_status = 
  ThingSpeak.writeField(channel,4,Message.wind_speed,apiKey);
  delay(100);
t_status = 
  ThingSpeak.writeField(channel,5,Message.wind_direction,apiKey);
  delay(100);
 t_status = 
  ThingSpeak.writeField(channel,6,Message.rain_volume,apiKey);

  Serial.printf("light value: %f \n", whole_data[Message.UID-1].light_sensor_value);
  Serial.printf("temp value: %f \n", whole_data[Message.UID-1].temperature);
  Serial.printf("humid value: %f \n", whole_data[Message.UID-1].humidity);
  Serial.printf("speed value: %f \n", whole_data[Message.UID-1].wind_speed);
  Serial.printf("direction value: %f \n", whole_data[Message.UID-1].wind_direction);
  Serial.printf("rain value: %f \n", whole_data[Message.UID-1].rain_volume);

  delay(3000);
}

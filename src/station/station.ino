/*  
* Time : 12:14 PM 2024-09-02
*/
#include "light_sensor.h"
#include "humid_temp_sensor.h"
#include "weather_station.h"
#include "config.h"
#include <WiFi.h>

const char* ssid     = "802.11";
const char* password = "12345678p";

// Implement to take uint8_t

WiFiServer server(80);

String header;
unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void check_wifi(){
WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

lightSensor Light_Sensor;


Data Message;

humidTempSensor Humid_Temp_Sensor;

weatherStation Weather_Station;

void setup(){
  Serial.begin(9600);
  // Get static IP
  IPAddress local_IP(192,168,237,5);
  IPAddress gateway(192,168,237,1);
  IPAddress subnet(255,255,255,0);
  IPAddress primaryDNS(8,8,8,8);
  IPAddress secondaryDNS(8,8,8,8);

  WiFi.config(local_IP,gateway,subnet,primaryDNS,secondaryDNS);
  check_wifi();
  Weather_Station.init();
  Light_Sensor.begin();
  Humid_Temp_Sensor.begin();

// Start Server
  server.begin();
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
// Serial.println("Direction ");
// Serial.print(Message.wind_direction);
delay(1000);

 WiFiClient client = server.available();
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());




if (client) {
 currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
      char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println("</style></head>");

            client.println("<body><h1>GCEK Weather Station</h1>");
            client.println("<body><h3> Station IP :  " +  String(WiFi.localIP().toString()) +  "</h3>");

            client.println("<p>Temperature  " + String(Message.temperature) + " degree C</p>");
            client.println("<p>humidity " + String(Message.humidity) + "</p>");
            client.println("<p>Wind Speed  " + String(Message.wind_speed) + " (kph) </p>");
            client.println("<p>Wind Direction  " + String(Message.wind_direction) + "</p>");
            client.println("<p>Total Rain Fall " +String(Message.rain_volume) + " (mm)  </p>");
            client.println("<p>Light Intensity " + String(Message.light_sensor_value)+ "</p>");

            client.println("</body></html>");

            client.println();
            break;
          } else {
          currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }


}



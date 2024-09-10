/*  
* Time : 12:14 PM 2024-09-02
*/
#include "light_sensor.h"
#include "humid_temp_sensor.h"
#include "weather_station.h"
#include "config.h"
#include <WiFi.h>

const char* ssid  = "GCEK-WiFi";
const char* password = "";

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
void reconnect(){
if ((WiFi.status()) != WL_CONNECTED ){
  WiFi.disconnect();
  delay(100);
  WiFi.reconnect();
}
}

void setup(){
  Serial.begin(9600);
  // Get static IP
  IPAddress local_IP(172,16,36,8);
  IPAddress gateway(172,16,36,1);
  IPAddress subnet(255,255,252,0);
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

void loop() {
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Humid_Temp_Sensor.get_readings();
  Message.light_sensor_value = Light_Sensor.get_value();
  Message.temperature = Humid_Temp_Sensor.temperature;
  Message.humidity = Humid_Temp_Sensor.humidity;
  Message.wind_speed = Weather_Station.get_speed();
  Message.wind_direction = Weather_Station.get_direction();
  Message.rain_volume = Weather_Station.get_rain();

  WiFiClient client = server.available();

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
            if (header.indexOf("GET /data") >= 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: application/json");
              client.println("Connection: close");
              client.println();
              client.print("{");
              client.print("\"temperature\":"); client.print(Message.temperature); client.print(",");
              client.print("\"humidity\":"); client.print(Message.humidity); client.print(",");
              client.print("\"wind_speed\":"); client.print(Message.wind_speed); client.print(",");
              client.print("\"wind_direction\":"); client.print(Message.wind_direction); client.print(",");
              client.print("\"rain_volume\":"); client.print(Message.rain_volume); client.print(",");
              client.print("\"light_sensor_value\":"); client.print(Message.light_sensor_value);
              client.println("}");
              client.println();
              break;
            } else {
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
            client.println("<h3> Station IP :  " +  String(WiFi.localIP().toString()) +  "</h3>");
              client.println("<p id='temperature'>Temperature: " + String(Message.temperature) + " (degree) C</p>");
              client.println("<p id='humidity'>Humidity: " + String(Message.humidity) + " %</p>");
              client.println("<p id='wind_speed'>Wind Speed: " + String(Message.wind_speed) + " kph </p>");
              client.println("<p id='wind_direction'>Wind Direction: " + String(Message.wind_direction) + "(degrees) </p>");
              client.println("<p id='rain_volume'>Total Rain Fall: " + String(Message.rain_volume) + " mm</p>");
              client.println("<p id='light_intensity'>Light Intensity: " + String(Message.light_sensor_value) + "</p>");
              client.println("<script>");
              client.println("setInterval(function() {");
              client.println("  var xhr = new XMLHttpRequest();");
              client.println("  xhr.onreadystatechange = function() {");
              client.println("    if (xhr.readyState == 4 && xhr.status == 200) {");
              client.println("      var data = JSON.parse(xhr.responseText);");
              client.println("      document.getElementById('temperature').innerHTML = 'Temperature: ' + data.temperature + ' (degree)C';");
              client.println("      document.getElementById('humidity').innerHTML = 'Humidity: ' + data.humidity + ' %';");
              client.println("      document.getElementById('wind_speed').innerHTML = 'Wind Speed: ' + data.wind_speed + ' kph';");
              client.println("      document.getElementById('wind_direction').innerHTML = 'Wind Direction: ' + data.wind_direction;");
              client.println("      document.getElementById('rain_volume').innerHTML = 'Total Rain Fall: ' + data.rain_volume + ' mm';");
              client.println("      document.getElementById('light_intensity').innerHTML = 'Light Intensity: ' + data.light_sensor_value;");
              client.println("    }");
              client.println("  };");
              client.println("  xhr.open('GET', '/data', true);");
              client.println("  xhr.send();");
              client.println("}, 5000);");
              client.println("</script>");

              client.println("</body></html>");
              client.println();
              break;
            }
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
      }
      }

    reconnect();
      }

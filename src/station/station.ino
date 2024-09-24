/*  
* Time : 12:14 PM 2024-09-02
*/
#include "light_sensor.h"
#include "humid_temp_sensor.h"
#include "weather_station.h"
#include "battery_monitor.h"
#include "config.h"
#include <WiFi.h>
#include "battery_monitor.h"
#include <pins.h>
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

Data new_data;

BatteryMonitor battery_monitor;

humidTempSensor Humid_Temp_Sensor;

weatherStation Weather_Station;
void reconnect(){
if ((WiFi.status()) != WL_CONNECTED ){
  Serial.println("Reconnecting .");
  WiFi.disconnect();
  WiFi.reconnect();
  delay(5000);
}
}

void setup(){
  Serial.begin(9600);
  // Get static IP
  IPAddress local_IP(replace_me);
  IPAddress gateway(replace_me);
  IPAddress subnet(replace_me);

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
  new_data.light_sensor_value = Light_Sensor.get_value();
  new_data.temperature = Humid_Temp_Sensor.temperature;
  new_data.humidity = Humid_Temp_Sensor.humidity;
  new_data.wind_speed = Weather_Station.get_speed();
  new_data.wind_direction = Weather_Station.get_direction();
  new_data.rain_volume = Weather_Station.get_rain();
  new_data.battery_voltage = battery_monitor.get_voltage(ADC_PIN);
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
              // client.print("\"temperature\":"); client.print(new_data.temperature); client.print(",");
              // client.print("\"humidity\":"); client.print(new_data.humidity); client.print(",");
              // client.print("\"wind_speed\":"); client.print(new_data.wind_speed); client.print(",");
              // client.print("\"wind_direction\":"); client.print(new_data.wind_direction); client.print(",");
              // client.print("\"rain_volume\":"); client.print(new_data.rain_volume); client.print(",");
              // client.print("\"light_sensor_value\":"); client.print(new_data.light_sensor_value);client.print(",");
              client.print("\"battery_voltage\":"); client.print(new_data.battery_voltage);client.print(",");
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
              // client.println("<p id='temperature'>Temperature: " + String(new_data.temperature) + " (degree) C</p>");
              // client.println("<p id='humidity'>Humidity: " + String(new_data.humidity) + " %</p>");
              // client.println("<p id='wind_speed'>Wind Speed: " + String(new_data.wind_speed) + " kph </p>");
              // client.println("<p id='wind_direction'>Wind Direction: " + String(new_data.wind_direction) + "(degrees) </p>");
              // client.println("<p id='rain_volume'>Total Rain Fall: " + String(new_data.rain_volume) + " mm</p>");
              // client.println("<p id='light_intensity'>Light Intensity: " + String(new_data.light_sensor_value) + "</p>");
              // client.println("<p id='light_intensity'>Light Intensity: " + String(new_data.light_sensor_value) + "</p>");
              client.println("<p id='battery_voltage'>Battery Voltage: " + String(new_data.battery_voltage) + "</p>");
              client.println("<script>");
              client.println("setInterval(function() {");
              client.println("  var xhr = new XMLHttpRequest();");
              client.println("  xhr.onreadystatechange = function() {");
              client.println("    if (xhr.readyState == 4 && xhr.status == 200) {");
              client.println("      var data = JSON.parse(xhr.responseText);");
              // client.println("      document.getElementById('temperature').innerHTML = 'Temperature: ' + data.temperature + ' (degree)C';");
              // client.println("      document.getElementById('humidity').innerHTML = 'Humidity: ' + data.humidity + ' %';");
              // client.println("      document.getElementById('wind_speed').innerHTML = 'Wind Speed: ' + data.wind_speed + ' kph';");
              // client.println("      document.getElementById('wind_direction').innerHTML = 'Wind Direction: ' + data.wind_direction;");
              // client.println("      document.getElementById('rain_volume').innerHTML = 'Total Rain Fall: ' + data.rain_volume + ' mm';");
              // client.println("      document.getElementById('light_intensity').innerHTML = 'Light Intensity: ' + data.light_sensor_value;");
              client.println("      document.getElementById('battery_voltage').innerHTML = 'Battery Voltage: ' + data.battery_voltage;");
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
  client.stop();
    reconnect();
    delay(100);
      }

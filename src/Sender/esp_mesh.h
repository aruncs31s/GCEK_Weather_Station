
#ifndef __ESP_MESH__
#define __ESP_MESH__
#include <esp_now.h>
#include <esp_wifi.h>
#include <stdint.h>  // Required for uint8_t
#include <string.h>  // Required for memcpy

class espMesh {
public:
  class mesh {
  public:
    void init();
    static void print_status(const uint8_t *mac_addr, esp_now_send_status_t status);
    void set_broadcast_address(uint8_t *addr);
    uint8_t broadcastAddress[6];  // Moved to inside the mesh class for encapsulation
    bool send(){

    }
  private:
    esp_now_peer_info_t peerInfo;

  };
  mesh Mesh;

  class wifi {
  public:
    void begin(uint8_t channel);
  };
  wifi Wifi;

private:
  uint8_t wifiChannel = 6;  // Correct initialization
};

// Define Data structure outside the class
typedef struct Data {
  uint8_t UID;
  char someChar[50];
  float light_sensor_value;
  long int wind_count;
  float wind_speed;
  int y;
} Data;

#endif // __ESP_MESH__

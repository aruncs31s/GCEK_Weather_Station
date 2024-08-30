#include "esp_mesh.h"
#include <WiFi.h>

void espMesh::mesh::print_status(const uint8_t *mac_addr,
                                 esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success"
                                                : "Delivery Fail");
}
void espMesh::mesh::set_broadcast_address(uint8_t *addr) {
  memcpy(broadcastAddress, addr, sizeof(broadcastAddress));
}

void espMesh::mesh::init() {
  if (esp_now_init() != ESP_OK) {
    Serial.println("Failed Starting");
    return;
  }
  esp_now_register_send_cb(print_status);
  memcpy(peerInfo.peer_addr, broadcastAddress, 6); // 6 -> number of bytes
  peerInfo.channel = 6;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}
void espMesh::wifi::begin(uint8_t channel) {
  WiFi.mode(WIFI_STA);
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);
}

#include <WiFi.h>
#include <WiFiUdp.h>

// Replace with your WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Desktop IP and port
const char* desktop_ip = "192.168.1.100";
const int desktop_port = 12345;

// Desktop MAC for WOL
byte desktop_mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

WiFiUDP udp;

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  delay(5000); // Wait for network stabilization

  // Send Wake-on-LAN packet on power restore
  sendWOL(desktop_mac);

  // Start sending heartbeats
}

void loop() {
  udp.beginPacket(desktop_ip, desktop_port);
  udp.write("heartbeat");
  udp.endPacket();
  delay(30000); // 30 seconds
}

void sendWOL(byte* mac) {
  byte packet;
  // 6 bytes FF
  for (int i = 0; i < 6; i++) packet[i] = 0xFF;
  // 16 repetitions of MAC
  for (int i = 6; i < 102; i += 6)
    memcpy(&packet[i], mac, 6);
  udp.beginPacket("255.255.255.255", 9); // WOL standard port
  udp.write(packet, 102);
  udp.endPacket();
}

#include "esp_camera.h"
#include <WiFi.h>
#define PWDN_GPIO_NUM     -1
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// Replace with your Wi-Fi credentials
const char* ssid = "Spot-Mesh";
const char* password = "Whatever1";

// Select the correct camera model
#define CAMERA_MODEL_AI_THINKER


// Start Camera Server
void startCameraServer();

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi Connected!");
  Serial.print("Stream URL: http://");
  Serial.println(WiFi.localIP());

  // Start the camera
  startCameraServer();
}

void loop() {
  delay(100);
}

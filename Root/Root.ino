#include "D:/Sru/smart-street-lights/Shared/Mesh.h"
#include "Handlers.h"


void SetupIO() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void SetupEspNow() {
  ESP_ERROR_CHECK(esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE));
  if (esp_now_init() != ESP_OK) DL("Error initializing ESP-NOW");
  // set callback routines
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
}

void setup() {
  SetupIO();
  WiFi.mode(WIFI_STA);
  SetupEspNow();
  Serial.println("Setup done");
}

void loop() {}

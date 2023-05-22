#define BOARD_ID 3
#include "D:/Sru/smart-street-lights/Shared/Mesh.h"
#include "Handlers.h"

void SetupIO(){
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void SetupWifi() {
  D("Client Board MAC Address: ");DL(WiFi.macAddress());
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  GetSavedChannel();
}

void SetupEspNow() {
  ESP_ERROR_CHECK(esp_wifi_set_channel(channel,  WIFI_SECOND_CHAN_NONE));
  if(esp_now_init() != ESP_OK) DL("Error initializing ESP-NOW");
  // set callback routines
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
  pairingStatus = REQUEST_PAIRING;
}

void setup() {
  SetupIO();
  SetupWifi();
  SetupEspNow();
}
void loop() {
  if(pairingStatus<PAIRING_COMPLETE) HandlePairing();
  delay(LOOPDELAY);
}

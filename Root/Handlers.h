void HandleData() {}

void HandlePairing()
{
  uint8_t* node_addr;
  memcpy(node_addr, pairingData.macAddr, sizeof(uint8_t[6])); // Copy the mac address
  D("Pairing request from: "); PrintMac(node_addr);
  DL(pairingData.msgType);DL(pairingData.id);DL(pairingData.channel);
  if (pairingData.id <= 0) return; // react to node messages only
  pairingData.id = 0;       // 0 is server
  // If server is in AP_STA mode peers need to send data to server soft AP MAC address
  WiFi.softAPmacAddress(pairingData.macAddr);
  pairingData.channel = channel;
  // Send confirmation for node to add peer
  esp_err_t result = esp_now_send(node_addr, (uint8_t *) &pairingData, sizeof(pairingData));
  // Add the node to peer list
  AddPeer(node_addr, channel);
}

void HandleCommand() {}

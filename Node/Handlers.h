void HandleData() {
    // Nothing to do here currently
}

void PairingResponseHandler() {
    if(pairingData.id != 0) return; // Ignore if the reply is not from server
    bool added = AddPeer(pairingData.macAddr, pairingData.channel); // add the server to the peer list 
    // Copy the mac address to the serverAddress variable.
    if(added) memcpy(serverAddress, pairingData.macAddr, sizeof(uint8_t[6]));
}

void RequestPairing(){
  pairingData.msgType = PAIRING;
  pairingData.id = BOARD_ID;     
  pairingData.channel = channel;
  esp_now_send(serverAddress, (uint8_t *) &pairingData, sizeof(pairingData));
  lastSent = millis();
}

void CheckForTimeout() {
  unsigned long now = millis();
  if (now - lastSent >= MESH_TIMEOUT) {
    lastSent = now;
    channel++;
    if(channel > MAX_CHANNEL) channel = 1;
    pairingStatus = REQUEST_PAIRING;
  }
}

void HandleCommand() {
    switch(meshCommand.todo) {
    case TURNON:
        // turn on led & relay
        break;
    case TURNOFF:
        // turn off led & relay
        break;
    }
}

void HandlePairing(){
  switch(pairingStatus) {
    case NOT_PAIRED:
      break;
    case REQUEST_PAIRING:
      RequestPairing();
      break;
    case PAIRING_RESPONSE:
      PairingResponseHandler();
      break;
    case PAIRING_INITIATED:
      CheckForTimeout();
      break;
    case PAIRING_COMPLETE:
      // nothing to do here 
      break;
  }
}  
void HandleData() {}
void HandlePairing() {
switch(pairingStatus) {
    case REQUEST_PAIRING:
      RequestPairing();
      break;
    case PAIRING_INITIATED:
      CheckForTimeout();
      break;
    case PAIRING_COMPLETE:
      // nothing to do here 
      break;
  }
}  

void HandleCommand() {}


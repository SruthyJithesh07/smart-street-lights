// Guard to prevent multiple inclusions of this header file.
#ifndef MESH_H
#define MESH_H

#include <EEPROM.h>
#include "Common.h"
#include "MeshDataTypes.h"

// Instances of the command, message, and pairing struct to be used globally.
struct_message meshMessage;
struct_pairing pairingData;
struct_command meshCommand;
uint8_t channel = CHANNEL;
unsigned long lastSent = 0;

// Pairing status variable initialized to NOT_PAIRED.
PairingStatus pairingStatus = NOT_PAIRED;

// Function declarations.
// These should be implemented at the Node and Root.
void HandleData();
void HandlePairing();
void HandleCommand();

// Callback function for data sent.
void OnDataSent(const uint8_t *sent_to, esp_now_send_status_t status)
{
    D(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success to " : "Delivery Fail to ");
    PrintMac(sent_to);
}

// Callback function for data received.
void OnDataRecv(const uint8_t *recd_from, const uint8_t *incomingData, int len)
{
    D("Data received from ");
    PrintMac(recd_from);
    uint8_t type = incomingData[0]; // First byte of the message is the type of message.

    D(len);
    D(" bytes of type ");
    DL(type);

    // Switch statement to handle received data based on its type.
    switch (type)
    {
    case DATA:
        // If the data is of type DATA, copy it to meshMessage and handle it.
        memcpy(&meshMessage, incomingData, sizeof(meshMessage));
        HandleData();
        break;
    case PAIRING:
        // If the data is of type PAIRING, copy it to pairingData and handle it.
        memcpy(&pairingData, incomingData, sizeof(pairingData));
        HandlePairing();
        break;
    case COMMAND:
        // If the data is of type COMMAND, copy it to meshCommand and handle it.
        memcpy(&meshCommand, incomingData, sizeof(meshCommand));
        HandleCommand();
        break;
    }
}

// Conditional compilation depending on whether SAVE_CHANNEL is defined or not.
#ifdef SAVE_CHANNEL

// Function to get the saved channel from EEPROM.
void GetSavedChannel()
{
    DL("Get Saved Channel");
    // Variable to hold the saved channel.
    int savedChannel;

    // Initialize EEPROM with the size of 10.
    EEPROM.begin(10);

    // Read the saved channel from the first location of EEPROM.
    savedChannel = EEPROM.read(0);

    // Check if the saved channel is within valid range, if it is, assign it to channel,
    // else assign the default CHANNEL.
    if (savedChannel >= 1 && savedChannel <= MAX_CHANNEL)
    {
        channel = savedChannel;
    }
    else
    {
        channel = CHANNEL;
    }

    // Print the channel to serial.
    DL(channel);
}

// Function to save the pairing channel to EEPROM.
void SetSavedChannel()
{
    DL("Set Saved Channel");
    EEPROM.write(0, pairingData.channel); // Write the pairing channel to the first location of EEPROM.
    EEPROM.commit(); // Commit changes to EEPROM.
}

// If SAVE_CHANNEL is not defined, GetSavedChannel and SetSavedChannel do nothing.
#else
void GetSavedChannel() {}
void SetSavedChannel() {}
#endif

// Function to remove a peer from ESP-NOW.
void RemovePeer(const uint8_t *mac_to_rem)
{
    D("Remove Peer: "); PrintMac(mac_to_rem);
    esp_now_del_peer(mac_to_rem);
}

// Function to add a peer to ESP-NOW.
bool AddPeer(const uint8_t *mac_to_add, uint8_t chan)
{
    D("Add Peer: "); PrintMac(mac_to_add);
    // If peer already exists, return from function.
    if (esp_now_is_peer_exist(mac_to_add)) return true;

    // Define a peer struct and initialize to zeros.
    esp_now_peer_info_t peer;
    memset(&peer, 0, sizeof(esp_now_peer_info_t));

    // Set the WiFi channel.
    ESP_ERROR_CHECK(esp_wifi_set_channel(chan, WIFI_SECOND_CHAN_NONE));
    
    peer.channel = chan; // Assign channel
    peer.encrypt = false; // Disable encryption.
    memcpy(peer.peer_addr, mac_to_add, sizeof(uint8_t[6])); // Copy the mac address

    // Add the peer to ESP-NOW.
    if (esp_now_add_peer(&peer) != ESP_OK)
    {
        DL("Failed to add peer");
        return false;
    }

    return true;

}

// End of multiple inclusion guard.
#endif

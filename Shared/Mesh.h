#ifndef MESH_H
#define MESH_H

#include "Common.h"

typedef struct struct_command
{
    uint8_t msgType;
    uint8_t id;
    uint8_t todo;
} struct_command;

typedef struct struct_message
{
    uint8_t msgType;
    uint8_t id;
    float temp;
    float hum;
    unsigned int readingId;
} struct_message;

typedef struct struct_pairing
{ // new structure for pairing
    uint8_t msgType;
    uint8_t id;
    uint8_t macAddr[6];
    uint8_t channel;
} struct_pairing;

enum MessageType
{
    PAIRING,
    DATA,
    COMMAND
};
enum CommandType
{
    TURNON,
    TURNOFF,
    MORE,
    LESS,
    PING
};
enum PairingStatus
{
    NOT_PAIRED,
    REQUEST_PAIRING,
    PAIRING_INITIATED,
    PAIRING_COMPLETE
};

struct_message meshMessage;
struct_pairing pairingData;
struct_command meshCommand;
PairingStatus pairingStatus = NOT_PAIRED;

void HandleData();
void HandlePairing();
void HandleCommand();

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    D("Last Packet Send Status: ");
    D(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success to " : "Delivery Fail to ");
    PrintMac(mac_addr);
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len)
{
    D("Data received from ");
    PrintMac(mac_addr);
    uint8_t type = incomingData[0]; // first message byte is the type of message
    D(len);
    D(" bytes of type ");
    DL(type);
    switch (type)
    {
    case DATA:
        memcpy(&meshMessage, incomingData, sizeof(meshMessage));
        HandleData();
        break;
    case PAIRING:
        memcpy(&pairingData, incomingData, sizeof(pairingData));
        HandlePairing();
        break;
    case COMMAND:
        memcpy(&meshCommand, incomingData, sizeof(meshCommand));
        HandleCommand();
        break;
    }
}

#endif
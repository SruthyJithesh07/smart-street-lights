// Guard to prevent multiple inclusions of this header file.
#ifndef MESH_DATA_TYPES_H
#define MESH_DATA_TYPES_H

// Struct that represents a command.
typedef struct struct_command
{
    uint8_t msgType;
    uint8_t id;
    uint8_t todo;
} struct_command;

// Struct that represents a message.
typedef struct struct_message
{
    uint8_t msgType;
    uint8_t id;
    float temp;
    float hum;
    unsigned int readingId;
} struct_message;

// Struct that represents pairing information.
typedef struct struct_pairing
{
    uint8_t msgType;
    uint8_t id;
    uint8_t macAddr[6];
    uint8_t channel;
} struct_pairing;

// Enum to define types of messages.
enum MessageType
{
    PAIRING,
    DATA,
    COMMAND
};

// Enum to define types of commands.
enum CommandType
{
    TURNON,
    TURNOFF,
    MORE,
    LESS,
    PING
};

// Enum to define pairing status.
enum PairingStatus
{
    NOT_PAIRED,
    REQUEST_PAIRING,
    PAIRING_INITIATED,
    PAIRING_RESPONSE,
    PAIRING_COMPLETE
};


// End of multiple inclusion guard.
#endif

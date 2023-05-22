// Guard to prevent multiple inclusions of this header file.
#ifndef COMMON_H
#define COMMON_H

// Includes required libraries for WiFi and ESP-NOW.
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>

#define DEBUG    (1)      // Define DEBUG to switch between debug and non-debug modes.
#define CHANNEL  5        // Define default channel
#define SAVE_CHANNEL  (1) // Define SAVE_CHANNEL to save last used channel.
#define MAX_CHANNEL   11  // Define SAVE_CHANNEL to save last used channel.
#define MESH_TIMEOUT  250

// Conditional compilation depending on whether DEBUG is defined or not.
#ifdef DEBUG
  // Debugging macros to print to serial. D for print, DF for floating point print, DL for println.
  #define D(x)      Serial.print(x)
  #define DF(x)     Serial.print(x,4)
  #define DL(x)     Serial.println(x)
  
  // Loop delay in milliseconds for debugging mode.
  #define LOOPDELAY   500                 
#else
  // If not in debug mode, these macros do nothing.
  #define D(x)
  #define DF(x)
  #define DL(x)

  // Loop delay in milliseconds for non-debugging mode.
  #define LOOPDELAY   2000                
#endif

// Function to print MAC address in hexadecimal format, only active in debug mode.
void PrintMac(const uint8_t * mac_addr){
#ifdef DEBUG
  // Temporary string to hold MAC address in human readable format.
  char macStr[18];
  // Formats MAC address to standard hexadecimal format (xx:xx:xx:xx:xx:xx).
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  // Print the MAC address using the debug print macro.
  DL(macStr);
#endif
}

// End of multiple inclusion guard.
#endif

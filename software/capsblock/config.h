// ===================================================================================
// User Configurations for CAPS bLOCK
// ===================================================================================
//
// Description:
// ------------
// Tired of accidentally hitting the CAPS-LOCK key? It doesn't have to be. 
// CAPS bLOCK identifies itself as a USB HID keyboard and constantly monitors the
// state of CAPS LOCK. It immediately deactivates it if it has been activated.
//
// Operating Instructions:
// -----------------------
// - Connect the board via USB to your PC. It should be detected as a HID keyboard.
// - The blocking function can be switched on/off by pressing the ACT button. The LED
//   will light up when the blocking function is activated.

#pragma once

// Pin definitions
#define PIN_LED             PC1       // pin connected to LED (active LOW)
#define PIN_KEY             PC2       // pin connected to ACT button (active LOW)

// USB pin definitions
#define USB_PORT            A         // [A,C,D] GPIO Port to use with D+ and D-
#define USB_PIN_DP          1         // [0-4] GPIO Number for USB D+ Pin
#define USB_PIN_DM          2         // [0-4] GPIO Number for USB D- Pin

// USB configuration descriptor
#define USB_MAX_POWER_mA    50        // max power in mA 

// USB device descriptor
#define USB_VENDOR_ID       0x1209    // VID
#define USB_PRODUCT_ID      0xc003    // PID
#define USB_DEVICE_VERSION  0x0100    // v1.0 (BCD-format)
#define USB_LANGUAGE        0x0409    // US English

// USB descriptor strings
#define MANUF_STR           "wagiminator"
#define PROD_STR            "CAPS bLOCKer"
#define SERIAL_STR          "CH32V003HID"

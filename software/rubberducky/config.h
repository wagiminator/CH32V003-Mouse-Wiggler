// ===================================================================================
// User Configurations for Rubber Ducky
// ===================================================================================
//
// Description:
// ------------
// Identifies itself as a USB HID keyboard and types a message on button press.
//
// Operating Instructions:
// -----------------------
// - Connect the board via USB to your PC. It should be detected as a HID keyboard.
// - Open a text editor and place the cursor inside the text box.
// - Press the button and you can see a message typed in by the device.
// - You can edit the keyboard macro in macros.h.

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
#define PROD_STR            "Rubber Ducky"
#define SERIAL_STR          "CH32V003HID"

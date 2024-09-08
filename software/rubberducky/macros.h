// ===================================================================================
// User Configurations for Rubber Ducky
// ===================================================================================
//
// Define the keyboard actions here.
// For keyboard commands refer to usb_keyboard.h. Of course, you can also press any
// keyboard shortcut or other key combinations you like.

#pragma once

#include <usb_keyboard.h>             // USB HID keyboard functions

// This macro will be executed on ACT button press
static inline void KBD_macro(void) {
  KBD_print("Hello world!");          // type message
  KBD_type(KBD_KEY_RETURN);           // press return key
}

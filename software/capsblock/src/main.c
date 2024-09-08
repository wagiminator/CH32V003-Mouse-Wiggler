// ===================================================================================
// Project:   CAPS bLOCKer for CH32V003
// Version:   v1.0
// Year:      2023
// Author:    Stefan Wagner
// Github:    https://github.com/wagiminator
// EasyEDA:   https://easyeda.com/wagiminator
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// Tired of accidentally hitting the CAPS-LOCK key? It doesn't have to be. 
// CAPS bLOCK identifies itself as a USB HID keyboard and constantly monitors the
// state of CAPS LOCK. It immediately deactivates it if it has been activated.
//
// References:
// -----------
// - CNLohr ch32v003fun: https://github.com/cnlohr/ch32v003fun
// - CNLohr rv003usb:    https://github.com/cnlohr/rv003usb
// - WCH Nanjing Qinheng Microelectronics: http://wch.cn
//
// Compilation Instructions:
// -------------------------
// - Make sure GCC toolchain (gcc-riscv64-unknown-elf, newlib) and Python3 with rvprog
//   are installed. In addition, Linux requires access rights to WCH-LinkE programmer.
// - Connect the WCH-LinkE programmer to the MCU board.
// - Run 'make flash'.
//
// Operating Instructions:
// -----------------------
// - Connect the board via USB to your PC. It should be detected as a HID keyboard.
// - The blocking function can be switched on/off by pressing the ACT button. The LED
//   will light up when the blocking function is activated.


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================
#include "config.h"                   // user configurations
#include "system.h"                   // system functions
#include "gpio.h"                     // GPIO functions
#include "usb_keyboard.h"             // USB HID keyboard functions

// ===================================================================================
// Main Function
// ===================================================================================
int main(void) {
  // Setup
  PIN_input_PU(PIN_KEY);              // set button pin to input pullup
  PIN_output(PIN_LED);                // set LED pin to output
  DLY_ms(1);                          // wait a bit for USB
  KBD_init();                         // init USB HID keyboard

  // Initial state: ACTIVATED
  uint8_t act = 1;                    // set activation state flag
  PIN_low(PIN_LED);                   // switch on indicator LED

  // Loop
  while(1) {
    if(act && KBD_CAPS_LOCK_state) {  // CAPS LOCK was pressed?
      KBD_type(KBD_KEY_CAPS_LOCK);    // press CAPS LOCK again to deactivate
      DLY_ms(30);                     // wait a bit
    }

    if(!PIN_read(PIN_KEY)) {          // button pressed ?
      PIN_write(PIN_LED, act);        // set indicator LED
      act = !act;                     // toggle activation state flag
      DLY_ms(10);                     // debounce
      while(!PIN_read(PIN_KEY));      // wait for button released
      DLY_ms(10);                     // debounce
    }
  }
}

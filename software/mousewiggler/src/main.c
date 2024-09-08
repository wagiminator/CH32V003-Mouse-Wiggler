// ===================================================================================
// Project:   Mouse Wiggler for CH32V003
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
// Mouse Wiggler is a tool that simulates movements of the mouse pointer so that 
// no screen saver is activated and the PC or notebook is not put to sleep. The
// mouse pointer movements are imperceptibly small, so that you can continue to
// work normally on your PC even with the function activated.
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
// - Connect the board via USB to your PC. It should be detected as a HID mouse.
// - The wiggle function can be switched on/off by pressing the ACT button. The LED
//   will light up when the wiggle function is activated.


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================
#include "config.h"                   // user configurations
#include "system.h"                   // system functions
#include "gpio.h"                     // GPIO functions
#include "usb_mouse.h"                // USB HID mouse functions

// ===================================================================================
// Main Function
// ===================================================================================
int main(void) {
  // Setup
  PIN_input_PU(PIN_KEY);              // set button pin to input pullup
  PIN_output(PIN_LED);                // set LED pin to output
  DLY_ms(1);                          // wait a bit for USB
  MOUSE_init();                       // init USB HID mouse

  // Initial state: ACTIVATED
  uint8_t cnt = 1;                    // set time counter
  uint8_t act = 1;                    // set activation state flag
  PIN_low(PIN_LED);                   // switch on indicator LED

  // Loop
  while(1) {
    if(act && !--cnt) {               // time to wiggle ?
      MOUSE_move( 1, 0);              // move mouse pointer just a tiny bit
      DLY_ms(20);                     // wait for next poll
      MOUSE_move(-1, 0);              // move pointer back to where it was
    }

    if(!PIN_read(PIN_KEY)) {          // button pressed ?
      PIN_write(PIN_LED, act);        // set indicator LED
      act = !act;                     // toggle activation state flag
      DLY_ms(10);                     // debounce
      while(!PIN_read(PIN_KEY));      // wait for button released
    }

    DLY_ms(50);                       // wait a bit
  }
}

# Mouse Wiggler based on CH32V003
**Mouse Wiggler** is a tool that simulates movements of the mouse pointer so that no screen saver is activated and the PC or laptop is not put to sleep. Since the board can be used in many ways, it can also become a **Rubber Ducky** or a **CAPS bLOCKer** with the additional firmware that is included. It is controlled via the push button at the end of the board and displays its status via an LED.

![MouseWiggler_pic1.jpg](https://raw.githubusercontent.com/wagiminator/CH32V003-Mouse-Wiggler/main/documentation/MouseWiggler_pic1.jpg)

# Hardware
## Schematic
![MouseWiggler_wiring.png](https://raw.githubusercontent.com/wagiminator/CH32V003-Mouse-Wiggler/main/documentation/MouseWiggler_wiring.png)

## The CH32V003 Family of 32-bit RISC-V Microcontrollers
The CH32V003 series is a collection of industrial-grade general-purpose microcontrollers that utilize the QingKe RISC-V2A core design supporting the RV32EC instruction set. These microcontrollers are equipped with various features such as a 48MHz system main frequency, 16KB flash, 2KB SRAM, 2.7V - 5.5V supply voltage support, a single-wire serial debug interface, low power consumption, and an ultra-small package. Additionally, the CH32V003 series includes a built-in set of components including a DMA controller, a 10-bit ADC, op-amp comparators, multiple timers, and standard communication interfaces such as USART, I2C, and SPI.

## Building Instructions
1. Take the Gerber files (the *zip* file inside the *hardware* folder) and upload them to a PCB (printed circuit board) manufacturer of your choice (e.g., [JLCPCB](https://jlcpcb.com/)). They will use these files to create the circuit board for your device and send it to you.
2. Once you have the PCB, you can start soldering the components onto it. Use the BOM (bill of materials) and schematic as a guide to make sure everything is connected correctly. You can find the corresponding files in the *hardware* folder.
3. Upload the firmware by following the instructions in the next section (see below).

![MouseWiggler_pic2.jpg](https://raw.githubusercontent.com/wagiminator/CH32V003-Mouse-Wiggler/main/documentation/MouseWiggler_pic2.jpg)
![MouseWiggler_pic3.jpg](https://raw.githubusercontent.com/wagiminator/CH32V003-Mouse-Wiggler/main/documentation/MouseWiggler_pic3.jpg)

# Software
## Software USB
Since the CH32V003 lacks a hardware USB peripheral, USB functionality is handled in software. Charles Lohr's excellent implementation, [RV003USB](https://github.com/cnlohr/rv003usb), is used for this. It emulates a USB low-speed device using pin-change interrupts and bit-banging, with assembly code for the low-level protocol and some C code for higher-level functionality.

## Firmware Versions
### Mouse Wiggler
Mouse Wiggler is an incredibly useful tool that helps prevent your computer from going into sleep mode or activating a screensaver. It does this by simulating small, imperceptible movements of the mouse pointer, keeping your computer active and alert without disrupting your work flow. This feature is especially helpful for those who work in long stretches or for those who leave their computer on for extended periods of time, such as for download or rendering tasks. When the wiggle function is activated, the LED will light up, making it easy to know that the device is working.

Connect the board via USB to your PC. It should be detected as a HID mouse. Activate/deactivate the wiggle function by pressing the push button. The LED lights up when the function is activated.

### Rubber Ducky
A USB Rubber Ducky is a small device that looks like a regular USB drive. It can be plugged into a computer and once plugged in, it can emulate a keyboard and inject keystrokes that can execute malicious code or exfiltrate data to the attacker. However, this version of the rubber ducky is completely harmless. It identifies itself as a USB HID keyboard and types a predefined message when the push button is pressed. This can be used for various purposes like automating repetitive tasks, controlling the PC via keyboard shortcuts, entering complex passwords, and more. The included rubber ducky firmware can be reprogrammed by editing *macros.h* to customize the keystrokes and messages according to your needs.

Connect the board via USB to your PC. It should be detected as a HID keyboard. Open a text editor und press the push button on the board.

### CAPS bLOCK
Tired of accidentally hitting the CAPS LOCK key and typing everything in uppercase? CAPS bLOCK is here to help you. Once plugged in, it identifies itself as a USB HID keyboard and constantly monitors the state of the CAPS LOCK key. If it has been accidentally activated, it immediately deactivates it. The device is designed to work seamlessly in the background. When the blocking function is activated, the LED will light up, making it easy to know that the device is working.

Connect the board via USB to your PC. It should be detected as a HID keyboard. Activate/deactivate the blocking function by pressing the push button. The LED lights up when the function is activated.

## Programming and Debugging Device
To program the CH32V003 microcontroller, you will need a special programming device which utilizes the proprietary single-wire serial debug interface (SDI). The [WCH-LinkE](http://www.wch-ic.com/products/WCH-Link.html) (pay attention to the "E" in the name) is a suitable device for this purpose and can be purchased commercially for around $4. This debugging tool is not only compatible with the CH32V003 but also with other WCH RISC-V and ARM-based microcontrollers.

![CH32V003_wch-linke.jpg](https://raw.githubusercontent.com/wagiminator/Development-Boards/main/CH32V003F4P6_DevBoard/documentation/CH32V003_wch-linke.jpg)

To use the WCH-LinkE on Linux, you need to grant access permissions beforehand by executing the following commands:
```
echo 'SUBSYSTEM=="usb", ATTR{idVendor}=="1a86", ATTR{idProduct}=="8010", MODE="666"' | sudo tee /etc/udev/rules.d/99-WCH-LinkE.rules
echo 'SUBSYSTEM=="usb", ATTR{idVendor}=="1a86", ATTR{idProduct}=="8012", MODE="666"' | sudo tee -a /etc/udev/rules.d/99-WCH-LinkE.rules
sudo udevadm control --reload-rules
```

On Windows, if you need to you can install the WinUSB driver over the WCH interface 1 using the [Zadig](https://zadig.akeo.ie/) tool.

To upload the firmware, you need to ensure that the Mouse Wiggler is disconnected from USB. Then, you should make the following connections to the WCH-LinkE (you can use a pogo pin clip for this):

```
WCH-LinkE      Wiggler
+-------+      +-----+
|  SWDIO| <--> |DIO  |
|    GND| ---> |GND  |
|    3V3| ---> |VCC  |
+-------+      +-----+
```

If the blue LED on the WCH-LinkE remains illuminated once it is connected to the USB port, it means that the device is currently in ARM mode and must be switched to RISC-V mode initially. There are a few ways to accomplish this:
- You can utilize the Python command-line tool [rvprog](https://pypi.org/project/rvprog/) (with *-v* option).
- Alternatively, you can select "WCH-LinkRV" in the software provided by WCH, such as MounRiver Studio or WCH-LinkUtility.
- Another option is to hold down the ModeS button on the device while plugging it into the USB port.

More information can be found in the [WCH-Link User Manual](http://www.wch-ic.com/downloads/WCH-LinkUserManual_PDF.html).

## Compiling and Uploading Firmware using the Makefile
### Linux
Install the toolchain (GCC compiler, Python3, and rvprog):
```
sudo apt install build-essential libnewlib-dev gcc-riscv64-unknown-elf
sudo apt install python3 python3-pip
pip install rvprog
```

Disconnect the Mouse Wiggler from the USB port. Connect the Mouse Wiggler via the 3-pin PROG header to the WCH-LinkE programming device (you can use a pogo pin clip for this). Open a terminal and navigate to the folder with the *makefile*. Run the following command to compile and upload:
```
make flash
```

### Other Operating Systems
Follow the instructions on [CNLohr's ch32v003fun page](https://github.com/cnlohr/ch32v003fun/wiki/Installation) to set up the toolchain on your respective operating system (for Windows, use WSL). Also, install [Python3](https://www.pythontutorial.net/getting-started/install-python/) and [rvprog](https://pypi.org/project/rvprog/). Compile and upload with "make flash". Note that I only have Debian-based Linux and have not tested it on other operating systems.

## Uploading pre-compiled Firmware Binary
WCH offers the free but closed-source software [WCH-LinkUtility](https://www.wch.cn/downloads/WCH-LinkUtility_ZIP.html) to upload the precompiled hex-file with Windows. Select the "WCH-LinkRV" mode in the software, open the *<firmware>.hex* file in the *bin* folder and upload it to the microcontroller.

Alternatively, there is an open-source tool called [minichlink](https://github.com/cnlohr/ch32v003fun/tree/master/minichlink) developed by Charles Lohr (CNLohr). It can be used with Windows, Linux and Mac.

If you have installed [Python3](https://www.pythontutorial.net/getting-started/install-python/) on your system, you can also use the platform-independent open-source command-line tool [rvprog](https://pypi.org/project/rvprog/) for uploading:
```
rvprog -f bin/<firmware>.bin
```

# References, Links and Notes
- [EasyEDA Design Files](https://oshwlab.com/wagiminator)
- [CNLohr: rv003usb](https://github.com/cnlohr/rv003usb)
- [MCU Templates](https://github.com/wagiminator/MCU-Templates)
- [MCU Flash Tools](https://github.com/wagiminator/MCU-Flash-Tools)
- [CH32V003 Datasheets](http://www.wch-ic.com/products/CH32V003.html)
- [CH552E Mouse Wiggler](https://github.com/wagiminator/CH552-MouseWiggler)

# License
![license.png](https://i.creativecommons.org/l/by-sa/3.0/88x31.png)

This work is licensed under Creative Commons Attribution-ShareAlike 3.0 Unported License. 
(http://creativecommons.org/licenses/by-sa/3.0/)

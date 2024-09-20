# VoltMax-Station
## What’s ev charger
* a. Description: 
  * An EV charger supports both dashboard display and touchscreen interface, offering functionalities such as user-friendly interaction through an LCD display, device connection, and basic data transmission. It enables user ID authentication, scheduling and canceling charging sessions, and firmware updates via OTA. The system also monitors essential factors like power voltage, temperature, and connectivity through RJ45, WiFi, or 4G, providing real-time alerts for any issues. With the ability to reset and clear cache, it ensures a smooth and efficient charging experience.
  
* b. supportive features 
  * Dashboard LCD/LED
  * Device connection: SAE J1772, vehicle simulator, continuing electrical board, power board, fan, speaker, motherboard, RFID
  * UART data transmission
  * User ID authentication
  * Start scheduled charging
  * Cancel scheduled charging
  * Clear cache
  * Reset
  * Retrieve all charging station information
  * Retrieve current version
  * RJ45/WiFi/4G basic connection to AP UI design interface
  * Detect power voltage, low power history, stop charging, alarm display
  * Detect high temperature, stop charging, alarm display

## How to implement 
* Hardware: 
  * Board: Microchip’s SAMA5D27-SOM1-EK1 MPU
  * Dashboard LCD/LED
  * 
* System Software:
  * OS: Linux kernel v5.4.81 
  * FW: uboot 2019.04-at91
  * runtime: python 3.8
  * frameworks: OCPP v1.6

* Application Software (Application under development) :
  * Dashboard implemented by C/C++ :
    * charge time 
    * charge voltage control 
    * output: date
    * payment 
    * alert 

## Boot process
* Bootloader: 



## OS Implementation
Set up the development environment for cross-compiling the OS. Using Buildroot or Yocto for embedded Linux.

## Debugging and Testing
* Enable UART output to log bootloader and OS boot messages.
* Perform extensive testing to validate peripheral drivers, memory access, and system stability.

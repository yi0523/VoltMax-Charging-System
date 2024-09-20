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
#### Prerequisite
create a folder to store the buildroot source code
buildroot-at91 (Burn binary)
buildroot-external-microchip (Setting related)
```
# mkdir git
# mkdir som1_ek
# cd git
```
#### 1. If make fails: First delete the “buildroot-at91” and “buildroot-external-microchip” folders
```
#rm -rf buildroot-at91/
#rm -rf buildroot-external-microchip/
```
#### 2. Buildroot Source Build, install necessary packages
```
ivy@ubuntu:~/git$
sudo apt update
 
sudo apt install build-essential ccache ecj fastjar file g++ gawk \gettext git java-propose-classpath libelf-dev libncurses5-dev \libncursesw5-dev libssl-dev python python2.7-dev python3 unzip wget \python3-distutils python3-setuptools python3-dev rsync subversion \swig time xsltproc zlib1g-dev
 
sudo apt-get install libssl1.0-dev
```
#### 3. Download build-root & Switch Branch,
When completed, two packages will be generated ”buildroot-at91” & “buildroot-external-microchip”
```
ivy@ubuntu:~/git/som1_ek $
git clone https://github.com/linux4sam/buildroot-at91.git -b 2020.02-at91
 
git clone https://github.com/linux4sam/buildroot-external-microchip.git -b 2020.02-at91   
```
#### 4. SAMA5D27 SOM1 EK source build
```
make atmel_sama5d27_som1_ek_mmc_dev_defconfig
 
BR2_EXTERNAL=../buildroot-external-microchip/ make sama5d27_som1_ek_graphics_defconfig
 
sudo apt-get install gtk-doc-tools
 
sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat libsdl1.2-dev xterm
 
make (6~7 hours)
```
- ![make](https://github.com/user-attachments/assets/01281573-4df7-4776-b905-e65d9ec77855)

#### 5. Solve the problem of patch package path
```
ivy@ubuntu:~/git/som1_ek/buildroot-at91$
make menuconfig
```
- choose External options
- ![choose External options](https://github.com/user-attachments/assets/aa06d099-1999-4eb1-816b-635f76124965)

- Remove the “*” of gst1-at91
- ![Remove the gst1-at91](https://github.com/user-attachments/assets/e3b64311-9b0c-4eca-879f-69f793d87819)

- make again
- ![make again](https://github.com/user-attachments/assets/2d01cfb7-9a61-4a8f-a776-a1703f1d312d)

- Successful
- ![Successful](https://github.com/user-attachments/assets/24580e2b-dc33-427a-95eb-d7d8bae9f418)


## OS Implementation
Set up the development environment for cross-compiling the OS. Using Buildroot or Yocto for embedded Linux.

## Debugging and Testing
* Enable UART output to log bootloader and OS boot messages.
* Perform extensive testing to validate peripheral drivers, memory access, and system stability.

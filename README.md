# VoltMax-Charging-System
## What’s ev charger
* a. Description: 
  * An EV charger supports both dashboard display and touchscreen interface, offering functionalities such as user-friendly interaction through an LCD display, device connection, and basic data transmission. It enables user ID authentication, scheduling and canceling charging sessions, and firmware updates via OTA. The system also monitors essential factors like power voltage, temperature, and connectivity through RJ45, WiFi, or 4G, providing real-time alerts for any issues. With the ability to reset and clear cache, it ensures a smooth and efficient charging experience.
  * Design
  
  ![d](https://github.com/user-attachments/assets/6080661f-3c8b-41d9-bddd-4118144258e7)
  * System setup
  
   ![env_build](https://github.com/user-attachments/assets/5a3cd95b-470d-44d8-bd7c-b642c2511581)
  
* b. Supportive features 
  * Dashboard LCD/LED
  * Device connection: SAE J1772, vehicle simulator,fan, speaker, motherboard, RFID
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
  
   ![a5d27_som1_ek_board](https://github.com/user-attachments/assets/5e7c5d76-d1a7-4020-b37d-3d558239cd2a)
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
* Example for verification result

 ![verification_result](https://github.com/user-attachments/assets/1fa557d6-05da-45b0-9ca1-8d9150edcbaf)
  

## Boot process

![Boot process](https://github.com/user-attachments/assets/66b1c3c9-67df-47d9-be9a-be5774535be0)
## System quickstart guide:
### Prerequisite
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


![make](https://github.com/user-attachments/assets/01281573-4df7-4776-b905-e65d9ec77855)

#### 5. Solve the problem of patch package path
```
ivy@ubuntu:~/git/som1_ek/buildroot-at91$
make menuconfig
```
- choose External options

 ![choose External options](https://github.com/user-attachments/assets/aa06d099-1999-4eb1-816b-635f76124965)

- Remove the “*” of gst1-at91

 ![Remove the gst1-at91](https://github.com/user-attachments/assets/e3b64311-9b0c-4eca-879f-69f793d87819)

- make again

 ![make again](https://github.com/user-attachments/assets/2d01cfb7-9a61-4a8f-a776-a1703f1d312d)

- Successful

 ![Successful](https://github.com/user-attachments/assets/24580e2b-dc33-427a-95eb-d7d8bae9f418)

### How to compile the firmware and flash the firmware
#### 1. Copy uboot-sd1-env.txt to path:
buildroot-external-microchip/board/microchip/sama5d27_som1_ek/
```
 # wget https://raw.githubusercontent.com/kamval/SAMA5D27-SOM1-EK1/master/3.%20headless%20SD1/uboot-env/uboot-sd1-env.txt
 # cp uboot-sd1-env.txt ../buildroot-external-microchip/board/microchip/sama5d27_som1_ek/
```
#### 2. Delete two files “at91bootstrap” “uboot”
```
cd git/som1_ek/buildroot-at91/output/build$
# rm -rf at91bootstrap3-v3.10.2/
# rm -rf uboot-linux4sam-2020.10.1/
```
#### 3. Modify the config value to SD1
```
# make menuconfig  
Modify the setting values ​​as follows:
→ Bootloaders ->   (sama5d27_som1_eksd1_uboot) Defconfig name
 
 
→ Bootloaders ->  (sama5d27_som1_ek_mmc1) Board defconfig 
 
→ Bootloaders
->  [*]   Environment image
 --->    ($(BR2_EXTERNAL_MCHP_PATH)/board/microchip/sama5d27_som1_ek/uboot-sd1-env.txt) Source files for environment
 --->    $(BR2_EXTERNAL_MCHP_PATH)/board/microchip/sama5d27_som1_ek/uboot-sd1-env.txt

```
#### 4. Compile bootloader 
```
git/som1_ek/buildroot-at91$ make
```
Burn the reprogrammed sdcard.img to microSD,and then put into SD1 and open it 
Can use: balenaEtcher( https://www.balena.io/etcher/ )

## Demo boot

![demo_boot](https://github.com/user-attachments/assets/d2ab7177-c76d-4719-82cf-0ede3251f43d)

### Update the firmware to flash memory
### Firmware flashing process 
#### 1. Used Sam-ba_3.5
Download path : https://ww1.microchip.com/downloads/en/DeviceDoc/sam-ba_3.5-win32.zip

#### 2. Buildroot
* Create a directory under git file 
```
git clone https://github.com/linux4sam/buildroot-at91.git
git clone https://github.com/linux4microchip/buildroot-external-microchip.git
```
* Go to the buildroot-at91 path
```
git checkout linux4sam-2022.10 -b buildroot-at91-linux4sam-2022.10
```
* Go to the buildroot-external-microchip path
```
git checkout linux4microchip-2022.10 -b buildroot-external-microchip-linux4microchip-2022.10
```
* Copy these two files under this path buildroot-external-microchip/
```
0000_buildroot_external_microchip_mx-linux4sam-2022.10.patch 
0000_buildroot_External_microchip_esmt-2022.10.patch

ivy@ubuntu:~/git/som1_emst/buildroot-external-microchip$ ls

![ls](https://github.com/user-attachments/assets/84ebc495-9a06-4f4c-b607-6121c7c86073)
```
* Enter two cmd:
```
git apply 0000_buildroot_external_microchip_mx-linux4sam-2022.10.patch
git apply 0000_buildroot_External_microchip_esmt-2022.10.patch
```
* Go back to the buildroot-at91 path
```
BR2_EXTERNAL=../buildroot-external-microchip make sama5d27_som1_ek_graphics_defconfig
```
* Compile bootloader 
```
ivy@ubuntu:~/git/som1_emst/buildroot-at91$ make
```
* Open the buildroot configuration file
```
vim sama5d27_som1_ek_graphics_defconfig
```
* Modify the following values, and if there are no following parameters, please add them manually
```
BR2_TARGET_ROOTFS_UBIFS_LEBSIZE=0x3E000
BR2_TARGET_ROOTFS_UBI_PEBSIZE=0x40000
BR2_TARGET_ROOTFS_UBIFS_MINIOSIZE=0x1000
```
* Go back to the buildroot-at91 path for the second compilation
```
ivy@ubuntu:~/git/som1_emst/buildroot-at91$ BR2_EXTERNAL=../buildroot-extern
al-microchip make samasd27_som1_ek_graphics_defconfig
```

* Compile bootloader again
  
#### 3. Image
* The file shown in the buildroot-at91/output/images path and place it under sam-ba_3.5:

 ![ls](https://github.com/user-attachments/assets/eae2041c-3894-40c5-9996-55b32b9bac96)

* Open cmd under sma-ba_3.5 and enter nand.bat to start burning
connect the purple short-circuit line and then connect USB1, execute program.bat

![start burning](https://github.com/user-attachments/assets/5bbc82a9-a1b5-4932-a1b5-777b83b96eed)

* After burning
```
sam-ba -p serial -d sama5d2 -a bootconfig -c writecfg:bscr:valid,bureg0 -c writecfg:bureg0:ext_mem_boot
```

* Press reset on the development version to boot successfully

 ![boot successfully](https://github.com/user-attachments/assets/95d4711d-64cd-45cb-b518-60cb41af8760)


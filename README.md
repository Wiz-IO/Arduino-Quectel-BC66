# Arduino for Quectel BC66 LTE Narow Band modules ( OpenCPU based )

**A few words in the beginning**
* This project not an official product of Quectel / Mediatek
* The project is based on Quectel OpenCPU and port must be work on all modules
* The full/exended port will make later, this will be start base
* License: Free for all
* This version: 1.0.0

**Chipset Mediatek MT2625 SoC**
Ultra-low power, 3GPP Release-14 enabled NB-IoT platform for wide-ranging home, civic, industrial or mobile applications
https://www.mediatek.com/products/nbIot/mt2625


**Module: Quectel BC66**
is a high-performance, multi-band NB-IoT module...
https://www.quectel.com/product/bc66.htm
* Test Board for the project: BC66-TE-B ( it is shield Arduino, unfortunately... )
* Module at board BC66NA... is obsolete, will replase BC66NB... and firmvare for NB
* Firmware & Drivers: http://URL
* API: OpenCPU, native C, EAT (Embedded AT) oriented
* User Application Size: ROM (BIN) 200k, RAM 100k

![ScreenShot](https://raw.githubusercontent.com/Wiz-IO/Arduino_MT2625_BC66/master/board.jpg)

**Tools**
* Arduino IDE (Windows for now)
https://www.arduino.cc/
* GCC Linaro - download last version
https://releases.linaro.org/components/toolchain/gcc-linaro/latest/
* Firmware, USB Drivers, Quectel IoT Flash Tool
http://URL

![ScreenShot](https://raw.githubusercontent.com/Wiz-IO/Arduino_MT2625_BC66/master/Arduino.jpg)

**INSTALL

(Later will make JSON install file)

* Download and istall latest GCC Linaro, Quectel Drivers and Module Flash Uploader
* Run Flash Uploader and update your module with OpenCPU firmware(URL)
* Copy folder wizio_bc66 to YOUR_INSTALED_PATH\Arduino\hardware\
* Move/Copy this files to GCC bin folder (this is Sourcery CodeBench files MAKE and RM):
    * from Arduino\hardware\wizio_bc66\1.0.0\system\cs-make.exe
    * from Arduino\hardware\wizio_bc66\1.0.0\system\cs-rm.exe
* Open file Arduino\hardware\wizio_bc66\1.0.0\board.txt and edit your GCC path: wizio_BC66.build.compiler_path=D:/Program/ARM/gcc-linaro-arm-eabi/bin/
* Start Arduino, select board, play, compile... app is APPGS3MDM32A01.bin
* Run Flash Uploader, select app_image_bin.cfg from Arduino Bulild Folder or from Arduino\hardware\wizio_bc66\1.0.0\system (this is copy) 



**If you want to help / support - contact me**

# Other - Comming soon...

# Arduino for Quectel BC66 LTE Narow Band modules 
 ... and [Quectel development platform for PlatformIO](https://github.com/Wiz-IO/platform-quectel) v 2.0.0
 (must be full Arduino compatible)

**A few words in the beginning**
* **Version 2.0.0** ... beta, not everything tested...
* This project not an official product of Quectel / Mediatek
* The project is based on Quectel OpenCPU and **reverse engineering**

![IMG](https://raw.githubusercontent.com/Wiz-IO/Arduino-Quectel-BC66/master/images/ARDUINO_BC66.png)

**Chipset Mediatek MT2625 SoC**
Ultra-low power, 3GPP Release-14 enabled NB-IoT platform for wide-ranging home, civic, industrial or mobile applications
https://www.mediatek.com/products/nbIot/mt2625


**Module: Quectel BC66**
is a high-performance, multi-band NB-IoT module...
https://www.quectel.com/product/bc66.htm
* Test Board for the project: BC66-TE-B ( it is shield Arduino, unfortunately... )
* API: OpenCPU, native C, EAT (Embedded AT) oriented
* User Application Size: ROM (BIN) 200k, RAM 100k
* you need firmware **BC66NBR01A04 or BC66NBR01A05**

![ScreenShot](https://raw.githubusercontent.com/Wiz-IO/Arduino_MT2625_BC66/master/board.jpg)

**Tools**
* Arduino IDE (Windows)
https://www.arduino.cc/
* Firmware, USB Drivers, Quectel IoT Flash Tool
https://app.box.com/s/3wrkh1yzn09yuyb5f8v5vllmlir0571s

![ScreenShot](https://raw.githubusercontent.com/Wiz-IO/Arduino-Quectel-BC66/master/images/arduino.png)

Video: Simple MQTT Example 
https://youtu.be/njaAHkIkIx0

**ATTENTION: Before start exeriments:**
* Update firmware version **BC66NBR01A04 or BC66NBR01A05**
* Make Backup of NVDM Fields (module "eeprom")
* IoT Flash Tool, [Backup] button, check-box "Backup", select file for backup (use IMEI as name), [Start] and keep the file
* Now you can start all and you can restore the module if need
* ATTENTION: if you upload application to module you lose standart AT command via uarts
* Restore AT interface: send "AT+EPORT=1,connl,0", then remove application 
* [SEE THIS](https://github.com/Wiz-IO/platform-quectel/wiki/Framework-OpenCPU#how-to-restore-at-command-interface)
* [Other examples](https://github.com/Wiz-IO/platformio-quectel-examples)


## Install

* Add json link to Arduino - Preferences 

http://wizio.eu/arduino/bc66/package_wizio.bc66_index.json

* Open Borad Manager, Find WizIO, Install OR Update (remove old versions)
* Select Board
* Select Firmware
* Click [Compile] or [Upload]

**Thanks to**

* Radu Igret ( Quectel )



>If you want to help / support:   
[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donate_SM.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=ESUP9LCZMZTD6)

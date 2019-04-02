# Arduino for Quectel BC66 LTE Narow Band modules 
 ... and [Quectel development platform for PlatformIO](https://github.com/Wiz-IO/platform-quectel) v 2.0.0
 (must be full Arduino compatible)

**A few words in the beginning**
* This project not an official product of Quectel / Mediatek
* The project is based on Quectel OpenCPU and port must be work on all NB modules
* Quectel modules BC66NA will not be supported, your module must be marked as BC66NB-
* Quectel BC26 should work ( with small modifications maybe, I do not have a module for experiments )
* The full/exended port will make later, this will be start base
* License: Free for all
* This compile version: 1.0.4
* Added Extended API


**Chipset Mediatek MT2625 SoC**
Ultra-low power, 3GPP Release-14 enabled NB-IoT platform for wide-ranging home, civic, industrial or mobile applications
https://www.mediatek.com/products/nbIot/mt2625


**Module: Quectel BC66**
is a high-performance, multi-band NB-IoT module...
https://www.quectel.com/product/bc66.htm
* Test Board for the project: BC66-TE-B ( it is shield Arduino, unfortunately... )
* Modules BC66NA... is obsolete, replace with BC66NB... and firmware for NB
* API: OpenCPU, native C, EAT (Embedded AT) oriented
* User Application Size: ROM (BIN) 200k, RAM 100k

![ScreenShot](https://raw.githubusercontent.com/Wiz-IO/Arduino_MT2625_BC66/master/board.jpg)

**Tools**
* Arduino IDE (Windows for now)
https://www.arduino.cc/
* Firmware, USB Drivers, Quectel IoT Flash Tool
https://app.box.com/s/3wrkh1yzn09yuyb5f8v5vllmlir0571s
* MQTT test monitor 
http://quectel.slimfitdesign.com/nb-iot/mqtt/
* Python Uploader(for Linux, MAC ...)
https://github.com/Wiz-IO/Mediatek-MT2625-Flash-Utility

![ScreenShot](https://raw.githubusercontent.com/Wiz-IO/Arduino-Quectel-BC66/master/images/arduino.png)

Video: Simple MQTT Example 
https://youtu.be/njaAHkIkIx0


MQTT Client example log
```
[DBG] READY
[DEV] Quectel EXTENDED API BC66NBR01A04
[DBG] CPU Frequency: 78000000 Hz
[ARDUINO] Begin
[DEV] MSG_ID_RIL_READY
[APP] MQTT Simple Example
[IMEI] 867997030026542
[BAND] AT+QBAND=1,3, rc = 0
[RIL] MSG_ID_URC_INDICATION: 2, 1
[RIL] MSG_ID_URC_INDICATION: 5, 2
[RIL] MSG_ID_URC_INDICATION: 5, 1
[APP] Narrow Band Level: -75,
[API] Connected
[API] MQTTConnect( 0 )
[API] MQTTPublish( 0 )
[API] MQTTDisconnect()
[API] Waithing...
```
result is there: http://quectel.slimfitdesign.com/nb-iot/mqtt/ 

**ATTENTION: Before start exeriments:**
* Update firmware version
* Make Backup of NVDM Fields (module "eeprom")
* IoT Flash Tool, [Backup] button, check-box "Backup", select file for backup (use IMEI as name), [Start] and keep the file
* Now you can start all and you can restore the module if need
* ATTENTION: if you upload application to module you lose standart AT command via uarts
* Restore AT interface: send "AT+EPORT=1,connl,0", then remove application 
* [SEE THIS](https://github.com/Wiz-IO/platform-quectel/wiki/Framework-OpenCPU#how-to-restore-at-command-interface)


## Install

* Add json link to Arduino - Preferences 

http://wizio.eu/arduino/bc66/package_wizio.bc66_index.json

* Open Borad Manager, Find WizIO, Install OR Update, Select board, Click [Compile] or [Upload]


**Thanks to**

* Radu Igret for terminal uploader


TODO:
* add SPI
* add I2S
* add all gpio-s
* debug and other stufs


Arduino + Extended API gives you tremendous opportunities for LTE Narrow Band

The extended API is dependent on firmware version.
The API support direct calls to the core as FreeRTOS, lvip, mbedtls, http, mqtt...etc.
API is selected as board model in Arduino Menu - Boards Manager.

Example: Quectel BC66NB-TE-B < R01A04V01 >

This api/board is dependent with firmware BC66NBR01A04V01 and module must be updated with this version.
API has soft protection of not correct versions.

Example: Simple MQTT, source from there, folder examples





>If you want to help / support:   
[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donate_SM.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=ESUP9LCZMZTD6)

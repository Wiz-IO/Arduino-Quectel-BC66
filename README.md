# Arduino for Quectel BC66 LTE Narow Band modules 
( OpenCPU based )

**A few words in the beginning**
* This project not an official product of Quectel / Mediatek
* The project is based on Quectel OpenCPU and port must be work on all NB modules
* Quectel modules BC66NA will not be supported, your module must be marked as BC66NB-
* The full/exended port will make later, this will be start base
* License: Free for all
* This version: 1.0.1


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

![ScreenShot](https://raw.githubusercontent.com/Wiz-IO/Arduino-Quectel-BC66/master/images/arduino.png)


**Install**

* Add json link to Arduino - Preferences (link is temporary, next will be)
http://46.233.13.100/arduino/bc66/package_wizio.bc66_0_index.json 
* Add json link to Arduino - Preferences 
http://wizio.eu//arduino/bc66/package_wizio.bc66_0_index.json
* Open Borad Manager, Find WizIO, Install, Select board, Click [Compile] or [Upload]

![ScreenShot](https://raw.githubusercontent.com/Wiz-IO/Arduino-Quectel-BC66/master/images/arduino_hardware.png)
![ScreenShot](https://raw.githubusercontent.com/Wiz-IO/Arduino-Quectel-BC66/master/images/gcc_bin.png)  
![ScreenShot](https://raw.githubusercontent.com/Wiz-IO/Arduino-Quectel-BC66/master/images/tool.png)

Thanks to: 
* Radu Igret for terminal uploader

TODO:
* add SPI
* add I2S
* add all gpio-s
* debug and other stufs


**If you want to help / support - contact me**

# Other - Comming soon....

# SSD1306_OLED_LIB
Adafruit GFX and SSD1306 Library updated for .9" OLED display


Follow below steps to setup OLED.

pre-requisites:
1) Download Arduino software from arduino.cc
2) You should have arduino UNO/ pro mini/ or any arduino compatable device.
3) some connecting wires

Configuring Arduino IDE:
------------------------

You need to add adafruif librarys (SSD1306 and GFX)
please download or clone this SSD1306_OLED_LIB to your PC.

and copy the belwo two foldes to <arduin installation path>/arduino/library/ folder
1) Adafruit_SSD1306-master
2) Adafruit-GFX-master


Thats it you are ready with required lib files.

How to upload basic OLED sketch to Arduino:
-------------------------------------------

Connect arduino to PC. 
Open "ssd1306_DIY_IOT.ino" from /arduino/library/Adafruit_SSD1306-master/examples and press compile and then click on upload button.

Thats all you are now done with software part.

Conecting OLED to Arduino:
--------------------------
Assuming you have Arduino UNO.

1) Connect VCC of OLED to 5V pin of arduino.
2) Connect GND of OLED to GND of arduino.
3) Connect SCL of OLED to SCl of arduino.
3) Connect SDA of OLED to SDA of arduino.

Thats all you are good with hw connections as well.

Now power up / press reset buttion. you should see adafruit logo & IOT logo.

Hurry you are done.

please check you tube for how to create image to bitmap file. and graphics creation, you will get more tutorials.
Happy learning....




Thanks,
Venugopal.
/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
//Q-IOT Logo made by image to LCD converter
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xf8,0x39,0x39,0xfc,0xe0,0x80,0xfe,0x19,0xce,0x1c,0x1f,0xff,0xff,0xf0,
0xff,0xff,0xf8,0x19,0x93,0xfc,0xc0,0x41,0xfe,0x59,0xcc,0xc,0xf,0xff,0xff,0xf0,
0xff,0xff,0xf9,0xc9,0x93,0xfc,0x9e,0x77,0xfe,0x79,0xc9,0xe4,0xcf,0xff,0xff,0xf0,
0xff,0xff,0xf9,0xc9,0xc7,0xfc,0x9e,0x77,0xfe,0x38,0x9,0xe4,0xcf,0xff,0xff,0xf0,
0xff,0xff,0xf9,0xc9,0xc7,0xfc,0x9e,0x77,0xff,0x8,0x9,0xe4,0x1f,0xff,0xff,0xf0,
0xff,0xff,0xf9,0xc9,0xcf,0xfc,0x9e,0x77,0xff,0xc9,0xc9,0xe4,0x7f,0xff,0xff,0xf0,
0xff,0xff,0xf9,0x89,0xcf,0xfc,0x8c,0x77,0xff,0xc9,0xc8,0xcc,0xff,0xff,0xff,0xf0,
0xff,0xff,0xf8,0x19,0xcf,0xfc,0xc0,0xf7,0xfc,0x19,0xcc,0xc,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xf3,0xff,0xff,0x7f,0xff,0x7f,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xfe,0x7,0xff,0xff,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xfe,0x7,0xff,0xff,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xe0,0xf,0xff,0xff,0xff,0xe0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0x0,0x1,0xff,0xff,0xff,0xe0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xfc,0x0,0x0,0x7f,0xff,0xff,0xe3,0xc7,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xf8,0x1f,0xf8,0x1f,0xff,0xff,0xe7,0xc7,0xff,0xff,0xff,0xfc,0x7,0xff,0xf0,
0xff,0xe0,0xff,0xfe,0xf,0xff,0xff,0xe7,0xc7,0xff,0xff,0xff,0xf8,0x3,0xff,0xf0,
0xff,0xc3,0xff,0xff,0x87,0xff,0xff,0xe3,0x87,0xff,0xff,0xff,0xf8,0x3,0xff,0xf0,
0xff,0xc7,0xe0,0xf,0xc3,0xff,0xff,0xe0,0xf,0xff,0xff,0xff,0xf9,0xe3,0xff,0xf0,
0xff,0x8f,0x80,0x3,0xe3,0xff,0xff,0xf0,0xf,0xff,0xff,0xff,0xf9,0xe3,0xff,0xf0,
0xff,0xf,0x1,0x1,0xe1,0xff,0xff,0xf8,0x3f,0xff,0xff,0xff,0xf9,0xe3,0xff,0xf0,
0xff,0x1e,0xf,0xe1,0xf1,0xff,0xff,0xf0,0x1f,0xfc,0x0,0x3f,0xc1,0xe0,0x1f,0xf0,
0xff,0x1e,0x1f,0xf8,0xf1,0xff,0xff,0xe0,0xf,0xf0,0x0,0xf,0x81,0xe0,0x1f,0xf0,
0xfe,0x3c,0x3f,0xf8,0xf8,0xff,0xff,0xe0,0xf,0xe0,0x7e,0x7,0x81,0xf0,0xf,0xf0,
0xfe,0x3c,0x7f,0xfc,0x78,0xff,0xff,0xe3,0x8f,0xc3,0xff,0xc3,0x8f,0xff,0x8f,0xf0,
0xfe,0x3c,0x7f,0xfc,0x78,0xff,0xff,0xe3,0x8f,0x87,0xff,0xe1,0x8f,0xff,0x8f,0xf0,
0xfe,0x7c,0x7f,0xfc,0x78,0xff,0xff,0xe3,0x8f,0xf,0x1,0xf0,0x83,0xf0,0xf,0xf0,
0xfe,0x7c,0x7f,0xfc,0x78,0xff,0xff,0xe3,0x8f,0x1e,0x0,0x78,0x1,0xe0,0xf,0xf0,
0xfc,0x78,0x7f,0xfc,0x78,0xff,0xff,0xe3,0x8e,0x3c,0x0,0x7c,0x41,0xe0,0x1f,0xf0,
0xfc,0x78,0xff,0xfc,0x78,0xff,0xff,0xe3,0x8e,0x3c,0x7e,0x3c,0x71,0xe3,0xff,0xf0,
0xfc,0x78,0xff,0xfc,0x78,0xe0,0x0,0xe3,0x8e,0x38,0x7e,0x3c,0x79,0xe3,0xff,0xf0,
0xfc,0x78,0xff,0xfc,0x78,0xc0,0x0,0x63,0x8e,0x78,0xff,0x3c,0x79,0xe3,0xff,0xf0,
0xfc,0x7c,0x7f,0xfc,0x78,0x80,0x0,0x63,0x8e,0x78,0xff,0x1e,0x79,0xe3,0xff,0xf0,
0xfe,0x7c,0x7f,0xfc,0x78,0x8f,0xfc,0x63,0x8c,0x78,0xff,0x1e,0x79,0xe3,0xff,0xf0,
0xfe,0x7c,0x7f,0xfc,0x78,0x8f,0xfc,0x63,0x8c,0x78,0xff,0x1e,0x39,0xe3,0xff,0xf0,
0xfe,0x3c,0x7f,0xfc,0x78,0xc0,0x0,0x63,0x8c,0x78,0xff,0x1e,0x79,0xe3,0xff,0xf0,
0xfe,0x3c,0x7f,0xf8,0xf8,0xc0,0x0,0x63,0x8c,0x78,0xff,0x1c,0x79,0xe3,0xff,0xf0,
0xfe,0x3c,0x3f,0xf8,0xf1,0xe0,0x0,0xe3,0x8e,0x78,0xff,0x3c,0x79,0xe3,0xff,0xf0,
0xfe,0x3e,0x3f,0xf1,0xf1,0xff,0xff,0xe3,0x8e,0x78,0xfe,0x3c,0x79,0xe3,0xff,0xf0,
0xff,0x1e,0x1f,0xe1,0xe1,0xff,0xff,0xe3,0x8e,0x3c,0x7e,0x3c,0x79,0xe3,0xff,0xf0,
0xff,0x1f,0x0,0x3,0xe3,0xff,0xff,0xe3,0x8e,0x3c,0x3c,0x78,0x79,0xe0,0x1f,0xf0,
0xff,0x8f,0x80,0x7,0xc3,0xff,0xff,0xe3,0x8f,0x3e,0x0,0x78,0xf9,0xf0,0xf,0xf0,
0xff,0x87,0xe0,0x1f,0x87,0xff,0xff,0xe3,0x8f,0x1f,0x1,0xf0,0xf8,0xf8,0xf,0xf0,
0xff,0xc3,0xff,0xff,0x83,0xff,0xff,0xe3,0x8f,0x8f,0xe7,0xe1,0xf8,0xff,0x8f,0xf0,
0xff,0xe1,0xff,0xff,0xc1,0xff,0xff,0xe3,0x8f,0x87,0xff,0xc3,0xfc,0x7f,0x8f,0xf0,
0xff,0xf0,0x3f,0xe1,0xe0,0x7f,0xff,0xe3,0x8f,0xc1,0xfe,0x7,0xfc,0x3f,0xf,0xf0,
0xff,0xf8,0x0,0x0,0xf8,0x1f,0xff,0xe0,0xf,0xe0,0x0,0xf,0xfe,0x0,0x1f,0xf0,
0xff,0xfe,0x0,0x0,0x7e,0x1f,0xff,0xf0,0xf,0xf8,0x0,0x3f,0xff,0x0,0x1f,0xf0,
0xff,0xff,0xe0,0x1c,0x3f,0x1f,0xff,0xff,0xff,0xff,0x1,0xff,0xff,0xe0,0xff,0xf0,
0xff,0xff,0xff,0xfe,0xf,0x8f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0x83,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xc0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xf0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xfc,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
};

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  // text display tests
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("DIY IOT SHOP!");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  //display.println(3.141592);
  display.setTextSize(1);
  display.setTextColor(WHITE); 
  display.println("");
  display.println("");
  display.println("");
  display.println("http://www.ebay.in/usr/diy_iot_shop");
  display.display();
  delay(4000);

  // miniature bitmap display
  display.clearDisplay();
  display.drawBitmap(0, 0,  logo16_glcd_bmp, 128, 816, 1);
  display.display();

  // draw a bitmap icon and 'animate' movement
  //testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
}


void loop() {
  
}


void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, WHITE);
    }
    display.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS],  logo16_glcd_bmp, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
	icons[f][XPOS] = random(display.width());
	icons[f][YPOS] = 0;
	icons[f][DELTAY] = random(5) + 1;
      }
    }
   }
}


void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }    
  display.display();
}

void testdrawcircle(void) {
  for (int16_t i=0; i<display.height(); i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
    display.display();
  }
}

void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<display.height()/2; i+=3) {
    // alternate colors
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
    display.display();
    color++;
  }
}

void testdrawtriangle(void) {
  for (int16_t i=0; i<min(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    display.display();
  }
}

void testfilltriangle(void) {
  uint8_t color = WHITE;
  for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
    display.fillTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
  }
}

void testdrawroundrect(void) {
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, WHITE);
    display.display();
  }
}

void testfillroundrect(void) {
  uint8_t color = WHITE;
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
  }
}
   
void testdrawrect(void) {
  for (int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
    display.display();
  }
}

void testdrawline() {  
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, WHITE);
    display.display();
  }
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, WHITE);
    display.display();
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, WHITE);
    display.display();
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
    display.display();
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
    display.display();
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
    display.display();
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, WHITE);
    display.display();
  }
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE); 
    display.display();
  }
  delay(250);
}

void testscrolltext(void) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("scroll");
  display.display();
 
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);    
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
}

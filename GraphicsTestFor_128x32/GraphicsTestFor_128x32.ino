/*

  GraphicsTest.ino

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


#define width 128
#define height 32
#define scale 8 

/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
*/
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void u8g2_box_frame(uint8_t a) {
  u8g2.drawStr( 0, 0, "drawBox");
  u8g2.drawBox(5,10,width/scale,height/2);
  u8g2.drawBox(10+4*a,15,30,15);
  u8g2.drawStr( 64, 0, "drawFrame");
  u8g2.drawFrame(64,10,width/scale,height/2);
  u8g2.drawFrame(64-4*a,15,30,15);
}

void u8g2_disc_circle(uint8_t a) {
  u8g2.drawStr( 0, 0, "drawDisc");
  u8g2.drawDisc(10,18,10);
  u8g2.drawDisc(10+4*a,20,7);
  u8g2.drawStr( 64, 0, "drawCircle");
  u8g2.drawCircle(74,18,10);
  u8g2.drawCircle(74-4*a,20,7);
}

void u8g2_r_frame(uint8_t a) {
  u8g2.drawStr( 0, 0, "drawRFrame/Box");
  u8g2.drawRFrame(5, 10,20,20, a+1);
  u8g2.drawRBox(69, 10,20,20, a+1);
}

void u8g2_string(uint8_t a) {
  u8g2.setFontDirection(0);
  u8g2.drawStr(20, 10, "Font Rotation");
  u8g2.drawStr(a,0, " 0");
  u8g2.setFontDirection(1);
  u8g2.drawStr(width,a, " 90");
  u8g2.setFontDirection(2);
  u8g2.drawStr(width-a,height, " 180");
  u8g2.setFontDirection(3);
  u8g2.drawStr(0,height-a, " 270");
}


//Fan-out effect
void u8g2_line(uint8_t a) {
  u8g2.drawStr( 0, 0, "drawLine");

  u8g2.drawLine(64, 8,  width/2-a, height);
  u8g2.drawLine(64, 8,  width/2-2*a, height);
  u8g2.drawLine(64, 8,  width/2-3*a, height);
  u8g2.drawLine(64, 8,  width/2-4*a, height);
  u8g2.drawLine(64, 8,  width/2-5*a, height);
  u8g2.drawLine(64, 8,  width/2-6*a, height);
  u8g2.drawLine(64, 8,  width/2-7*a, height);
  u8g2.drawLine(64, 8,  width/2-8*a, height);
  
  u8g2.drawLine(64, 8,  width/2+a, height);
  u8g2.drawLine(64, 8,  width/2+2*a, height);
  u8g2.drawLine(64, 8,  width/2+3*a, height);
  u8g2.drawLine(64, 8,  width/2+4*a, height);
  u8g2.drawLine(64, 8,  width/2+5*a, height);
  u8g2.drawLine(64, 8,  width/2+6*a, height);
  u8g2.drawLine(64, 8,  width/2+7*a, height);
  u8g2.drawLine(64, 8,  width/2+8*a, height);
  
  
 
}

void u8g2_triangle(uint8_t a) {
  uint16_t offset = a;
  u8g2.drawStr( 0, 0, "drawTriangle");
  u8g2.drawTriangle(64,8+2*a, width-2*a,2*a, width-2*a,height);
  u8g2.drawTriangle(0,8+4*a, width/2-2*a,4*a, width/2-4*a,height);

}

//This one was a bitch
void u8g2_ascii_1() {
  char s[2] = " ";
  uint8_t x, y;
  u8g2.setFontDirection(3);
  u8g2.drawStr( 0, height-1, "Page1");
  for( x = 0; x < 9; x++ ) {
    for( y = 0; y < 5; y++ ) {
      s[0] ++; 
      u8g2.drawStr( x*13 +10,height-1 - y*6, s);
    }
  }
}

void u8g2_ascii_2() {
  char s[2] = "M";
  uint8_t x, y;
  u8g2.setFontDirection(3);
  u8g2.drawStr( 0, height-1, "Page2");
  for( x = 0; x < 9; x++ ) {
    for( y = 0; y < 5; y++ ) {
      s[0]++; 
      u8g2.drawStr( x*13 +10,height-1 - y*6, s);
    }
  }
}

void u8g2_extra_page(uint8_t a)
{
  u8g2.drawStr( 0, 0, "Icons");
  u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.setFontPosTop();
  u8g2.drawUTF8(0, 10, "☀ ☁ ☃ ");
  switch(a) {
    case 0:
    case 1:
    u8g2.drawUTF8(64, 10, "☔");
      break;
    case 2:
    case 3:
      u8g2.drawUTF8(64, 10, "☂");
      break;
    case 4:
    case 5:
    u8g2.drawUTF8(64, 10, "☔");
      break;
    case 6:
    case 7:
      u8g2.drawUTF8(64, 10, "☂");
      break;
  }
}

#define cross_width 24
#define cross_height 24
static const unsigned char cross_bits[] U8X8_PROGMEM  = {
  0x00, 0x18, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x42, 0x00, 
  0x00, 0x42, 0x00, 0x00, 0x42, 0x00, 0x00, 0x81, 0x00, 0x00, 0x81, 0x00, 
  0xC0, 0x00, 0x03, 0x38, 0x3C, 0x1C, 0x06, 0x42, 0x60, 0x01, 0x42, 0x80, 
  0x01, 0x42, 0x80, 0x06, 0x42, 0x60, 0x38, 0x3C, 0x1C, 0xC0, 0x00, 0x03, 
  0x00, 0x81, 0x00, 0x00, 0x81, 0x00, 0x00, 0x42, 0x00, 0x00, 0x42, 0x00, 
  0x00, 0x42, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x18, 0x00, };

#define cross_fill_width 24
#define cross_fill_height 24
static const unsigned char cross_fill_bits[] U8X8_PROGMEM  = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x18, 0x64, 0x00, 0x26, 
  0x84, 0x00, 0x21, 0x08, 0x81, 0x10, 0x08, 0x42, 0x10, 0x10, 0x3C, 0x08, 
  0x20, 0x00, 0x04, 0x40, 0x00, 0x02, 0x80, 0x00, 0x01, 0x80, 0x18, 0x01, 
  0x80, 0x18, 0x01, 0x80, 0x00, 0x01, 0x40, 0x00, 0x02, 0x20, 0x00, 0x04, 
  0x10, 0x3C, 0x08, 0x08, 0x42, 0x10, 0x08, 0x81, 0x10, 0x84, 0x00, 0x21, 
  0x64, 0x00, 0x26, 0x18, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

#define cross_block_width 14
#define cross_block_height 14
static const unsigned char cross_block_bits[] U8X8_PROGMEM  = {
  0xFF, 0x3F, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 
  0xC1, 0x20, 0xC1, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 
  0x01, 0x20, 0xFF, 0x3F, };

void u8g2_bitmap_overlay(uint8_t a) {
  uint8_t frame_size = 28;

 

  
  u8g2.setBitmapMode(false /* solid */);
  u8g2.drawFrame(0, 0, frame_size, frame_size);
  u8g2.drawXBMP(2, 2, cross_width, cross_height, cross_bits);
  if(a & 4)
    u8g2.drawXBMP(7, 7, cross_block_width, cross_block_height, cross_block_bits);

  u8g2.setBitmapMode(true /* transparent*/);
  u8g2.drawFrame(frame_size + 5, 0, frame_size, frame_size);
  u8g2.drawXBMP(frame_size + 7, 2, cross_width, cross_height, cross_bits);
  if(a & 4)
    u8g2.drawXBMP(frame_size + 2, 7, cross_block_width, cross_block_height, cross_block_bits);
}

void u8g2_bitmap_modes(uint8_t transparent) {
  const uint8_t frame_size = 24;

  u8g2.drawBox(0, 0, frame_size * 5, frame_size);
  
  
  if(!transparent) {
    u8g2.setBitmapMode(false /* solid */);
   
  } else {
    u8g2.setBitmapMode(true /* transparent*/);
    
  }
  u8g2.setDrawColor(0);// Black
  u8g2.drawXBMP(frame_size * 0.5, 4, cross_width, cross_height, cross_bits);
  u8g2.setDrawColor(1); // White
  u8g2.drawXBMP(frame_size * 2, 4, cross_width, cross_height, cross_bits);
  u8g2.setDrawColor(2); // XOR
  u8g2.drawXBMP(frame_size * 3.5, 4, cross_width, cross_height, cross_bits);
}

uint8_t draw_state = 0;

void draw(void) {
  u8g2_prepare();
  switch(draw_state >> 3) {
    case 0: u8g2_box_frame(draw_state&7); break;
    case 1: u8g2_disc_circle(draw_state&7); break;
    case 2: u8g2_r_frame(draw_state&7); break;
    case 3: u8g2_string(draw_state&7); break;
    case 4: u8g2_line(draw_state&7); break;
    case 5: u8g2_triangle(draw_state&7); break;
    case 6: u8g2_ascii_1(); break;
    case 7: u8g2_ascii_2(); break;
    case 8: 
    case 9:
    case 10:
    case 11:
    u8g2_extra_page(draw_state&7); break;
    /*case 9: u8g2_bitmap_modes(0); break;
    case 10: u8g2_bitmap_modes(1); break;
    case 11: u8g2_bitmap_overlay(draw_state&7); break;*/
  }
}


void setup(void) {
  u8g2.begin();
}

void loop(void) {
  // picture loop  
  u8g2.clearBuffer();
  draw();
  u8g2.sendBuffer();
  
  // increase the state
  draw_state++;
  if ( draw_state >= 12*8 )
    draw_state = 0;

  // deley between each page
  delay(100);

}

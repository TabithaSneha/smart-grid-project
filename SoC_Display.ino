// C++ code
//
/*
  LiquidCrystal Library - Hello World

   Demonstrates the use of a 16x2 LCD display.
  The LiquidCrystal library works with all LCD
  displays that are compatible with the  Hitachi
  HD44780 driver. There are many of them out
  there, and you  can usually tell them by the
  16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
  * LCD RS pin to digital pin 12
  * LCD Enable pin to digital pin 11
  * LCD D4 pin to digital pin 5
  * LCD D5 pin to digital pin 4
  * LCD D6 pin to digital pin 3
  * LCD D7 pin to digital pin 2
  * LCD R/W pin to ground
  * LCD VSS pin to ground
  * LCD VCC pin to 5V
  * 10K resistor:
  * ends to +5V and ground
  * wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008  by David
  A. Mellis
  library modified 5 Jul 2009  by Limor Fried
  (http://www.ladyada.net)
  example added 9 Jul 2009  by Tom Igoe
  modified 22 Nov 2010  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystal
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

void setup() {
  lcd_1.begin(16, 2);  // Set up the number of columns and rows on the LCD.

  // Print a message to the LCD.
  lcd_1.print("Battery SoC(%)");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting
  // begins with 0):
  int adc = analogRead(A0);

  if (adc < 350) {
    adc = 0;
  }

  float C = 0.0;
  int sample = 1;
  float AvgC = 0.0;

  if(adc > 0){
    for (int i = 0; i < 1000; i++) {
      float voltage = adc * 5 / 1023.0; //V
      float current = voltage / 10 * 1500; //mA
      C += current;
      sample++;
      delay(1);
    }

    AvgC = C/sample; //mAh measured by averaging over 1 second
  }

  float SoC = (AvgC/750) * 100; //Assuming 9V battery has initial mAh as 750 mAh

  lcd_1.setCursor(0, 1);
  lcd_1.print(SoC);
  delay(100);
}

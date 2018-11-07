/*
 This sketch prints "Hello World!" to the LCD

  The circuit:
 * LCD RS pin to digital pin 10
 * LCD Enable pin to digital pin 9
 * LCD D4 pin to digital pin 8
 * LCD D5 pin to digital pin 7
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 5
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3) 
 * 
 * http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

 /*
  SD card datalogger

 This example shows how to log data from three analog sensors
 to an SD card using the SD library.

 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */
// define headers
#define PIN_V1 0
#define PIN_I1 1
#define PIN_I2 2
#define PIN_V2 3


// include the library code:
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>

const int chipSelect = 4;

int addr = 10;
int value;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(10, 9, 8, 7, 6, 5);

void setup() {

  pinMode(PIN_V1, INPUT_PULLUP);
  pinMode(PIN_I1, INPUT_PULLUP);
  pinMode(PIN_V2, INPUT_PULLUP);
  pinMode(PIN_I2, INPUT_PULLUP);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");

    // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    
  value = EEPROM.read(addr);
  if (value > 100)
    EEPROM.write(addr, 10);
    else 
      EEPROM.write(addr, value + 1);
  }

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");


  
}

void loop() {

  delay(500);

  // make a string for assembling the data to log:
  

  // read three sensors and append to the string:
//  for (int analogPin = 0; analogPin < 3; analogPin++) {
//    int sensor = analogRead(analogPin);
//    dataString += String(sensor);
//    if (analogPin < 2) {
//      dataString += ",";
//    }
//  }
  
  int V1 = analogRead(PIN_V1);
  int I1 = analogRead(PIN_I1);
  
  int V2 = analogRead(PIN_V2);
  int I2 = analogRead(PIN_I2);

  String dataString_line1 = "";
  String dataString_line2 = "";
  dataString_line1 += "V1:" + String(V1) + "   V2:" +  String(V2);
  dataString_line2 += "I1:" + String(I1) + "   I2:" +  String(I2);
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog2.txt", FILE_WRITE);

  String saveString = "V1;" + String(V1) + ";I1;" +  String(I1) + ";V2;" +  String(V2) + ";I2;" +  String(I2);
  
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(saveString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(saveString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }


  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  // print the number of seconds since reset:
  lcd.print(dataString_line1);

  lcd.setCursor(0, 1);
  lcd.print(dataString_line2);


  
}


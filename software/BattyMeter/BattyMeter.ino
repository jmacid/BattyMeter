// BattyMeter V1.01

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

#define zeroI1 508
#define zeroI2 508


// include the library code:
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>


const int chipSelect = 4;

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

  // Read the sensors
    
  int analogV1 = analogRead(PIN_V1);
  int analogI1 = analogRead(PIN_I1);
  
  int analogV2 = analogRead(PIN_V2);
  int analogI2 = analogRead(PIN_I2);

  // Convert the analog variables into physics variables

  String strV1 = String((float) analogV1*55/1024).substring(0,4);
  String strI1 = String((float) (analogI1 - zeroI1)/1024*60);

  if (analogI1 > zeroI1)
    strI1.substring(0,4);
    else strI1.substring(0,5);
  
  
  String strV2 = String((float) analogV2*55/1024).substring(0,4);
  String strI2 = String((float) (analogI2 - zeroI2)/1024*60);

  if (analogI2 > zeroI2)
    strI2.substring(0,4); 
  else strI2.substring(0,5);
  
  String dataString_line1 = "";
  String dataString_line2 = "";
  dataString_line1 += "V1:" + String(strV1) + " V2:" +  String(strV2);
  dataString_line2 += "I1:" + String(strI1) + " I2:" +  String(strI2);
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog2.txt", FILE_WRITE);

  String saveString = "V1;" + String(strV1) + ";I1;" +  String(strI1) + ";V2;" +  String(strV2) + ";I2;" +  String(strI2);
  
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(saveString);
    dataFile.close();
    // print to the serial port too:
    //Serial.println(saveString);
    Serial.println(strV1 + " ; " + String(analogV1));
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }


  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.clear(); // Clear the lcd screen also set the cursor in 0 0 
  lcd.print("V1:" + strV1);
  lcd.setCursor(8, 0);
  lcd.print("V2:" + strV2);

  // print the number of seconds since reset:

  lcd.setCursor(0, 1);
  lcd.print("I1:" + strI1);
  lcd.setCursor(8, 1);
  lcd.print("I2:" + strI2);



  
}


/*********************************************************************/

/*
 * Project: Tech Camp 2017 - Day Zero
 * Title: Tricorder
 * Author/s: Alan Ibbett
 *           Chris Richards
 * Date: 25 Sep 2017
 * Ver: 1.8
*/

/*********************************************************************/
/*
** GPS **
   using TinyGPS++ library by Mikal Hart
   This sample code demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial.
     GPS Serial -- 9600 baud
     
    Nano              GPS
    -----             ----
    Pin D6(rx)    -   TX
    Pin D5(tx)    -   RX
                  -   VCC
                  -   GND


** BME 280 Sensor **

    Nano              Sensor
    -----             ----
    Pin A4        -   SDA  
    Pin A5        -   SCL


** Dot Matrix Display **
  Using GFX and PCD8544 library.  Written by Limor Fried/Ladyada for Adafruit Industries. BSD license, check license.txt for more information.=
  These displays use SPI to communicate, 4 or 5 pins are required to interface.
  ###  Note: 10k Ohm Resistors on all Dot Matrix Display Signal Inputs

    Nano              Sensor
    -----             ----
    Pin D4        -   P8 LED 
    Pin D8        -   P7 SCLK   
    Pin D9        -   P6 DN(MOSI)
    Pin D10       -   P5 D/C  
    Pin D12       -   P4 RST   
    Pin D11       -   P3 SCE    
    GND           -   P2 GND  
    3V3           -   P1 VCC   


** Morse LED **

    Nano              
    -----             
    Pin D7


** I2C Expander **

    Nano              Sensor
    -----             ----
    Pin A4        -   SDA  
    Pin A5        -   SCL


** BackLight **

    Nano              Display
    -----             ----
    Pin D4        -   P8 LED

*********************************************************************/
// Variable Defines
uint8_t morseLED = 7;          // Pin D7 - used for morse code LED
uint8_t BackLightLED = 4;      // Pin D4 - used to supply vcc to Dot Matrix Backlight
bool BackLight = LOW;         // Backlight On/Off  --- HIGH = ON /  LOW = OFF


/*********************************************************************/
// Display Defines

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 8 - Serial clock out (SCLK)
// pin 9 - Serial data out (DIN)
// pin 10 - Data/Command select (D/C)
// pin 11 - LCD chip select (CS)
// pin 12 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);
#define xsize 84
#define ysize 48


/*********************************************************************/
// Keypad Defines
#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#define I2CADDR 0x38 //use for PCF8574

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// Digitran keypad, bit numbers of PCF8574 i/o port
byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad

Keypad_I2C kpd( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574 );


/***********************************************************************/
//BME280 Sensor

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C


/************************************************************************/
// GPS Module

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial gpsSerial (6, 5); // RX, TX
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;

int GPS_ERROR_FLAG = 0;


/************************************************************************/
/*       Menuing System variables    */

void (*menuItem)(); 

/************************************************************************/

void setup()   {

  pinMode(morseLED,OUTPUT);
  digitalWrite(morseLED,HIGH);
  pinMode(BackLightLED,OUTPUT);
  digitalWrite(BackLightLED,HIGH);
  Serial.begin(9600);
  display.begin();
  Wire.begin( );
  kpd.begin( makeKeymap(keys) );

  //Serial.println(TinyGPSPlus::libraryVersion());
  gpsSerial.begin(9600);

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(255);
  display.clearDisplay();   // clears the screen and buffer
  display.setRotation(2);

 
  bool status;
    
    // default settings
    drawMenuItem("Powering Up");
    delay(1500);

// Check Sensor    
    status = bme.begin();
    if (!status) {
        display.setTextSize(1);
        display.setTextColor(BLACK);
        display.setCursor(3,rowPixel(1));
        display.print("No Sensor");
        display.display();
        delay(2000);
       
    }
    else{
        display.setTextSize(1);
        display.setTextColor(BLACK);
        display.setCursor(3,rowPixel(1));
        display.print("Sensor    OK");
        display.display();
        delay(2000);
    }

// Check GPS
  // This ensures the gps is being "fed".
  unsigned long start = millis();
  do 
  {
    while (gpsSerial.available())
      gps.encode(gpsSerial.read());
  } while (millis() - start < 1000);
  
  // This check is to ensure that GPS is connected and data of some kind is being received.
  if (millis() > 5000 && gps.charsProcessed() < 10) {
        display.setTextSize(1);
        display.setTextColor(BLACK);
        display.setCursor(3,rowPixel(2));
        display.print("No GPS");
        display.display();
        delay(2000);
    }
    else{
        display.setTextSize(1);
        display.setTextColor(BLACK);
        display.setCursor(3,rowPixel(2));
        display.print("GPS       OK");
        display.display();
        delay(2000);
    }

  // Delay a little longer
    delay(500);
    
  menuItem = &mainMenu;
  menuItem();
  digitalWrite(morseLED,LOW);
  digitalWrite(BackLightLED,LOW);
  
}


/*********************************************************************/
// Main Program Loop
void loop() {

  char key = kpd.getKey();
  if (key){
    menuSelect(key);
  }
  
}




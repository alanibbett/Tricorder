/*********************************************************************
Day Zero V1.0 

*********************************************************************/

/**********************************************************************/
//Morse LED defines

uint8_t morseLED = 7;





/*********************************************************************/




// display defines

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

#include <TinyGPS++.h>

#include <SoftwareSerial.h>

SoftwareSerial gpsSerial (6, 7); // RX, TX

TinyGPSPlus gps;

/************************************************************************/
/*       Menuing System variables    */

void (*menuItem)(); 





/************************************************************************/


/*
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

*/

/***************************************************************************/
#define backLight 4
uint8_t brightness = 160;


void setup()   {

  pinMode(morseLED,OUTPUT);
  digitalWrite(morseLED,HIGH);
  pinMode(backLight,OUTPUT);
  digitalWrite(backLight,HIGH);
  
  Serial.begin(9600);
  display.begin();
  Wire.begin( );
  kpd.begin( makeKeymap(keys) );
  
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(2);
  display.clearDisplay();   // clears the screen and buffer
  display.setRotation(2);

 
  bool status;
    
    // default settings
drawMenuItem("Powering Up");
    status = bme.begin();
    if (!status) {
        display.setTextSize(1);
        display.setTextColor(BLACK);
        display.setCursor(5,rowPixel(1));
        display.print("No Sensor");
        display.display();
        delay(1000);
       
    }
    else{
        display.setTextSize(1);
        display.setTextColor(BLACK);
        display.setCursor(3,rowPixel(1));
        display.print("BME Sensor OK");
        display.display();
        delay(1000);
    }
    //Serial.println(TinyGPSPlus::libraryVersion());
    gpsSerial.begin(9600);
 

menuItem = &mainMenu;
menuItem();
digitalWrite(morseLED,LOW);
digitalWrite(backLight,LOW); 

}


void loop() {

  char key = kpd.getKey();
  if (key){
    menuSelect(key);
  }
  
}



/*********************************************************************
Day Zero V1.0 

*********************************************************************/



// this file contains the functions to implemt a simple menuing system

/* the check button function gets called in the main look and based on the value a menu item is identified.
 *  
 *  
 *  
 */


 void menuSelect( char keyPressed ){


 
  
  switch (keyPressed) {
    case 'A':
      menuItem = &mainMenu;

      break;
    case 'B':
      menuItem = &sensorMenu;

      break;
    case 'C':
      menuItem = &gpsMenu;
 
      break;
    case 'D':
      menuItem = &morseMenu;
      break;
      
    case '1':
      doBackLight();
      break;

       
    default:
      return;
      break;

     
    }

   menuItem();
 }



void doBackLight()
{

    digitalWrite(backLight,!digitalRead(backLight));
}





void mainMenu(){
drawMenuItem("DayZero");
display.setTextSize(1);
display.setTextColor(BLACK,WHITE);

display.setCursor(2,rowPixel(1));
display.print(F("A   - Main"));
display.setCursor(2,rowPixel(2));
display.print(F("B   - Sensors"));
display.setCursor(2,rowPixel(3));
display.print(F("C   - GPS"));
display.setCursor(2,rowPixel(4));
display.print(F("D   - Morse"));

display.display();




char key = kpd.getKey();
  if (key){
    menuSelect(key);
  }
}

void gpsMenu(){
drawMenuItem("GPS");
display.setTextSize(1);
display.setTextColor(BLACK,WHITE);


while (1){
   // This sketch displays information every time a new sentence is correctly encoded.
    while (gpsSerial.available() > 0)
        if (gps.encode(gpsSerial.read()))

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    display.setCursor(2,rowPixel(1));
    display.print(F("No GPS "));
    //while(true);
  }
  
display.setCursor(2,rowPixel(1));
display.print(F("Lat:"));
display.setCursor(1,rowPixel(2));

  if (gps.location.isValid())
  {
    display.print(gps.location.lat(), 6);
    digitalWrite(morseLED,HIGH);
  }
  else
  {
    display.print(F("INVALID"));
    digitalWrite(morseLED,LOW);
  }


display.setCursor(2,rowPixel(3));
display.print(F("Long:"));
display.setCursor(2,rowPixel(4));

  if (gps.location.isValid())
  {
    display.print(gps.location.lng(), 6);
  }
  else
  {
    display.print(F("INVALID"));
  }
  
display.display();


 char key = kpd.getKey();
if (key == 'A' || key == 'B' || key == 'C' || key == 'D'){menuSelect(key);break;}

 }//while loop
}


void sensorMenu(){
drawSensors();
  char key = kpd.getKey();
  if (key){
    menuSelect(key);
  }
}

void morseMenu(){
drawMenuItem("Morse");
display.setTextSize(1);
display.setTextColor(BLACK,WHITE);
display.setCursor(2,rowPixel(1));
display.print(F("*   - Led On"));
display.setCursor(2,rowPixel(2));
display.print(F("#   - Led Off"));
display.setCursor(2,rowPixel(3));
display.print(F("0   - Flash"));
display.display();

while (1) {


    
  char key = kpd.getKey();
  if (key){
    if (key == '*') { digitalWrite (morseLED,HIGH);}
    else if (key == '#') { digitalWrite (morseLED,LOW);}
    else if (key == '0') {
      while (kpd.keyDown('0')){
        kpd.getKey();
        digitalWrite(morseLED,HIGH);
      }
      digitalWrite(morseLED,LOW);
    }
    else { menuSelect(key); return;}
    }//key


  } // while
}//morse function


void drawSensors(){
drawMenuItem("Sensors");
const uint8_t col1 = 34;

display.drawRect(0,0,xsize-1,ysize-1,BLACK); // outside box
display.drawRect(0,0,xsize-1,9,BLACK); // top box
display.drawRect(0,8,col1,ysize-2,BLACK); //left box
display.setTextSize(1);
display.setTextColor(BLACK,WHITE);


while (1) {
display.setCursor(2,rowPixel(1));
display.print(F("Temp"));
display.setCursor(col1 + 2,rowPixel(1));
display.print(bme.readTemperature(),1);

display.setCursor(3,rowPixel(2));
display.print(F("Pres"));
display.setCursor(col1 + 2,rowPixel(2));
display.print(bme.readPressure()/100,1);

display.setCursor(3,rowPixel(3));
display.print(F("Hum"));
display.setCursor(col1 + 2,rowPixel(3));
display.print(bme.readHumidity(),1);
display.display();

char key = kpd.getKey();
if (key == 'A' || key == 'B' || key == 'C' || key == 'D'){menuSelect(key);break;}



} //while loop
  
}












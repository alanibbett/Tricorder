/*********************************************************************/

/*
 * Project: Tech Camp 2017 - Day Zero
 * Title: Tricorder
 * Author/s: Alan Ibbett
 *           Chris Richards

*/

/*********************************************************************/

//  this file contains the functions to implement a simple menu system

/* the check button function gets called in the main loop and based on the value a menu item is identified.
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
      menuItem = &toggleBackLight;   
 
      break;
    default:
      return;
      break;  
   }

   menuItem();
 }


void toggleBackLight(){
  BackLight = !BackLight;
  digitalWrite(BackLightLED,BackLight);       
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


/*********************************************************************/

/*
 * Project: Tech Camp 2017 - Day Zero
 * Title: Tricorder
 * Author/s: Alan Ibbett
 *           Chris Richards

*/

/*********************************************************************/
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
  display.setCursor(2,rowPixel(4));
  display.print(F("5   - S.O.S"));
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
      else if (key == '5') {
        // "S"
        morseDotDash("dot",1);
        morseDotDash("dot",1);
        morseDotDash("dot",3);

        // "O"
        morseDotDash("dash",1);
        morseDotDash("dash",1);
        morseDotDash("dash",3);

        // "S"
        morseDotDash("dot",1);
        morseDotDash("dot",1);
        morseDotDash("dot",7);
      
    }
    else { menuSelect(key); return;}
    }//key
    
  } // while
  
}//morse function

// Control morse code dot or dash output including duration timing
void morseDotDash(String ddtype,int duration){
  int durUnit = 300;
  digitalWrite (morseLED,HIGH);
  if (ddtype == "dot") {delay(durUnit);}                 // unit of duration for dot = 1
  else if (ddtype == "dash") {delay(durUnit * 3);}       // unit of duration for dash = 3  
  digitalWrite (morseLED,LOW);
  delay(duration*durUnit);                // timing duration within the same letter, after a letter or after a word   
}

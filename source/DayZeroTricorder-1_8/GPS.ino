/*********************************************************************/

/*
 * Project: Tech Camp 2017 - Day Zero
 * Title: Tricorder
 * Author/s: Alan Ibbett
 *           Chris Richards

*/

/*********************************************************************/

void gpsMenu(){
  drawMenuItem("GPS Sig:     ");  // Extra spaces to push title left to make room for Signal Status text
  display.setTextSize(1);
  display.setTextColor(BLACK,WHITE);

  while (1){
    unsigned long start = millis();
    do 
    {
      while (gpsSerial.available())
        gps.encode(gpsSerial.read());
    } while (millis() - start < 250);


// GPS Data Check - check if Lat & Long data is valid and if GPS age data is older than 3 seconds     
    if (gps.location.lat()==0 || gps.location.lng()==0 || gps.location.age() > 3000) {
      GPS_ERROR_FLAG = 1;
    }
    else {
      GPS_ERROR_FLAG = 0;
    }
  
    display.setCursor(2,rowPixel(1));
    display.print(F("Lat:"));
    display.setCursor(1,rowPixel(2));


    if (GPS_ERROR_FLAG == 0)
    {
      display.print(gps.location.lat(), 6);
      display.setCursor(58,rowPixel(0));
      display.print(F("Good"));
      display.drawRect(0,0,xsize-1,9,BLACK);
    }
    else
    {
      display.print(F("--          "));
      display.setCursor(58,rowPixel(0));
      display.print(F("    "));
      display.setCursor(58,rowPixel(0));
      display.print(F("Bad "));
      display.drawRect(0,0,xsize-1,9,BLACK);
    }

    display.setCursor(2,rowPixel(3));
    display.print(F("Long:"));
    display.setCursor(2,rowPixel(4));

    if (GPS_ERROR_FLAG == 0)
    {
      display.print(gps.location.lng(), 6);
    }
    else
    {
      display.print(F("--          "));
    }
  
    display.display();


    char key = kpd.getKey();
    if (key == 'A' || key == 'B' || key == 'C' || key == 'D'){menuSelect(key);break;}

  }//while loop
}

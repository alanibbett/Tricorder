/*********************************************************************/

/*
 * Project: Tech Camp 2017 - Day Zero
 * Title: Tricorder
 * Author/s: Alan Ibbett
 *           Chris Richards

*/

/*********************************************************************/

void sensorMenu(){
  drawSensors();
  char key = kpd.getKey();
  if (key){
    menuSelect(key);
  }
}

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

/*
    display.setCursor(3,rowPixel(4));
    display.print(F("Alt"));
    display.setCursor(col1 + 2,rowPixel(4));
    display.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
*/

    display.display();

    char key = kpd.getKey();
    if (key == 'A' || key == 'B' || key == 'C' || key == 'D'){menuSelect(key);break;}

  } //while loop
  
}

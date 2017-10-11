/*********************************************************************/

/*
 * Project: Tech Camp 2017 - Day Zero
 * Title: Tricorder
 * Author/s: Alan Ibbett
 *           Chris Richards

*/

/*********************************************************************/

void drawBackBox() {
  display.clearDisplay();   // clears the screen and buffer
  display.drawRect(0,0,xsize-1,ysize-1,BLACK);
  display.drawRect(0,0,xsize-1,9,BLACK);  
}

void drawMenuItem(char * title){
  drawBackBox();
  uint8_t titleLength = strlen(title) * 6; // width of title in pixels font is 5 + 1 for between characters
  uint8_t screenLength = xsize-2; // take 2 pixels off for the border
  uint8_t startX = (screenLength-titleLength)/2 + 2;
 
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(startX,rowPixel(0));
  display.println(title);
  display.display();
}


uint8_t rowPixel(uint8_t row){
  const uint8_t rowHeight = 10;
  return (row*9) + 1; 
}




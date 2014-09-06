int lcdPrintScroller(uint8_t col, uint8_t row, uint8_t dispLength, const char *str)
{
  static uint8_t counter;
  uint8_t strLength = 0;

  while(*(str+strLength)) // get the length of the string
    strLength++;

  lcd.setCursor(col,row); // got to start position on screen/display

  for (uint8_t i=0; i<=dispLength; i++) // print the characters of str for the amount of dispLength
  {
    uint8_t offset = counter+i;
    
    if (counter+i >= strLength)         // if the offset rolls over the length of the string then roll over to the beginning
      offset = (counter + i) - (strLength);
    
    lcd.print(str[offset]);
  }
  
  counter++;
  if (counter >= strLength) { counter = 0; }
}

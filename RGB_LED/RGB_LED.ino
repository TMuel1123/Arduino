
/*
  Cycle trough the colors of an RGB LED
  
  TMuel1123 @ Google+  
*/

const int bluePin  = 9;
const int greenPin = 10;
const int redPin   = 11;

enum eColorSteps
{
	eColor_Start,
	eColor_Cyan,
	eColor_Green,
	eColor_Yellow,
	eColor_Red,
	eColor_Purple,
	eColor_Blue
} eColorStep;

unsigned char BLUE  = 0;
unsigned char GREEN = 0;
unsigned char RED   = 0;

void setup()
{
  pinMode(bluePin,  OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin,   OUTPUT);
}

void loop()
{
  // Cycle through all colors with min (0) and max (255) brightness for each color and with 64 steps from 0 to 255
  fColorCycle(0,255,64);

  // Update the analog putputs with the new RGB values  
  analogWrite(bluePin,  BLUE);
  analogWrite(greenPin, GREEN);
  analogWrite(redPin,   RED);

  delay(20); // Wait 20ms till next step
}

void fColorCycle (unsigned char bytMinBrightnes, unsigned char bytMaxBrightnes, unsigned char bytSteps)
{
  unsigned char bytBrightnesWidth = (bytMaxBrightnes - bytMinBrightnes);
  unsigned char bytStepWidth = (((((unsigned int)bytBrightnesWidth) << 3) / bytSteps) + 1) >> 3;

  if (bytBrightnesWidth < bytSteps) { bytSteps = bytBrightnesWidth; }

  if (bytStepWidth == 0) { return; }

  switch (eColorStep)
  {
    case eColor_Start:
      if (BLUE < (bytMaxBrightnes - bytStepWidth)) { BLUE += bytStepWidth; }
      else { BLUE = bytMaxBrightnes; eColorStep = eColor_Cyan; }
    break;
  
    case eColor_Cyan:
      if (GREEN < (bytMaxBrightnes - bytStepWidth)) { GREEN += bytStepWidth; }
      else { GREEN = bytMaxBrightnes; eColorStep = eColor_Green; }
    break;
  
    case eColor_Green:
      if (BLUE > (bytMinBrightnes + bytStepWidth)) { BLUE -= bytStepWidth; }
      else { BLUE = bytMinBrightnes; eColorStep = eColor_Yellow; }
    break;
  
    case eColor_Yellow:
      if (RED < (bytMaxBrightnes - bytStepWidth)) { RED += bytStepWidth; }
      else { RED = bytMaxBrightnes; eColorStep = eColor_Red; }
    break;
  
    case eColor_Red:
      if (GREEN > (bytMinBrightnes + bytStepWidth)) { GREEN -= bytStepWidth; }
      else { GREEN = bytMinBrightnes; eColorStep = eColor_Purple; }
    break;
  
    case eColor_Purple:
      if (BLUE < (bytMaxBrightnes - bytStepWidth)) { BLUE += bytStepWidth; }
      else { BLUE = bytMaxBrightnes; eColorStep = eColor_Blue; }
    break;
  
    case eColor_Blue:
      if (RED > (bytMinBrightnes + bytStepWidth)) { RED -= bytStepWidth; }
      else { RED = bytMinBrightnes; eColorStep = eColor_Cyan; }
    break;
  }
}

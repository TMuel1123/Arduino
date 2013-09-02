// Do not use vallues above 255
#define SAMPLECOUNT 255

byte startButton =  7; // Pull Pin 7 to GND to start conversion
byte sampleLED   = 13; // LED is on while the waveform is sampled
byte printLED    = 11; // Optional LED; Is on as long as the data is written to the serial output
byte sampleInput = A0; // Analog input 

byte analogValues[SAMPLECOUNT];  // Array to store the analog values
unsigned long time[SAMPLECOUNT]; // Array to store the time stamp
unsigned long startTime = 0;     // Variable to hold the start time of the conversions
unsigned long endTime = 0;       // Variable to hold the end time of the conversions


void setup()
{
  pinMode(sampleInput, INPUT);
  pinMode(startButton, INPUT_PULLUP);
  pinMode(printLED,    OUTPUT);
  pinMode(sampleLED,   OUTPUT);

  Serial.begin(57600);
}

void loop()
{
  delay(300);
  
  Serial.println("");
  
  while(digitalRead(startButton)); // Wait here for button press
  
  recordWave();
  printResult();
  typeResult(); // Comment this line out if you not use a Arduino Leonardo
}

void recordWave()
{
  startTime = micros();
  digitalWrite(sampleLED, 1);

  // Store the values in the RAM
  for (byte i=0; i<SAMPLECOUNT; i++)
  {
    analogValues[i] = (analogRead(A0)>>2);
    time[i] = micros();
//  Serial.println(analogRead(A0)>>2);
  }
  digitalWrite(sampleLED, 0);
  endTime = micros();
}

void printResult()
{
  digitalWrite(printLED, 1);
  Serial.print("Start time: ");
  Serial.print(startTime);
  Serial.println("uS");

  Serial.println("0\t0");
  // Write the values from RAM to serial out
  for (byte i=0; i<SAMPLECOUNT; i++)
  {
    Serial.print(time[i] - startTime);
    Serial.print("\t");
    Serial.print(analogValues[i]);
    Serial.println("\t");
  }
  Serial.print(time[SAMPLECOUNT-1] - startTime);
  Serial.println("\t255");

  Serial.print("End time: ");
  Serial.print(endTime);
  Serial.println("uS");
  digitalWrite(printLED, 0);
}

// Comment everything below this line if an Arduino Leonardo is not used

void typeResult()
{
  int temp = 0;

  Keyboard.begin();
  delay(300);
  
  // Jump to the beginning of the file
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_HOME);
  Keyboard.releaseAll();
  
  Keyboard.print(0);
  Keyboard.print("\t");
  Keyboard.print(0);
  Keyboard.println("\t");

  for (byte i=0; i<SAMPLECOUNT; i++)
  {
    Keyboard.print(time[i] - startTime);
    Keyboard.print("\t");

    Keyboard.print(analogValues[i]);
    Keyboard.println("\t");
  }

  Keyboard.print(time[SAMPLECOUNT-1] - startTime);
  Keyboard.print("\t");
  Keyboard.print(255);
  Keyboard.println("\t");
    
  // Jump to the beginning of the file
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_HOME);
  Keyboard.releaseAll();

  Keyboard.end();
}



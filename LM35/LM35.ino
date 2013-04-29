
void setup()
{
  analogReference(INTERNAL);
  Serial.begin(19200);
}
void loop()
{
  float fTemp = mapFloat(analogRead(A0), 0, 1023, 0, 110);

  Serial.print("Temperature: ");
  Serial.print(fTemp);
  Serial.println(" C");
  delay(1000);
}

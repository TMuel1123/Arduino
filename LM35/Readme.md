You may will find the function call mapFloat()

I added it to the standart libs of the Arduino by adding the following lines to WMath.cpp in the core folder

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

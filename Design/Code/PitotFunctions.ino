int readWindSpeed()
{
    outputVoltage = (analogRead(PITOT)-528)*ANLCONV;
//  Serial.println(analogRead(0));
//  Serial.print("Output voltage: ");
//  Serial.println(outputVoltage);
  double diff_pressure = outputVoltage*1000;
//  Serial.print("Differential pressure: ");
//  Serial.println(diff_pressure);
  return sqrt(2*(diff_pressure)/AIRDENS);
}

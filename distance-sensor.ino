
void setupDistanceSensor()
{
  Serial.println("Setup Distance Sesnor: Begin");
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  Serial.println("Setup Distance Sesnor: Complete");
}

long getDistance()
{
  long duration, distanceCm;

  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN,HIGH);

  // convert the time into a distance
  distanceCm = duration / 29.1 / 2 ;

  if (distanceCm > 0){
    Serial.print(distanceCm);
    Serial.print("cm");
    Serial.println();
  }
  else {
    Serial.println("Out of range");
    distanceCm = -1;
  }
  delay(1000);

  return distanceCm;
}



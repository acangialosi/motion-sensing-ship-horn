// These are the pins for the Distance sensor
const int ECHO_PIN = D6;
const int TRIG_PIN = D5;

// This is the pin for the Button
const int BUTTON_PIN = D2;

// These are the pins for the confrmation light
const int LED1_PIN = D0;
const int LED2_PIN = D7;

void setup()
{
  Serial.begin(9600);

  setupConfirmationLight();

  setupDistanceSensor();

  setupButton();
}

void loop()
{
  long distance = -1;
  bool buttonPressed = false;

  distance = getDistance();
  buttonPressed = getButtonState();

  if((distance > 25 && distance < 75) || buttonPressed)
  {
    Serial.println("In Range; play horn");
    playBoatHorn();
  }
}

void StopAllExecution()
{
      while (true);  // Loop forever. Don't do anything more
}

void setupConfirmationLight()
{
  // initialize the confirmation light
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}
void playBoatHorn()
{
  Serial.println(F("Started playing horn"));
  flashConfirmationLight(3);
  Serial.println("Done playing horn");
}
void flashConfirmationLight(int n)
{
  Serial.printlnf("Started flashing confirmation light %d time(s)", n);
  for(int i=0; i<n; i++)
  {
    // To blink the LED, first we'll turn it on...
    //digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);

    // We'll leave it on for 100 ms...
    delay(100);

    // Then we'll turn it off...
    //digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);

  }
}

void setupButton()
{
  Serial.println("Setup Button: Begin");

  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT);

  Serial.println("Setup Button: Complete");
}

bool getButtonState()
{
  bool buttonState = false;

  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON_PIN);

  Serial.print("Button state: ");
  Serial.println(buttonState);

  if (buttonState)
  {
    flashConfirmationLight(2);
  }
  return buttonState;
}

void setupDistanceSensor()
{
  Serial.println("Setup Distance Sesnor: Begin");
  pinMode(TRIG_PIN, OUTPUT);
  //digitalWriteFast(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  delay(50);
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

    flashConfirmationLight(1);
  }
  else {
    Serial.println("Out of range");
    distanceCm = -1;
  }
  delay(100);

  return distanceCm;
}

void getDistancev2(uint32_t wait, bool info)
{
    uint32_t duration, inches, cm;

    /* Trigger the sensor by sending a HIGH pulse of 10 or more microseconds */
    digitalWriteFast(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWriteFast(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);

    inches = duration / 74 / 2;
    cm = duration / 29 / 2;


    Serial.printlnf("%6d in / %6d cm / %6d us", inches, cm, duration);

    delay(wait); // slow down the output
}

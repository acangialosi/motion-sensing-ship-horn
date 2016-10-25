
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
  return buttonState;
}

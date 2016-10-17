// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// These are the pins used for the breakout example
#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

// These are the pins for the Distance sensor
const int ECHO_PIN = A1;
const int TRIG_PIN = A2;

// This is the pin for the Button
const int BUTTON_PIN = 2;

Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

void setup() 
{
  Serial.begin(9600);
  
  setupMusicPlayer();

  setupDistanceSensor();

  setupButton();
}

void loop() 
{  
  long distance = -1;
  bool buttonPressed = false;
  
  distance = getDistance(); 
  buttonPressed = getButtonState();
  
  if((distance > 10 && distance < 50) || buttonPressed)
  {
    Serial.println("In Range; play horn");
    playBoatHorn();
  }
}

void StopAllExecution()
{
      while (true);  // Loop forever. Don't do anything more
}

void setupMusicPlayer()
{
  Serial.println("Setup Music Player: Begin");
  Serial.println("Adafruit VS1053 Library Test");

  // initialise the music player
  if (! musicPlayer.begin()) { // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    StopAllExecution();
  }
  Serial.println(F("VS1053 found"));

  musicPlayer.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working
 
  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    StopAllExecution();
}
  Serial.println("SD OK!");
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(10,10);

  if (! musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT))
  {
    Serial.println(F("DREQ pin is not an interrupt pin"));
  }

  Serial.println("Setup Music Player: Complete");
}

void setupDistanceSensor()
{
  Serial.println("Setup Distance Sesnor: Begin");
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  Serial.println("Setup Distance Sesnor: Complete");
}

void setupButton()
{
  Serial.println("Setup Button: Begin");

  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT);

  Serial.println("Setup Button: Complete");
}

void playBoatHorn()
{
  Serial.println(F("Started playing"));

  musicPlayer.playFullFile("track001.mp3");

  Serial.println("Done playing music");
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

bool getButtonState()
{
  bool buttonState = false;
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON_PIN);

  Serial.print("Button state: ");
  Serial.println(buttonState);
  return buttonState;
}


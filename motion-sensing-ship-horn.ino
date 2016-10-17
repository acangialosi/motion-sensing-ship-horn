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
  
  if((distance > 10 && distance < 100) || buttonPressed)
  {
    Serial.println("In Range; play horn");
    playBoatHorn();
  }
}

void StopAllExecution()
{
      while (true);  // Loop forever. Don't do anything more
}

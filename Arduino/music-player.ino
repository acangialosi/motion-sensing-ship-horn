
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


void playBoatHorn()
{
  Serial.println(F("Started playing"));

  musicPlayer.playFullFile("track001.mp3");

  Serial.println("Done playing music");
}

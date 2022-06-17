#include <Arduino.h>
#include <stdint.h>

#include "HID-Project.h"
#include "HID-Settings.h"
#include <math.h>
#include <Encoder.h>
#include <PinButton.h> // Double/single/long press
#define ENCODER_USE_INTERRUPTS
#define ENCODER_OPTIMIZE_INTERRUPTS
const int PRESS_TIME = 15;
const int NUM_SLIDERS = 3;
int analogSliderValues[NUM_SLIDERS];
int Gaming, Music;
//Encoder
Encoder knobGaming(3, 4);
Encoder knobMusic(6, 7);
//Encoder button
PinButton encoder_button0(9);
PinButton encoder_button1(2);

void setup() {
  Serial.begin(9600);
  Consumer.begin();
  Keyboard.begin();
  analogSliderValues[1] = 512;
  knobGaming.write(102);
  analogSliderValues[2] = 512;
  knobMusic.write(102);
  delay(1000);
}

void sendSliderValues() {
    String builtString = String("");
    for (int i = 0; i < NUM_SLIDERS; i++) {
      builtString += String((int)analogSliderValues[i]);
      if (i < NUM_SLIDERS - 1) {
        builtString += String("|");
      }
    }
    Serial.println(builtString);
}

void printSliderValues(){
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());
    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    }else{
      Serial.write("\n");
    }
  }
}

void checkEncoders(){
  //GAMING
  //Emulate an axis
  if (Gaming > 0 && Gaming < 208){
    analogSliderValues[1]=Gaming*5;   
  }
  //Lock if it's too high
  else if (Gaming >= 208){
    analogSliderValues[1]=1024;
    knobGaming.write(208);
  //Lock if it's too low 
  }else{
    analogSliderValues[1]=0;
    knobGaming.write(0);
  }
  //MUSIC
  //Emulate an axis
  if (Music > 0 && Music < 208){
    analogSliderValues[2]= Music*5;
  }
  //Lock if it's too high
  else if (Music >= 208){
    analogSliderValues[2]=1024;
    knobMusic.write(208);
  //Lock if it's too low 
  }else{
    analogSliderValues[2]=0;
    knobMusic.write(0);
  }
}

void checkButtons(){
  unsigned long time_now = millis();
  if (encoder_button1.isSingleClick())
  {
    Consumer.write(MEDIA_VOLUME_MUTE);
  }
  if (encoder_button1.isDoubleClick())
  {
    Keyboard.press(KEY_LEFT_WINDOWS);
    Keyboard.press(KEY_L);
    if (millis() < time_now + PRESS_TIME){
      Keyboard.release(KEY_LEFT_WINDOWS);
      Keyboard.release(KEY_L);
    }
  }
  if (encoder_button1.isLongClick())
  {
    Keyboard.press(KEY_RIGHT_CTRL);
    Keyboard.press(KEY_F9);
    if (millis() < time_now + PRESS_TIME){
      Keyboard.release(KEY_RIGHT_CTRL);
      Keyboard.release(KEY_F9);
    }
  }
  if (encoder_button0.isSingleClick())
  {
    Consumer.write(MEDIA_PLAY_PAUSE);
  }
  if (encoder_button0.isDoubleClick())
  {
    Consumer.write(CONSUMER_EMAIL_READER); 
    //need to set up in registry, see at the bottom
  }
  if (encoder_button0.isLongClick())
  {
    Consumer.write(MEDIA_NEXT);
  }
}

void loop() {
  //Update state
  encoder_button0.update();
  encoder_button1.update();
  Gaming = knobGaming.read();
  Music = knobMusic.read();
  //Send State
  checkButtons();
  checkEncoders();
  sendSliderValues();
  //printSliderValues();//debug
}

/*
    BUTTON0                 BUTTON1

    SHORT CLICK             SHORT CLICK
    MUTE ALL                PLAY/PAUSE

    DOUBLE CLICK            DOUBLE CLICK
    LOCK WINDOWS            LAUNCH MEDIA PLAYER*

    LONG PRESS              LONG PRESS
    TS3 MUTE(CTRL+F9)       NEXT SONG

    * - (Add/Change in registry at HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\AppKey\15 :
         REG_SZ, ShellExecute, "x:/pathToYourMusicPlayer/MusicPlayer.exe")
*/

/* My pinout:
    Encoder0: Button 9, Rotary 4,3
    Encoder1: Button 2, Rotary 7,6
    // Pin 7 and 3 is an interrupt 
*/



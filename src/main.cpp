#include <Arduino.h>
#include <stdint.h>

#include "HID-Project.h"
#include "HID-Settings.h"
#include "Encoder.h"
#include <PinButton.h> // Double/single/long press

#define ENCODER_USE_INTERRUPTS
#define ENCODER_OPTIMIZE_INTERRUPTS
long ANTISCROLL = 10;
long PRESS_TIME = 15;

//Encoder button
PinButton encoder_button0(9);
PinButton encoder_button1(2);

//Encoder
Encoder encoder0(4,3);
Encoder encoder1(7,6);
int32_t lastEncoder0 = 0;
int32_t lastEncoder1 = 0;



void setup() {
    //Serial.begin(9600);
	encoder0.write(0);
	encoder1.write(0);
    Gamepad.begin();
    Gamepad.end();
    Consumer.begin();
    Keyboard.begin();
    Mouse.begin();
    delay(1000);
}

void loop() {
    //Update state
    encoder_button0.update();
    encoder_button1.update();

    //Press gamepad
    //Buttons
    if (encoder_button0.isSingleClick())
    {
        Consumer.write(MEDIA_VOLUME_MUTE);
    }
    if (encoder_button0.isDoubleClick())
    {
        Keyboard.press(KEY_LEFT_WINDOWS);
        Keyboard.press(KEY_L);
        delay(PRESS_TIME);
        Keyboard.release(KEY_LEFT_WINDOWS);
        Keyboard.release(KEY_L);
    }
    if (encoder_button0.isLongClick())
    {
        Keyboard.press(KEY_RIGHT_CTRL);
        Keyboard.press(KEY_F9);
        delay(PRESS_TIME);
        Keyboard.release(KEY_RIGHT_CTRL);
        Keyboard.release(KEY_F9);
    }

    if (encoder_button1.isSingleClick())
    {
        Consumer.write(MEDIA_PLAY_PAUSE);
    }
    if (encoder_button1.isDoubleClick())
    {
        Consumer.write(CONSUMER_EMAIL_READER); // (need to set up in registry, see at the bottom)
    }
    if (encoder_button1.isLongClick())
    {
        Consumer.write(MEDIA_NEXT);
    }
    //1st encoder
    if (encoder1.read() <= lastEncoder1 - 4){
		lastEncoder1 = encoder1.read();
        Keyboard.press(KEY_RIGHT_CTRL);
        Keyboard.press(KEY_RIGHT_SHIFT);
        delay(ANTISCROLL);
        Mouse.move(0,0,1);
        delay(ANTISCROLL);
        Keyboard.release(KEY_RIGHT_CTRL);
        Keyboard.release(KEY_RIGHT_SHIFT);
	}
    if (encoder1.read() >= lastEncoder1 + 4){
		lastEncoder1 = encoder1.read();
        Keyboard.press(KEY_RIGHT_CTRL);
        Keyboard.press(KEY_RIGHT_SHIFT);
        delay(ANTISCROLL);
        Mouse.move(0,0,-1);
        delay(ANTISCROLL);
        Keyboard.release(KEY_RIGHT_CTRL);
        Keyboard.release(KEY_RIGHT_SHIFT);
	}
    //2nd encoder
    if (encoder0.read() <= lastEncoder0 - 4){
		lastEncoder0 = encoder0.read();
        // Keyboard.press(KEY_RIGHT_ALT);
        Keyboard.press(KEY_RIGHT_WINDOWS);
        Keyboard.press(KEY_RIGHT_SHIFT);
        delay(ANTISCROLL);
        Mouse.move(0,0,1);
        delay(ANTISCROLL);
        // Keyboard.release(KEY_RIGHT_ALT);
        Keyboard.release(KEY_RIGHT_WINDOWS);
        Keyboard.release(KEY_RIGHT_SHIFT);
	}
    if (encoder0.read() >= lastEncoder0 + 4){
		lastEncoder0 = encoder0.read();
        // Keyboard.press(KEY_RIGHT_ALT);
        Keyboard.press(KEY_RIGHT_WINDOWS);
        Keyboard.press(KEY_RIGHT_SHIFT);
        delay(ANTISCROLL);
        Mouse.move(0,0,-1);
        delay(ANTISCROLL);
        // Keyboard.release(KEY_RIGHT_ALT);
        Keyboard.release(KEY_RIGHT_SHIFT);
        Keyboard.release(KEY_RIGHT_WINDOWS);
	} 
}


/*
BUTTON0           BUTTON1

SHORT CLICK       SHORT CLICK
MUTE ALL          PLAY/PAUSE

DOUBLE CLICK      DOUBLE CLICK
LOCK WINDOWS      LAUNCH MEDIA PLAYER (Add/Change in registry at "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\AppKey\15" : the first type idk what it is in english, ShellExecute , "x:/pathToYourMusicPlayer/MusicPlayer.exe")

LONG PRESS        LONG PRESS
TS3 MUTE          NEXT SONG
*/

/* My pinout:
    Encoder0: Button 9, Rotary 4,3
    Encoder1: Button 2, Rotary 7,6
    // Pin 7 and 3 is an interrupt 
*/



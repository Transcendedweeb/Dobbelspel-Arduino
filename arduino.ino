#include <Servo.h>
#include <FastLED.h>
#include <Adafruit_TiCoServo.h>

// Servo
Adafruit_TiCoServo servo1;Adafruit_TiCoServo servo2;Adafruit_TiCoServo servo3;Adafruit_TiCoServo servo4;
int pos = 0;
int isUp = 0;
// --------------------------------------------------------------------------------------------------------

// keypad
#include "Adafruit_Keypad.h"

const byte ROWSx= 1;
const byte COLSx= 1;
const byte ROWSx2= 1;
const byte COLSx2= 1;
const byte ROWSx3= 1;
const byte COLSx3= 1;
const byte ROWSx4= 1;
const byte COLSx4= 1;
const byte ROWS= 1;
const byte COLS= 4;
const byte ROWS2= 1;
const byte COLS2= 4;
const byte ROWS3= 1;
const byte COLS3= 4;
const byte ROWS4= 1;
const byte COLS4= 4;
char keysx[ROWSx][COLSx]=
{
{'6'}
};
char keysx2[ROWSx2][COLSx2]=
{
{'7'}
};
char keysx3[ROWSx3][COLSx3]=
{
{'8'}
};
char keysx4[ROWSx4][COLSx4]=
{
{'9'}
};
char keys[ROWS][COLS]=
{
{'2', '1', '4', '3'}
};
char keys2[ROWS2][COLS2]=
{
{'2', '1', '4', '3'}
};
char keys3[ROWS3][COLS3]=
{
{'2', '1', '4', '3'}
};
char keys4[ROWS4][COLS4]=
{
{'2', '1', '4', '3'}
};
byte rowPinsx[ROWSx] = {44};
byte colPinsx[COLSx] = {45};
byte rowPinsx2[ROWSx2] = {46};
byte colPinsx2[COLSx2] = {47};
byte rowPinsx3[ROWSx3] = {48};
byte colPinsx3[COLSx3] = {49};
byte rowPinsx4[ROWSx4] = {50};
byte colPinsx4[COLSx4] = {51};
byte rowPins[ROWS] = {39};
byte colPins[COLS] = {40, 41, 42, 43};
byte rowPins2[ROWS2] = {34};
byte colPins2[COLS2] = {35, 36, 37, 38};
byte rowPins3[ROWS3] = {29};
byte colPins3[COLS2] = {30, 31, 32, 33};
byte rowPins4[ROWS4] = {24};
byte colPins4[COLS4] = {25, 26, 27, 28};
Adafruit_Keypad customKeypadx = Adafruit_Keypad( makeKeymap(keysx), rowPinsx, colPinsx, ROWSx, COLSx);
Adafruit_Keypad customKeypadx2 = Adafruit_Keypad( makeKeymap(keysx2), rowPinsx2, colPinsx2, ROWSx2, COLSx2);
Adafruit_Keypad customKeypadx3 = Adafruit_Keypad( makeKeymap(keysx3), rowPinsx3, colPinsx3, ROWSx3, COLSx3);
Adafruit_Keypad customKeypadx4 = Adafruit_Keypad( makeKeymap(keysx4), rowPinsx4, colPinsx4, ROWSx4, COLSx4);
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Adafruit_Keypad customKeypad2 = Adafruit_Keypad( makeKeymap(keys2), rowPins2, colPins2, ROWS2, COLS2);
Adafruit_Keypad customKeypad3 = Adafruit_Keypad( makeKeymap(keys3), rowPins3, colPins3, ROWS3, COLS3);
Adafruit_Keypad customKeypad4 = Adafruit_Keypad( makeKeymap(keys4), rowPins4, colPins4, ROWS4, COLS4);
// --------------------------------------------------------------------------------------------------------

// LED
#define DATA_PIN    7
#define NUM_LEDS    64
#define BRIGHTNESS  5
CRGB leds[NUM_LEDS];
byte rng = 0;
byte lastRng = 0;
byte shuffleCounter = 0;
char shuffle = false;

int Larray[7][64] = 
{
  {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  },

  {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  },

  {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 1, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0,
  0, 1, 0, 0, 1, 0, 1, 0,
  0, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  },

  {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 1, 0, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0,
  0, 0, 1, 1, 0, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  },

  {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  },

  {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 0, 0, 1, 0,
  0, 1, 0, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  },

  {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 1, 0, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  },
};
// --------------------------------------------------------------------------------------------------------

void setup(){
  Serial.begin(9600);

  // Servo
  servo1.attach(11);servo2.attach(8);servo3.attach(6);servo4.attach(5);
  servo1.write(170);servo2.write(170);servo3.write(170);servo4.write(170);
  // --------------------------------------------------------------------------------------------------------

  customKeypadx.begin();customKeypadx2.begin();customKeypadx3.begin(); customKeypadx4.begin();
  customKeypad.begin();customKeypad2.begin();customKeypad3.begin();customKeypad4.begin();

  // LED
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 
  FastLED.setBrightness(  BRIGHTNESS );
  // --------------------------------------------------------------------------------------------------------
  delay(40);
}

void loop() {
  customKeypadx.tick();customKeypadx2.tick();customKeypadx3.tick();customKeypadx4.tick();
  customKeypad.tick();customKeypad2.tick();customKeypad3.tick();customKeypad4.tick();
  while(customKeypadx.available() || customKeypadx2.available() || customKeypadx3.available() || customKeypadx4.available() ||
        customKeypad.available() || customKeypad2.available() || customKeypad3.available() || customKeypad4.available())
  {
    keypadEvent z = customKeypadx.read();
    if(z.bit.EVENT == KEY_JUST_PRESSED)
    {
        char a = z.bit.KEY;
        int b = z.bit.KEY-48;
        Serial.println(b);
    }
    keypadEvent y = customKeypadx2.read();
    if(y.bit.EVENT == KEY_JUST_PRESSED)
    {
        char a = y.bit.KEY;
        int b = y.bit.KEY-48;
        Serial.println(b);
    }
    keypadEvent x = customKeypadx3.read();
    if(x.bit.EVENT == KEY_JUST_PRESSED)
    {
        char a = x.bit.KEY;
        int b = x.bit.KEY-48;
        Serial.println(b);
    }
    keypadEvent w = customKeypadx4.read();
    if(w.bit.EVENT == KEY_JUST_PRESSED)
    {
        char a = w.bit.KEY;
        int b = w.bit.KEY-48;
        Serial.println(b);
        RunMotor();
    }
    keypadEvent v = customKeypad.read();
    if(v.bit.EVENT == KEY_JUST_PRESSED)
    {
        char a = v.bit.KEY;
        int b = v.bit.KEY-48;
        Serial.println(b);
        if(b == 1){shuffle = true;}
    }
    keypadEvent u = customKeypad2.read();
    if(u.bit.EVENT == KEY_JUST_PRESSED)
    {
        char a = u.bit.KEY;
        int b = u.bit.KEY-48;
        Serial.println(b);
        if(b == 1){shuffle = true;}
    }
    keypadEvent t = customKeypad3.read();
    if(t.bit.EVENT == KEY_JUST_PRESSED)
    {
        char a = t.bit.KEY;
        int b = t.bit.KEY-48;
        Serial.println(b);
        if(b == 1){shuffle = true;}
    }
    keypadEvent s = customKeypad4.read();
    if(s.bit.EVENT == KEY_JUST_PRESSED)
    {
        char a = s.bit.KEY;
        int b = s.bit.KEY-48;
        Serial.println(b);
        if(b == 1){shuffle = true;}
    }
  }
  if(shuffle){
    delay(500);
    RandomLed();
    FastLED.show();
    shuffleCounter++;
    if(shuffleCounter > 3){shuffle = false;shuffleCounter = 0;}
    else{delay(700);}
  } else{ShowCurrentLed(); FastLED.show();}
  delay(10);
}

void RunMotor(){
   if(isUp == 0){
     for(pos = 170; pos >=60; pos--){
        servo1.write(pos);
        servo2.write(pos);
        servo3.write(pos);
        servo4.write(pos);
        delay(20);
      }
     isUp = 1;
  }
  else if(isUp == 1){
      for (pos = 60; pos <= 170; pos++) {
        servo1.write(pos);servo2.write(pos);servo3.write(pos);servo4.write(pos);
        delay(20);
      }
      isUp = 0;
   }
}

void ShowCurrentLed()
{
   for(int j = 0; j<64; j++)
   {
     if(Larray[rng][j] == 1){leds[j] = CRGB::Red;}
     else{leds[j] = CRGB::White;}
   }
}

void GetRandomNumber()
{
   while(true){
    rng = random(1,7);
    if(rng != lastRng){lastRng = rng; break;}
  }
}

void RandomLed()
{
   GetRandomNumber();
   for(int j = 0; j<64; j++)
   {
     if(Larray[rng][j] == 1){leds[j] = CRGB::Red;}
     else{leds[j] = CRGB::White;}
   }
}

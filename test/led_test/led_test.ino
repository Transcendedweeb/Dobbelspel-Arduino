#include "Adafruit_Keypad.h"
#include <FastLED.h>

// LED
#define DATA_PIN     7
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

// keypad
const byte ROWSx= 1;
const byte COLSx= 1;
char keysx[ROWSx][COLSx]=
{
{'1'}
};
byte rowPinsx[ROWSx] = {50};
byte colPinsx[COLSx] = {51};
Adafruit_Keypad customKeypadx = Adafruit_Keypad( makeKeymap(keysx), rowPinsx, colPinsx, ROWSx, COLSx);
// --------------------------------------------------------------------------------------------------------

void setup()
{
  Serial.begin(9600);
  customKeypadx.begin();

  //  LED
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 
  FastLED.setBrightness(  BRIGHTNESS );
  // --------------------------------------------------------------------------------------------------------
}

void loop()
{
  customKeypadx.tick();
  while(customKeypadx.available())
  {
    keypadEvent e = customKeypadx.read();
    if(e.bit.EVENT == KEY_JUST_PRESSED)
      {
        char a = e.bit.KEY;
        int b = e.bit.KEY-48;
        Serial.println(a);
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

void RandomLed()
{
   GetRandomNumber();
   for(int j = 0; j<64; j++)
   {
     if(Larray[rng][j] == 1){leds[j] = CRGB::Red;}
     else{leds[j] = CRGB::White;}
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

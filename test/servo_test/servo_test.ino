#include <Servo.h>

// Servo
Servo servo1;Servo servo2;Servo servo3;Servo servo4;
int pos = 0;
int isUp = 0;
// --------------------------------------------------------------------------------------------------------

// keypad
#include "Adafruit_Keypad.h"

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

void setup(){
  Serial.begin(9600);

  // Servo
  servo1.attach(11);servo2.attach(10);servo3.attach(9);servo4.attach(8);
  servo1.write(170);servo2.write(170);servo3.write(170);servo4.write(170);
  // --------------------------------------------------------------------------------------------------------

  customKeypadx.begin();
  delay(40);
}

void loop() {
  customKeypadx.tick();
  while(customKeypadx.available())
  {
    keypadEvent e = customKeypadx.read();
    if(e.bit.EVENT == KEY_JUST_PRESSED)
      {
        char a = e.bit.KEY;
        int b = e.bit.KEY-48;
        Serial.println(a);
        if(b == 1){RunMotor();}
      }
  }
}

void RunMotor(){
  Serial.println(isUp);
   if(isUp == 0){
     for(pos = 170; pos >=60; pos--){
        servo1.write(pos);servo2.write(pos);servo3.write(pos);servo4.write(pos);
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

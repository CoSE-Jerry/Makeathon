//this is the demo code for the stepper motor, connect pins 8,9,10,11 and 5v, and ground

#include <Stepper.h>

#define STEPS_PER_MOTOR_REVOLUTION 32

#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64

Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 8, 10, 9, 11);

//rotation steps
int  Steps2Take;  

void setup() {
}

void loop() {
  rotate();
  delay(1000);
  //pause for 1s
}

void rotate()
{
  Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION / 4 ; // Rotate CW 1 turn
  small_stepper.setSpeed(700);
  small_stepper.step(Steps2Take);

  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}


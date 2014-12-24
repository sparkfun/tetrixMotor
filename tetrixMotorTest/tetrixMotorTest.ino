/**********************************************************************************************
 * tetrixMotorTest.ino
 * 
 * Upload this program to your Arduino and open up the Serial Monitor
 * to manually control / specify the speed of your servo motor.
 * 
 * Hardware connections:
 * =====================
 * To connect the standard TETRIX Servo motors to an Arduino, we suggest using
 * the ProtoCAT shield. This has break-outs for all of the digital I/O pins on the 
 * Arduino.
 * 
 * For maximum power, it's recommended that the RED power wire is connected directly to VIN.
 * 
 * TETRIX MOTORS  <-------->  ARDUINO
 * ============================================= 
 * WHITE (signal)           Digital pin 9, 10, 11, 12
 * RED (power)              VIN (Battery Power -- 5V works too, but won't be as strong or fast)
 * BLACK (ground)           Ground (GND)
 * 
 * 24 December 2014 -- B. Huang, SparkFun Electronics
 *
 * This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
 * This code is completely free for any use.
/*********************************************************************************************/

#include <tetrixMotor.h> // includes the tetrixMotor library - uses Servo.h
#include <Servo.h>                         

tetrixMotor leftMotor;  // creates an instance of the tetrixMotor class
tetrixMotor rightMotor;  // creates an instance of the tetrixMotor class
tetrixMotor clawMotor;
tetrixMotor armMotor;

void setup()
{
  Serial.begin(9600);    // start Serial Comm on Arduino
  leftMotor.attach(12, CONT);   // setup / attach the leftMotor onto pin 12 -- CONT sets min/max to -255 to 255
  rightMotor.attach(11, CONT);  // setup / attach the rightMotor onto pin 11 -- CONT sets min/max to -255 to 255
  clawMotor.attach(10, SERVO);  // setup / attach the clawMotor onto pin 10 -- SERVO sets min/max to 0 to 180
  armMotor.attach(9, SERVO);    // setup / attach the armMotor onto pin 9   -- SERVO sets min/max to 0 to 180 

  leftMotor.write(-30);
  leftMotor.setZero();  // zero (neutral) point appears to be closer to -30 than 0.
  rightMotor.write(-30);
  rightMotor.setZero(); // zero (neutral) point appears to be closer to -30 than 0.
}

void loop()
{
  // inputValue array for user input.
  int inputValues[4];  
  
  // Print out prompt for user.
  Serial.println("Enter in motor powers for left, right, claw, and arm: ");

  // Read in values from Serial Monitor
  readInput(inputValues, 4);  // reads in 4 values and returns values to array inputValues[]

  // Print out a message to let you know that the value was received
  Serial.print("Setting motors to: ");
  Serial.print(inputValues[0]);
  Serial.print("\t");    // tab character
  Serial.print(inputValues[1]);
  Serial.print("\t");    // tab character
  Serial.print(inputValues[2]);
  Serial.print("\t");    // tab character
  Serial.print(inputValues[3]);
  Serial.print("\t");    // tab character
  Serial.println();
  Serial.println();

  // send commands to motors
  leftMotor.write(inputValues[0]);
  rightMotor.write(-inputValues[1]);  // invert the right to drive the robot fwd / rev
  clawMotor.write(inputValues[2]);
  armMotor.write(inputValues[3]);  
}

/*********************************************************************************
 * readInput() functions. These functions simplify the reading of inputs from the
 * user through the Serial Monitor.
 * 
 * These have a built-in "wait" loop until the input is recieved.
/********************************************************************************/
int readInput()
{
  // Holding loop until an input is read.
  while (Serial.available() == 0)
  {
  } // do nothing
  int inputVal = Serial.parseInt();   // Read in value from Serial Monitor  
  return inputVal;
}

void readInput(int * inputVal, int nArgs)
{
  // Holding loop until an input is read.
  while (Serial.available() == 0)
  {
  } // do nothing

  for (int x=0; x<nArgs; x++)
  {  
    inputVal[x] = Serial.parseInt();
  }
  return;
}

void readInput(float * inputVal, int nArgs)
{
  // Holding loop until an input is read.
  while (Serial.available() == 0)
  {
  } // do nothing

  for (int x=0; x<nArgs; x++)
  {  
    inputVal[x] = Serial.parseFloat();
  }
  return;
}



/****************************************************************
* Core header file for all the various tetrixMotor functions.
* 
* 22 Dec 2014- Brian Huang, SparkFun Electronics
* 
* Code developed in Arduino 1.0.6
/***************************************************************/

#ifndef tetrixMotor_h
#define tetrixMotor_h

#include <Arduino.h>
#include <Servo.h>


enum MotorType {SERVO, CONT};

class tetrixMotor : public Servo
{
  public:
    tetrixMotor();      // Constructor. 
	virtual void attach(int pin);
	virtual void attach(int pin, MotorType type);
    virtual void write(int power);  // drive in direction given by sign, at speed given by the
                            //  magnitude of the parameter. Pos. values CW, Neg. values CCW

	// default MAX and MIN are +255 to -255. Change these limits with setMax() and setMin()
    void setMax(int max);
    void setMin(int min);
	int getMax();
	int getMin();
	
	// set a deadBand limit for the motor. i.e. the abs(power) must be greater than the deadBand to
	// drive the motor.
	void setDeadBand(int deadBand);    // sets the deadBand limit on the motor
    int getDeadBand();
	// often times the zero point of a motor is not exactly at 0. Use this to reset the zero point.
	void setZeroPoint(int zeroPoint);  // sets the zeroPoint
	void setZero();  // sets the zeroPoint
	int getZeroPoint();
	void setMinPulse(int minPulse);    // sets the min pulse width
	void setMaxPulse(int maxPulse);    // sets the max pulse width
	void setNeutralPulse(int neutralPulse);  // sets the zero pulse width
	
	int getMinPulse();    // returns the min pulse width
	int getMaxPulse();    // returns the max pulse width
	int getNeutralPulse();   // returns the zero pulse width

	
	// private variables and objects used in this class.
	
	private:
	uint8_t _pin;
	int _maxPulse;
	int _minPulse;
	int _neutralPulse;
	int _max;
	int _min;
	int _deadBand;			// 
	int _neutralPoint;			// zeroPoint or neutral point in the range
};
#endif
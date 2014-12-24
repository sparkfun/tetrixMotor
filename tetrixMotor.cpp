/*******************************************************************
* Main CPP for tetrixMotor library. Uses the Servo library and scales 
* an input power (-255 to +255) to a pulse width for the VEX motor 
* controller. 
*
* Positive values rotate the motor CW, negative balues rotate the 
* motor CCW.
*
* 22 Dec 2014 - Brian Huang, SparkFun Electronics
* Code developed in Arduino 1.0.6
/******************************************************************/

#include "tetrixMotor.h"
#include <avr/interrupt.h>
#include <Arduino.h>

tetrixMotor::tetrixMotor()
{
	_neutralPoint = 0;  // default zeroPoint
	_deadBand = 0;      // default deadBand
	_maxPulse = 2000;
	_neutralPulse = 1500;
	_minPulse = 1000;
	_min = -255;
	_max = +255;
	
}

void tetrixMotor::attach(int pin)
{
	Servo::attach(pin);
	Servo::writeMicroseconds(_neutralPulse);
	_pin = pin;
}

void tetrixMotor::attach(int pin, MotorType type)
{
	Servo::attach(pin);
	Servo::writeMicroseconds(_neutralPulse);
	_pin = pin;
	if (type == SERVO)
	{
		_min = 0;
		_max = 180;
		_neutralPoint = 90;  // default zeroPoint
	}
	else if (type == CONT)
	{
		_min = -255;
		_max = +255;
		_neutralPoint = 0;  // default zeroPoint
	
	}
}

void tetrixMotor::write(int power)
{	
	// VEX Motor Controller spins CW for pulse widths less than 1500 uS and
	// CCW for pulse widths greater than 1500. map() scales the power to a
	// pulse width.
	int pulseWidth;
	
	// if it's greater than _deadBand -- then it spinning in the CW
	if ((power - _neutralPoint) > _deadBand)
	{
		pulseWidth = map(power, _neutralPoint, _max, _neutralPulse, _minPulse);	
		Servo::writeMicroseconds(pulseWidth);
		}
	else if ((power - _neutralPoint) < -_deadBand)
	{
		pulseWidth = map(power, _min, _neutralPoint, _maxPulse, _neutralPulse);	
		Servo::writeMicroseconds(pulseWidth);
	}
	else if (power > _max)
	{
		Servo::writeMicroseconds(power);
	}
	else
	{
		Servo::writeMicroseconds(_neutralPulse);
	}
}

void tetrixMotor::setZero()
{
	_neutralPulse = Servo::readMicroseconds();
}

void tetrixMotor::setZeroPoint(int neutralPoint)  
{
	if (neutralPoint >= _max)
	{
		_neutralPoint = _max;
	}
	else if (neutralPoint <= _min)
	{
		_neutralPoint = _min;
	}
	else
	{
		_neutralPoint = neutralPoint;
	}
}

int tetrixMotor::getZeroPoint() 
{
	return _neutralPoint;
}

void tetrixMotor::setDeadBand(int deadBand)
{
	_deadBand = deadBand;
} 

int tetrixMotor::getDeadBand()
{
	return _deadBand;
}

void tetrixMotor::setMax(int max)
{
	if(max <= _neutralPoint)
	{
		_max = _neutralPoint;
	}
	else
		_max = max;
}

void tetrixMotor::setMin(int min)
{
	if(min >= _neutralPoint)
	{
		_min = _neutralPoint;
	}
	else
		_min = min;
}

int tetrixMotor::getMax() 
{
	return _max;
}
int tetrixMotor::getMin() 
{
	return _min;
}

void tetrixMotor::setMaxPulse(int maxPulse)
{
	_maxPulse = maxPulse;
}

void tetrixMotor::setMinPulse(int minPulse)
{
	_minPulse = minPulse;
}


void tetrixMotor::setNeutralPulse(int neutralPulse)
{
	_neutralPulse = neutralPulse;
}


int tetrixMotor::getMaxPulse()
{
	return _maxPulse;
}

int tetrixMotor::getMinPulse()
{
	return _minPulse;
}


int tetrixMotor::getNeutralPulse()
{
	return _neutralPulse;
}

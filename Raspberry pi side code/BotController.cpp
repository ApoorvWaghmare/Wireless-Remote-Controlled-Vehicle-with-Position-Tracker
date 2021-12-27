#include <iostream>
#include <wiringPi.h>

#include "BotController.h"

using namespace std;

BotController::BotController()
{
    //ctor
}

void BotController::setUpIOPins()
{
	wiringPiSetup();

	//setting output pins
	pinMode(lMotor1, OUTPUT);
	pinMode(lMotor2, OUTPUT);
	pinMode(rMotor1, OUTPUT);
	pinMode(rMotor2, OUTPUT);
}

void BotController::runBot(int direction)
{
	if(direction == 1) // forward direction
	{
		digitalWrite(lMotor1, 0);
		digitalWrite(lMotor2, 1);
		digitalWrite(rMotor1, 1);
		digitalWrite(rMotor2, 0);
		cout<< "Moving forward" <<endl;
	}
	else if(direction == 2) // backward direction
	{
		digitalWrite(lMotor1, 1);
		digitalWrite(lMotor2, 0);
		digitalWrite(rMotor1, 0);
		digitalWrite(rMotor2, 1);
		cout<< "Moving backward" <<endl;
	}
	else if(direction == 3) // turing right
	{
		digitalWrite(lMotor1, 0);
		digitalWrite(lMotor2, 0);
		digitalWrite(rMotor1, 1);
		digitalWrite(rMotor2, 0);
		cout<< "Turning right" <<endl;
	}
	else if(direction == 4) // turing left
	{
		digitalWrite(lMotor1, 0);
		digitalWrite(lMotor2, 1);
		digitalWrite(rMotor1, 0);
		digitalWrite(rMotor2, 0);
		cout<< "Turnign left" <<endl;
	}
	else if(direction == 5) // stop
	{
		digitalWrite(lMotor1, 0);
		digitalWrite(lMotor2, 0);
		digitalWrite(rMotor1, 0);
		digitalWrite(rMotor2, 0);
		cout<< "Stop" <<endl;
	}
}

BotController::~BotController()
{
    //dtor
}

#include <iostream>

#include "PositionComputer.h"

using namespace std;

PositionComputer::PositionComputer()
{
    //ctor
}

void PositionComputer::computeCoordinates(AccelerometerInterface* accTime, Displacement* xAxis, Displacement* yAxis, std::chrono::steady_clock::time_point start)
{
	double tx1 = accTime->getTime(start);
	double ax1 = accTime->getAccX();
	double tx2, ax2;

	double ty1 = accTime->getTime(start);
	double ay1 = accTime->getAccX();
	double ty2, ay2;

	for(int i = 0; i < 50; i++)
	{
		cout<<i<<endl;

		// for xAxis
		tx2 = accTime->getTime(start);
		ax2 = accTime->getAccX();
		xAxis->calculateCoordinate(tx1, ax1, tx2, ax2);
		cout<<"	x displacement = "<<xAxis->getCoordinate()<<endl;
		tx1 = tx2;
		ax1 = ax2;

		//for yAxis
		ty2 = accTime->getTime(start);
		ay2 = accTime->getAccY();
		yAxis->calculateCoordinate(ty1, ay1, ty2, ay2);
		cout<<"	y displacement = "<<yAxis->getCoordinate()<<endl;
		ty1 = ty2;
		ay1 = ay2;
	}
}

PositionComputer::~PositionComputer()
{
    //dtor
}

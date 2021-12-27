#include "Displacement.h"

Displacement::Displacement()
{
    //ctor
}

double Displacement::getCoordinate()
{
	return m_Coordinate;
}

void Displacement::calculateCoordinate(double t1, double a1, double t2, double a2)
{
	double tempAvgAcc = (a1 + a2) / 2;
	double dt = t2 - t1;

	double Travelled = (m_initialVelocity * dt) + (0.5 * tempAvgAcc * dt * dt);
	m_Coordinate = m_Coordinate + Travelled;

	double finalVelocity = m_initialVelocity + (tempAvgAcc * dt);
	m_initialVelocity = finalVelocity;
}

Displacement::~Displacement()
{
    //dtor
}

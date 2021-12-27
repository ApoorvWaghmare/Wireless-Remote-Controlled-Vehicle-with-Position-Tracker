#include "stdafx.h"
#include "Coordinates.h"


Coordinates::Coordinates()
{
}

void Coordinates::setCurrentX(double x)
{
	m_CurrentXCoordinate = x;
}

void Coordinates::setCurrentY(double y)
{
	m_CurrentYCoordinate = y;
}

double Coordinates::getCurrentXCoordinate()
{
	return m_CurrentXCoordinate;
}

double Coordinates::getCurrentYCoordinate()
{
	return m_CurrentYCoordinate;
}

Coordinates::~Coordinates()
{
}

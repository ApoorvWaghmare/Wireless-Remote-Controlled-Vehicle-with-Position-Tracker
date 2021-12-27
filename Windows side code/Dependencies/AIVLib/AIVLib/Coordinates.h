#pragma once

using namespace std;

class Coordinates
{
public:
	Coordinates();
	~Coordinates();
	double getCurrentXCoordinate();
	double getCurrentYCoordinate();
	void setCurrentX(double x);
	void setCurrentY(double y);
private:
	double m_CurrentXCoordinate = 0;
	double m_CurrentYCoordinate = 0;
};


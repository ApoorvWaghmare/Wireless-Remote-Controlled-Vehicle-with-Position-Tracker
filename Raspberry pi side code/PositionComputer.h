#ifndef CALCULATECOORDINATE_H
#define CALCULATECOORDINATE_H

#include <chrono>

#include "AccelerometerInterface.h"
#include "Displacement.h"

using namespace std;


class PositionComputer
{
    public:
        PositionComputer();
        virtual ~PositionComputer();
		void computeCoordinates(AccelerometerInterface* accTime, Displacement* xAxis, Displacement* yAxis, std::chrono::steady_clock::time_point start);

    protected:

    private:
};

#endif // CALCULATECOORDINATE_H

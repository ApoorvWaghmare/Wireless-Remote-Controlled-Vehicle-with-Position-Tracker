#ifndef XDISPLACEMENT_H
#define XDISPLACEMENT_H

class Displacement
{
    public:
        Displacement();
        virtual ~Displacement();
        double getCoordinate();
		void calculateCoordinate(double t1, double a1, double t2, double a2);

    protected:

    private:
        double m_Coordinate = 0;
		double m_initialVelocity = 0;
};

#endif // XDISPLACEMENT_H

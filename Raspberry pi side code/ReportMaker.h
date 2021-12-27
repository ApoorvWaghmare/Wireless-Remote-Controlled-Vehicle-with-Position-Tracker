#ifndef REPORTMAKER_H
#define REPORTMAKER_H

#include <fstream>

class ReportMaker
{
    public:
        ReportMaker();
        virtual ~ReportMaker();
        //void openFile();
        //void fillReport(double time, double acc);
        //void closeFile();

    protected:

    private:
        //ofstream fileObj("AccelerationTimeReport.txt");
};

#endif // REPORTMAKER_H

#include <iostream>
#include <wiringPiI2C.h>

#include "AccelerometerInterface.h"

using namespace std;

AccelerometerInterface::AccelerometerInterface()
{
    //ctor
}

void AccelerometerInterface::MPUInitialization()
{
    fd = wiringPiI2CSetup(Device_Address); // intializes I2C with devic address

    wiringPiI2CWriteReg8 (fd, SMPLRT_DIV, 0x07);	/* Write to sample rate register */
    wiringPiI2CWriteReg8 (fd, PWR_MGMT_1, 0x01);	/* Write to power management register */
    wiringPiI2CWriteReg8 (fd, CONFIG, 0);		/* Write to Configuration register */
    wiringPiI2CWriteReg8 (fd, GYRO_CONFIG, 24);	/* Write to Gyro Configuration register */
    wiringPiI2CWriteReg8 (fd, INT_ENABLE, 0x01);	/*Write to interrupt enable register */

    accXCalib = getAccX();
    accYCalib = getAccY();

    cout<<"x acc for calibaration = "<<accXCalib<<endl;
    cout<<"y acc for calibaration = "<<accYCalib<<endl;
}

short AccelerometerInterface::readRawData(int addr)
{
    short high_byte,low_byte,value;

    high_byte = wiringPiI2CReadReg8(fd, addr);
    low_byte = wiringPiI2CReadReg8(fd, addr+1);
    value = (high_byte << 8) | low_byte;

    return value;
}

double AccelerometerInterface::getAccX()
{
    double Acc_x = readRawData(ACCEL_XOUT_H);
    accX = (Acc_x * 9.81 / 16384.0) - accXCalib;

    return accX;
}

double AccelerometerInterface::getAccY()
{
    double Acc_y = readRawData(ACCEL_YOUT_H);
    accY = (Acc_y * 9.81 / 16384.0) - accYCalib;

    return accY;
}

double AccelerometerInterface::getTime(std::chrono::steady_clock::time_point start)
{
    std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

    return (duration / 1000);
}

AccelerometerInterface::~AccelerometerInterface()
{
    //dtor
}

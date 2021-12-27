#ifndef ACCELEROMETERINTERFACE_H
#define ACCELEROMETERINTERFACE_H

#define Device_Address 0x68	/*Device Address/Identifier for MPU6050*/
#define PWR_MGMT_1   0x6B
#define SMPLRT_DIV   0x19
#define CONFIG       0x1A
#define GYRO_CONFIG  0x1B
#define INT_ENABLE   0x38
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D

#include <chrono>

class AccelerometerInterface
{
    public:
        AccelerometerInterface();
        virtual ~AccelerometerInterface();
        void MPUInitialization();
		double getAccX();
		double getAccY();
		double getTime(std::chrono::steady_clock::time_point start);//gives time in seconds

    protected:

    private:
        short readRawData(int addr);
		int fd;
		double accX, accY;
		double accXCalib = 0, accYCalib = 0;
};

#endif // ACCELEROMETERINTERFACE_H

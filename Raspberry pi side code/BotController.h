#ifndef BOTCONTROLLER_H
#define BOTCONTROLLER_H

#define lMotor1 0
#define lMotor2 2
#define rMotor1 4
#define rMotor2 5

class BotController
{
    public:
        BotController();
        virtual ~BotController();
        void setUpIOPins();
		void runBot(int direction);

    protected:

    private:
};

#endif // BOTCONTROLLER_H

#ifndef BOT_H
#define BOT_H

#include "TCPServer.h"
#include "BotController.h"
#include "AccelerometerInterface.h"
#include "Displacement.h"
#include "PositionComputer.h"

class Bot
{
    public:
        Bot();
        virtual ~Bot();
        void initializeAllSystems();
        void acceptClient();
        void startOperations();

    protected:

    private:
        TCPServer server;
        BotController botController;
        AccelerometerInterface accTime;
        Displacement xAxis;
        Displacement yAxis;
        PositionComputer positionComputer;
};

#endif // BOT_H

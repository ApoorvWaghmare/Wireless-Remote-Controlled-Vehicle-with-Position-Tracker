#include <iostream>

#include "Bot.h"

using namespace std;

int main()
{
    Bot bot;

    bot.initializeAllSystems();
    bot.acceptClient();
    bot.startOperations();

    return 0;
}

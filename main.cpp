#include <iostream>
#include "mediator.h"

int main(int argc, char *argv[])
{
    PMediator mediator = std::make_shared<Mediator>(argc, argv);
    mediator->init();
    return mediator->mainLoop();
}

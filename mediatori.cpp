#include "mediatori.h"

PMediatorI BaseComponent::getMediator()
{
    if (auto mediator = mMediator.lock())
        return mediator;
    else
        return std::make_shared<DummyMediator>();
}

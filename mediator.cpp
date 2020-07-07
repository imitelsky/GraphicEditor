#include "mediator.h"
#include "window.h"
#include "container.h"
#include "configuration.h"

Mediator::Mediator(int argc, char *argv[]) : mApp(argc, argv)
{

}

void Mediator::init()
{
    mWindow        = std::make_shared<Window>(shared_from_this());
    mContainer     = std::make_shared<Container>(shared_from_this());
	mConfiguration = std::make_shared<Configuration>();
    mContext       = Context::create();

    mWindow->show();
}

void Mediator::setState(int iId)
{
	mContext->setState(iId);
}

void Mediator::notify(const PBaseComponent& iSender, int iEvent)
{
    if (iSender == mWindow)
    {
        switch (iEvent) {
            case eEventId_MouseReleased:
                mContext->request(mWindow->getFirstPos(), mWindow->getSecondPos(), mContainer);
                break;
			case eEventId_Save:
				mContainer->save();
				mConfiguration->save();
				break;
			case eEventId_Load:
				mConfiguration->load(mContainer);
				break;
        }
    }
    if (iSender == mContainer)
    {
        dropUpdateCommand();
        processCommands();
    }
}

void Mediator::dropDrawCommand(int iShapeId, sPoint iBottomLeft, sPoint iTopRigtht)
{
    mCommands.push(std::make_shared<DrawCommand>(mWindow, iShapeId, iBottomLeft, iTopRigtht));
}
void Mediator::dropClearCommand(int iShapeId, sPoint iBottomLeft, sPoint iTopRigtht)
{
    mCommands.push(std::make_shared<ClearCommand>(mWindow, iShapeId, iBottomLeft, iTopRigtht));
}
void Mediator::dropUpdateCommand()
{
    mCommands.push(std::make_shared<UpdateCommand>(mWindow));
}

void Mediator::processCommands()
{
    PCommand command;
    while(!mCommands.empty())
    {
        command = mCommands.front();
        mCommands.pop();
        command->execute();
    }
}

void Mediator::save(int iShapeId, sPoint iBottomLeft, sPoint iTopRigtht)
{
	mConfiguration->add(iShapeId, iBottomLeft, iTopRigtht);
}

int Mediator::mainLoop()
{
    return mApp.exec();
}

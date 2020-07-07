#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "mediatori.h"
#include "command.h"
#include "context.h"
#include "configurationi.h"

#include <QApplication>

class Mediator : public MediatorI, public std::enable_shared_from_this<Mediator>
{
public:
    Mediator(int argc, char *argv[]);

    void setState(int iId) override;

    void notify(const PBaseComponent& iSender, int iEvent) override;

    void dropDrawCommand(int iShapeId, sPoint iBottomLeft, sPoint iTopRigtht) override;
    void dropClearCommand(int iShapeId, sPoint iBottomLeft, sPoint iTopRigtht) override;
    void dropUpdateCommand() override;
    void processCommands() override;
	virtual void save(int iShapeId, sPoint iBottomLeft, sPoint iTopRigtht) override;

    void init() override;
    int  mainLoop() override;

private:
    QApplication           mApp;

    PWindowI               mWindow;
    PContainerI            mContainer;
	PConfigurationI        mConfiguration;
    PContext               mContext;
    std::queue<PCommand>   mCommands;
};

using PMediator = std::shared_ptr<Mediator>;

#endif // MEDIATOR_H

#ifndef MEDIATORI_H
#define MEDIATORI_H

#include "defines.h"

class BaseComponent;
class MediatorI;
class DummyMediator;
using PMediatorI = std::shared_ptr<MediatorI>;
using WMediatorI = std::weak_ptr<MediatorI>;
using PBaseComponent = std::shared_ptr<BaseComponent>;

class BaseComponent
{
public:
	BaseComponent(PMediatorI iMediator) : mMediator(iMediator) {}
	virtual ~BaseComponent() {}
    PMediatorI getMediator();
protected:
	WMediatorI mMediator;
};

class MediatorI
{
public:
    MediatorI() {}
	virtual ~MediatorI() {}

	virtual void setState(int iId) = 0;

	virtual void notify(const PBaseComponent& iSender, int iEvent) = 0;

	virtual void dropDrawCommand(int iShapeId, sPoint iBottomLeft, sPoint iTopRigtht) = 0;
	virtual void dropClearCommand(int iShapeId, sPoint iBottomLeft, sPoint iTopRigtht) = 0;
	virtual void dropUpdateCommand() = 0;
	virtual void processCommands() = 0;
	virtual void save(int iShapeId, sPoint iBottomLeft, sPoint iTopRigtht) = 0;

	virtual void init() = 0;
    virtual int  mainLoop() = 0;
};

class DummyMediator : public MediatorI
{
public:
    DummyMediator() {}
    virtual void setState(int) override {}
    virtual void notify(const PBaseComponent&, int) override {}
    virtual void dropDrawCommand(int, sPoint, sPoint) override {}
    virtual void dropClearCommand(int, sPoint, sPoint) override {}
    virtual void dropUpdateCommand() override {}
    virtual void processCommands() override {}
    virtual void save(int, sPoint, sPoint) override {}
    virtual void init() override {}
    virtual int  mainLoop() override {return -1;}
};

#endif

#ifndef CONTEXT_H
#define CONTEXT_H

#include "containeri.h"

class Context;
class State;

using stateId = unsigned int;
using PState = std::shared_ptr<State>;
using WState = std::weak_ptr<State>;
using PContext = std::shared_ptr<Context>;
using WContext = std::weak_ptr<Context>;

class Context : public std::enable_shared_from_this<Context>
{
public:
	Context();
    ~Context();
    void setState(const stateId iState);
    void request(const sPoint& iFirst, const sPoint& iSecond, const PContainerI& iContainer);
	static PContext create();
private:
	void init();
    WState mState;
    std::vector<PState> mStates;
};

class State
{
public:
	State(PContext iContext) : mContext(iContext) {}
    virtual ~State() {}
    virtual void handle(const sPoint& iFirst, const sPoint& iSecond, const PContainerI& iContainer) = 0;
protected:
    WContext mContext;
};

class Move : public State
{
public:
	Move(PContext iContext) : State(iContext) {}
    void handle(const sPoint& iFirst, const sPoint& iSecond, const PContainerI& iContainer) override;
};

class DrawRectangle : public State
{
public:
	DrawRectangle(PContext iContext) : State(iContext) {}
    void handle(const sPoint& iFirst, const sPoint& iSecond, const PContainerI& iContainer) override;
};

class DrawTriangle : public State
{
public:
	DrawTriangle(PContext iContext) : State(iContext) {}
    void handle(const sPoint& iFirst, const sPoint& iSecond, const PContainerI& iContainer) override;
};

class DrawEllipse : public State
{
public:
	DrawEllipse(PContext iContext) : State(iContext) {}
    void handle(const sPoint& iFirst, const sPoint& iSecond, const PContainerI& iContainer) override;
};

class DrawLine : public State
{
public:
	DrawLine(PContext iContext) : State(iContext) {}
    void handle(const sPoint& iFirst, const sPoint& iSecond, const PContainerI& iContainer) override;
};

#endif // CONTEXT_H

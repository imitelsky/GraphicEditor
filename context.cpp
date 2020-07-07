#include "context.h"

Context::Context()
{

}

Context::~Context()
{
}

PContext Context::create()
{
	auto res = std::make_shared<Context>();
	res->init();
	return res;
}

void Context::init()
{
	mStates.resize(eStateId_EnumNo);

    mStates[eStateId_Move]            = std::make_shared<Move>(shared_from_this());
	mStates[eStateId_CreateRectangle] = std::make_shared<DrawRectangle>(shared_from_this());
    mStates[eStateId_CreateTriangle]  = std::make_shared<DrawTriangle>(shared_from_this());
    mStates[eStateId_CreateEllipse]   = std::make_shared<DrawEllipse>(shared_from_this());
    mStates[eStateId_Connect]         = std::make_shared<DrawLine>(shared_from_this());

	setState(eStateId_Move);
}

void Context::setState(const stateId iState)
{
    mState = mStates[iState];
}

void Context::request(const sPoint &iFirst, const sPoint &iSecond, const PContainerI& iContainer)
{
	if (auto state = mState.lock())
		state->handle(iFirst, iSecond, iContainer);
}

void Move::handle(const sPoint &iFirst, const sPoint &iSecond, const PContainerI& iContainer)
{
    iContainer->move(iFirst, iSecond);
}

void DrawRectangle::handle(const sPoint &iFirst, const sPoint &iSecond, const PContainerI& iContainer)
{
    iContainer->addShape(eShapeId_Rectangle, iFirst, iSecond);
    if (auto context = mContext.lock()) 
		context->setState(eStateId_Move);
}

void DrawTriangle::handle(const sPoint &iFirst, const sPoint &iSecond, const PContainerI& iContainer)
{
    iContainer->addShape(eShapeId_Triangle, iFirst, iSecond);
	if (auto context = mContext.lock()) 
		context->setState(eStateId_Move);
}

void DrawEllipse::handle(const sPoint &iFirst, const sPoint &iSecond, const PContainerI& iContainer)
{
    iContainer->addShape(eShapeId_Ellipse, iFirst, iSecond);
	if (auto context = mContext.lock()) 
		context->setState(eStateId_Move);
}

void DrawLine::handle(const sPoint &iFirst, const sPoint &iSecond, const PContainerI& iContainer)
{
    iContainer->addLine(iFirst, iSecond);
	if (auto context = mContext.lock()) 
		context->setState(eStateId_Move);
}

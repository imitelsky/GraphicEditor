#ifndef COMMAND_H
#define COMMAND_H

#include "windowi.h"

class Command
{
public:
    Command() = delete;
    virtual ~Command() {}
    virtual void execute() = 0;
    Command(PWindowI iWindow) : mWindow(iWindow) {}
protected:
    WWindowI mWindow;
};

class UpdateCommand : public Command
{
public:
    UpdateCommand() = delete;
    void execute() override;
    UpdateCommand(PWindowI iWindow) : Command(iWindow) {}
};

class DrawCommand : public Command
{
public:
    DrawCommand() = delete;
    void execute() override;
    DrawCommand(PWindowI iWindow, int iShapeId, sPoint iBottomLeft, sPoint iTopRight) :
        Command(iWindow), mShapeId(iShapeId), mBottomLeft(iBottomLeft), mTopRight(iTopRight) {}
private:
    int    mShapeId;
    sPoint mBottomLeft;
    sPoint mTopRight;
};

class ClearCommand : public Command
{
public:
    ClearCommand() = delete;
    void execute() override;
    ClearCommand(PWindowI iWindow, int iShapeId, sPoint iBottomLeft, sPoint iTopRight) :
        Command(iWindow), mShapeId(iShapeId), mBottomLeft(iBottomLeft), mTopRight(iTopRight) {}
private:
    int    mShapeId;
    sPoint mBottomLeft;
    sPoint mTopRight;
};


using PCommand = std::shared_ptr<Command>;

#endif // COMMAND_H

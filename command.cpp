#include "command.h"

void DrawCommand::execute()
{
    if (auto window = mWindow.lock())
        window->draw(mShapeId, mBottomLeft.x, mBottomLeft.y, mTopRight.x, mTopRight.y);
}
void ClearCommand::execute()
{
    if (auto window = mWindow.lock())
        window->clear(mShapeId, mBottomLeft.x, mBottomLeft.y, mTopRight.x, mTopRight.y);
}
void UpdateCommand::execute()
{
    if (auto window = mWindow.lock())
        window->updateView();
}

#include "container.h"


bool Container::isPointBelongsToShape(const sPoint &iPoint, PShape& iShape)
{
    if (iPoint >= iShape->getBottomLeft() && iPoint <= iShape->getTopRight())
        return true;
    else
        return false;
}

void Container::move(const sPoint &iFirst, const sPoint &iSecond)
{
    for(auto& shape : mShapes)
        if (isPointBelongsToShape(iFirst, shape))
        {
            shape->move(iSecond - iFirst);
            if (auto mediator = mMediator.lock())
                mediator->notify(shared_from_this(), eEventId_UpdateView);
            break;
        }
}

void Container::addShape(const int iId, const sPoint &iFirst, const sPoint &iSecond)
{
    PShape shape = nullptr;

    switch (iId)
    {
        case eShapeId_Rectangle:
            shape = std::make_shared<Rectangle>(iFirst, iSecond);
            break;
        case eShapeId_Triangle:
            shape = std::make_shared<Triangle>(iFirst, iSecond);
            break;
        case eShapeId_Ellipse:
            shape = std::make_shared<Ellipse>(iFirst, iSecond);
            break;
    }

    if (shape == nullptr)
        return;

    shape->setContainer(shared_from_this());
    shape->draw();

    mShapes.push_back(shape);
    if (auto mediator = mMediator.lock())
        mediator->notify(shared_from_this(), eEventId_UpdateView);
}

void Container::addLine(const sPoint &iFirst, const sPoint &iSecond)
{
    PSubject shape1 = nullptr;
    PSubject shape2 = nullptr;

    for(auto shape : mShapes)
    {
        if (isPointBelongsToShape(iFirst, shape))
            shape1 = std::dynamic_pointer_cast<Subject>(shape);
        if (isPointBelongsToShape(iSecond, shape))
            shape2 = std::dynamic_pointer_cast<Subject>(shape);
    }

    if (shape1 == nullptr || shape2 == nullptr)
        return;

    PShape line = Line::create(shape1, shape2);

    line->setContainer(shared_from_this());
    line->draw();

    mLines.push_back(line);
    if (auto mediator = mMediator.lock())
        mediator->notify(shared_from_this(), eEventId_UpdateView);
}

void Container::draw()
{
    for (auto& shape : mShapes)
        shape->draw();
    for (auto& line : mLines)
        line->draw();
}

void Container::clear()
{
	for (auto& shape : mShapes)
		shape->clear();
	for (auto& line : mLines)
		line->clear();

	mLines.clear();
	mShapes.clear();
}

void Container::save()
{
	for (auto& shape : mShapes)
		getMediator()->save(shape->getId(), shape->getBottomLeft(), shape->getTopRight());
	for (auto& line : mLines)
		getMediator()->save(line->getId(), line->getBottomLeft(), line->getTopRight());
}

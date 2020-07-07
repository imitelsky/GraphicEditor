#ifndef WINDOWI_H
#define WINDOWI_H

#include "mediatori.h"

class WindowI : public BaseComponent
{
public:
    WindowI(PMediatorI iMediator) : BaseComponent(iMediator) {}
    virtual ~WindowI() {}

	virtual const sPoint& getFirstPos() const = 0;
	virtual const sPoint& getSecondPos() const = 0;

	virtual void draw(int iShapeId, int iX1, int iY1, int iX2, int iY2) = 0;
	virtual void clear(int iShapeId, int iX1, int iY1, int iX2, int iY2) = 0;

	virtual void show() = 0;

	virtual void updateView() = 0;
};

using PWindowI = std::shared_ptr<WindowI>;
using WWindowI = std::weak_ptr<WindowI>;

#endif

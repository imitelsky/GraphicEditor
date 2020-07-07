#ifndef CONTAINERI_H
#define CONTAINERI_H

#include "mediatori.h"

class ContainerI : public BaseComponent
{
public:
    ContainerI(PMediatorI iMediator) : BaseComponent(iMediator) {}
    virtual ~ContainerI() {}

	virtual void move(const sPoint& iFirst, const sPoint& iSecond) = 0;
	virtual void addShape(const int iId, const sPoint& iFirst, const sPoint& iSecond) = 0;
	virtual void addLine(const sPoint& iFirst, const sPoint& iSecond) = 0;
	virtual void draw() = 0;
	virtual void clear() = 0;
	virtual void save() = 0;
};

using PContainerI = std::shared_ptr<ContainerI>;

#endif

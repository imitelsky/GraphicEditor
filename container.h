#ifndef CONTAINER_H
#define CONTAINER_H

#include "containeri.h"
#include <vector>

class Shape;
class Subject;
class Observer;
using PShape = std::shared_ptr<Shape>;
using PSubject = std::shared_ptr<Subject>;
using WSubject = std::weak_ptr<Subject>;
using PObserver = std::shared_ptr<Observer>;
using WObserver = std::weak_ptr<Observer>;


class Container : public ContainerI, public std::enable_shared_from_this<Container>
{
public:
    Container(PMediatorI iMediator) : ContainerI(iMediator) {}

    void move(const sPoint& iFirst, const sPoint& iSecond) override;
    void addShape(const int iId, const sPoint& iFirst, const sPoint& iSecond) override;
    void addLine(const sPoint& iFirst, const sPoint& iSecond) override;
    void draw() override;
	void clear() override;
	void save() override;

private:
    std::vector<PShape> mShapes;
    std::vector<PShape> mLines;

    bool isPointBelongsToShape(const sPoint &iPoint, PShape& iShape);
};


using PContainer = std::shared_ptr<Container>;
using WContainer = std::weak_ptr<Container>;


class Shape
{
public:
    Shape() {}
    virtual void setContainer(PContainer iContainer) { mContainer = iContainer; }
    //virtual const sPoint& getBottomLeft() = 0;
    //virtual const sPoint& getTopRight() = 0;
    virtual sPoint getBottomLeft() = 0;
	virtual sPoint getTopRight() = 0;
	virtual int getId() = 0;
    virtual void draw() = 0;
    virtual void clear() = 0;
    virtual void redraw() = 0;
    virtual void move(const sPoint&) {}
protected:
    WContainer mContainer;

    sPoint mBottomLeft;
    sPoint mTopRight;
};



class Observer
{
public:
    Observer() {}
    Observer(PSubject iFirstShape, PSubject iSecondShape) : mFirstShape(iFirstShape), mSecondShape(iSecondShape) {}
    virtual void update() = 0;
protected:
    WSubject mFirstShape;
    WSubject mSecondShape;
};



class Subject
{
public:
  void attach(PObserver iObs) { mLines.push_back(iObs); }
  void notify()
  {
      for (auto& line : mLines)
		  if (auto _line = line.lock())
            _line->update();
  }
  //virtual const sPoint& getBottomLeft() = 0;
  //virtual const sPoint& getTopRight() = 0;
  virtual sPoint getBottomLeft() = 0;
  virtual sPoint getTopRight() = 0;
protected:
    std::vector<WObserver> mLines;
};



class Rectangle : public Shape, public Subject
{
public:
    Rectangle(const sPoint& iFirst, const sPoint& iSecond)
    {
        mBottomLeft = {std::min(iFirst.x, iSecond.x), std::min(iFirst.y, iSecond.y)};
        mTopRight = {std::max(iFirst.x, iSecond.x), std::max(iFirst.y, iSecond.y)};
    }
    //virtual const sPoint& getBottomLeft() {return mBottomLeft;}
	//virtual const sPoint& getTopRight() {return mTopRight;}
	virtual sPoint getBottomLeft() { return mBottomLeft; }
	virtual sPoint getTopRight() { return mTopRight; }
	virtual int getId() { return eShapeId_Rectangle; }
    virtual void draw()
    {
        if (auto container = mContainer.lock())
            container->getMediator()->dropDrawCommand(eShapeId_Rectangle, mBottomLeft, mTopRight);
    }
    virtual void clear()
    {
        if (auto container = mContainer.lock())
            container->getMediator()->dropClearCommand(eShapeId_Rectangle, mBottomLeft, mTopRight);
    }
    virtual void redraw() {}

    virtual void move(const sPoint& iTranslation)
    {
        clear();
        mBottomLeft += iTranslation;
        mTopRight += iTranslation;
        notify();
        draw();
    }
};

class Triangle : public Shape, public Subject
{
public:
    Triangle(const sPoint& iFirst, const sPoint& iSecond)
    {
        mBottomLeft = {std::min(iFirst.x, iSecond.x), std::min(iFirst.y, iSecond.y)};
        mTopRight = {std::max(iFirst.x, iSecond.x), std::max(iFirst.y, iSecond.y)};
    }
    //virtual const sPoint& getBottomLeft() {return mBottomLeft;}
    //virtual const sPoint& getTopRight() {return mTopRight;}
	virtual sPoint getBottomLeft() { return mBottomLeft; }
	virtual sPoint getTopRight() { return mTopRight; }
	virtual int getId() { return eShapeId_Triangle; }
    virtual void draw()
    {
        if (auto container = mContainer.lock())
            container->getMediator()->dropDrawCommand(eShapeId_Triangle, mBottomLeft, mTopRight);
    }
    virtual void clear()
    {
        if (auto container = mContainer.lock())
            container->getMediator()->dropClearCommand(eShapeId_Triangle, mBottomLeft, mTopRight);
    }
    virtual void redraw() {}

    virtual void move(const sPoint& iTranslation)
    {
        clear();
        mBottomLeft += iTranslation;
        mTopRight += iTranslation;
        notify();
        draw();
    }
};

class Ellipse : public Shape, public Subject
{
public:
    Ellipse(const sPoint& iFirst, const sPoint& iSecond)
    {
        mBottomLeft = {std::min(iFirst.x, iSecond.x), std::min(iFirst.y, iSecond.y)};
        mTopRight = {std::max(iFirst.x, iSecond.x), std::max(iFirst.y, iSecond.y)};
    }
    //virtual const sPoint& getBottomLeft() {return mBottomLeft;}
    //virtual const sPoint& getTopRight() {return mTopRight;}
	virtual sPoint getBottomLeft() { return mBottomLeft; }
	virtual sPoint getTopRight() { return mTopRight; }
	virtual int getId() { return eShapeId_Ellipse; }
    virtual void draw()
    {
        if (auto container = mContainer.lock())
            container->getMediator()->dropDrawCommand(eShapeId_Ellipse, mBottomLeft, mTopRight);
    }
    virtual void clear()
    {
        if (auto container = mContainer.lock())
            container->getMediator()->dropClearCommand(eShapeId_Ellipse, mBottomLeft, mTopRight);
    }
    virtual void redraw() {}

    virtual void move(const sPoint& iTranslation)
    {
        clear();
        mBottomLeft += iTranslation;
        mTopRight += iTranslation;
        notify();
        draw();
    }
};



class Line : public Shape, public Observer, public std::enable_shared_from_this<Line>
{
public:
    Line() {}
    static PShape create(PSubject& iFirstShape, PSubject& iSecondShape)
    {
        auto res = std::make_shared<Line>();
        res->init(iFirstShape, iSecondShape);
        return res;
    }

    //virtual const sPoint& getBottomLeft() {return mBottomLeft;}
    //virtual const sPoint& getTopRight() {return mTopRight;}
	virtual sPoint getBottomLeft() { return mBottomLeft; }
	virtual sPoint getTopRight() { return mTopRight; }
	virtual int getId() { return eShapeId_Line; }
    virtual void draw()
    {
        if (auto container = mContainer.lock())
            container->getMediator()->dropDrawCommand(eShapeId_Line, mBottomLeft, mTopRight);
    }
    virtual void clear()
    {
        if (auto container = mContainer.lock())
            container->getMediator()->dropClearCommand(eShapeId_Line, mBottomLeft, mTopRight);
    }
    virtual void redraw() {}

    void update()
    {
        clear();
        auto firstShape = mFirstShape.lock();
        auto secondShape = mSecondShape.lock();
        if (firstShape && secondShape)
        {
            mBottomLeft = (firstShape->getBottomLeft() + firstShape->getTopRight()) / 2;
            mTopRight = (secondShape->getBottomLeft() + secondShape->getTopRight()) / 2;
        }
        draw();
    }
private:
    void init(PSubject& iFirstShape, PSubject& iSecondShape)
    {
        iFirstShape->attach(shared_from_this());
        iSecondShape->attach(shared_from_this());
        mFirstShape = iFirstShape;
        mSecondShape = iSecondShape;
        mBottomLeft = (iFirstShape->getBottomLeft() + iFirstShape->getTopRight()) / 2;
        mTopRight = (iSecondShape->getBottomLeft() + iSecondShape->getTopRight()) / 2;
    }
};

#endif // CONTAINER_H

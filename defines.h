#ifndef DEFINES_H
#define DEFINES_H

#include <queue>
#include <memory>

enum eShapeId
{
    eShapeId_Undefined = 0,
    eShapeId_Rectangle,
    eShapeId_Triangle,
    eShapeId_Ellipse,
    eShapeId_Line,
    eShapeId_EnumNo,
};

enum eStateId
{
	eStateId_Move = 0,
	eStateId_CreateRectangle,
	eStateId_CreateTriangle,
	eStateId_CreateEllipse,
	eStateId_Connect,
	eStateId_EnumNo,
};

enum eEventId
{
    eEventId_MouseReleased = 0,
    eEventId_UpdateView,
	eEventId_Save,
	eEventId_Load,
    eEventId_EnumNo,
};

struct sPoint
{
    int x;
    int y;
    sPoint() = default;
    sPoint(sPoint&) = default;
    sPoint(sPoint&&) = default;
    sPoint& operator=(const sPoint&) = default;
    friend const sPoint operator+(const sPoint& iFirst, const sPoint& iSecond)
    {
        return {iFirst.x + iSecond.x, iFirst.y + iSecond.y};
    }
    friend const sPoint operator-(const sPoint& iFirst, const sPoint& iSecond)
    {
        return {iFirst.x - iSecond.x, iFirst.y - iSecond.y};
    }
    friend sPoint& operator+=(sPoint& iLeft, const sPoint& iRight)
    {
        iLeft.x += iRight.x; iLeft.y += iRight.y;
        return iLeft;
    }
    friend const sPoint operator/(const sPoint& iPoint, const int iValue)
    {
        return {iPoint.x / iValue, iPoint.y / iValue};
    }
    friend bool operator>=(const sPoint& iFirst, const sPoint& iSecond)
    {
        return (iFirst.x >= iSecond.x) && (iFirst.y >= iSecond.y);
    }
    friend bool operator<=(const sPoint& iFirst, const sPoint& iSecond)
    {
        return (iFirst.x <= iSecond.x) && (iFirst.y <= iSecond.y);
    }
};


#endif // DEFINES_H

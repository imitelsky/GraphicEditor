#include "renderarea.h"

#include <QPainter>


RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    mImage = new QImage(400, 200, QImage::Format_ARGB32_Premultiplied);
    mImage->fill(QColor(Qt::white));
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

void RenderArea::mouseMoveEvent(QMouseEvent* /*e*/)
{
}

void RenderArea::mousePressEvent(QMouseEvent *e)
{
    mousePressed = e->pos();
}

void RenderArea::mouseReleaseEvent(QMouseEvent *e)
{
    mouseReleased = e->pos();
    mouseSignal();
}

void RenderArea::paintEvent(QPaintEvent* /*e*/)
{

    if (mImage->height() < height() || mImage->width() < width())
    {
        QImage *newImage = new QImage(width(), height(), QImage::Format_ARGB32_Premultiplied);
        newImage->fill(QColor(Qt::white));
        QPainter painter(newImage);
        painter.drawImage(QPoint(0, 0), *mImage);
        delete mImage;
        mImage = newImage;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawImage(0,0,*mImage);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

void RenderArea::modifyImage(QPainter& iPainter, int iShapeId, int iX1, int iY1, int iX2, int iY2)
{
    switch (iShapeId) {
    case Line:
        iPainter.drawLine(QPoint(iX1, iY1), QPoint(iX2, iY2));
        break;
    case Rectangle:
    {
        QRect rect(QPoint(iX1, iY1), QPoint(iX2, iY2));
        iPainter.drawRect(rect);
        break;
    }
    case Ellipse:
    {
        QRect rect(QPoint(iX1, iY1), QPoint(iX2, iY2));
        iPainter.drawEllipse(rect);
        break;
    }
    case Triangle:
        QPolygon polygon;
        for (auto point : {QPoint(iX2, iY2),QPoint(static_cast<int>((iX2 + iX1)/2), iY1), QPoint(iX1, iY2)})
            polygon << point;
        iPainter.drawPolygon(polygon);
        break;
    }
}

void RenderArea::draw(int iShapeId, int iX1, int iY1, int iX2, int iY2)
{
    QPainter painter(mImage);
    painter.setPen(QColor(Qt::black));

    modifyImage(painter, iShapeId, iX1, iY1, iX2, iY2);
}

void RenderArea::clear(int iShapeId, int iX1, int iY1, int iX2, int iY2)
{
    QPainter painter(mImage);
    painter.setPen(QColor(Qt::white));

    modifyImage(painter, iShapeId, iX1, iY1, iX2, iY2);
}

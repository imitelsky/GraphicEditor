#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QMouseEvent>
#include <QImage>

class RenderArea : public QWidget
{

    Q_OBJECT

public:
    enum Shape { Undefined = 0, Rectangle, Triangle, Ellipse, Line, };

    RenderArea(QWidget *parent = 0);

    QPoint& getMousePressedPos() {return mousePressed;}
    QPoint& getMouseReleasedPos() {return mouseReleased;}

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

Q_SIGNALS:
    void mouseSignal();

public slots:
    void draw(int iShapeId, int iX1, int iY1, int iX2, int iY2);
    void clear(int iShapeId, int iX1, int iY1, int iX2, int iY2);

protected:
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;

private:
    void modifyImage(QPainter &iPainter, int iShapeId, int iX1, int iY1, int iX2, int iY2);

private:
    QImage *mImage;
    Shape shape;
    QPen pen;
    QPoint mousePressed;
    QPoint mouseReleased;
    QSize mMaxSize;
};

#endif // RENDERAREA_H

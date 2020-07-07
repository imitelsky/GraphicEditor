#ifndef WINDOW_H
#define WINDOW_H

#include "windowi.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE
class RenderArea;

enum eButtonId
{
    eButtonId_Rectangle = 0,
    eButtonId_Triangle,
    eButtonId_Ellipse,
    eButtonId_Move,
    eButtonId_Connect,
    eButtonId_Save,
    eButtonId_Load,
    eButtonId_EnumNo,
};

const std::string sButtonLable[eButtonId_EnumNo]{"Rectangle", "Triangle", "Ellipse", "Move", "Connect", "Save", "Load"};


class Window : public QWidget, public WindowI, public std::enable_shared_from_this<Window>
{
    Q_OBJECT

public:
    Window(PMediatorI iMediator);
    virtual ~Window();

    const sPoint& getFirstPos() const {return mFirstPos;}
    const sPoint& getSecondPos() const {return mSecondPos;}

    void draw(int iShapeId, int iX1, int iY1, int iX2, int iY2);
    void clear(int iShapeId, int iX1, int iY1, int iX2, int iY2);

    void show() override;

Q_SIGNALS:
    void updateView();

private slots:
    void onRenderAreaMouseReleased();
    void onRectangleButtonClicked();
    void onTriangleButtonClicked();
    void onEllipseButtonClicked();
    void onMoveButtonClicked();
    void onConnectButtonClicked();
    void onSaveButtonClicked();
    void onLoadButtonClicked();

private:

    RenderArea                *mRenderArea;
    std::vector<QPushButton*> mButtons;

    sPoint mFirstPos;
    sPoint mSecondPos;
};

#endif // WINDOW_H

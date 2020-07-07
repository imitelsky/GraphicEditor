#include "window.h"
#include "renderarea.h"

#include <QtWidgets>

Window::Window(PMediatorI iMediator) : WindowI(iMediator)
{
    mRenderArea = new RenderArea;

    mButtons.resize(eButtonId_EnumNo);
    for (auto& button : mButtons)
        button = new QPushButton;

    connect( mButtons[eButtonId_Rectangle], SIGNAL(clicked(bool)), this, SLOT(onRectangleButtonClicked()) );
    connect( mButtons[eButtonId_Triangle],  SIGNAL(clicked(bool)), this, SLOT(onTriangleButtonClicked())  );
    connect( mButtons[eButtonId_Ellipse],   SIGNAL(clicked(bool)), this, SLOT(onEllipseButtonClicked())   );
    connect( mButtons[eButtonId_Move],      SIGNAL(clicked(bool)), this, SLOT(onMoveButtonClicked())      );
    connect( mButtons[eButtonId_Connect],   SIGNAL(clicked(bool)), this, SLOT(onConnectButtonClicked())   );
    connect( mButtons[eButtonId_Save],      SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked())      );
    connect( mButtons[eButtonId_Load],      SIGNAL(clicked(bool)), this, SLOT(onLoadButtonClicked())      );

    connect( this,        SIGNAL(updateView()),  mRenderArea, SLOT(update()));
    connect( mRenderArea, SIGNAL(mouseSignal()), this,        SLOT(onRenderAreaMouseReleased()) );

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->addWidget(mRenderArea, 0, 0, 1, eButtonId_EnumNo);
    for (uint i = eButtonId_Rectangle; i < eButtonId_EnumNo; i++)
    {
        mButtons[i]->setText(sButtonLable[i].c_str());
        mainLayout->addWidget(mButtons[i], 1, i, Qt::AlignRight);
    }
    setLayout(mainLayout);
}

Window::~Window()
{
    delete mRenderArea;
    for (auto& button : mButtons)
    {
        delete button;
        button = nullptr;
    }
}

void Window::show()
{
    QWidget::show();
}

void Window::onRectangleButtonClicked()
{
    if (auto mediator = mMediator.lock())
        mediator->setState(eStateId_CreateRectangle);
}

void Window::onTriangleButtonClicked()
{
    if (auto mediator = mMediator.lock())
        mediator->setState(eStateId_CreateTriangle);
}

void Window::onEllipseButtonClicked()
{
    if (auto mediator = mMediator.lock())
        mediator->setState(eStateId_CreateEllipse);
}

void Window::onMoveButtonClicked()
{
    if (auto mediator = mMediator.lock())
        mediator->setState(eStateId_Move);
}

void Window::onConnectButtonClicked()
{
    if (auto mediator = mMediator.lock())
        mediator->setState(eStateId_Connect);
}

void Window::onSaveButtonClicked()
{
    if (auto mediator = mMediator.lock())
        mediator->notify(shared_from_this(), eEventId_Save);
}

void Window::onLoadButtonClicked()
{
    if (auto mediator = mMediator.lock())
        mediator->notify(shared_from_this(), eEventId_Load);
}

void Window::onRenderAreaMouseReleased()
{
    mFirstPos = {mRenderArea->getMousePressedPos().x(), mRenderArea->getMousePressedPos().y()};
    mSecondPos = {mRenderArea->getMouseReleasedPos().x(), mRenderArea->getMouseReleasedPos().y()};
    if (auto mediator = mMediator.lock())
        mediator->notify(shared_from_this(), eEventId_MouseReleased);
}

void Window::draw(int iShapeId, int iX1, int iY1, int iX2, int iY2)
{
    mRenderArea->draw(iShapeId, iX1, iY1, iX2, iY2);
}

void Window::clear(int iShapeId, int iX1, int iY1, int iX2, int iY2)
{
    mRenderArea->clear(iShapeId, iX1, iY1, iX2, iY2);
}

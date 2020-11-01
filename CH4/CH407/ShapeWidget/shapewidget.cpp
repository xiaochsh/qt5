#include "shapewidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>

ShapeWidget::ShapeWidget(QWidget *parent)
    : QWidget(parent)
{
    QPixmap pix;
    pix.load("16.png", 0, Qt::AvoidDither | Qt::ThresholdDither | Qt::ThresholdAlphaDither);
    resize(pix.size());
    setMask(QBitmap(pix.mask()));
}

ShapeWidget::~ShapeWidget()
{
}

void ShapeWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) // event->button()返回产生事件的按钮
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    if (event->button() == Qt::RightButton)
    {
        close();
    }
}

void ShapeWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) // event->buttons()返回产生事件的按钮状态
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void ShapeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap("16.png"));
}


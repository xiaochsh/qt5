#ifndef SVGWINDOW_H
#define SVGWINDOW_H

#include "svgwidget.h"
#include <QScrollArea>
#include <QMouseEvent>

class SvgWindow : public QScrollArea
{
    Q_OBJECT
public:
    SvgWindow(QWidget *parent = nullptr);
    void setFile(QString);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    SvgWidget *svgWidget;
    QPoint mousePressPos;
    QPoint scrollBarValueOnMousePress;
};

#endif // SVGWINDOW_H

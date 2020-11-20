#include "svgwindow.h"

SvgWindow::SvgWindow(QWidget *parent) : QScrollArea (parent)
{
    svgWidget = new SvgWidget;
    setWidget (svgWidget);
}

void SvgWindow::setFile(QString fileName)
{
    svgWidget->load (fileName);
    QSvgRenderer *render = svgWidget->renderer ();
    svgWidget->resize (render->defaultSize ());
}

void SvgWindow::mousePressEvent(QMouseEvent *e)
{
    mousePressPos = e->pos ();
    scrollBarValueOnMousePress.rx () = horizontalScrollBar ()->value ();
    scrollBarValueOnMousePress.ry () = verticalScrollBar ()->value ();
    e->accept ();
}

void SvgWindow::mouseMoveEvent(QMouseEvent *e)
{
    horizontalScrollBar ()->setValue (scrollBarValueOnMousePress.x () -
            e->pos ().x () + mousePressPos.x ());
    verticalScrollBar ()->setValue (scrollBarValueOnMousePress.y () -
            e->pos ().y () + mousePressPos.y ());
    horizontalScrollBar ()->update ();
    verticalScrollBar ()->update ();
    e->accept ();
}

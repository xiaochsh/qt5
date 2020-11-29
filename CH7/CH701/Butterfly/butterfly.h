#ifndef BUTTERFLY_H
#define BUTTERFLY_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>

class Butterfly : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Butterfly(QObject *parent = nullptr);
    void timerEvent(QTimerEvent *event);
    QRectF boundingRect() const;  // 继承QGraphicsItem的类需实现该方法

signals:

public slots:

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    bool up;
    QPixmap pix_up;
    QPixmap pix_down;

    qreal angle;
};

#endif // BUTTERFLY_H

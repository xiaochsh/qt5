#ifndef DIGICLOCK_H
#define DIGICLOCK_H

#include <QLCDNumber>

class DigiClock : public QLCDNumber
{
    Q_OBJECT
public:
    DigiClock(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

public slots:
    void showTime();

private:
    QPoint dragPosition;
    bool showColon;
};

#endif // DIGICLOCK_H

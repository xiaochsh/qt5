#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <QWidget>
#include <QKeyEvent>
#include <QPaintEvent>

class KeyEvent : public QWidget
{
    Q_OBJECT

public:
    KeyEvent(QWidget *parent = nullptr);
    ~KeyEvent();

    void drawPix();
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap *pix;
    QImage image;
    int startX;
    int startY;
    int width;
    int height;
    int step;
};
#endif // KEYEVENT_H

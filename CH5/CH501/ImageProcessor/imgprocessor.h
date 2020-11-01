#ifndef IMGPROCESSOR_H
#define IMGPROCESSOR_H

#include <QMainWindow>

class ImgProcessor : public QMainWindow
{
    Q_OBJECT

public:
    ImgProcessor(QWidget *parent = nullptr);
    ~ImgProcessor();
};
#endif // IMGPROCESSOR_H

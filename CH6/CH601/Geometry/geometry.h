#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QEvent>

class Geometry : public QDialog
{
    Q_OBJECT

public:
    Geometry(QWidget *parent = nullptr);
    ~Geometry();

    void updateLabel();

private:
    QLabel *xLabel;
    QLabel *xValueLabel;
    QLabel *yLabel;
    QLabel *yValueLabel;
    QLabel *frameLabel;
    QLabel *frameValueLabel;
    QLabel *posLabel;
    QLabel *posValbeLabel;
    QLabel *geometryLabel;
    QLabel *geometryValueLabel;
    QLabel *widthLabel;
    QLabel *widthValueLabel;
    QLabel *heightLabel;
    QLabel *heightValueLabel;
    QLabel *rectLabel;
    QLabel *rectValueLabel;
    QLabel *sizeLabel;
    QLabel *sizeValueLabel;
    QGridLayout *mainLayout;

protected:
    void moveEvent(QMoveEvent *);
    void resizeEvent(QResizeEvent *);
};
#endif // GEOMETRY_H

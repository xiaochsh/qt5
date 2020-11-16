#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    paintArea = new PaintArea;

    shapeLabel = new QLabel(tr("形状："));
    shapeComboBox = new QComboBox;
    shapeComboBox->addItem (tr("Line"), PaintArea::Line);
    shapeComboBox->addItem (tr("Rectangle"), PaintArea::Rectangle);
    shapeComboBox->addItem (tr("RoundRect"), PaintArea::RoundRect);
    shapeComboBox->addItem (tr("Ellipse"), PaintArea::Ellipse);
    shapeComboBox->addItem (tr("Polygon"), PaintArea::Polygon);
    shapeComboBox->addItem (tr("Polyline"), PaintArea::Polyline);
    shapeComboBox->addItem (tr("Points"), PaintArea::Points);
    shapeComboBox->addItem (tr("Arc"), PaintArea::Arc);
    shapeComboBox->addItem (tr("Path"), PaintArea::Path);
    shapeComboBox->addItem (tr("Text"), PaintArea::Text);
    shapeComboBox->addItem (tr("Pixmap"), PaintArea::Pixmap);
    connect (shapeComboBox, static_cast<void (QComboBox::*)(const int)>(&QComboBox::activated), this, &MainWidget::ShowShape);
}

MainWidget::~MainWidget()
{
}


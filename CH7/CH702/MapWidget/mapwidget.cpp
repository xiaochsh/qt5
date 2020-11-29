#include "mapwidget.h"
#include <QSlider>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QGraphicsScene>
#include <math.h>

MapWidget::MapWidget() : QGraphicsView()
{
    readMap();

    zoom = 50;

    int width = map.width();
    int height = map.height();
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setSceneRect(- width / 2, - height / 2, width, height);
    setScene(scene);
    setCacheMode(CacheBackground);

    QSlider *slider = new QSlider;
    slider->setOrientation(Qt::Vertical);
    slider->setRange(0, 100);
    slider->setTickInterval(10);
    slider->setValue(50);
    connect(slider, &QSlider::valueChanged, this, &MapWidget::slotZoom);

    QLabel *zoominLabel = new QLabel;
    zoominLabel->setScaledContents(true);
    zoominLabel->setPixmap(QPixmap("zoomin.png"));

    QLabel *zoomoutLabel = new QLabel;
    zoomoutLabel->setScaledContents(true);
    zoomoutLabel->setPixmap(QPixmap("zoomout.png"));

    QLabel *label1 = new QLabel(tr("GraphicsView:"));
    viewCoord = new QLabel;
    QLabel *label2 = new QLabel(tr("GraphicsScene:"));
    sceneCoord = new QLabel;
    QLabel *label3 = new QLabel(tr("map:"));
    mapCoord = new QLabel;

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(label1, 0, 0);
    gridLayout->addWidget(viewCoord, 0, 1);
    gridLayout->addWidget(label2, 1, 0);
    gridLayout->addWidget(sceneCoord, 1, 1);
    gridLayout->addWidget(label3, 2, 0);
    gridLayout->addWidget(mapCoord, 2, 1);
    gridLayout->setSizeConstraint(QLayout::SetFixedSize);

    QFrame *coordFrame = new QFrame;
    coordFrame->setLayout(gridLayout);

    QVBoxLayout *zoomLayout = new QVBoxLayout;
    zoomLayout->addWidget(zoominLabel);
    zoomLayout->addWidget(slider);
    zoomLayout->addWidget(zoomoutLabel);

    QVBoxLayout *coordLayout = new QVBoxLayout;
    coordLayout->addWidget(coordFrame);
    coordLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(zoomLayout);
    mainLayout->addLayout(coordLayout);
    mainLayout->addStretch();
    mainLayout->setMargin(30);
    mainLayout->setSpacing(10);
    setLayout(mainLayout);

    setWindowTitle("Map Widget");
    setMinimumSize(600, 400);
}

MapWidget::~MapWidget()
{
}


void MapWidget::readMap()
{
    QString mapName;
    QFile mapFile("maps.txt");
    bool ok = mapFile.open(QIODevice::ReadOnly);
    if (ok)
    {
        QTextStream ts(&mapFile);
        if (!ts.atEnd())
        {
            ts >> mapName;
            ts >> x1 >> y1 >> x2 >> y2;
        }
    }
    map.load(mapName);
}

void MapWidget::slotZoom(int value)
{
    qreal s;
    if (value > zoom)
    {
        s = pow(1.01, value - zoom);
    }
    else
    {
        s = pow(1 / 1.01, zoom - value);
    }
    scale(s, s);
    zoom = value;
}

void MapWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(int(sceneRect().left()), int(sceneRect().top()), map);
}

void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint viewPoint = event->pos();
    viewCoord->setText(QString::number(viewPoint.x()) + "," +
                       QString::number(viewPoint.y()));
    QPointF scenePoint = mapToScene(viewPoint);
    sceneCoord->setText(QString::number(scenePoint.x()) + "," +
                        QString::number(scenePoint.y()));
    QPointF latLon = mapToMap(scenePoint);
    mapCoord->setText(QString::number(latLon.x()) + "," +
                      QString::number(latLon.y()));
}

QPointF MapWidget::mapToMap(QPointF p)
{
    QPointF latLon;
    qreal w = sceneRect().width();
    qreal h = sceneRect().height();

    qreal lon = y1 - ((h /2 + p.y()) * abs(y1 - y2) / h);
    qreal lat = x1 + ((w /2 + p.x()) * abs(x1 - x2) / w);

    latLon.setX(lat);
    latLon.setY(lon);

    return latLon;
}

#include "palette.h"
#include <QHBoxLayout>
#include <QGridLayout>

Palette::Palette(QWidget *parent)
    : QDialog(parent)
{
    createCtrlFrame();
    createContentFrame();
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(ctrlFrame);
    mainLayout->addWidget(contentFrame);
}

Palette::~Palette()
{
}

void Palette::createCtrlFrame()
{
    ctrlFrame = new QFrame(this);
    windowLabel = new QLabel(tr("QPalette::Window: "));
    windowComboBox = new QComboBox;
    fillColorList(windowComboBox);
    connect(windowComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), [=](int){ Palette::ShowWindow(); });
    // connect(windowComboBox, SIGNAL(activated(int)), this, SLOT(Palette::ShowWindow()));

    windowTextLabel = new QLabel(tr("QPalette::windowText: "));
    windowTextComboBox = new QComboBox;
    fillColorList(windowTextComboBox);
    connect(windowTextComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), [=](int){ Palette::ShowWindText(); });

    buttonLabel = new QLabel(tr("QPalette::Button: "));
    buttonComboBox = new QComboBox;
    fillColorList(buttonComboBox);
    connect(buttonComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), [=](int){ Palette::ShowButton(); });

    buttonTextLabel = new QLabel(tr("QPalette::ButtonText: "));
    buttonTextComboBox = new QComboBox;
    fillColorList(buttonTextComboBox);
    connect(buttonTextComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), [=](int){ Palette::ShowButtonText(); });

    baseLabel = new QLabel(tr("QPalette::Base: "));
    baseComboBox = new QComboBox;
    fillColorList(baseComboBox);
    connect(baseComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), [=](int){ Palette::ShowBase(); });

    QGridLayout *mainLayout = new QGridLayout(ctrlFrame);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(windowLabel, 0, 0);
    mainLayout->addWidget(windowComboBox, 0, 1);
    mainLayout->addWidget(windowTextLabel, 1, 0);
    mainLayout->addWidget(windowTextComboBox, 1, 1);
    mainLayout->addWidget(buttonLabel, 2, 0);
    mainLayout->addWidget(buttonComboBox, 2, 1);
    mainLayout->addWidget(buttonTextLabel, 3, 0);
    mainLayout->addWidget(buttonTextComboBox, 3, 1);
    mainLayout->addWidget(baseLabel, 4, 0);
    mainLayout->addWidget(baseComboBox, 4, 1);
}

void Palette::createContentFrame()
{
    contentFrame = new QFrame(this);

    label1 = new QLabel(tr("请选择一个值："));
    comboBox1 = new QComboBox;

    label2 = new QLabel(tr("请输入字符串："));
    lineEdit2 = new QLineEdit;

    textEdit = new QTextEdit;

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addWidget(label1, 0, 0);
    topLayout->addWidget(comboBox1, 0, 1);
    topLayout->addWidget(label2, 1, 0);
    topLayout->addWidget(lineEdit2, 1, 1);
    topLayout->addWidget(textEdit, 2, 0, 1, 2);

    OkBtn = new QPushButton(tr("确认"));
    CancelBtn = new QPushButton(tr("取消"));

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch(1);
    bottomLayout->addWidget(OkBtn);
    bottomLayout->addWidget(CancelBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(contentFrame);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

}

void Palette::ShowWindow()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[windowComboBox->currentIndex()]);

    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Window, color);
    contentFrame->setPalette(p);

    contentFrame->update();
}

void Palette::ShowWindText()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[windowTextComboBox->currentIndex()]);

    QPalette p = contentFrame->palette();
    p.setColor(QPalette::WindowText, color);
    contentFrame->setPalette(p);

    contentFrame->update();
}

void Palette::ShowButton()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[buttonComboBox->currentIndex()]);

    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Button, color);
    contentFrame->setPalette(p);

    contentFrame->update();
}

void Palette::ShowButtonText()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[buttonTextComboBox->currentIndex()]);

    QPalette p = contentFrame->palette();
    p.setColor(QPalette::ButtonText, color);
    contentFrame->setPalette(p);

    contentFrame->update();
}

void Palette::ShowBase()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[baseComboBox->currentIndex()]);

    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Base, color);
    contentFrame->setPalette(p);

    contentFrame->update();
}

void Palette::fillColorList(QComboBox *comboBox)
{
    QStringList colorList = QColor::colorNames();
    QString color;
    foreach(color, colorList)
    {
        QPixmap pix(QSize(70, 20));
        pix.fill(QColor(color));
        comboBox->addItem(QIcon(pix), NULL);
        comboBox->setIconSize(QSize(70, 20));
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}

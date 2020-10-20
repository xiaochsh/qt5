#include "dialog.h"
#include <QString>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QMessageBox>
#include <QPixmap>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("各种标准对话框的实例"));

    fileBtn = new QPushButton;
    fileBtn->setText(tr("文件标准对话框实例"));
    fileLineEdit = new QLineEdit;
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(fileBtn, 0, 0);
    mainLayout->addWidget(fileLineEdit, 0, 1);
    connect(fileBtn, &QPushButton::clicked, this, &Dialog::showFile);

    colorBtn = new QPushButton;
    colorBtn->setText(tr("颜色标准对话框实例"));
    colorFrame = new QFrame;
    colorFrame->setFrameShape(QFrame::Box);
    colorFrame->setAutoFillBackground(true);
    mainLayout->addWidget(colorBtn, 1, 0);
    mainLayout->addWidget(colorFrame, 1, 1);
    connect(colorBtn, &QPushButton::clicked, this, &Dialog::showColor);

    fontBtn = new QPushButton;
    fontBtn->setText(tr("字体标准对话框实例"));
    fontLineEdit = new QLineEdit;
    mainLayout->addWidget(fontBtn, 2, 0);
    mainLayout->addWidget(fontLineEdit, 2, 1);
    connect(fontBtn, &QPushButton::clicked, this, &Dialog::showFont);

    inputBtn = new QPushButton;
    inputBtn->setText(tr("标准输入对话框实例"));
    mainLayout->addWidget(inputBtn, 3, 0);
    connect(inputBtn, &QPushButton::clicked, this, &Dialog::showInputDlg);

    msgBtn = new QPushButton;
    msgBtn->setText(tr("标准消息对话框实例"));
    mainLayout->addWidget(msgBtn, 3, 1);
    connect(msgBtn, &QPushButton::clicked, this, &Dialog::showMsgDlg);

    customBtn = new QPushButton;
    customBtn->setText (tr("用户自定义消息对话框实例"));
    label = new QLabel;
    label->setFrameStyle (QFrame::Panel | QFrame::Sunken);
    mainLayout->addWidget (customBtn, 4, 0);
    mainLayout->addWidget (label, 4, 1);
    connect (customBtn, &QPushButton::clicked, this, &Dialog::showCustomDlg);
}

Dialog::~Dialog()
{
}

void Dialog::showFile()
{
    QString s = QFileDialog::getOpenFileName(this, "open file dialog", ".",
                                             "C++ files(*.cpp);;C files(*.c);;Head files(*.h)");
    fileLineEdit->setText(s);
}

void Dialog::showColor()
{
    QColor c = QColorDialog::getColor(Qt::blue);
    if (c.isValid())
    {
        colorFrame->setPalette(QPalette(c));
    }
}

void Dialog::showFont()
{
    bool ok;
    QFont f = QFontDialog::getFont(&ok);
    if (ok)
    {
        fontLineEdit->setText(f.toString());
    }
}

void Dialog::showInputDlg()
{
    inputDlg = new InputDlg(this);
    inputDlg->show();
}

void Dialog::showMsgDlg()
{
    msgDlg = new MsgBoxDlg(this);
    msgDlg->show();
}

void Dialog::showCustomDlg ()
{
    label->setText (tr("Custom Message Box"));
    QMessageBox customMsgBox;
    customMsgBox.setWindowTitle (tr("用户自定义消息框"));
    QPushButton *yesBtn = customMsgBox.addButton (tr("Yes"), QMessageBox::ActionRole);
    QPushButton *noBtn = customMsgBox.addButton (tr("No"), QMessageBox::ActionRole);
    QPushButton *cancelBtn = customMsgBox.addButton (tr("Cancel"), QMessageBox::ActionRole);
    customMsgBox.setText (tr("这是一个用户自定义消息框！"));
    customMsgBox.setIconPixmap (QPixmap("qt.ico"));
    customMsgBox.exec ();

    if (customMsgBox.clickedButton () == yesBtn)
        label->setText ("Custom Message Box/Yes");
    if (customMsgBox.clickedButton () == noBtn)
        label->setText ("Custom Message Box/No");
    if (customMsgBox.clickedButton () == cancelBtn)
        label->setText ("Custom Message Box/Cancel");
    return;
}


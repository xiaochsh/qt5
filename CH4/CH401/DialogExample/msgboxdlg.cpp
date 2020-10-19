#include "msgboxdlg.h"

MsgBoxDlg::MsgBoxDlg(QWidget* parent) : QDialog(parent)
{
    setWindowTitle(tr("标准消息对话框的实例"));
    label = new QLabel;
    label->setText(tr("请选择一种消息框"));

    questionBtn = new QPushButton;
    questionBtn->setText(tr("QuestionMsg"));

    informationBtn = new QPushButton;
    informationBtn->setText(tr("InformationMsg"));

    warningBtn = new QPushButton;
    warningBtn->setText(tr("WarningMsg"));

    criticlBtn = new QPushButton;
    criticlBtn->setText(tr("CriticalMsg"));

    aboutBtn = new QPushButton;
    aboutBtn->setText(tr("AboutMsg"));

    aboutQtBtn = new QPushButton;
    aboutQtBtn->setText(tr("AboutQtMsg"));

    // 布局
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(label, 0, 0, 1, 2);
    mainLayout->addWidget(questionBtn, 1, 0);
    mainLayout->addWidget(informationBtn, 1, 1);
    mainLayout->addWidget(warningBtn, 2, 0);
    mainLayout->addWidget(criticlBtn, 2, 1);
    mainLayout->addWidget(aboutBtn, 3, 0);
    mainLayout->addWidget(aboutQtBtn, 3, 1);

    // 事件关联
    connect(questionBtn, &QPushButton::clicked, this, &MsgBoxDlg::showQuestionMsg);
    connect(informationBtn, &QPushButton::clicked, this, &MsgBoxDlg::showInfomationMsg);
    connect(warningBtn, &QPushButton::clicked, this, &MsgBoxDlg::showWarningMsg);
    connect(criticlBtn, &QPushButton::clicked, this, &MsgBoxDlg::showCriticalMsg);
    connect(aboutBtn, &QPushButton::clicked, this, &MsgBoxDlg::showAboutMsg);
    connect(aboutQtBtn, &QPushButton::clicked, this, &MsgBoxDlg::showAboutQtMsg);
}

void MsgBoxDlg::showQuestionMsg()
{

}

void MsgBoxDlg::showInfomationMsg()
{

}

void MsgBoxDlg::showWarningMsg()
{

}

void MsgBoxDlg::showCriticalMsg()
{

}

void MsgBoxDlg::showAboutMsg()
{

}

void MsgBoxDlg::showAboutQtMsg()
{

}

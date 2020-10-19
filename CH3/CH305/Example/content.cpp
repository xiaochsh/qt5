#include "content.h"

Content::Content(QWidget *parent)
    : QFrame(parent)
{
    stack = new QStackedWidget;
    stack->setFrameStyle(QFrame::Panel | QFrame::Raised);
    baseInfo = new BaseInfo();
    contact = new Contact();
    detail = new Detail();
    stack->addWidget(baseInfo);
    stack->addWidget(contact);
    stack->addWidget(detail);

    AmendBtn = new QPushButton(tr("修改"));
    CloseBtn = new QPushButton(tr("关闭"));
    QHBoxLayout *BtnLayout = new QHBoxLayout();
    BtnLayout->addStretch(1);
    BtnLayout->addWidget(AmendBtn);
    BtnLayout->addWidget(CloseBtn);

    QVBoxLayout *Rightlayout = new QVBoxLayout(this);
    Rightlayout->setMargin(10);
    Rightlayout->setSpacing(6);
    Rightlayout->addWidget(stack);
    Rightlayout->addLayout(BtnLayout);
}

Content::~Content()
{
}


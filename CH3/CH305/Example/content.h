#ifndef CONTENT_H
#define CONTENT_H

#include <QFrame>
#include <QStackedWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "baseinfo.h"
#include "contact.h"
#include "detail.h"

class Content : public QFrame
{
    Q_OBJECT
public:
    QStackedWidget *stack;
    QPushButton *AmendBtn;
    QPushButton *CloseBtn;

    BaseInfo *baseInfo;
    Contact *contact;
    Detail *detail;
public:
    Content(QWidget *parent = nullptr);
    ~Content();
};
#endif // CONTENT_H

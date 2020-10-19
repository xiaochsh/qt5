#include "mainwindow.h"
#include <QSplitter>
#include <QTextEdit>
//#include <QTextCodec>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("ZYsong18030", 12);
    // 主分割窗口
    QSplitter *splitterMain = new QSplitter(Qt::Horizontal, 0);
    QTextEdit *textLeft = new QTextEdit(QObject::tr("Left Widget"), splitterMain);
    textLeft->setAlignment(Qt::AlignCenter);
    // 右部分分割窗口
    QSplitter *splitterRight = new QSplitter(Qt::Vertical, splitterMain);
    splitterRight->setOpaqueResize(false);
    QTextEdit *textUp = new QTextEdit(QObject::tr("Yop Widget"), splitterRight);
    textUp->setAlignment(Qt::AlignCenter);
    QTextEdit *textBottom = new QTextEdit(QObject::tr("Bottom Widget"), splitterRight);
    textBottom->setAlignment(Qt::AlignCenter);
    splitterMain->setStretchFactor(1, 1);
    splitterMain->setWindowTitle(QObject::tr("Splitter"));
    splitterMain->show();
//    MainWindow w;
//    w.show();
    return a.exec();
}

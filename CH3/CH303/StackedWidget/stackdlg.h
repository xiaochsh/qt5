#ifndef STACKDLG_H
#define STACKDLG_H

#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>

class StackDlg : public QDialog
{
    Q_OBJECT

private:
    QListWidget *list;
    QStackedWidget *stack;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;

public:
    StackDlg(QWidget *parent = nullptr);
    ~StackDlg();
};
#endif // STACKDLG_H

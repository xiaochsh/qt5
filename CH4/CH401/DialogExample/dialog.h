#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QFrame>

#include "inputdlg.h"
#include "msgboxdlg.h"

class Dialog : public QDialog
{
    Q_OBJECT

private:
    QPushButton *fileBtn;
    QLineEdit *fileLineEdit;
    QGridLayout *mainLayout;

    QPushButton *colorBtn;
    QFrame *colorFrame;

    QPushButton *fontBtn;
    QLineEdit *fontLineEdit;

    QPushButton *inputBtn;
    InputDlg *inputDlg;

    QPushButton *msgBtn;
    MsgBoxDlg *msgDlg;

    QPushButton *customBtn;
    QLabel *label;

private slots:
    void showFile();
    void showColor();
    void showFont();
    void showInputDlg();
    void showMsgDlg();
    void showCustomDlg();

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
};
#endif // DIALOG_H

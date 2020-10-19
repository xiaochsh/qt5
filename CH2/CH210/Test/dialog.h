#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

// naming convention 自动建立signal-slot连接
// connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_lineEdit_textChanged()));
public slots:
    void on_lineEdit_textChanged();

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H

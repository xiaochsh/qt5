#ifndef PROGRESSDLG_H
#define PROGRESSDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>

class ProgressDlg : public QDialog
{
    Q_OBJECT

public:
    ProgressDlg(QWidget *parent = nullptr);
    ~ProgressDlg();
private:
    QLabel *FileNum;
    QLineEdit *FileNumLineEdit;
    QLabel *ProgressType;
    QComboBox *comboBox;
    QProgressBar *progressBar;
    QPushButton *starBtn;
    QGridLayout *mainLayout;
private slots:
    void starProgress();
};
#endif // PROGRESSDLG_H

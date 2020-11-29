#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QDir>
#include <QListWidgetItem>
#include <QFileInfoList>

class FileView : public QDialog
{
    Q_OBJECT

public:
    FileView(QWidget *parent = nullptr);
    ~FileView();

    void showFileInfoList(QDir dir);

public slots:
    void slotReturnPressedShow();
    void slotDirShow(QListWidgetItem *item);

private:
    QLineEdit *fileLineEdit;
    QListWidget *fileListWidget;

    QVBoxLayout *mainLayout;

private:
    void getFileInfoList(QFileInfoList list);
};
#endif // FILEVIEW_H

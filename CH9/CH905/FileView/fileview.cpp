#include "fileview.h"

FileView::FileView(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("File View"));

    fileLineEdit = new QLineEdit(tr("/"));
    fileListWidget = new QListWidget;

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(fileLineEdit);
    mainLayout->addWidget(fileListWidget);

    connect(fileLineEdit, &QLineEdit::returnPressed, this, &FileView::slotReturnPressedShow);
    connect(fileListWidget, &QListWidget::itemDoubleClicked, this, &FileView::slotDirShow);

    QString root {"/"};
    QDir rootDir(root);
    QStringList string;
    string << "*";
    QFileInfoList list = rootDir.entryInfoList(string);
    getFileInfoList(list);
}

FileView::~FileView()
{
}

void FileView::showFileInfoList(QDir dir)
{
    QStringList string;
    string << "*";
    QFileInfoList list = dir.entryInfoList(string, QDir::AllEntries, QDir::DirsFirst);
    getFileInfoList(list);
}

void FileView::slotReturnPressedShow()
{
    QString dir = fileLineEdit->text();
    showFileInfoList(QDir(dir));
}

void FileView::getFileInfoList(QFileInfoList list)
{
    fileListWidget->clear();
    for (int i = 0; i < list.count(); ++i) {
        QFileInfo tmpFileInfo = list.at(i);
        if (tmpFileInfo.isDir())
        {
            QIcon icon("dir.png");
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem *tmp = new QListWidgetItem(icon, fileName);
            fileListWidget->addItem(tmp);
        }
        else if (tmpFileInfo.isFile())
        {
            QIcon icon("file.png");
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem *tmp = new QListWidgetItem(icon, fileName);
            fileListWidget->addItem(tmp);
        }
    }
}

void FileView::slotDirShow(QListWidgetItem * item)
{
    QString str = item->text();
    QDir dir;
    dir.setPath(fileLineEdit->text());
    dir.cd(str);
    fileLineEdit->setText(dir.absolutePath());
    showFileInfoList(dir);
}


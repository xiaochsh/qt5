#ifndef IMGPROCESSOR_H
#define IMGPROCESSOR_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCharFormat>
#include "showwidget.h"

class ImgProcessor : public QMainWindow
{
    Q_OBJECT

public:
    ImgProcessor(QWidget *parent = nullptr);
    ~ImgProcessor();

    void createActions();
    void createMenus();
    void createToolBars();

    void loadFile(QString filename);
    void mergeFormat(QTextCharFormat);

private:
    QMenu *fileMenu;
    QMenu *zoomMenu;
    QMenu *rotateMenu;
    QMenu *mirrorMenu;

    QImage img;
    QString filename;
    ShowWidget *showWidget;

    QAction *openFileAction;
    QAction *newFileAction;
    QAction *printTextAction;
    QAction *printImageAction;
    QAction *exitAction;

    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *aboutAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;

    QAction *rotate90Action;
    QAction *rotate180Action;
    QAction *rotate270Action;

    QAction *mirrorVerticalAction;
    QAction *mirrorHorizontalAction;

    QAction *undoAction;
    QAction *redoAction;

    QToolBar *fileTool;
    QToolBar *zoomTool;
    QToolBar *rotateTool;
    QToolBar *mirrorTool;

    QToolBar *doToolBar;

protected slots:
    void ShowNewFile();
    void ShowOpenFile();
    void ShowPrintText();
    void ShowPrintImage();
};
#endif // IMGPROCESSOR_H

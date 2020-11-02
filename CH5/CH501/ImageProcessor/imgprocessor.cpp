#include "imgprocessor.h"
#include <QApplication>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QPainter>

ImgProcessor::ImgProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle (tr("Easy Word"));

    showWidget = new ShowWidget(this);
    setCentralWidget (showWidget);

    createActions ();
    createMenus ();
    createToolBars ();

    if (img.load ("image.png"))
    {
        showWidget->imageLabel->setPixmap (QPixmap::fromImage (img));
    }
}

ImgProcessor::~ImgProcessor()
{
}

void ImgProcessor::createActions()
{
    openFileAction = new QAction(QIcon("open.png"), tr("打开"), this);
    openFileAction->setShortcut (tr("Ctrl+O"));
    openFileAction->setToolTip (tr("打开一个文件"));
    connect (openFileAction, &QAction::triggered, this, &ImgProcessor::ShowOpenFile);

    newFileAction = new QAction(QIcon("new.png"), tr("新建"), this);
    newFileAction->setShortcut (tr("Ctrl+N"));
    newFileAction->setToolTip (tr("新建一个文件"));
    connect (newFileAction, &QAction::triggered, this, &ImgProcessor::ShowNewFile);

    exitAction = new QAction(tr("退出"), this);
    exitAction->setShortcut (tr("Ctrl+Q"));
    exitAction->setToolTip (tr("退出程序"));
    connect(exitAction, &QAction::triggered, this, &ImgProcessor::close);

    copyAction = new QAction(QIcon("copy.png"), tr("复制"), this);
    copyAction->setShortcut (tr("Ctrl+C"));
    copyAction->setToolTip (tr("复制文件"));
    connect (copyAction, &QAction::triggered, showWidget->text, &QTextEdit::copy);
    // connect (copyAction, SIGNAL (triggered()), showWidget->text, SLOT (copy()));

    cutAction = new QAction(QIcon("cut.png"), tr("剪切"), this);
    cutAction->setShortcut (tr("Ctrl+X"));
    cutAction->setToolTip (tr("剪切文件"));
    connect (copyAction, &QAction::triggered, showWidget->text, &QTextEdit::cut);

    pasteAction = new QAction(QIcon("paste.png"), tr("粘贴"), this);
    pasteAction->setShortcut (tr("Ctrl+V"));
    pasteAction->setToolTip (tr("粘贴文件"));
    connect (copyAction, &QAction::triggered, showWidget->text, &QTextEdit::paste);

    aboutAction = new QAction(tr("关于"), this);
    connect (aboutAction, &QAction::triggered, this, &QApplication::aboutQt);

    printTextAction = new QAction(QIcon("printText.png"), tr("打印文本"), this);
    printTextAction->setToolTip (tr("打印一个文本"));
    connect (printTextAction, &QAction::triggered, this, &ImgProcessor::ShowPrintText);

    printImageAction = new QAction(QIcon("printImage.png"), tr("打印图像"), this);
    printImageAction->setToolTip (tr("打印一幅图像"));
    connect (printImageAction, &QAction::triggered, this, &ImgProcessor::ShowPrintImage);

    zoomInAction = new QAction(QIcon("zoomin.png"), tr("放大"), this);
    zoomInAction->setToolTip (tr("放大一张图片"));

    zoomOutAction = new QAction(QIcon("zoomout.png"), tr("缩小"), this);
    zoomOutAction->setToolTip (tr("缩小一张图片"));

    rotate90Action = new QAction(QIcon("rotate90.png"), tr("旋转90°"), this);
    rotate90Action->setToolTip (tr("将一幅图旋转90°"));

    rotate180Action = new QAction(QIcon("rotate180.png"), tr("旋转180°"), this);
    rotate180Action->setToolTip (tr("将一幅图旋转180°"));

    rotate270Action = new QAction(QIcon("rotate270.png"), tr("旋转270°"), this);
    rotate270Action->setToolTip (tr("将一幅图旋转270°"));

    mirrorVerticalAction = new QAction(QIcon("mirrorVertical.png"), tr("纵向镜像"), this);
    mirrorVerticalAction->setToolTip (tr("对一张图做纵向镜像"));

    mirrorHorizontalAction = new QAction(QIcon("mirrorHorizontal.png"), tr("横向镜像"), this);
    mirrorHorizontalAction->setToolTip (tr("对一张图做横向镜像"));

    undoAction = new QAction(QIcon("undo.png"), tr("撤销"), this);
    connect (undoAction, &QAction::triggered, showWidget->text, &QTextEdit::undo);

    redoAction = new QAction(QIcon("redo.png"), tr("重做"), this);
    connect (redoAction, &QAction::triggered, showWidget->text, &QTextEdit::redo);
}

void ImgProcessor::createMenus()
{
    fileMenu = menuBar ()->addMenu (tr("文件"));
    fileMenu->addAction (openFileAction);
    fileMenu->addAction (newFileAction);
    fileMenu->addAction (printTextAction);
    fileMenu->addAction (printImageAction);
    fileMenu->addSeparator ();
    fileMenu->addAction (exitAction);

    zoomMenu = menuBar ()->addMenu (tr("编辑"));
    zoomMenu->addAction (copyAction);
    zoomMenu->addAction (cutAction);
    zoomMenu->addAction (pasteAction);
    zoomMenu->addAction (aboutAction);
    zoomMenu->addSeparator ();
    zoomMenu->addAction (zoomInAction);
    zoomMenu->addAction (zoomOutAction);

    rotateMenu = menuBar ()->addMenu (tr("旋转"));
    rotateMenu->addAction (rotate90Action);
    rotateMenu->addAction (rotate180Action);
    rotateMenu->addAction (rotate270Action);

    mirrorMenu = menuBar ()->addMenu (tr("镜像"));
    mirrorMenu->addAction (mirrorVerticalAction);
    mirrorMenu->addAction (mirrorHorizontalAction);
}

void ImgProcessor::createToolBars()
{
    fileTool = addToolBar ("File");
    fileTool->addAction (openFileAction);
    fileTool->addAction (newFileAction);
    fileTool->addAction (printTextAction);
    fileTool->addAction (printImageAction);
    fileTool->setAllowedAreas (Qt::TopToolBarArea | Qt::RightToolBarArea | Qt::LeftToolBarArea);

    zoomTool = addToolBar ("Edit");
    zoomTool->addAction (copyAction);
    zoomTool->addAction (cutAction);
    zoomTool->addAction (pasteAction);
    zoomTool->addSeparator ();
    zoomTool->addAction (zoomInAction);
    zoomTool->addAction (zoomOutAction);

    rotateTool = addToolBar ("rotate");
    rotateTool->addAction (rotate90Action);
    rotateTool->addAction (rotate180Action);
    rotateTool->addAction (rotate270Action);

    doToolBar = addToolBar ("doEdit");
    doToolBar->addAction (undoAction);
    doToolBar->addAction (redoAction);
    doToolBar->setMovable (false);
}

void ImgProcessor::ShowNewFile ()
{
    ImgProcessor *newImgProcessor = new ImgProcessor;
    newImgProcessor->show ();
}

void ImgProcessor::ShowOpenFile ()
{
    filename = QFileDialog::getOpenFileName (this);
    if (!filename.isEmpty ())
    {
        if (showWidget->text->document ()->isEmpty ())
        {
            loadFile (filename);
        }
        else
        {
            ImgProcessor *newImgProcessor = new ImgProcessor;
            newImgProcessor->show ();
            newImgProcessor->loadFile (filename);
        }
    }
}

void ImgProcessor::loadFile(QString filename)
{
    printf ("file name:%s\n", filename.data ());

    QFile file(filename);
    if (file.open (QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream textStream(&file);
        while (!textStream.atEnd ())
        {
            showWidget->text->append (textStream.readLine ());
            printf ("read line\n");
        }
        printf ("end\n");
    }
}

void ImgProcessor::ShowPrintText ()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec())
    {
        QTextDocument *doc = showWidget->text->document ();
        doc->print (&printer);
    }
}

void ImgProcessor::ShowPrintImage ()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec ())
    {
        QPainter painter(&printer);
        QRect rect = painter.viewport ();
        QSize size = img.size ();
        size.scale (rect.size (), Qt::KeepAspectRatio);

        painter.setViewport (rect.x (), rect.y (), size.width (), size.height ());
        painter.setWindow (img.rect ());
        painter.drawImage (0, 0, img);
    }
}


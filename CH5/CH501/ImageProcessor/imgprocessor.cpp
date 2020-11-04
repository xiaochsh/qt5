#include "imgprocessor.h"
#include <QApplication>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QPainter>
#include <QMatrix>
#include <QFontDatabase>
#include <QString>
#include <QColor>
#include <QColorDialog>
#include <QActionGroup>
#include <QTextList>

ImgProcessor::ImgProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle (tr("Easy Word"));

    showWidget = new ShowWidget(this);
    setCentralWidget (showWidget);

    fontLabel1 = new QLabel(tr("字体："));
    fontComboBox = new QFontComboBox;
    fontComboBox->setFontFilters (QFontComboBox::ScalableFonts);

    fontLabel2 = new QLabel(tr("字号:"));
    sizeComboBox = new QComboBox;
    QFontDatabase db;
    foreach (int size, db.standardSizes ())
    {
        sizeComboBox->addItem (QString::number (size));
    }

    boldBtn = new QToolButton;
    boldBtn->setIcon (QIcon("bold.png"));
    boldBtn->setCheckable (true);

    italicBtn = new QToolButton;
    italicBtn->setIcon (QIcon("italic.png"));
    italicBtn->setCheckable (true);

    underlineBtn = new QToolButton;
    underlineBtn->setIcon (QIcon("underline.png"));
    underlineBtn->setCheckable (true);

    colorBtn = new QToolButton;
    colorBtn->setIcon (QIcon("color.png"));
    colorBtn->setCheckable (true);

    listLabel = new QLabel(tr("排序"));
    listComboBox = new QComboBox;
    listComboBox->addItem ("Standard");
    listComboBox->addItem ("QTextListFormat::ListDisc");
    listComboBox->addItem ("QTextListFormat::ListCircle");
    listComboBox->addItem ("QTextListFormat::ListSquare");
    listComboBox->addItem ("QTextListFormat::ListDecimal");
    listComboBox->addItem ("QTextListFormat::ListLowerAlpha");
    listComboBox->addItem ("QTextListFormat::ListUpperAlpha");
    listComboBox->addItem ("QTextListFormat::ListLowerRoman");
    listComboBox->addItem ("QTextListFormat::ListUpperRoman");

    createActions ();
    createMenus ();
    createToolBars ();

    if (img.load ("image.png"))
    {
        showWidget->imageLabel->setPixmap (QPixmap::fromImage (img));
    }

    connect(fontComboBox, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::activated), this, &ImgProcessor::ShowFontComboBox);
    connect(sizeComboBox, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::activated), this, &ImgProcessor::ShowSizeSpinBox);
    connect(boldBtn, &QToolButton::clicked, this, &ImgProcessor::ShowBoldBtn);
    connect(italicBtn, &QToolButton::clicked, this, &ImgProcessor::ShowItalicBtn);
    connect(underlineBtn, &QToolButton::clicked, this, &ImgProcessor::ShowUnderlineBtn);
    connect(colorBtn, &QToolButton::clicked, this, &ImgProcessor::ShowColorBtn);
    connect(showWidget->text, static_cast<void (QTextEdit::*)(const QTextCharFormat &)>(&QTextEdit::currentCharFormatChanged), this, &ImgProcessor::ShowCurrentFormatChangerd);

    connect(listComboBox, static_cast<void (QComboBox::*) (int)> (&QComboBox::activated), this, &ImgProcessor::ShowList);
    connect(showWidget->text->document (), SIGNAL(undoAvailable(bool)), undoAction, SLOT(setChecked(bool)));
    connect(showWidget->text->document (), SIGNAL(redoAvailable(bool)), redoAction, SLOT(setChecked(bool)));
    connect(showWidget->text, &QTextEdit::cursorPositionChanged, this, &ImgProcessor::ShowCursorPositionChanged);

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
    connect (zoomInAction, &QAction::triggered, this, &ImgProcessor::ShowZoomIn);

    zoomOutAction = new QAction(QIcon("zoomout.png"), tr("缩小"), this);
    zoomOutAction->setToolTip (tr("缩小一张图片"));
    connect (zoomOutAction, &QAction::triggered, this, &ImgProcessor::ShowZoomOut);

    rotate90Action = new QAction(QIcon("rotate90.png"), tr("旋转90°"), this);
    rotate90Action->setToolTip (tr("将一幅图旋转90°"));
    connect (rotate90Action, &QAction::triggered, this, &ImgProcessor::ShowRotate90);

    rotate180Action = new QAction(QIcon("rotate180.png"), tr("旋转180°"), this);
    rotate180Action->setToolTip (tr("将一幅图旋转180°"));
    connect (rotate180Action, &QAction::triggered, this, &ImgProcessor::ShowRotate180);

    rotate270Action = new QAction(QIcon("rotate270.png"), tr("旋转270°"), this);
    rotate270Action->setToolTip (tr("将一幅图旋转270°"));
    connect (rotate270Action, &QAction::triggered, this, &ImgProcessor::ShowRotate270);

    mirrorVerticalAction = new QAction(QIcon("mirrorVertical.png"), tr("纵向镜像"), this);
    mirrorVerticalAction->setToolTip (tr("对一张图做纵向镜像"));
    connect (mirrorVerticalAction, &QAction::triggered, this, &ImgProcessor::ShowMirrorVertical);

    mirrorHorizontalAction = new QAction(QIcon("mirrorHorizontal.png"), tr("横向镜像"), this);
    mirrorHorizontalAction->setToolTip (tr("对一张图做横向镜像"));
    connect (mirrorHorizontalAction, &QAction::triggered, this, &ImgProcessor::ShowMirrorHorizontal);

    undoAction = new QAction(QIcon("undo.png"), tr("撤销"), this);
    connect (undoAction, &QAction::triggered, showWidget->text, &QTextEdit::undo);

    redoAction = new QAction(QIcon("redo.png"), tr("重做"), this);
    connect (redoAction, &QAction::triggered, showWidget->text, &QTextEdit::redo);

    actionGroup = new QActionGroup(this);

    leftAction = new QAction(QIcon("left.png"), "左对齐", actionGroup);
    leftAction->setCheckable (true);

    rightAction = new QAction(QIcon("right.png"), "右对齐", actionGroup);
    rightAction->setCheckable (true);

    centerAction = new QAction(QIcon("center.png"), "居中", actionGroup);
    centerAction->setCheckable (true);

    justifyAction = new QAction(QIcon("justify.png"), "两端对齐", actionGroup);
    justifyAction->setCheckable (true);

    connect (actionGroup, static_cast<void (QActionGroup::*) (QAction *)> (&QActionGroup::triggered), this, &ImgProcessor::ShowAlignment);
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

    fontToolBar = addToolBar ("Font");
    fontToolBar->addWidget (fontLabel1);
    fontToolBar->addWidget (fontComboBox);
    fontToolBar->addWidget (fontLabel2);
    fontToolBar->addWidget (sizeComboBox);
    fontToolBar->addSeparator ();
    fontToolBar->addWidget (boldBtn);
    fontToolBar->addWidget (italicBtn);
    fontToolBar->addWidget (underlineBtn);
    fontToolBar->addSeparator ();
    fontToolBar->addWidget (colorBtn);

    this->addToolBarBreak(Qt::TopToolBarArea);

    listToolBar = addToolBar ("list");
    listToolBar->addWidget (listLabel);
    listToolBar->addWidget (listComboBox);
    listToolBar->addSeparator ();
    listToolBar->addActions (actionGroup->actions ());
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

void ImgProcessor::ShowZoomIn ()
{
    if (img.isNull ())
        return;
    QMatrix matrix;
    matrix.scale (2, 2);
    img = img.transformed (matrix);
    showWidget->imageLabel->setPixmap (QPixmap::fromImage (img));
}

void ImgProcessor::ShowZoomOut ()
{
    if (img.isNull ())
        return;
    QMatrix matrix;
    matrix.scale (0.5, 0.5);
    img = img.transformed (matrix);
    showWidget->imageLabel->setPixmap (QPixmap::fromImage (img));
}

void ImgProcessor::ShowRotate90 ()
{
    if (img.isNull ())
        return;
    QMatrix matrix;
    matrix.rotate (90);
    img = img.transformed (matrix);
    showWidget->imageLabel->setPixmap (QPixmap::fromImage (img));
}

void ImgProcessor::ShowRotate180 ()
{
    if (img.isNull ())
        return;
    QMatrix matrix;
    matrix.rotate (180);
    img = img.transformed (matrix);
    showWidget->imageLabel->setPixmap (QPixmap::fromImage (img));
}

void ImgProcessor::ShowRotate270 ()
{
    if (img.isNull ())
        return;
    QMatrix matrix;
    matrix.rotate (270);
    img = img.transformed (matrix);
    showWidget->imageLabel->setPixmap (QPixmap::fromImage (img));
}

void ImgProcessor::ShowMirrorVertical ()
{
    if (img.isNull ())
        return;
    img = img.mirrored (false, true); // mirrored(x_flag, y_flag)
    showWidget->imageLabel->setPixmap (QPixmap::fromImage (img));
}

void ImgProcessor::ShowMirrorHorizontal ()
{
    if (img.isNull ())
        return;
    img = img.mirrored (true, false);
    showWidget->imageLabel->setPixmap (QPixmap::fromImage (img));
}

void ImgProcessor::ShowFontComboBox (QString comboStr)
{
    QTextCharFormat fmt;
    fmt.setFontFamily (comboStr);
    mergeFormat (fmt);
}

void ImgProcessor::mergeFormat(QTextCharFormat format)
{
    QTextCursor cursor = showWidget->text->textCursor ();
    if (!cursor.hasSelection ())
        cursor.select (QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat (format);
    showWidget->text->mergeCurrentCharFormat (format);
}

void ImgProcessor::ShowSizeSpinBox (QString spinValue)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize (spinValue.toFloat ());
    showWidget->text->mergeCurrentCharFormat (fmt);
}

void ImgProcessor::ShowBoldBtn ()
{
    QTextCharFormat fmt;
    fmt.setFontWeight (boldBtn->isChecked () ? QFont::Bold : QFont::Normal);
    showWidget->text->mergeCurrentCharFormat (fmt);
}

void ImgProcessor::ShowItalicBtn ()
{
    QTextCharFormat fmt;
    fmt.setFontItalic (italicBtn->isChecked ());
    showWidget->text->mergeCurrentCharFormat (fmt);
}

void ImgProcessor::ShowUnderlineBtn ()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline (underlineBtn->isChecked ());
    showWidget->text->mergeCurrentCharFormat (fmt);
}

void ImgProcessor::ShowColorBtn ()
{
    QColor color = QColorDialog::getColor (Qt::red, this);
    if (color.isValid ())
    {
        QTextCharFormat fmt;
        fmt.setForeground (color);
        showWidget->text->mergeCurrentCharFormat (fmt);
    }
}

void ImgProcessor::ShowCurrentFormatChangerd (const QTextCharFormat & fmt)
{
    fontComboBox->setCurrentIndex (fontComboBox->findText (fmt.fontFamily ()));
    sizeComboBox->setCurrentIndex (sizeComboBox->findText (QString::number (fmt.fontPointSize ())));
    boldBtn->setChecked (fmt.font ().bold ());
    italicBtn->setChecked (fmt.fontItalic ());
    underlineBtn->setChecked (fmt.fontUnderline ());
}

void ImgProcessor::ShowAlignment (QAction *act)
{
    if (act == leftAction)
        showWidget->text->setAlignment (Qt::AlignLeft);
    if (act == rightAction)
        showWidget->text->setAlignment (Qt::AlignRight);
    if (act == centerAction)
        showWidget->text->setAlignment (Qt::AlignCenter);
    if (act == justifyAction)
        showWidget->text->setAlignment (Qt::AlignJustify);
}

void ImgProcessor::ShowCursorPositionChanged ()
{
    if (showWidget->text->alignment () == Qt::AlignLeft)
        leftAction->setChecked (true);
    if (showWidget->text->alignment () == Qt::AlignRight)
        rightAction->setChecked (true);
    if (showWidget->text->alignment () == Qt::AlignCenter)
        centerAction->setChecked (true);
    if (showWidget->text->alignment () == Qt::AlignJustify)
        justifyAction->setChecked (true);
}

void ImgProcessor::ShowList (int index)
{
    QTextCursor cursor = showWidget->text->textCursor ();

    if (index != 0)
    {
        QTextListFormat::Style style = QTextListFormat::ListDisc;
        switch (index)
        {
        default:
        case 1:
            style = QTextListFormat::ListDisc; break;
        case 2:
            style = QTextListFormat::ListCircle; break;
        case 3:
            style = QTextListFormat::ListSquare; break;
        case 4:
            style = QTextListFormat::ListDecimal; break;
        case 5:
            style = QTextListFormat::ListLowerAlpha; break;
        case 6:
            style = QTextListFormat::ListUpperAlpha; break;
        case 7:
            style = QTextListFormat::ListLowerRoman; break;
        case 8:
            style = QTextListFormat::ListUpperRoman; break;
        }
        cursor.beginEditBlock ();

        QTextBlockFormat blockFmt = cursor.blockFormat ();
        QTextListFormat listFmt;

        if (cursor.currentList ())
        {
            listFmt = cursor.currentList ()->format();
        }
        else
        {
            listFmt.setIndent (blockFmt.indent () + 1);
            blockFmt.setIndent (0);
            cursor.setBlockFormat (blockFmt);
        }
        listFmt.setStyle (style);
        cursor.createList (listFmt);

        cursor.endEditBlock ();
    }
    else
    {
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex (-1);
        cursor.mergeBlockFormat (bfmt);
    }
}

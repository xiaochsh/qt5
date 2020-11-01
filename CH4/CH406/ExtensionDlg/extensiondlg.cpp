#include "extensiondlg.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QLabel>

ExtensionDlg::ExtensionDlg(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Extension Dialog"));

    createBaseInfo();
    createDetailInfo();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(baseWidget);
    layout->addWidget(detailWidget);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setSpacing(10);
}

ExtensionDlg::~ExtensionDlg()
{
}

void ExtensionDlg::createBaseInfo()
{
    baseWidget = new QWidget;

    QLabel *nameLabel = new QLabel(tr("姓名："));
    QLineEdit *nameLineEdit = new QLineEdit;

    QLabel *sexLabel = new QLabel(tr("性别："));
    QComboBox *sexComboBox = new QComboBox;
    sexComboBox->insertItem(0, tr("女"));
    sexComboBox->insertItem(1, tr("男"));

    QGridLayout *leftLayout = new QGridLayout;
    leftLayout->addWidget(nameLabel, 0, 0);
    leftLayout->addWidget(nameLineEdit, 0, 1);
    leftLayout->addWidget(sexLabel, 1, 0);
    leftLayout->addWidget(sexComboBox, 1, 1);

    QPushButton *OkBtn = new QPushButton(tr("确定"));
    QPushButton *DetailBtn = new QPushButton(tr("详细"));
    QDialogButtonBox *btnBox = new QDialogButtonBox(Qt::Vertical);
    btnBox->addButton(OkBtn, QDialogButtonBox::ActionRole);
    btnBox->addButton(DetailBtn, QDialogButtonBox::ActionRole);

    QHBoxLayout *mainLayout = new QHBoxLayout(baseWidget);
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(btnBox);
    connect(DetailBtn, &QPushButton::clicked, this, &ExtensionDlg::showDetailInfo);
}

void ExtensionDlg::createDetailInfo()
{
    detailWidget = new QWidget;

    QLabel *ageLabel = new QLabel(tr("年龄："));
    QLineEdit *ageLineEdit = new QLineEdit;
    ageLineEdit->setText(tr("30"));

    QLabel *departmentLabel = new QLabel(tr("部门："));
    QComboBox *departmentComboBox = new QComboBox;
    departmentComboBox->addItem(tr("部门1"));
    departmentComboBox->addItem(tr("部门2"));
    departmentComboBox->addItem(tr("部门3"));
    departmentComboBox->addItem(tr("部门4"));

    QLabel *emailLabel = new QLabel(tr("email："));
    QLineEdit *emailLineEdit = new QLineEdit;

    QGridLayout *mainLayout = new QGridLayout(detailWidget);
    mainLayout->addWidget(ageLabel, 0, 0);
    mainLayout->addWidget(ageLineEdit, 0, 1);
    mainLayout->addWidget(departmentLabel, 1, 0);
    mainLayout->addWidget(departmentComboBox, 1, 1);
    mainLayout->addWidget(emailLabel, 2, 0);
    mainLayout->addWidget(emailLineEdit, 2, 1);

    detailWidget->hide();
}

void ExtensionDlg::showDetailInfo()
{
    if (detailWidget->isHidden())
    {
        detailWidget->show();
    }
    else {
        detailWidget->hide();
    }
}

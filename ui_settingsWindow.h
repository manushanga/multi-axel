/********************************************************************************
** Form generated from reading UI file 'settingsWindow.ui'
**
** Created: Sun May 13 21:42:12 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSWINDOW_H
#define UI_SETTINGSWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_settingsWindow
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *outputDirectoryLabel;
    QLineEdit *outputDirectoryLineEdit;
    QLabel *maxSpeedLabel;
    QLineEdit *maxSpeedLineEdit;
    QLabel *maxConnectionsLabel;
    QLineEdit *maxConnectionsLineEdit;
    QLabel *proxyLabel;
    QLineEdit *proxyLineEdit;
    QLabel *userAgentLabel;
    QLineEdit *userAgentLineEdit;
    QDialogButtonBox *pbBox;

    void setupUi(QDialog *settingsWindow)
    {
        if (settingsWindow->objectName().isEmpty())
            settingsWindow->setObjectName(QString::fromUtf8("settingsWindow"));
        settingsWindow->resize(652, 205);
        settingsWindow->setMaximumSize(QSize(16777215, 205));
        formLayout = new QFormLayout(settingsWindow);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        label = new QLabel(settingsWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 17));

        formLayout->setWidget(0, QFormLayout::SpanningRole, label);

        outputDirectoryLabel = new QLabel(settingsWindow);
        outputDirectoryLabel->setObjectName(QString::fromUtf8("outputDirectoryLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, outputDirectoryLabel);

        outputDirectoryLineEdit = new QLineEdit(settingsWindow);
        outputDirectoryLineEdit->setObjectName(QString::fromUtf8("outputDirectoryLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, outputDirectoryLineEdit);

        maxSpeedLabel = new QLabel(settingsWindow);
        maxSpeedLabel->setObjectName(QString::fromUtf8("maxSpeedLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, maxSpeedLabel);

        maxSpeedLineEdit = new QLineEdit(settingsWindow);
        maxSpeedLineEdit->setObjectName(QString::fromUtf8("maxSpeedLineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, maxSpeedLineEdit);

        maxConnectionsLabel = new QLabel(settingsWindow);
        maxConnectionsLabel->setObjectName(QString::fromUtf8("maxConnectionsLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, maxConnectionsLabel);

        maxConnectionsLineEdit = new QLineEdit(settingsWindow);
        maxConnectionsLineEdit->setObjectName(QString::fromUtf8("maxConnectionsLineEdit"));

        formLayout->setWidget(4, QFormLayout::FieldRole, maxConnectionsLineEdit);

        proxyLabel = new QLabel(settingsWindow);
        proxyLabel->setObjectName(QString::fromUtf8("proxyLabel"));

        formLayout->setWidget(5, QFormLayout::LabelRole, proxyLabel);

        proxyLineEdit = new QLineEdit(settingsWindow);
        proxyLineEdit->setObjectName(QString::fromUtf8("proxyLineEdit"));

        formLayout->setWidget(5, QFormLayout::FieldRole, proxyLineEdit);

        userAgentLabel = new QLabel(settingsWindow);
        userAgentLabel->setObjectName(QString::fromUtf8("userAgentLabel"));

        formLayout->setWidget(6, QFormLayout::LabelRole, userAgentLabel);

        userAgentLineEdit = new QLineEdit(settingsWindow);
        userAgentLineEdit->setObjectName(QString::fromUtf8("userAgentLineEdit"));

        formLayout->setWidget(6, QFormLayout::FieldRole, userAgentLineEdit);

        pbBox = new QDialogButtonBox(settingsWindow);
        pbBox->setObjectName(QString::fromUtf8("pbBox"));
        pbBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(7, QFormLayout::FieldRole, pbBox);


        retranslateUi(settingsWindow);

        QMetaObject::connectSlotsByName(settingsWindow);
    } // setupUi

    void retranslateUi(QDialog *settingsWindow)
    {
        settingsWindow->setWindowTitle(QApplication::translate("settingsWindow", "settingsWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("settingsWindow", "Note: Leaving empty will make multi-axel use the default setting for the field left blank.", 0, QApplication::UnicodeUTF8));
        outputDirectoryLabel->setText(QApplication::translate("settingsWindow", "Output directory", 0, QApplication::UnicodeUTF8));
        maxSpeedLabel->setText(QApplication::translate("settingsWindow", "Max speed", 0, QApplication::UnicodeUTF8));
        maxConnectionsLabel->setText(QApplication::translate("settingsWindow", "Max connections", 0, QApplication::UnicodeUTF8));
        proxyLabel->setText(QApplication::translate("settingsWindow", "Proxy\n"
"(user:pass@host:port)", 0, QApplication::UnicodeUTF8));
        userAgentLabel->setText(QApplication::translate("settingsWindow", "User agent", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class settingsWindow: public Ui_settingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWINDOW_H

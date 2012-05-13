/********************************************************************************
** Form generated from reading UI file 'aboutWindow.ui'
**
** Created: Sun May 13 13:59:01 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTWINDOW_H
#define UI_ABOUTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QString::fromUtf8("About"));
        About->resize(361, 282);
        gridLayout = new QGridLayout(About);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(About);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 3, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(About);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2, 0, Qt::AlignTop);


        gridLayout->addLayout(verticalLayout, 2, 0, 1, 1);

        label = new QLabel(About);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 17));
        label->setTextFormat(Qt::RichText);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(About);
        QObject::connect(pushButton, SIGNAL(clicked()), About, SLOT(accept()));

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QApplication::translate("About", "aboutWindow", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("About", "Close", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("About", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Developer</span></p><p align=\"center\">Madura A. (madura.x86@gmail.com)</p><p align=\"center\"><span style=\" font-weight:600;\">License</span></p><p align=\"center\">GPL v2</p><p align=\"center\"><span style=\" font-weight:600;\">Git</span></p><p align=\"center\"><a href=\"https://github.com/madurax86/multi-axel\"><span style=\" text-decoration: underline; color:#0057ae;\">https://github.com/madurax86/multi-axel</span></a></p><p align=\"center\"><span style=\" font-weight:600;\">Copyright</span></p><p align=\"center\">(C) 2012 Madura A.</p></body></html>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("About", "<html><head/><body><p align=\"center\">A GUI front end for <span style=\" font-weight:600;\">multi</span>ple <span style=\" font-weight:600;\">axel</span> processes</p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTWINDOW_H

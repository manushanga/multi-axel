/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created: Sun Jul 1 17:09:10 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QAction *actionQuit;
    QAction *actionNew_Download;
    QAction *actionAbout;
    QAction *actionSettings;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTreeView *lstDownloads;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbAdd;
    QPushButton *pbStart;
    QPushButton *pbStop;
    QPushButton *pbRemove;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QMenu *menuSettings;

    void setupUi(QMainWindow *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName(QString::fromUtf8("mainWindow"));
        mainWindow->resize(389, 384);
        actionQuit = new QAction(mainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionNew_Download = new QAction(mainWindow);
        actionNew_Download->setObjectName(QString::fromUtf8("actionNew_Download"));
        actionAbout = new QAction(mainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionSettings = new QAction(mainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        centralwidget = new QWidget(mainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lstDownloads = new QTreeView(centralwidget);
        lstDownloads->setObjectName(QString::fromUtf8("lstDownloads"));
        lstDownloads->setRootIsDecorated(false);
        lstDownloads->setExpandsOnDoubleClick(false);

        verticalLayout->addWidget(lstDownloads);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pbAdd = new QPushButton(centralwidget);
        pbAdd->setObjectName(QString::fromUtf8("pbAdd"));

        horizontalLayout->addWidget(pbAdd);

        pbStart = new QPushButton(centralwidget);
        pbStart->setObjectName(QString::fromUtf8("pbStart"));
        pbStart->setFlat(false);

        horizontalLayout->addWidget(pbStart);

        pbStop = new QPushButton(centralwidget);
        pbStop->setObjectName(QString::fromUtf8("pbStop"));

        horizontalLayout->addWidget(pbStop);

        pbRemove = new QPushButton(centralwidget);
        pbRemove->setObjectName(QString::fromUtf8("pbRemove"));

        horizontalLayout->addWidget(pbRemove);


        verticalLayout->addLayout(horizontalLayout);

        mainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 389, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        mainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionNew_Download);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuAbout->addAction(actionAbout);
        menuSettings->addAction(actionSettings);

        retranslateUi(mainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), mainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindow)
    {
        mainWindow->setWindowTitle(QApplication::translate("mainWindow", "Multi Axel", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("mainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionNew_Download->setText(QApplication::translate("mainWindow", "New Download", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("mainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("mainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        pbAdd->setText(QApplication::translate("mainWindow", "Add", 0, QApplication::UnicodeUTF8));
        pbStart->setText(QApplication::translate("mainWindow", "Start/Resume", 0, QApplication::UnicodeUTF8));
        pbStop->setText(QApplication::translate("mainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        pbRemove->setText(QApplication::translate("mainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("mainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("mainWindow", "Help", 0, QApplication::UnicodeUTF8));
        menuSettings->setTitle(QApplication::translate("mainWindow", "Options", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

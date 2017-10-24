/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *openPushButton;
    QPushButton *savePushButton;
    QPushButton *setPushButton;
    QPushButton *redoPushButton;
    QLabel *frameshowLabel;
    QPushButton *contourModelPushButton;
    QPushButton *undoPushButton;
    QPushButton *autoPushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(660, 573);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 8);

        openPushButton = new QPushButton(centralWidget);
        openPushButton->setObjectName(QStringLiteral("openPushButton"));

        gridLayout->addWidget(openPushButton, 1, 1, 1, 1);

        savePushButton = new QPushButton(centralWidget);
        savePushButton->setObjectName(QStringLiteral("savePushButton"));

        gridLayout->addWidget(savePushButton, 1, 3, 1, 1);

        setPushButton = new QPushButton(centralWidget);
        setPushButton->setObjectName(QStringLiteral("setPushButton"));

        gridLayout->addWidget(setPushButton, 1, 0, 1, 1);

        redoPushButton = new QPushButton(centralWidget);
        redoPushButton->setObjectName(QStringLiteral("redoPushButton"));

        gridLayout->addWidget(redoPushButton, 1, 4, 1, 1);

        frameshowLabel = new QLabel(centralWidget);
        frameshowLabel->setObjectName(QStringLiteral("frameshowLabel"));

        gridLayout->addWidget(frameshowLabel, 1, 7, 1, 1);

        contourModelPushButton = new QPushButton(centralWidget);
        contourModelPushButton->setObjectName(QStringLiteral("contourModelPushButton"));

        gridLayout->addWidget(contourModelPushButton, 1, 6, 1, 1);

        undoPushButton = new QPushButton(centralWidget);
        undoPushButton->setObjectName(QStringLiteral("undoPushButton"));

        gridLayout->addWidget(undoPushButton, 1, 5, 1, 1);

        autoPushButton = new QPushButton(centralWidget);
        autoPushButton->setObjectName(QStringLiteral("autoPushButton"));

        gridLayout->addWidget(autoPushButton, 1, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 660, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QString());
        openPushButton->setText(QApplication::translate("MainWindow", "Open", 0));
        savePushButton->setText(QApplication::translate("MainWindow", "Save", 0));
        setPushButton->setText(QApplication::translate("MainWindow", "Set", 0));
        redoPushButton->setText(QApplication::translate("MainWindow", "Redo", 0));
        frameshowLabel->setText(QString());
        contourModelPushButton->setText(QApplication::translate("MainWindow", "Poly", 0));
        undoPushButton->setText(QApplication::translate("MainWindow", "Undo", 0));
        autoPushButton->setText(QApplication::translate("MainWindow", "Manual", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

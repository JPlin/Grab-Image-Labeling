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
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushShowOriginButton;
    QPushButton *pushSkinButton;
    QPushButton *openPushButton;
    QPushButton *pushLBrowButton;
    QPushButton *pushLEyeButton;
    QPushButton *pushShowMaskButton;
    QPushButton *pushRBrowButton;
    QPushButton *contourModelPushButton;
    QPushButton *pushMouthButton;
    QLabel *label;
    QPushButton *redoPushButton;
    QPushButton *setPushButton;
    QPushButton *pushLEarButton;
    QPushButton *pushREarButton;
    QPushButton *pushREyeButton;
    QPushButton *pushNoseButton;
    QPushButton *undoPushButton;
    QPushButton *autoPushButton;
    QPushButton *savePushButton;
    QLabel *frameshowLabel;
    QPushButton *pushMixButton;
    QScrollBar *horizontalScrollBar;
    QSlider *horizontalSlider;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(662, 648);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushShowOriginButton = new QPushButton(centralWidget);
        pushShowOriginButton->setObjectName(QStringLiteral("pushShowOriginButton"));

        gridLayout->addWidget(pushShowOriginButton, 0, 1, 1, 1);

        pushSkinButton = new QPushButton(centralWidget);
        pushSkinButton->setObjectName(QStringLiteral("pushSkinButton"));

        gridLayout->addWidget(pushSkinButton, 0, 7, 1, 1);

        openPushButton = new QPushButton(centralWidget);
        openPushButton->setObjectName(QStringLiteral("openPushButton"));

        gridLayout->addWidget(openPushButton, 4, 1, 1, 1);

        pushLBrowButton = new QPushButton(centralWidget);
        pushLBrowButton->setObjectName(QStringLiteral("pushLBrowButton"));

        gridLayout->addWidget(pushLBrowButton, 2, 0, 1, 1);

        pushLEyeButton = new QPushButton(centralWidget);
        pushLEyeButton->setObjectName(QStringLiteral("pushLEyeButton"));

        gridLayout->addWidget(pushLEyeButton, 2, 2, 1, 1);

        pushShowMaskButton = new QPushButton(centralWidget);
        pushShowMaskButton->setObjectName(QStringLiteral("pushShowMaskButton"));

        gridLayout->addWidget(pushShowMaskButton, 0, 0, 1, 1);

        pushRBrowButton = new QPushButton(centralWidget);
        pushRBrowButton->setObjectName(QStringLiteral("pushRBrowButton"));

        gridLayout->addWidget(pushRBrowButton, 2, 1, 1, 1);

        contourModelPushButton = new QPushButton(centralWidget);
        contourModelPushButton->setObjectName(QStringLiteral("contourModelPushButton"));

        gridLayout->addWidget(contourModelPushButton, 4, 6, 1, 1);

        pushMouthButton = new QPushButton(centralWidget);
        pushMouthButton->setObjectName(QStringLiteral("pushMouthButton"));

        gridLayout->addWidget(pushMouthButton, 2, 5, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(640, 480));
        label->setSizeIncrement(QSize(1, 1));

        gridLayout->addWidget(label, 3, 0, 1, 8);

        redoPushButton = new QPushButton(centralWidget);
        redoPushButton->setObjectName(QStringLiteral("redoPushButton"));

        gridLayout->addWidget(redoPushButton, 4, 4, 1, 1);

        setPushButton = new QPushButton(centralWidget);
        setPushButton->setObjectName(QStringLiteral("setPushButton"));

        gridLayout->addWidget(setPushButton, 4, 0, 1, 1);

        pushLEarButton = new QPushButton(centralWidget);
        pushLEarButton->setObjectName(QStringLiteral("pushLEarButton"));

        gridLayout->addWidget(pushLEarButton, 2, 6, 1, 1);

        pushREarButton = new QPushButton(centralWidget);
        pushREarButton->setObjectName(QStringLiteral("pushREarButton"));

        gridLayout->addWidget(pushREarButton, 2, 7, 1, 1);

        pushREyeButton = new QPushButton(centralWidget);
        pushREyeButton->setObjectName(QStringLiteral("pushREyeButton"));

        gridLayout->addWidget(pushREyeButton, 2, 3, 1, 1);

        pushNoseButton = new QPushButton(centralWidget);
        pushNoseButton->setObjectName(QStringLiteral("pushNoseButton"));

        gridLayout->addWidget(pushNoseButton, 2, 4, 1, 1);

        undoPushButton = new QPushButton(centralWidget);
        undoPushButton->setObjectName(QStringLiteral("undoPushButton"));
        undoPushButton->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(undoPushButton, 4, 5, 1, 1);

        autoPushButton = new QPushButton(centralWidget);
        autoPushButton->setObjectName(QStringLiteral("autoPushButton"));

        gridLayout->addWidget(autoPushButton, 4, 2, 1, 1);

        savePushButton = new QPushButton(centralWidget);
        savePushButton->setObjectName(QStringLiteral("savePushButton"));

        gridLayout->addWidget(savePushButton, 4, 3, 1, 1);

        frameshowLabel = new QLabel(centralWidget);
        frameshowLabel->setObjectName(QStringLiteral("frameshowLabel"));

        gridLayout->addWidget(frameshowLabel, 4, 7, 1, 1);

        pushMixButton = new QPushButton(centralWidget);
        pushMixButton->setObjectName(QStringLiteral("pushMixButton"));

        gridLayout->addWidget(pushMixButton, 0, 6, 1, 1);

        horizontalScrollBar = new QScrollBar(centralWidget);
        horizontalScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
        horizontalScrollBar->setMinimum(4);
        horizontalScrollBar->setMaximum(150);
        horizontalScrollBar->setSingleStep(5);
        horizontalScrollBar->setValue(50);
        horizontalScrollBar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalScrollBar, 1, 2, 1, 2);

        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMinimum(0);
        horizontalSlider->setMaximum(100);
        horizontalSlider->setPageStep(5);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 1, 5, 1, 2);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setEnabled(true);

        gridLayout->addWidget(label_2, 1, 4, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 662, 21));
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
        pushShowOriginButton->setText(QApplication::translate("MainWindow", "ShowOrigin", 0));
        pushSkinButton->setText(QApplication::translate("MainWindow", "ShowSkin", 0));
        openPushButton->setText(QApplication::translate("MainWindow", "Open", 0));
        pushLBrowButton->setText(QApplication::translate("MainWindow", "LeftBrow", 0));
        pushLEyeButton->setText(QApplication::translate("MainWindow", "LeftEye", 0));
        pushShowMaskButton->setText(QApplication::translate("MainWindow", "ShowMask", 0));
        pushRBrowButton->setText(QApplication::translate("MainWindow", "RightBrow", 0));
        contourModelPushButton->setText(QApplication::translate("MainWindow", "Poly", 0));
        pushMouthButton->setText(QApplication::translate("MainWindow", "Mouth", 0));
        label->setText(QString());
        redoPushButton->setText(QApplication::translate("MainWindow", "Redo", 0));
        setPushButton->setText(QApplication::translate("MainWindow", "Set", 0));
        pushLEarButton->setText(QApplication::translate("MainWindow", "LeftEar", 0));
        pushREarButton->setText(QApplication::translate("MainWindow", "RightEar", 0));
        pushREyeButton->setText(QApplication::translate("MainWindow", "RightEye", 0));
        pushNoseButton->setText(QApplication::translate("MainWindow", "Nose", 0));
        undoPushButton->setText(QApplication::translate("MainWindow", "Undo", 0));
        autoPushButton->setText(QApplication::translate("MainWindow", "Manual", 0));
        savePushButton->setText(QApplication::translate("MainWindow", "Save", 0));
        frameshowLabel->setText(QString());
        pushMixButton->setText(QApplication::translate("MainWindow", "MixButton", 0));
        label_2->setText(QApplication::translate("MainWindow", "Hair Thresh", 0));
        label_3->setText(QApplication::translate("MainWindow", "Face Thresh", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'setparameterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETPARAMETERDIALOG_H
#define UI_SETPARAMETERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_SetParameterDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *lineEdit_SequencePath;
    QLabel *label2;
    QLineEdit *lineEdit_FileFormat;
    QLabel *label_2;
    QLineEdit *lineEdit_OutputPath;
    QLabel *label_3;
    QLineEdit *lineEdit_StartFrame;

    void setupUi(QDialog *SetParameterDialog)
    {
        if (SetParameterDialog->objectName().isEmpty())
            SetParameterDialog->setObjectName(QStringLiteral("SetParameterDialog"));
        SetParameterDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(SetParameterDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(SetParameterDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 91, 21));
        lineEdit_SequencePath = new QLineEdit(SetParameterDialog);
        lineEdit_SequencePath->setObjectName(QStringLiteral("lineEdit_SequencePath"));
        lineEdit_SequencePath->setGeometry(QRect(110, 41, 271, 20));
        label2 = new QLabel(SetParameterDialog);
        label2->setObjectName(QStringLiteral("label2"));
        label2->setGeometry(QRect(10, 90, 71, 16));
        lineEdit_FileFormat = new QLineEdit(SetParameterDialog);
        lineEdit_FileFormat->setObjectName(QStringLiteral("lineEdit_FileFormat"));
        lineEdit_FileFormat->setGeometry(QRect(110, 90, 113, 20));
        label_2 = new QLabel(SetParameterDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 140, 81, 16));
        lineEdit_OutputPath = new QLineEdit(SetParameterDialog);
        lineEdit_OutputPath->setObjectName(QStringLiteral("lineEdit_OutputPath"));
        lineEdit_OutputPath->setGeometry(QRect(110, 140, 271, 20));
        label_3 = new QLabel(SetParameterDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 190, 91, 16));
        lineEdit_StartFrame = new QLineEdit(SetParameterDialog);
        lineEdit_StartFrame->setObjectName(QStringLiteral("lineEdit_StartFrame"));
        lineEdit_StartFrame->setGeometry(QRect(110, 190, 81, 20));

        retranslateUi(SetParameterDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SetParameterDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SetParameterDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SetParameterDialog);
    } // setupUi

    void retranslateUi(QDialog *SetParameterDialog)
    {
        SetParameterDialog->setWindowTitle(QApplication::translate("SetParameterDialog", "Dialog", 0));
        label->setText(QApplication::translate("SetParameterDialog", "Sequences Path :", 0));
        lineEdit_SequencePath->setText(QApplication::translate("SetParameterDialog", "C:\\Users\\culan\\Desktop\\VIVIDJPG\\egtest04", 0));
        label2->setText(QApplication::translate("SetParameterDialog", "File Format :", 0));
        lineEdit_FileFormat->setText(QApplication::translate("SetParameterDialog", "frame%.5d.jpg", 0));
        label_2->setText(QApplication::translate("SetParameterDialog", "Output Path :", 0));
        lineEdit_OutputPath->setText(QApplication::translate("SetParameterDialog", "C:\\Users\\culan\\Desktop\\Labeled\\egtest04", 0));
        label_3->setText(QApplication::translate("SetParameterDialog", "Start Frame : ", 0));
        lineEdit_StartFrame->setText(QApplication::translate("SetParameterDialog", "0", 0));
    } // retranslateUi

};

namespace Ui {
    class SetParameterDialog: public Ui_SetParameterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETPARAMETERDIALOG_H

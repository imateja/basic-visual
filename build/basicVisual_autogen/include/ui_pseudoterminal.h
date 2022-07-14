/********************************************************************************
** Form generated from reading UI file 'pseudoterminal.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PSEUDOTERMINAL_H
#define UI_PSEUDOTERMINAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PseudoTerminal
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *outputTF;
    QHBoxLayout *horizontalLayout;
    QLineEdit *inputTF;
    QPushButton *submitBtn;

    void setupUi(QDialog *PseudoTerminal)
    {
        if (PseudoTerminal->objectName().isEmpty())
            PseudoTerminal->setObjectName(QString::fromUtf8("PseudoTerminal"));
        PseudoTerminal->resize(218, 300);
        verticalLayout = new QVBoxLayout(PseudoTerminal);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        outputTF = new QTextEdit(PseudoTerminal);
        outputTF->setObjectName(QString::fromUtf8("outputTF"));
        outputTF->setReadOnly(true);
        outputTF->setAcceptRichText(false);

        verticalLayout->addWidget(outputTF);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, -1, -1);
        inputTF = new QLineEdit(PseudoTerminal);
        inputTF->setObjectName(QString::fromUtf8("inputTF"));
        inputTF->setReadOnly(false);

        horizontalLayout->addWidget(inputTF);

        submitBtn = new QPushButton(PseudoTerminal);
        submitBtn->setObjectName(QString::fromUtf8("submitBtn"));

        horizontalLayout->addWidget(submitBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(PseudoTerminal);

        QMetaObject::connectSlotsByName(PseudoTerminal);
    } // setupUi

    void retranslateUi(QDialog *PseudoTerminal)
    {
        PseudoTerminal->setWindowTitle(QCoreApplication::translate("PseudoTerminal", "Dialog", nullptr));
        submitBtn->setText(QCoreApplication::translate("PseudoTerminal", "Submit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PseudoTerminal: public Ui_PseudoTerminal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PSEUDOTERMINAL_H

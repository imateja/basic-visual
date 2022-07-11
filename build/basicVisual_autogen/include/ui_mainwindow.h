/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionImport_as_custom_function;
    QAction *actionImport_custom_function;
    QAction *actionExit;
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QAction *actionBuild;
    QAction *actionRun;
    QAction *actionDebug;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QGraphicsView *mainGV;
    QTabWidget *tabWidget;
    QWidget *Instructions;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *AssignBtn;
    QLineEdit *assignVarName;
    QPushButton *IfBtn;
    QPushButton *WhileBtn;
    QPushButton *printBtn;
    QPushButton *inputBtn;
    QLineEdit *inputVarName;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QPushButton *editBtn;
    QPushButton *deleteBtn;
    QSpacerItem *verticalSpacer;
    QPushButton *nextBtn;
    QWidget *Expressions;
    QPushButton *plusBtn;
    QPushButton *minusBtn;
    QPushButton *mulBtn;
    QPushButton *divBtn;
    QPushButton *varBtn;
    QPushButton *constBtn;
    QPushButton *gteqBtn;
    QPushButton *lseqBtn;
    QPushButton *gtBtn;
    QPushButton *lsBtn;
    QPushButton *eqBtn;
    QPushButton *neqBtn;
    QPushButton *andBtn;
    QPushButton *orBtn;
    QPushButton *notBtn;
    QTextEdit *varTF;
    QTextEdit *constTF;
    QPushButton *backBtn;
    QPushButton *deleteBtn_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuBuild;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(1054, 620);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        actionImport_as_custom_function = new QAction(MainWindow);
        actionImport_as_custom_function->setObjectName(QString::fromUtf8("actionImport_as_custom_function"));
        actionImport_custom_function = new QAction(MainWindow);
        actionImport_custom_function->setObjectName(QString::fromUtf8("actionImport_custom_function"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionZoom_in = new QAction(MainWindow);
        actionZoom_in->setObjectName(QString::fromUtf8("actionZoom_in"));
        actionZoom_out = new QAction(MainWindow);
        actionZoom_out->setObjectName(QString::fromUtf8("actionZoom_out"));
        actionBuild = new QAction(MainWindow);
        actionBuild->setObjectName(QString::fromUtf8("actionBuild"));
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QString::fromUtf8("actionRun"));
        actionDebug = new QAction(MainWindow);
        actionDebug->setObjectName(QString::fromUtf8("actionDebug"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        mainGV = new QGraphicsView(centralwidget);
        mainGV->setObjectName(QString::fromUtf8("mainGV"));
        mainGV->setBaseSize(QSize(800, 800));
        mainGV->setSceneRect(QRectF(0, 0, 800, 600));

        formLayout->setWidget(0, QFormLayout::FieldRole, mainGV);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        Instructions = new QWidget();
        Instructions->setObjectName(QString::fromUtf8("Instructions"));
        verticalLayout_3 = new QVBoxLayout(Instructions);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        AssignBtn = new QPushButton(Instructions);
        AssignBtn->setObjectName(QString::fromUtf8("AssignBtn"));

        verticalLayout_2->addWidget(AssignBtn);

        assignVarName = new QLineEdit(Instructions);
        assignVarName->setObjectName(QString::fromUtf8("assignVarName"));

        verticalLayout_2->addWidget(assignVarName);

        IfBtn = new QPushButton(Instructions);
        IfBtn->setObjectName(QString::fromUtf8("IfBtn"));

        verticalLayout_2->addWidget(IfBtn);

        WhileBtn = new QPushButton(Instructions);
        WhileBtn->setObjectName(QString::fromUtf8("WhileBtn"));

        verticalLayout_2->addWidget(WhileBtn);

        printBtn = new QPushButton(Instructions);
        printBtn->setObjectName(QString::fromUtf8("printBtn"));

        verticalLayout_2->addWidget(printBtn);

        inputBtn = new QPushButton(Instructions);
        inputBtn->setObjectName(QString::fromUtf8("inputBtn"));

        verticalLayout_2->addWidget(inputBtn);

        inputVarName = new QLineEdit(Instructions);
        inputVarName->setObjectName(QString::fromUtf8("inputVarName"));

        verticalLayout_2->addWidget(inputVarName);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        editBtn = new QPushButton(Instructions);
        editBtn->setObjectName(QString::fromUtf8("editBtn"));

        verticalLayout_2->addWidget(editBtn);

        deleteBtn = new QPushButton(Instructions);
        deleteBtn->setObjectName(QString::fromUtf8("deleteBtn"));

        verticalLayout_2->addWidget(deleteBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        nextBtn = new QPushButton(Instructions);
        nextBtn->setObjectName(QString::fromUtf8("nextBtn"));

        verticalLayout_2->addWidget(nextBtn);


        verticalLayout_3->addLayout(verticalLayout_2);

        tabWidget->addTab(Instructions, QString());
        Expressions = new QWidget();
        Expressions->setObjectName(QString::fromUtf8("Expressions"));
        plusBtn = new QPushButton(Expressions);
        plusBtn->setObjectName(QString::fromUtf8("plusBtn"));
        plusBtn->setGeometry(QRect(20, 30, 51, 25));
        minusBtn = new QPushButton(Expressions);
        minusBtn->setObjectName(QString::fromUtf8("minusBtn"));
        minusBtn->setGeometry(QRect(110, 30, 50, 25));
        mulBtn = new QPushButton(Expressions);
        mulBtn->setObjectName(QString::fromUtf8("mulBtn"));
        mulBtn->setGeometry(QRect(20, 70, 51, 25));
        divBtn = new QPushButton(Expressions);
        divBtn->setObjectName(QString::fromUtf8("divBtn"));
        divBtn->setGeometry(QRect(110, 70, 51, 25));
        varBtn = new QPushButton(Expressions);
        varBtn->setObjectName(QString::fromUtf8("varBtn"));
        varBtn->setGeometry(QRect(110, 400, 51, 31));
        constBtn = new QPushButton(Expressions);
        constBtn->setObjectName(QString::fromUtf8("constBtn"));
        constBtn->setGeometry(QRect(110, 360, 50, 30));
        gteqBtn = new QPushButton(Expressions);
        gteqBtn->setObjectName(QString::fromUtf8("gteqBtn"));
        gteqBtn->setGeometry(QRect(20, 130, 51, 25));
        lseqBtn = new QPushButton(Expressions);
        lseqBtn->setObjectName(QString::fromUtf8("lseqBtn"));
        lseqBtn->setGeometry(QRect(110, 130, 51, 25));
        gtBtn = new QPushButton(Expressions);
        gtBtn->setObjectName(QString::fromUtf8("gtBtn"));
        gtBtn->setGeometry(QRect(20, 170, 51, 25));
        lsBtn = new QPushButton(Expressions);
        lsBtn->setObjectName(QString::fromUtf8("lsBtn"));
        lsBtn->setGeometry(QRect(110, 170, 51, 25));
        eqBtn = new QPushButton(Expressions);
        eqBtn->setObjectName(QString::fromUtf8("eqBtn"));
        eqBtn->setGeometry(QRect(20, 210, 51, 25));
        neqBtn = new QPushButton(Expressions);
        neqBtn->setObjectName(QString::fromUtf8("neqBtn"));
        neqBtn->setGeometry(QRect(110, 210, 51, 25));
        andBtn = new QPushButton(Expressions);
        andBtn->setObjectName(QString::fromUtf8("andBtn"));
        andBtn->setGeometry(QRect(20, 270, 51, 25));
        orBtn = new QPushButton(Expressions);
        orBtn->setObjectName(QString::fromUtf8("orBtn"));
        orBtn->setGeometry(QRect(110, 270, 51, 25));
        notBtn = new QPushButton(Expressions);
        notBtn->setObjectName(QString::fromUtf8("notBtn"));
        notBtn->setGeometry(QRect(60, 310, 61, 25));
        varTF = new QTextEdit(Expressions);
        varTF->setObjectName(QString::fromUtf8("varTF"));
        varTF->setGeometry(QRect(20, 400, 81, 31));
        constTF = new QTextEdit(Expressions);
        constTF->setObjectName(QString::fromUtf8("constTF"));
        constTF->setGeometry(QRect(20, 360, 81, 31));
        backBtn = new QPushButton(Expressions);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));
        backBtn->setGeometry(QRect(40, 490, 101, 25));
        deleteBtn_2 = new QPushButton(Expressions);
        deleteBtn_2->setObjectName(QString::fromUtf8("deleteBtn_2"));
        deleteBtn_2->setGeometry(QRect(40, 460, 100, 25));
        label = new QLabel(Expressions);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 10, 80, 17));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(Expressions);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 110, 80, 17));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(Expressions);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 250, 80, 17));
        label_3->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(Expressions, QString());

        formLayout->setWidget(0, QFormLayout::LabelRole, tabWidget);


        verticalLayout->addLayout(formLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1054, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuBuild = new QMenu(menubar);
        menuBuild->setObjectName(QString::fromUtf8("menuBuild"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuBuild->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionExit);
        menuBuild->addAction(actionRun);
        menuBuild->addAction(actionDebug);
        menuBuild->addAction(actionBuild);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionSave_As->setText(QCoreApplication::translate("MainWindow", "Save As", nullptr));
        actionImport_as_custom_function->setText(QCoreApplication::translate("MainWindow", "Import as custom function", nullptr));
        actionImport_custom_function->setText(QCoreApplication::translate("MainWindow", "Import custom function", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionZoom_in->setText(QCoreApplication::translate("MainWindow", "Zoom in", nullptr));
        actionZoom_out->setText(QCoreApplication::translate("MainWindow", "Zoom out", nullptr));
        actionBuild->setText(QCoreApplication::translate("MainWindow", "Build", nullptr));
        actionRun->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        actionDebug->setText(QCoreApplication::translate("MainWindow", "Debug", nullptr));
        AssignBtn->setText(QCoreApplication::translate("MainWindow", "Assign", nullptr));
        IfBtn->setText(QCoreApplication::translate("MainWindow", "If", nullptr));
        WhileBtn->setText(QCoreApplication::translate("MainWindow", "While", nullptr));
        printBtn->setText(QCoreApplication::translate("MainWindow", "Print", nullptr));
        inputBtn->setText(QCoreApplication::translate("MainWindow", "Input", nullptr));
        editBtn->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        deleteBtn->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        nextBtn->setText(QCoreApplication::translate("MainWindow", "Next", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Instructions), QCoreApplication::translate("MainWindow", "Instructions", nullptr));
        plusBtn->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        minusBtn->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        mulBtn->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        divBtn->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        varBtn->setText(QCoreApplication::translate("MainWindow", "var", nullptr));
        constBtn->setText(QCoreApplication::translate("MainWindow", "const", nullptr));
        gteqBtn->setText(QCoreApplication::translate("MainWindow", ">=", nullptr));
        lseqBtn->setText(QCoreApplication::translate("MainWindow", "<=", nullptr));
        gtBtn->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        lsBtn->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        eqBtn->setText(QCoreApplication::translate("MainWindow", "==", nullptr));
        neqBtn->setText(QCoreApplication::translate("MainWindow", "!=", nullptr));
        andBtn->setText(QCoreApplication::translate("MainWindow", "and", nullptr));
        orBtn->setText(QCoreApplication::translate("MainWindow", "or", nullptr));
        notBtn->setText(QCoreApplication::translate("MainWindow", "not", nullptr));
        backBtn->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        deleteBtn_2->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Arithmetic", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Relational", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Logical", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Expressions), QCoreApplication::translate("MainWindow", "Expressions", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuBuild->setTitle(QCoreApplication::translate("MainWindow", "Build", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

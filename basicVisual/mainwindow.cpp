#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "maingraphicsview.hpp"
#include "instruction.h"
#include "instructioncontainer.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _mainGraphicsView(new mainGraphicsView)
{
    ui->setupUi(this);
    setupActions(); //sets up the needed connections for the taskbar

    //mainGV is the name of out GraphicsView in .ui file
    _mainGraphicsView->setSceneRect(ui->mainGV->rect());
    ui->mainGV->setScene(_mainGraphicsView);
    ui->mainGV->setRenderHint(QPainter::Antialiasing);
    ui->mainGV->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    connect(ui->AssignBtn, &QPushButton::clicked, this, &MainWindow::addAssign);
    connect(ui->WhileBtn, &QPushButton::clicked, this, &MainWindow::addWhile);
    connect(ui->IfBtn, &QPushButton::clicked, this, &MainWindow::addIf);
    connect(ui->ForBtn, &QPushButton::clicked, this, &MainWindow::addFor);
    connect(this, &MainWindow::newSquareOnGV, dynamic_cast<mainGraphicsView *>(_mainGraphicsView), &mainGraphicsView::addedSquareOnGV);

}

MainWindow::~MainWindow()
{
    delete ui;
    for (auto instr : _instructions)
    {
        delete instr;
    }

}
//These are just test functions, actual ones are gonna look completely different
void MainWindow::addAssign()
{
    const auto instr= new Instruction("_ = _", Instruction::TypeOfInstruction::ASSIGN);

    _instructions.push_back(instr);

    const auto node = new InstructionContainer(instr);
    _mainGraphicsView->addItem(node);

    emit newSquareOnGV(node);
}

void MainWindow::addWhile()
{
    const auto instr= new Instruction("cond", Instruction::TypeOfInstruction::WHILE);

    _instructions.push_back(instr);

    const auto node = new InstructionContainer(instr);
    _mainGraphicsView->addItem(node);

    emit newSquareOnGV(node);
}

void MainWindow::addIf()
{
    const auto instr= new Instruction("cond", Instruction::TypeOfInstruction::IF);

    _instructions.push_back(instr);

    const auto node = new InstructionContainer(instr);
    _mainGraphicsView->addItem(node);

    emit newSquareOnGV(node);
}

void MainWindow::addFor()
{
    const auto instr= new Instruction("text", Instruction::TypeOfInstruction::FOR);

    _instructions.push_back(instr);

    const auto node = new InstructionContainer(instr);
    _mainGraphicsView->addItem(node);

    emit newSquareOnGV(node);
}

void MainWindow::setupActions()
{
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onActionOpen);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onActionSave);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::onActionSaveAs);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::onActionExit);
}
//TODO:other actions
void MainWindow::onActionOpen()
{
    QString fileName = QFileDialog::getOpenFileName(
         this,
         tr("Open Visual"), ".",
         tr("basicVisual Files (*.bv)"));
    //TODO: if fileName is empty
}

void MainWindow::onActionSave()
{
// i have no idea what to do here
}

void MainWindow::onActionSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(
            this,
            tr("Save Visual"), ".",
            tr("Visual (*.bv)"));

   //TODO: if fileName is empty
}

void MainWindow::onActionExit()
{
    QMessageBox::StandardButton response = QMessageBox::question(
           this, "Exit", "Force exit?", QMessageBox::Yes| QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes
       );

    if(response == QMessageBox::Yes)
        MainWindow::close();
    else
        return;
}




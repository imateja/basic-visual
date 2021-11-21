#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "maingraphicsview.hpp"
#include "instruction.h"
#include "instructioncontainer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _mainGraphicsView(new mainGraphicsView)
{
    ui->setupUi(this);
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



#include "inc/mainwindow.h"
#include "./ui_mainwindow.h"
#include "inc/maingraphicsview.hpp"
#include "inc/instruction.h"
#include "inc/instructioncontainer.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include "inc/instructiondialog.h"

#include "inc/exprtree.h"
#include <QString>

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
    connect(ui->startBtn, &QPushButton::clicked, this, &MainWindow::addStart);
    connect(this, &MainWindow::newSquareOnGV, dynamic_cast<mainGraphicsView *>(_mainGraphicsView), &mainGraphicsView::addedSquareOnGV);

}

MainWindow::~MainWindow()
{
    delete ui;
}
//These are just test functions, actual ones are gonna look completely different
void MainWindow::addStart()
{
    auto selected = new StartExprAST();
    _mainGraphicsView->addItem(selected);
    emit newSquareOnGV(selected);
}
void MainWindow::addAssign()
{
    //InstructionDialog* WhileDialog = new InstructionDialog(this);
    if(1)//WhileDialog->exec())
    {
    //WhileDialog->getCondition()
    auto selected = ExprTree::Tree().selected;
    if (auto end = dynamic_cast<EndExprAST*>(selected)){
        selected = end->start_;
    }
    if (selected){
        auto newElement = new AssignExprAST(QString("x"),new ValueExprAST(5));
        if(selected->next_){
            auto tmp = selected->next_;
            selected->next_= newElement;
            selected->next_->next_ = tmp;
        }else{
            selected->next_ = newElement;
        }

        _mainGraphicsView->addItem(selected->next_);
        emit newSquareOnGV(selected->next_);
    }

    }
}

void MainWindow::addWhile()
{
    //InstructionDialog* WhileDialog = new InstructionDialog(this);
    if(1)//WhileDialog->exec())
    {
    //WhileDialog->getCondition()
    auto selected = ExprTree::Tree().selected;
    if (auto end = dynamic_cast<EndExprAST*>(selected)){
        selected = end->start_;
    }
    if (selected){
        auto newElement = new WhileExprAST(new ValueExprAST(5));
        if(selected->next_){
            auto tmp = selected->next_;
            selected->next_= newElement;
            selected->next_->next_ = tmp;
        }else{
            selected->next_ = newElement;
        }
        _mainGraphicsView->addItem(selected->next_);
        emit newSquareOnGV(selected->next_);

    }

    }
}

void MainWindow::addIf()
{
    //InstructionDialog* WhileDialog = new InstructionDialog(this);
    if(1)//WhileDialog->exec())
    {
    //WhileDialog->getCondition()
    auto selected = ExprTree::Tree().selected;
    if (auto end = dynamic_cast<EndExprAST*>(selected)){
        selected = end->start_;
    }
    if (selected){
        auto newElement = new IfExprAST(new ValueExprAST(5));
        if(selected->next_){
            auto tmp = selected->next_;
            selected->next_= newElement;
            selected->next_->next_ = tmp;
        }else{
            selected->next_ = newElement;
        }

        _mainGraphicsView->addItem(selected->next_);

        auto position=selected->next_->scenePos();

        emit newSquareOnGV(selected->next_);

        position=selected->next_->scenePos();
         qDebug()<<"outside emit"<<position<<"\n";
        auto h= selected->next_->getHeight();
        auto w= selected->next_->getWidth();
        //QGraphicsItemGroup *group = _mainGraphicsView->createItemGroup({selected->next_});
        auto thenblock= new ThenElseExprAST("then");
        auto elseblock= new ThenElseExprAST("else");
        thenblock->setPos(position.x()-50,position.y()+100);
        qDebug()<<"then emit"<<position.x() -50<<"\n";
        elseblock->setPos(position.x()+50,position.y() + 100);
        qDebug()<<"else emit"<<position.x() +50<<"\n";
        _mainGraphicsView->addItem(thenblock);

        _mainGraphicsView->addItem(elseblock);


    }

    }
}

//void MainWindow::addFor()
//{
//    InstructionDialog* ForDialog = new InstructionDialog(this);
//    if(ForDialog->exec())
//    {
//     //TODO: Add check if condition and all dialog boxes are filled right
//     const auto instr= new Instruction(ForDialog->getCondition(), Instruction::TypeOfInstruction::FOR);

//    _instructions.push_back(instr);

//    const auto node = new InstructionContainer(instr);
//    _mainGraphicsView->addItem(node);

//    emit newSquareOnGV(node);
//    }
//}

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




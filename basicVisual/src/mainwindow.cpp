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
    , _mainGraphicsView(new mainGraphicsView())

{
    ui->setupUi(this);
    setupActions(); //sets up the needed connections for the taskbar
    factor=0;

    //mainGV is the name of out GraphicsView in .ui file
    _mainGraphicsView->setSceneRect(ui->mainGV->rect());
    ui->mainGV->setScene(_mainGraphicsView);
    ui->mainGV->setRenderHint(QPainter::Antialiasing);
    ui->mainGV->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    mainBlock= new BlockExprAST();
    _mainGraphicsView->addItem(mainBlock);
    mainBlock->setParent(_mainGraphicsView);
    qDebug()<<mainBlock->parent()<<"/n";
    QPointF sceneCenter = ui->mainGV->mapToScene( ui->mainGV->viewport()->rect().center());
    mainBlock->setPos(sceneCenter.x(), sceneCenter.y());

//    mainBlock= new BlockExprAST();
//    _mainGraphicsView->addItem(mainBlock);
//    mainBlock->setParent(_mainGraphicsView);
//    qDebug()<<mainBlock->parent()<<"/n";
//    QPointF sceneCenter = ui->mainGV->mapToScene( ui->mainGV->viewport()->rect().center());
//    mainBlock->setPos(sceneCenter.x(), 0);

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
void MainWindow::positionElement(InstructionExprAST* elem, qint32 factor)
{
    QPointF sceneCenter = ui->mainGV->mapToScene( ui->mainGV->viewport()->rect().center());
    elem->setPos(sceneCenter.x(), factor*90);
}
//These are just test functions, actual ones are gonna look completely different
void MainWindow::addStart()
{
    auto instructionMode = mainBlock->isVisible();
    if(instructionMode){
        mainBlock->setVisible(false);
        //TODO: posao za izraze
    }
    else{
        //TODO: posao za izraze
        mainBlock->setVisible(true);
    }

}

inline BlockExprAST* MainWindow::getInsertionBlock(){
     return _mainGraphicsView->selectedItems().empty()
            ? mainBlock
            : static_cast<BlockExprAST*>(_mainGraphicsView->selectedItems().at(0)->parentItem());
}
void MainWindow::addInstruction(InstructionExprAST* newElement){
    if (_mainGraphicsView->selectedItems().empty()){
        newElement->setParentItem(mainBlock);
        mainBlock->insert(newElement);
    }else {
        auto parent = static_cast<BlockExprAST*>(_mainGraphicsView->selectedItems().at(0)->parentItem());
        newElement->setParentItem(parent);
        parent->insert(newElement,static_cast<InstructionExprAST*>(_mainGraphicsView->selectedItems().at(0)));
    }
    connect(newElement,&InstructionExprAST::ShouldUpdateScene,dynamic_cast<mainGraphicsView*>(_mainGraphicsView),&mainGraphicsView::updateScene);
    connect(newElement,&InstructionExprAST::signalSelected,dynamic_cast<mainGraphicsView *>(_mainGraphicsView),
            &mainGraphicsView::clearSelection);

    //_mainGraphicsView->addItem(newElement);
    QPointF sceneCenter = ui->mainGV->mapToScene( ui->mainGV->viewport()->rect().center());
    mainBlock->setPos(sceneCenter.x(), sceneCenter.y());
}
void MainWindow::addAssign()
{
    auto newElement = new AssignExprAST(QString("x"),new ValueExprAST(5));
    addInstruction(newElement);
}

//connect(newElement,&InstructionExprAST::signalSelected,_mainGraphicsView,[=](){
//    qDebug()<< node->instructionName_;
//    clearSelection();
//    node->setSelected(true);
//    qDebug()<<"selektovano je"<<"\n";
//});
void MainWindow::addWhile()
{
   auto newElement =new WhileExprAST(new ValueExprAST(5));
   addInstruction(newElement);
}

void MainWindow::addIf()
{
    auto newElement =new IfExprAST(new ValueExprAST(5));
    addInstruction(newElement);
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




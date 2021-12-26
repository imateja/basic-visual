#include "inc/mainwindow.h"
#include "./ui_mainwindow.h"
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
    , _mainGraphicsScene(new mainGraphicsScene())

{
    ui->setupUi(this);
    //sets up the needed connections for the taskbar
    factor=0;

    //mainGV is the name of out GraphicsView in .ui file
    _mainGraphicsScene->setSceneRect(ui->mainGV->rect());
    ui->mainGV->setScene(_mainGraphicsScene);
    ui->mainGV->setRenderHint(QPainter::Antialiasing);
    ui->mainGV->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    mainBlock= new BlockExprAST();
    _mainGraphicsScene->addItem(mainBlock);
    mainBlock->setParent(_mainGraphicsScene);
    qDebug()<<mainBlock->parent()<<"/n";
    QPointF sceneCenter = ui->mainGV->mapToScene( ui->mainGV->viewport()->rect().center());
    mainBlock->setPos(sceneCenter.x(), sceneCenter.y());

//    mainBlock= new BlockExprAST();
//    _mainGraphicsView->addItem(mainBlock);
//    mainBlock->setParent(_mainGraphicsView);
//    qDebug()<<mainBlock->parent()<<"/n";
//    QPointF sceneCenter = ui->mainGV->mapToScene( ui->mainGV->viewport()->rect().center());
//    mainBlock->setPos(sceneCenter.x(), 0);
    setupActions();
    setupConnections();


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

void MainWindow::Edit()
{
    if(mainBlock->isVisible()){
        if(_mainGraphicsScene->selectedItems().empty()){
            //TODO error handling
            return;
        }

        auto editableExpr = static_cast<InstructionExprAST*>(_mainGraphicsScene->selectedItems().at(0))->getEditableExpr();
        if(editableExpr == nullptr){
            //TODO error handling

            return;
        }

        ui->ExprEdit->setDisabled(false);
        ui->tabWidget->setCurrentIndex(1);
        ui->tab->setDisabled(true);

        _mainGraphicsScene->clearItems();
        _mainGraphicsScene->addItem(editableExpr);

        QPointF sceneCenter = ui->mainGV->mapToScene( ui->mainGV->viewport()->rect().center());
        editableExpr->setPos(sceneCenter.x(), sceneCenter.y());

        mainBlock->hide();

    }
}

void MainWindow::backPushed()
{
    if(!mainBlock->isVisible()){
        ui->tab->setDisabled(false);
        ui->tabWidget->setCurrentIndex(0);
        ui->ExprEdit->setDisabled(true);

        _mainGraphicsScene->clearItems();
        _mainGraphicsScene->addItem(mainBlock);

        mainBlock->show();
        mainBlock->updateChildren();
    }
}

inline BlockExprAST* MainWindow::getInsertionBlock(){
     return _mainGraphicsScene->selectedItems().empty()
            ? mainBlock
            : static_cast<BlockExprAST*>(_mainGraphicsScene->selectedItems().at(0)->parentItem());
}
void MainWindow::addInstruction(InstructionExprAST* newElement){
    if (_mainGraphicsScene->selectedItems().empty()){
        mainBlock->insert(newElement);
    }else {
        auto parent = static_cast<BlockExprAST*>(_mainGraphicsScene->selectedItems().at(0)->parentItem());
        parent->insert(newElement,static_cast<InstructionExprAST*>(_mainGraphicsScene->selectedItems().at(0)));
    }
    connect(newElement,&ExprAST::ShouldUpdateScene,dynamic_cast<mainGraphicsScene*>(_mainGraphicsScene),&mainGraphicsScene::updateScene);
    connect(newElement,&ExprAST::signalSelected,dynamic_cast<mainGraphicsScene *>(_mainGraphicsScene),
            &mainGraphicsScene::clearSelection);

    //_mainGraphicsView->addItem(newElement);
    QPointF sceneCenter = ui->mainGV->mapToScene( ui->mainGV->viewport()->rect().center());
    mainBlock->setPos(sceneCenter.x(), sceneCenter.y());
}
void MainWindow::addAssign()
{
    auto newElement = new AssignExprAST(QString("x"));
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
   auto newElement =new WhileExprAST();
   addInstruction(newElement);
}

void MainWindow::addIf()
{
    auto newElement =new IfExprAST();
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

void MainWindow::addPlus()
{}
void MainWindow::addMinus()
{}
void MainWindow::addMul()
{}
void MainWindow::addDiv()
{}
void MainWindow::addLs()
{}
void MainWindow::addGt()
{}
void MainWindow::addLseq()
{}
void MainWindow::addGteq()
{}
void MainWindow::addAnd()
{}
void MainWindow::addOr()
{}
void MainWindow::addNot()
{}
void MainWindow::addEq()
{}
void MainWindow::addNeq()
{}
void MainWindow::addVar()
{}
void MainWindow::addConst()
{}
void MainWindow::setupConnections()
{
    connect(ui->AssignBtn, &QPushButton::clicked, this, &MainWindow::addAssign);
    connect(ui->WhileBtn, &QPushButton::clicked, this, &MainWindow::addWhile);
    connect(ui->IfBtn, &QPushButton::clicked, this, &MainWindow::addIf);
    connect(ui->editBtn, &QPushButton::clicked, this, &MainWindow::Edit);
    connect(this, &MainWindow::newSquareOnGV, dynamic_cast<mainGraphicsScene *>(_mainGraphicsScene), &mainGraphicsScene::addedSquareOnGV);
    connect(ui->plusBtn, &QPushButton::clicked, this, &MainWindow::addPlus);
    connect(ui->minusBtn, &QPushButton::clicked, this, &MainWindow::addMinus);
    connect(ui->mulBtn, &QPushButton::clicked, this, &MainWindow::addMul);
    connect(ui->divBtn, &QPushButton::clicked, this, &MainWindow::addDiv);
    connect(ui->lsBtn, &QPushButton::clicked, this, &MainWindow::addLs);
    connect(ui->lseqBtn, &QPushButton::clicked, this, &MainWindow::addLseq);
    connect(ui->gtBtn, &QPushButton::clicked, this, &MainWindow::addGt);
    connect(ui->gteqBtn, &QPushButton::clicked, this, &MainWindow::addGteq);
    connect(ui->eqBtn, &QPushButton::clicked, this, &MainWindow::addEq);
    connect(ui->neqBtn, &QPushButton::clicked, this, &MainWindow::addNeq);
    connect(ui->orBtn, &QPushButton::clicked, this, &MainWindow::addOr);
    connect(ui->andBtn, &QPushButton::clicked, this, &MainWindow::addAnd);
    connect(ui->notBtn, &QPushButton::clicked, this, &MainWindow::addNot);
    connect(ui->varBtn, &QPushButton::clicked, this, &MainWindow::addVar);
    connect(ui->constBtn, &QPushButton::clicked, this, &MainWindow::addConst);
    connect(ui->backBtn, &QPushButton::clicked, this, &MainWindow::backPushed);

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




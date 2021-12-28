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
#include <QAbstractScrollArea>
#include <QWidget>
#include <QRegularExpression>

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
    ui->tabWidget->setCurrentIndex(0);
    mainBlock= new BlockExprAST();
    exprItem=nullptr;
    _mainGraphicsScene->addItem(mainBlock);
    position();
    connect(mainBlock,&ExprAST::ShouldUpdateScene,this,&MainWindow::updateScene);
    connect(mainBlock,&ExprAST::selectItem,_mainGraphicsScene,&mainGraphicsScene::setSelectedItem);
    connect(mainBlock,&ExprAST::updateSelection,_mainGraphicsScene,&mainGraphicsScene::selectItem);


//    mainBlock= new BlockExprAST();
//    _mainGraphicsView->addItem(mainBlock);
//    mainBlock->setParent(_mainGraphicsView);
//    qDebug()<<mainBlock->parent()<<"/n";
//    QPointF sceneCenter = ui->mainGV->mapToScene( ui->mainGV->viewport()->rect().center());
//    mainBlock->setPos(sceneCenter.x(), 0);
    setupActions();
    setupConnections();

    ui->mainGV->viewport()->installEventFilter(this);
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

void MainWindow::updateScene(){
    ExprAST* centerItem = stagedItem();
    centerItem->update();
    ui->mainGV->setSceneRect(centerItem->boundingRect());
    _mainGraphicsScene->update();
    //qDebug()<<"Scena se updatovala";
}

void MainWindow::position()
{
    ExprAST* centerItem = stagedItem();
    //qDebug() << centerItem->boundingRect()<< "\n";
    ui->mainGV->centerOn(centerItem);
    QPointF sceneCenter = ui->mainGV->mapToScene( ui->mainGV->viewport()->rect().center());
    centerItem->setPos(sceneCenter.x(), sceneCenter.y());
}

ExprAST* MainWindow::stagedItem(){
    return exprItem == nullptr ? mainBlock : exprItem;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->mainGV->viewport()){
        if(event->type() == QEvent::Resize){
            position();
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::Edit()
{
    if(mainBlock->isVisible()){
        if(_mainGraphicsScene->getSelectedItem() == nullptr){
            //TODO error handling
            return;
        }

        exprItem = static_cast<InstructionExprAST*>(_mainGraphicsScene->getSelectedItem())->getEditableExpr();
        if(exprItem == nullptr){
            //TODO error handling
            return;
        }


        ui->ExprEdit->setDisabled(false);
        ui->tabWidget->setCurrentIndex(1);
        ui->tab->setDisabled(true);

        _mainGraphicsScene->clearItems();
        _mainGraphicsScene->addItem(exprItem);

        connect(exprItem,&ExprAST::ShouldUpdateScene,this,&MainWindow::updateScene);
        connect(exprItem,&ExprAST::selectItem,_mainGraphicsScene,&mainGraphicsScene::setSelectedItem);
        connect(exprItem,&ExprAST::updateSelection,_mainGraphicsScene,&mainGraphicsScene::selectItem);


//        QPointF sceneCenter = ui->mainGV->mapToScene( ui->mainGV->viewport()->rect().center());
//        exprItem->setPos(sceneCenter.x(), sceneCenter.y());
        _mainGraphicsScene->setSelectedItem(nullptr);
        mainBlock->hide();
        exprItem->updateChildren();
        updateScene();
        _mainGraphicsScene->selectItem();
        position();

    }
}

void MainWindow::backPushed()
{
    if(!mainBlock->isVisible()){
        ui->tab->setDisabled(false);
        ui->tabWidget->setCurrentIndex(0);
        ui->ExprEdit->setDisabled(true);

        disconnect(exprItem,&ExprAST::ShouldUpdateScene,this,&MainWindow::updateScene);
        disconnect(exprItem,&ExprAST::selectItem,_mainGraphicsScene,&mainGraphicsScene::setSelectedItem);
        disconnect(exprItem,&ExprAST::updateSelection,_mainGraphicsScene,&mainGraphicsScene::selectItem);
        _mainGraphicsScene->clearItems();
        _mainGraphicsScene->addItem(mainBlock);
        exprItem = nullptr;

        _mainGraphicsScene->setSelectedItem(nullptr);
        mainBlock->show();
        mainBlock->updateChildren();
        updateScene();
        _mainGraphicsScene->selectItem();
        position();
    }
}

void MainWindow::addInstruction(InstructionExprAST* newElement){
    auto selected = _mainGraphicsScene->getSelectedItem();
    if (selected == nullptr){
        mainBlock->insert(newElement);
    }else {
        auto parent = static_cast<BlockExprAST*>(selected->parentItem());
        parent->insert(newElement,static_cast<InstructionExprAST*>(selected));
    }
    updateScene();
    position();
}
void MainWindow::addAssign()
{
    auto var = ui->assignVarName->text();
    QRegularExpression re("^[a-zA-Z_][a-zA-Z0-9_]*$");
    if (re.match(var).hasMatch()) {
        auto newElement = new AssignExprAST(var);
        ui->assignVarName->clear();
        addInstruction(newElement);
    }
    else {
        QMessageBox::information(this, "Invalid Variable name", "A valid variable name starts with a letter, followed by letters, digits, or underscores.");
    }

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

void MainWindow::addExpr(ExprAST* elem)
{
    if(_mainGraphicsScene->getSelectedItem() == nullptr){
        //TODO error handling
        return;
    }
    auto selected = dynamic_cast<PlaceholderExprAST*>(_mainGraphicsScene->getSelectedItem());
    if(selected){
        selected->setExpr(elem);
    }
    updateScene();
    position();

}

void MainWindow::addPlus()
{
    auto elem = new AddExprAST();
    addExpr(elem);
}

void MainWindow::addMinus()
{
    auto elem = new SubExprAST();
    addExpr(elem);
}
void MainWindow::addMul()
{
    auto elem = new MulExprAST();
    addExpr(elem);
}
void MainWindow::addDiv()
{
    auto elem = new DivExprAST();
    addExpr(elem);
}
void MainWindow::addLs()
{
    auto elem = new LtExprAST();
    addExpr(elem);
}
void MainWindow::addGt()
{
    auto elem = new GtExprAST();
    addExpr(elem);
}
void MainWindow::addLseq()
{
    auto elem = new LeqExprAST();
    addExpr(elem);
}
void MainWindow::addGteq()
{
    auto elem = new GeqExprAST();
    addExpr(elem);
}
void MainWindow::addAnd()
{
    auto elem = new AndExprAST();
    addExpr(elem);
}
void MainWindow::addOr()
{
    auto elem = new OrExprAST();
    addExpr(elem);
}
void MainWindow::addNot()
{
    auto elem = new NotExprAST();
    addExpr(elem);
}
void MainWindow::addEq()
{
    auto elem = new EqExprAST();
    addExpr(elem);
}
void MainWindow::addNeq()
{
    auto elem = new NeqExprAST();
    addExpr(elem);
}
void MainWindow::addVar()
{
    auto var = ui->varTF->toPlainText();
    QRegularExpression re("^[a-zA-Z_][a-zA-Z0-9_]*$");
    if (re.match(var).hasMatch()) {
        auto elem = new VariableExprAST(var);
        addExpr(elem);
        ui->varTF->clear();
    }
    else {
        QMessageBox::information(this, "Invalid Variable name", "A valid variable name starts with a letter, followed by letters, digits, or underscores.");
    }
}
void MainWindow::addConst()
{
    bool ok;
    auto val = ui->constTF->toPlainText().toDouble(&ok);
    if (ok) {
        auto elem = new ValueExprAST(val);
        addExpr(elem);
        ui->constTF->clear();
    }
    else {
        QMessageBox::information(this, "Invalid Value", "A valid value consists only of digits (with zero or one decimal dot).");
    }
}

void MainWindow::deletePushed(){
    auto item = _mainGraphicsScene->getSelectedItem();
    if(item){
        item->deleteMe();
        _mainGraphicsScene->setSelectedItem(nullptr);
        _mainGraphicsScene->selectItem();
        updateScene();
        position();
    }
}

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
    connect(ui->deleteBtn, &QPushButton::clicked, this, &MainWindow::deletePushed);
    connect(ui->deleteBtn_2, &QPushButton::clicked, this, &MainWindow::deletePushed);

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




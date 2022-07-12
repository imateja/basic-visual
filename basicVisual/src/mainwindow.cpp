#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QString>
#include <QAbstractScrollArea>
#include <QWidget>
#include <QRegularExpression>
#include <QThread>
#include "./ui_mainwindow.h"
#include <mainwindow.hpp>
#include <exprtree.hpp>
#include <interpret.hpp>
#include <compile.hpp>
#include <pseudoterminal.hpp>
#include <serializer.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _mainGraphicsScene(new mainGraphicsScene())
    , isAlreadyCompiled(false)
{
    ui->setupUi(this);
    factor=0;
    _mainGraphicsScene->setSceneRect(ui->mainGV->rect());
    ui->mainGV->setScene(_mainGraphicsScene);
    ui->mainGV->setRenderHint(QPainter::Antialiasing);
    ui->mainGV->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabEnabled(1, false);
    mainBlock = new BlockAST();
    initMainBlock();
    Interpret::mutex_.lock();
    setupActions();
    setupConnections();
    ui->nextBtn->hide();
    ui->mainGV->viewport()->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete _mainGraphicsScene;
    Interpret::mutex_.unlock();
    delete ui;
}

void MainWindow::updateScene()
{
    ExprAST* centerItem = stagedItem();
    centerItem->update();
    ui->mainGV->setSceneRect(centerItem->boundingRect());
    _mainGraphicsScene->update();
    _mainGraphicsScene->selectItem();
}

void MainWindow::position()
{
    ExprAST* centerItem = stagedItem();
    ui->mainGV->centerOn(centerItem);
    QPointF sceneCenter = ui->mainGV->mapToScene(ui->mainGV->viewport()->rect().center());
    centerItem->setPos(sceneCenter.x(), sceneCenter.y());
}

auto MainWindow::stagedItem() -> ExprAST*
{
    return exprItem == nullptr ? mainBlock : exprItem;
}

auto MainWindow::eventFilter(QObject *watched, QEvent *event) -> bool
{
    if (watched == ui->mainGV->viewport()) {
        if (event->type() == QEvent::Resize) {
            position();
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::Edit()
{
    if (mainBlock->isVisible()) {
        if (_mainGraphicsScene->getSelectedItem() == nullptr) {
            return;
        }
        if (dynamic_cast<InputAST*>(_mainGraphicsScene->getSelectedItem())){
            return;
        }
        exprItem = static_cast<InstructionAST*>(_mainGraphicsScene->getSelectedItem())->getEditableExpr();
        if (exprItem == nullptr) {
            return;
        }

        ui->tabWidget->setTabEnabled(1, true);
        ui->tabWidget->setCurrentIndex(1);
        ui->tabWidget->setTabEnabled(0, false);

        _mainGraphicsScene->clearItems();
        _mainGraphicsScene->addItem(exprItem);

        connect(exprItem, &ExprAST::ShouldUpdateScene, this, &MainWindow::updateScene);
        connect(exprItem, &ExprAST::selectItem, _mainGraphicsScene, &mainGraphicsScene::setSelectedItem);
        connect(exprItem, &ExprAST::updateSelection, _mainGraphicsScene, &mainGraphicsScene::selectItem);

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
    if (!mainBlock->isVisible()) {
        ui->tabWidget->setTabEnabled(0, true);
        ui->tabWidget->setCurrentIndex(0);
        ui->tabWidget->setTabEnabled(1, false);

        disconnect(exprItem, &ExprAST::ShouldUpdateScene, this, &MainWindow::updateScene);
        disconnect(exprItem, &ExprAST::selectItem, _mainGraphicsScene, &mainGraphicsScene::setSelectedItem);
        disconnect(exprItem, &ExprAST::updateSelection, _mainGraphicsScene, &mainGraphicsScene::selectItem);
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

void MainWindow::addInstruction(InstructionAST* newElement){
    auto selected = _mainGraphicsScene->getSelectedItem();
    if (selected == nullptr) {
        mainBlock->insert(newElement);
    }
    else {
        auto parent = static_cast<BlockAST*>(selected->parentItem());
        parent->insert(newElement,static_cast<InstructionAST*>(selected));
    }
    updateScene();
    position();
}

void MainWindow::addAssign()
{
    auto var = ui->assignVarName->text();
    QRegularExpression re("^[a-zA-Z_][a-zA-Z0-9_]*$");
    if (re.match(var).hasMatch()) {
        auto newElement = new AssignAST(var);
        addInstruction(newElement);
    }
    else {
        QMessageBox::information(this, "Invalid Variable name", "A valid variable name starts with a letter, followed by letters, digits, or underscores.");
    }

    ui->assignVarName->clear();
}

void MainWindow::addInput(){
    auto var = ui->inputVarName->text();
    QRegularExpression re("^[a-zA-Z_][a-zA-Z0-9_]*$");
    if (re.match(var).hasMatch()) {
        auto newElement = new InputAST(var);
        addInstruction(newElement);
    }
    else {
        QMessageBox::information(this, "Invalid Variable name", "A valid variable name starts with a letter, followed by letters, digits, or underscores.");
    }

    ui->inputVarName->clear();
}


void MainWindow::addWhile()
{
   auto newElement =new WhileAST();
   addInstruction(newElement);
}

void MainWindow::addIf()
{
    auto newElement =new IfAST();
    addInstruction(newElement);
}

void MainWindow::addPrint()
{
    auto newElement =new PrintAST();
    addInstruction(newElement);
}

void MainWindow::addExpr(ExprAST* elem)
{
    if (_mainGraphicsScene->getSelectedItem() == nullptr) {
        return;
    }
    auto selected = dynamic_cast<PlaceholderAST*>(_mainGraphicsScene->getSelectedItem());
    if (selected) {
        selected->setExpr(elem);
    }
    _mainGraphicsScene->setSelectedItem(nullptr);
    updateScene();
    position();
}

void MainWindow::addPlus()
{
    auto elem = new AddAST();
    addExpr(elem);
}

void MainWindow::addMinus()
{
    auto elem = new SubAST();
    addExpr(elem);
}

void MainWindow::addMul()
{
    auto elem = new MulAST();
    addExpr(elem);
}

void MainWindow::addDiv()
{
    auto elem = new DivAST();
    addExpr(elem);
}

void MainWindow::addLs()
{
    auto elem = new LtAST();
    addExpr(elem);
}

void MainWindow::addGt()
{
    auto elem = new GtAST();
    addExpr(elem);
}

void MainWindow::addLseq()
{
    auto elem = new LeqAST();
    addExpr(elem);
}

void MainWindow::addGteq()
{
    auto elem = new GeqAST();
    addExpr(elem);
}

void MainWindow::addAnd()
{
    auto elem = new AndAST();
    addExpr(elem);
}

void MainWindow::addOr()
{
    auto elem = new OrAST();
    addExpr(elem);
}

void MainWindow::addNot()
{
    auto elem = new NotAST();
    addExpr(elem);
}

void MainWindow::addEq()
{
    auto elem = new EqAST();
    addExpr(elem);
}

void MainWindow::addNeq()
{
    auto elem = new NeqAST();
    addExpr(elem);
}

void MainWindow::addVar()
{
    auto var = ui->varTF->toPlainText();
    QRegularExpression re("^[a-zA-Z_][a-zA-Z0-9_]*$");
    if (re.match(var).hasMatch()) {
        auto elem = new VariableAST(var);
        addExpr(elem);
    }
    else {
        QMessageBox::information(this, "Invalid Variable name", "A valid variable name starts with a letter, followed by letters, digits, or underscores.");
    }

    ui->varTF->clear();
}

void MainWindow::addConst()
{
    bool ok;
    auto val = ui->constTF->toPlainText().toDouble(&ok);
    if (ok) {
        auto elem = new ValueAST(val);
        addExpr(elem);
    }
    else {
        QMessageBox::information(this, "Invalid Value", "A valid value consists only of digits (with zero or one decimal dot).");
    }

    ui->constTF->clear();
}

void MainWindow::deletePushed()
{
    auto item = _mainGraphicsScene->getSelectedItem();
    if (item) {
        item->deleteMe();
        _mainGraphicsScene->setSelectedItem(nullptr);
        _mainGraphicsScene->selectItem();
        updateScene();
        position();
    }
}

void MainWindow::nextPushed()
{
    Interpret::mutex_.unlock();
}

void MainWindow::setupConnections()
{
    connect(ui->AssignBtn, &QPushButton::clicked, this, &MainWindow::addAssign);
    connect(ui->WhileBtn, &QPushButton::clicked, this, &MainWindow::addWhile);
    connect(ui->IfBtn, &QPushButton::clicked, this, &MainWindow::addIf);
    connect(ui->editBtn, &QPushButton::clicked, this, &MainWindow::Edit);
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
    connect(ui->nextBtn, &QPushButton::clicked, this, &MainWindow::nextPushed);
    connect(ui->printBtn, &QPushButton::clicked, this, &MainWindow::addPrint);
    connect(ui->inputBtn,&QPushButton::clicked,this,&MainWindow::addInput);
}

void MainWindow::setupActions()
{
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onActionOpen);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onActionSave);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::onActionExit);
    connect(ui->actionRun, &QAction::triggered, this, &MainWindow::onActionRun);
    connect(ui->actionDebug, &QAction::triggered, this, &MainWindow::onActionDebug);
    connect(ui->actionBuild, &QAction::triggered, this, &MainWindow::onActionBuild);
}

void MainWindow::onActionOpen()
{
    QString fileName = QFileDialog::getOpenFileName(
         this,
         tr("Open Visual"), ".",
         tr("JSON (*.json)"));
    auto mb = Serializer::load(fileName);
    auto tmp = dynamic_cast<BlockAST*>(ExprAST::makeFromVariant(mb));
    if(tmp != nullptr){
        delete mainBlock;
        mainBlock = tmp;
        backPushed();
        _mainGraphicsScene->clear();
        initMainBlock();
    } else {
        catchResult("Failed to open");
    }
}

void MainWindow::initMainBlock(){
    exprItem = nullptr;
    _mainGraphicsScene->addItem(mainBlock);
    connect(mainBlock, &ExprAST::ShouldUpdateScene, this, &MainWindow::updateScene);
    connect(mainBlock, &ExprAST::selectItem, _mainGraphicsScene, &mainGraphicsScene::setSelectedItem);
    connect(mainBlock, &ExprAST::updateSelection, _mainGraphicsScene, &mainGraphicsScene::selectItem);
    _mainGraphicsScene->setSelectedItem(nullptr);
    updateScene();
    position();
}

void MainWindow::onActionSave()
{
    QString fileName = QFileDialog::getSaveFileName(
            this,
            tr("Save Visual"), ".",
            tr("JSON (*.json)"));
    if (!fileName.endsWith(".json")){
        fileName.append(".json");
    }
    Serializer::save(*mainBlock,fileName);
}


void MainWindow::onActionExit()
{
    QMessageBox::StandardButton response = QMessageBox::question(
           this, "Exit", "Force exit?", QMessageBox::Yes| QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes
    );

    if (response == QMessageBox::Yes) {
        MainWindow::close();
    }
    else {
        return;
    }
}

void MainWindow::catchResult(QString result)
{
    if (result.isEmpty()) {
        QMessageBox::information(this, "Success", "Finished successfully");
    }
    else {
        QMessageBox::information(this, "Failure", result);
    }

}

void MainWindow::onActionRun()
{
    State::Domains().clear();
    Interpret::steps = false;
    auto terminal = new PseudoTerminal(this);
    terminal->show();
    QThread* thread = new QThread;
    Worker* worker = new Worker(mainBlock);
    worker->moveToThread(thread);
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(worker, SIGNAL(sendPrintText(QString)), terminal, SLOT(addLine(QString)));
    connect(worker, SIGNAL(sendResult(QString)), this, SLOT(catchResult(QString)));
    connect(worker,SIGNAL(changeButtonSettings(bool)),terminal,SLOT(changeBtnSettings(bool)));
    thread->start();
}

void MainWindow::onActionDebug()
{
    State::Domains().clear();
    ui->nextBtn->show();
    Interpret::steps = true;
    auto terminal = new PseudoTerminal(this);
    terminal->show();
    QThread* thread = new QThread;
    Worker* worker = new Worker(mainBlock);
    worker->moveToThread(thread);
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(worker, SIGNAL(finished()), ui->nextBtn, SLOT(hide()));
    connect(worker, SIGNAL(sendPrintText(QString)), terminal, SLOT(addLine(QString)));
    connect(worker, SIGNAL(sendResult(QString)), this, SLOT(catchResult(QString)));
    connect(worker, SIGNAL(changeButtonSettings(bool)),terminal, SLOT(changeBtnSettings(bool)));
    thread->start();
}


void MainWindow::onActionBuild()
{
    if (!isAlreadyCompiled) {
        isAlreadyCompiled = true;
        QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Save Visual"), ".",
                tr("Object File (*.o)"));
        if(!fileName.endsWith(".o"))
        {
            fileName.append(".o");
        }

        Compile::InitializeModuleAndPassManager();
        State::Domains().clear();
        auto res = Compile{mainBlock}.getValue();

        if(res.isEmpty()){
            Compile::compile(fileName);
        }

        catchResult(res);
    }
    else {
        catchResult("Cannot compile more than once.");
    }
}


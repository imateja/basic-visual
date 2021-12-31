#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QMutex>
#include <exprtree.hpp>
#include <maingraphicsscene.hpp>
#include <pseudoterminal.hpp>

class QGraphicsScene;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    BlockExprAST* mainBlock;
    ExprAST* exprItem;
    qint32 factor;

signals:
    void newSquareOnGV(InstructionExprAST*);

private slots:

    void addConst();
    void addVar();

    void addNot();
    void addMul();
    void addDiv();
    void addPlus();
    void addMinus();
    void addLs();
    void addLseq();
    void addGt();
    void addGteq();
    void addEq();
    void addNeq();
    void addAnd();
    void addOr();

    void addAssign();
    void addIf();
    void addWhile();
    void addPrint();

    void Edit();
    void addInput();
    void addExpr(ExprAST*);
    void backPushed();
    void deletePushed();
    void nextPushed();

private:
    void addInstruction(InstructionExprAST*);
    void onActionOpen();
    void onActionSave();
    void onActionSaveAs();
    void onActionExit();
    void onActionRun();
    void onActionDebug();
    void onActionBuild();
    Ui::MainWindow *ui;
    mainGraphicsScene *_mainGraphicsScene;
    QVector<Instruction*> _instructions;
    void setupActions();
    void setupConnections();
    void positionElement(InstructionExprAST* elem, qint32 factor);
    inline ExprAST* stagedItem();
    void initMainBlock();

public slots:
    void updateScene();
    void position();
    void catchResult(QString);

    // QObject interface
public:
    bool eventFilter(QObject* watched, QEvent* event) override;
};

#endif // MAINWINDOW_H

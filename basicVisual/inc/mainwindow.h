#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include "exprtree.h"
#include "maingraphicsscene.hpp"
#include <QDebug>

class QGraphicsScene;
class Instruction;
//class InstructionContainer;

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
    void newSquareOnGV(InstructionExprAST *);

private slots:

    void addAssign();
    void addWhile();
    void addIf();
    void Edit();
    void addExpr(ExprAST*);
    void addPlus();
    void addMinus();
    void addMul();
    void addDiv();
    void addLs();
    void addGt();
    void addLseq();
    void addGteq();
    void addAnd();
    void addOr();
    void addNot();
    void addEq();
    void addNeq();
    void addVar();
    void addConst();
    void backPushed();

private:
    void addInstruction(InstructionExprAST*);
    void onActionOpen();
    void onActionSave();
    void onActionSaveAs();
    void onActionExit();
    Ui::MainWindow *ui;
    mainGraphicsScene *_mainGraphicsScene;
    QVector<Instruction*> _instructions;
    void setupActions();
    void setupConnections();
    void positionElement(InstructionExprAST* elem, qint32 factor);
    inline ExprAST* stagedItem();


public slots:
    void updateScene();
    void position();


    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // MAINWINDOW_H

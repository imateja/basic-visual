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
    qint32 factor;

signals:
    void newSquareOnGV(InstructionExprAST *);

private slots:

    void addAssign();
    void addWhile();
    void addIf();
    void Edit();

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
    inline BlockExprAST* getInsertionBlock();
    void positionElement(InstructionExprAST* elem, qint32 factor);

};

#endif // MAINWINDOW_H

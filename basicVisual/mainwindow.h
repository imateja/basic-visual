#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include "instruction.h"
#include "instructioncontainer.h"

class QGraphicsScene;
class Instruction;
class InstructionContainer;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void newSquareOnGV(InstructionContainer *);

private slots:
    void addInstruction();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *_mainGraphicsView;
    QVector<Instruction*> _instructions;
};

#endif // MAINWINDOW_H

#ifndef MAINGRAPHICSVIEW_HPP
#define MAINGRAPHICSVIEW_HPP
#include <QGraphicsScene>
#include "exprtree.h"

class InstructionContainer;
class Instruction;

class mainGraphicsView : public QGraphicsScene
{
public:
    explicit mainGraphicsView(QObject *parent = nullptr);

public slots:
    //This should work for all the instruction we will overide shape and colour for specific instructions
    void addedSquareOnGV(InstructionExprAST *node);
    void SquareSelectedOnGV(InstructionExprAST *node);
    ;

private:
    void PositionNewNode(InstructionExprAST *node);
    void drawConnections();
    void SquareIsSelected();
    //Here we make vectors of all the statments that we have
    //Or maybe this kind of super container could work for all Instructions it depends on implementation of the codegen team
    //And how should our Instructions propagate their properties to codegen part of the project
    QVector<InstructionExprAST*> instructionVector_;
    QVector<QGraphicsLineItem *> lines_;
};



#endif // MAINGRAPHICSVIEW_HPP

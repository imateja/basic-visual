#ifndef MAINGRAPHICSSCENE_H
#define MAINGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QDebug>
#include <exprtree.hpp>

class InstructionContainer;
class Instruction;

class mainGraphicsScene : public QGraphicsScene
{
public:
    explicit mainGraphicsScene(QObject *parent = nullptr);

    void clearItems();
    inline ExprAST* getSelectedItem(){return selectedItem_;}

public slots:
    //This should work for all the instruction we will overide shape and colour for specific instructions
    void addedSquareOnGV(InstructionExprAST *node);
    void SquareSelectedOnGV(InstructionExprAST *node);
    void setSelectedItem(ExprAST* item);
    void selectItem();


private:
    void PositionNewNode(InstructionExprAST *node);

    void drawConnections();
    void SquareIsSelected();
    //Here we make vectors of all the statments that we have
    //Or maybe this kind of super container could work for all Instructions it depends on implementation of the codegen team
    //And how should our Instructions propagate their properties to codegen part of the project
    QVector<InstructionExprAST*> instructionVector_;
    QVector<QGraphicsLineItem *> lines_;

    ExprAST* selectedItem_;
};



#endif // MAINGRAPHICSSCENE_H

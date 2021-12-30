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
    void setSelectedItem(ExprAST* item);
    void selectItem();

private:
    ExprAST* selectedItem_;
};



#endif // MAINGRAPHICSSCENE_H

#include "inc/maingraphicsview.hpp"
#include "inc/instructioncontainer.h"
#include "inc/instruction.h"
#include <QDebug>

#include "inc/exprtree.h"


mainGraphicsView::mainGraphicsView(QObject *parent)
    :QGraphicsScene(parent)
{

}
//Adds square to the vector and draws it on the main graphics view
//TODO:Make squares movable and connected
void mainGraphicsView::addedSquareOnGV(InstructionExprAST *node)
{
    //connect(node, &InstructionExprAST::Moved, this, &mainGraphicsView::drawConnections);
    connect(node,&InstructionExprAST::signalSelected,this,[=](){
        qDebug()<< node->instructionName_;
        ExprTree::Tree().selected = node;
    });

    instructionVector_.append(node);
    PositionNewNode(node);


//    drawConnections();
}
//Positions the new node so there is no overlap
//TODO:make squares be close together under eachother
void mainGraphicsView::PositionNewNode(InstructionExprAST *node)
{
    const auto graphicsViewWidth = mainGraphicsView::width();
    qDebug()<<graphicsViewWidth<<"\n";
    auto numNewNode = 0;

    numNewNode =instructionVector_.size()-1;

    //const auto xPos = (node->getWidth() * numNewNode) % graphicsViewWidth;
    const auto yPos = node->getHeight() * ((node->getWidth() * numNewNode) / graphicsViewWidth);

    node->setPos(graphicsViewWidth/2 +300,yPos);

    qDebug()<<node->pos()<<" inside emit"<<"\n";
}

void mainGraphicsView::PositionNewNode(ThenElseExprAST *thenblock,ThenElseExprAST* elseblock, QPointF pos)
{
    const auto graphicsViewWidth = static_cast<int>(this->width());
    auto numNewNode = 0;

    numNewNode =instructionVector_.size()-1;



    thenblock->setPos(pos.x()-50, pos.y() + 100);
    elseblock->setPos(pos.x()+50, pos.y()+100);
}


void mainGraphicsView::SquareIsSelected(){
   qDebug() << "Selectovano je";
}

//void mainGraphicsView::drawConnections()
//{
//    //TODO: fix horrible complexity
//    for (auto line : _lines)
//    {
//        this->removeItem(line);
//        delete line;
//    }
//    _lines.clear();


//    for(int i=0; i<_assignInstructionVector.size(); ++i)
//    {
//        if(i==0) continue;

//        QLineF line(_assignInstructionVector[i]->posCenterTop(), _assignInstructionVector[i-1]->posCenterBottom());

//        auto newline= new QGraphicsLineItem(line);
//        _lines.append(newline);
//        this->addItem(newline);
//    }

//}











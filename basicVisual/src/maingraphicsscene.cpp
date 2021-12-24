#include "inc/maingraphicsscene.hpp"
#include "inc/instructioncontainer.h"
#include "inc/instruction.h"
#include <QDebug>

#include "inc/exprtree.h"


mainGraphicsScene::mainGraphicsScene(QObject *parent)
    :QGraphicsScene(parent)
{

}

void mainGraphicsScene::clearItems()
{
    for (auto elem : items()) {
        removeItem(elem);
    }
}
//Adds square to the vector and draws it on the main graphics view
//TODO:Make squares movable and connected

void mainGraphicsScene::addedSquareOnGV(InstructionExprAST *node)
{
    //connect(node, &InstructionExprAST::Moved, this, &mainGraphicsView::drawConnections);


    instructionVector_.append(node);
    PositionNewNode(node);


//    drawConnections();
}

void mainGraphicsScene::updateScene(){
    this->update();
    qDebug()<<"Scena se updatovala";
}

//Positions the new node so there is no overlap
//TODO:make squares be close together under eachother
void mainGraphicsScene::PositionNewNode(InstructionExprAST *node)
{
    const auto graphicsViewWidth = mainGraphicsScene::width();
    qDebug()<<graphicsViewWidth<<"\n";
    auto numNewNode = 0;

    numNewNode =instructionVector_.size()-1;

    //const auto xPos = (node->getWidth() * numNewNode) % graphicsViewWidth;
    const auto yPos = node->getHeight() * ((node->getWidth() * numNewNode) / graphicsViewWidth);
    QRectF rect = sceneRect();
    QPointF center = rect.center();

    //QPointF sceneCenter = _mainGraphicsView->mapToScene( view->viewport()->rect().center() );

    node->setPos(center.x(),center.y());

    qDebug()<<node->pos()<<" inside emit"<<"\n";
}

void mainGraphicsScene::SquareIsSelected(){
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











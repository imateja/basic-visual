#include "maingraphicsview.hpp"
#include "instructioncontainer.h"
#include "instruction.h"


mainGraphicsView::mainGraphicsView(QObject *parent)
    :QGraphicsScene(parent)
{

}
//Adds square to the vector and draws it on the main graphics view
//TODO:Make squares movable and connected
void mainGraphicsView::addedSquareOnGV(InstructionContainer *node)
{
    if(node->instruction()->getInstructionType() == Instruction::TypeOfInstruction::ASSIGN)
    {
        _assignInstructionVector.append(node);
    }

    else if(node->instruction()->getInstructionType() == Instruction::TypeOfInstruction::WHILE)
    {
        _assignInstructionVector.append(node);
    }

    else if(node->instruction()->getInstructionType() == Instruction::TypeOfInstruction::IF)
    {
        _assignInstructionVector.append(node);
    }

    else if(node->instruction()->getInstructionType() == Instruction::TypeOfInstruction::FOR)
    {
        _assignInstructionVector.append(node);
    }
    //TODO:Check what to do in the case where node has a TypeOfInsctruction that doesn't exist (maybe throw error)

    PositionNewNode(node);
}
//Positions the new node so there is no overlap
//TODO:make squares be close together under eachother
void mainGraphicsView::PositionNewNode(InstructionContainer *node)
{
    const auto graphicsViewWidth = static_cast<int>(this->width());
    auto numNewNode = 0;
    //TODO:add here conditions for other instructions
    if(node->instruction()->getInstructionType() == Instruction::TypeOfInstruction::ASSIGN)
    {
        numNewNode = _assignInstructionVector.size()-1;
    }

    else if(node->instruction()->getInstructionType() == Instruction::TypeOfInstruction::WHILE)
    {
        numNewNode = _assignInstructionVector.size()-1;
    }

    else if(node->instruction()->getInstructionType() == Instruction::TypeOfInstruction::IF)
    {
        numNewNode = _assignInstructionVector.size()-1;
    }

    else if(node->instruction()->getInstructionType() == Instruction::TypeOfInstruction::FOR)
    {
        numNewNode = _assignInstructionVector.size()-1;
    }

    const auto xPos = (node->getWidth() * numNewNode) % graphicsViewWidth;
    const auto yPos = node->getHeight() * ((node->getWidth() * numNewNode) / graphicsViewWidth);
    node->setPos(xPos,yPos);
}

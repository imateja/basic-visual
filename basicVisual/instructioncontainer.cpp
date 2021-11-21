#include "instructioncontainer.h"
#include <QPainter>
#include "instruction.h"

InstructionContainer::InstructionContainer(Instruction *instructions)
    :QGraphicsObject()
    ,_instructions(instructions)
{
     setFlags(GraphicsItemFlag::ItemIsSelectable);
}
//TODO: This getWidth() and getHeight() shoud be the proporties of specific classes that are subclass of Instruction
QRectF InstructionContainer::boundingRect() const
{
    return QRectF(0, 0, getWidth(), getHeight());
}

void InstructionContainer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   //TODO: check what i can do with this options
    Q_UNUSED(option)
    Q_UNUSED(widget)
   //TODO: Pen and colour should also be properties of subclasses
   //FIX: Colour and pen shouldnt be hardcoded
    if (_instructions->getInstructionType() == Instruction::TypeOfInstruction::ASSIGN)
    {
        painter->fillRect(boundingRect(), QColor::fromRgb(118, 83, 219));
        painter->setPen(Qt::white);

    const auto SquareText = QString("%1\n%2").arg(_instructions->getInstructionText(), _instructions->TypeOfInstructionToString());
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    }

    else if (_instructions->getInstructionType() == Instruction::TypeOfInstruction::WHILE)
    {
        painter->fillRect(boundingRect(), QColor::fromRgb(48, 213, 200));
        painter->setPen(Qt::white);

    const auto SquareText = QString("%1\n%2").arg(_instructions->getInstructionText(), _instructions->TypeOfInstructionToString());
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    }

    else if (_instructions->getInstructionType() == Instruction::TypeOfInstruction::IF)
    {
        painter->fillRect(boundingRect(), QColor::fromRgb(255, 191, 0));
        painter->setPen(Qt::white);

    const auto SquareText = QString("%1\n%2").arg(_instructions->getInstructionText(), _instructions->TypeOfInstructionToString());
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    }

    else if (_instructions->getInstructionType() == Instruction::TypeOfInstruction::FOR)
    {
        painter->fillRect(boundingRect(), QColor::fromRgb(128, 128, 0));
        painter->setPen(Qt::white);

    const auto SquareText = QString("%1\n%2").arg(_instructions->getInstructionText(), _instructions->TypeOfInstructionToString());
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    }

    //TODO:Default case (maybe throw error)
}

QPointF InstructionContainer::posCenterTop() const
    {
        return pos() + QPointF((getWidth()/2),0);
    }
QPointF InstructionContainer::posCenterBottom() const
    {
        return pos() + QPointF((getWidth()/2),getHeight());
    }




#ifndef INSTRUCTIONCONTAINER_H
#define INSTRUCTIONCONTAINER_H
#include <QGraphicsObject>
#include "instruction.h"

class Instruction;


class InstructionContainer : public QGraphicsObject
{
    Q_OBJECT

public:
    InstructionContainer(Instruction *instructions);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    inline const Instruction *instruction() const
       {
           return _instructions;
       }
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override ;
    QPointF posCenterTop() const;
    QPointF posCenterBottom() const;
   //This should be propagated from the subclases of the Instruction class
   //Or maybe we should make a container for every subclass (that should be discussed and decided until the next week)
    inline qint32 getWidth() const { return 150; }
    inline qint32 getHeight() const { return 50; }


signals:
    void Moved();
    void signalSelected();

private:
    Instruction* _instructions;


};

#endif // INSTRUCTIONCONTAINER_H

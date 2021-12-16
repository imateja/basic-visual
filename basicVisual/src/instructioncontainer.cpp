//#include "inc/instructioncontainer.h"
//#include <QPainter>
//#include "inc/instruction.h"

//InstructionContainer::InstructionContainer(InstructionExprAST *instruction, InstructionContainer* next)
//    :QGraphicsObject()
//    ,instruction_(instruction)
//    ,next_(next)
//{
//     setFlags(GraphicsItemFlag::ItemIsSelectable | GraphicsItemFlag::ItemIsMovable | GraphicsItemFlag::ItemIsFocusable);
//}
////TODO: This getWidth() and getHeight() shoud be the proporties of specific classes that are subclass of Instruction
//QRectF InstructionContainer::boundingRect() const
//{
//    return QRectF(0, 0, getWidth(), getHeight());
//}

//void InstructionContainer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{

//   //TODO: check what i can do with this options
//    Q_UNUSED(option)
//    Q_UNUSED(widget)
//   //TODO: Pen and colour should also be properties of subclasses
//   //FIX: Colour and pen shouldnt be hardcoded

//    painter->fillRect(boundingRect(), instruction_->color_);
//    painter->setPen(Qt::white);
//    const auto SquareText = QString("%1\n%2").arg(instruction_->instructionName_, instruction_->instructionName_);
//    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

//    //TODO:Default case (maybe throw error)
//}

//QPointF InstructionContainer::posCenterTop() const
//    {
//        return pos() + QPointF((getWidth()/2),0);
//    }
//QPointF InstructionContainer::posCenterBottom() const
//    {
//        return pos() + QPointF((getWidth()/2),getHeight());
//    }

//void InstructionContainer::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    QGraphicsObject::mouseMoveEvent(event);

//    //TODO:Emit signal that the item is moved
//    emit Moved();


//}
//void InstructionContainer::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

//    QGraphicsObject::mouseDoubleClickEvent(event);
//    QGraphicsObject::setSelected(true);

//    emit signalSelected();
//}

//InstructionContainer::~InstructionContainer(){
//    delete instruction_;
//}


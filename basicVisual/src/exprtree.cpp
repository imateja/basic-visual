#include "inc/exprtree.h"

ExprTree::~ExprTree(){
    delete program_;
}

void WhileExprAST::AcceptVisit(VisitorAST& v){
    v.VisitWhileExprAST(*this);
}
void IfExprAST::AcceptVisit(VisitorAST& v){
    v.VisitIfExprAST(*this);
}
void AssignExprAST::AcceptVisit(VisitorAST& v){
    v.VisitAssignExprAST(*this);
}
void BlockExprAST::AcceptVisit(VisitorAST& v){
    v.VisitBlockExprAST(*this);
}
void FunctionExprAST::AcceptVisit(VisitorAST& v){
    v.VisitFunctionExprAST(*this);
}
void EndExprAST::AcceptVisit(VisitorAST& v){
    v.VisitEndExprAST(*this);
}

void StartExprAST::AcceptVisit(VisitorAST& v){
    v.VisitStartExprAST(*this);
}
void ThenElseExprAST::AcceptVisit(VisitorAST& v){
    v.VisitThenElseExprAST(*this);
}

    IfExprAST::~IfExprAST(){
        delete cond_;
        delete then_;
        delete else_;
    }

    WhileExprAST::~WhileExprAST(){
        delete cond_;
        delete body_;
    }

    AssignExprAST::~AssignExprAST(){
        delete expr_;
    }

    BlockExprAST::~BlockExprAST(){
        while(auto next = body_->next_){
            delete body_;
            body_ = next;
        }
        delete body_;
    }
    StartExprAST::~StartExprAST(){

    }
    EndExprAST::~EndExprAST(){

    }
FunctionExprAST::~FunctionExprAST(){
    delete body_;
}

void InstructionExprAST::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);

    //TODO:Emit signal that the item is moved
    emit Moved();


}
void InstructionExprAST::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

    QGraphicsObject::mouseDoubleClickEvent(event);
    QGraphicsObject::setSelected(true);

    emit signalSelected();
}
//-----------------------COPY---------------------
//ExprAST* IfExprAST::copy() const{
//    return new IfExprAST(*this);
//}

//ExprAST* WhileExprAST::copy() const{
//    return new WhileExprAST(*this);
//}

//ExprAST* AssignExprAST::copy() const{
//    return new AssignExprAST(*this);
//}

//ExprAST* BlockExprAST::copy() const{
//    return new BlockExprAST(*this);
//}

//ExprAST* FunctionExprAST::copy() const{
//    return new FunctionExprAST(*this);
//}

//ExprAST* EndExprAST::copy() const{
//    return new EndExprAST(*this);
//}

//ExprAST* StartExprAST::copy() const{
//    return new EndExprAST(*this);
//}
void AssignExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   //TODO: check what i can do with this options
    Q_UNUSED(option)
    Q_UNUSED(widget)
   //TODO: Pen and colour should also be properties of subclasses
   //FIX: Colour and pen shouldnt be hardcoded

    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);
    const auto SquareText = QString("%1\n%2").arg(instructionName_, instructionName_);
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

    //TODO:Default case (maybe throw error)
}
void IfExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   //TODO: check what i can do with this options
    Q_UNUSED(option)
    Q_UNUSED(widget)
   //TODO: Pen and colour should also be properties of subclasses
   //FIX: Colour and pen shouldnt be hardcoded

    painter->fillRect(boundingRect(), color_);
    painter->drawEllipse(20,30,20,20);
    painter->setPen(Qt::white);
    const auto SquareText = QString("%1\n%2").arg(instructionName_, instructionName_);
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

    //TODO:Default case (maybe throw error)
}
void WhileExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   //TODO: check what i can do with this options
    Q_UNUSED(option)
    Q_UNUSED(widget)
   //TODO: Pen and colour should also be properties of subclasses
   //FIX: Colour and pen shouldnt be hardcoded

    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);
    const auto SquareText = QString("%1\n%2").arg(instructionName_, instructionName_);
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

    //TODO:Default case (maybe throw error)
}
void EndExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   //TODO: check what i can do with this options
    Q_UNUSED(option)
    Q_UNUSED(widget)
   //TODO: Pen and colour should also be properties of subclasses
   //FIX: Colour and pen shouldnt be hardcoded

    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);
    const auto SquareText = QString("%1\n%2").arg(instructionName_, instructionName_);
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

    //TODO:Default case (maybe throw error)
}
void StartExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   //TODO: check what i can do with this options
    Q_UNUSED(option)
    Q_UNUSED(widget)
   //TODO: Pen and colour should also be properties of subclasses
   //FIX: Colour and pen shouldnt be hardcoded

    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);
    const auto SquareText = QString("%1\n").arg("start");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

    //TODO:Default case (maybe throw error)
}
void ThenElseExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   //TODO: check what i can do with this options
    Q_UNUSED(option)
    Q_UNUSED(widget)
   //TODO: Pen and colour should also be properties of subclasses
   //FIX: Colour and pen shouldnt be hardcoded

    painter->fillRect(boundingRect(), QColor::fromRgb(128,128,0));
    painter->setPen(Qt::white);
    const auto SquareText = QString("%1").arg(name_);
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

    //TODO:Default case (maybe throw error)
}
QRectF ThenElseExprAST::boundingRect() const
{
    return QRectF(250, 0, 100, 70);
}

QRectF AssignExprAST::boundingRect() const
{
    float w=160;
    float h=80;
    return QRectF(-w/2, -h/2, w, h);
}

QRectF WhileExprAST::boundingRect() const
{
    return QRectF(0, 0, 150, 200);
}

QRectF IfExprAST::boundingRect() const
{
    return QRectF(0, 0, getWidth(), getHeight());
}

QRectF StartExprAST::boundingRect() const
{
    float w=160;
    float h=80;
    return QRectF(-w/2, 0, w, h);
}

QRectF EndExprAST::boundingRect() const
{
    return QRectF(0, 0, 150, 200);
}

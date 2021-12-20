#include "inc/exprtree.h"

//ExprTree::~ExprTree(){
//    delete program_;
//}

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
       for(auto& next : body_)
            delete next;
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

    emit signalSelected();

    QGraphicsObject::mouseDoubleClickEvent(event);
    QGraphicsObject::setSelected(true);
    qDebug()<<"blaaaa"<<"\n";


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

    painter->fillRect(boundingRect(), QColor::fromRgb(0,128,0));
    painter->setPen(Qt::white);
    const auto SquareText = QString("%1\n").arg("start");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

    //TODO:Default case (maybe throw error)
}
void BlockExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   //TODO: check what i can do with this options
    Q_UNUSED(option)
    Q_UNUSED(widget)
   //TODO: Pen and colour should also be properties of subclasses
   //FIX: Colour and pen shouldnt be hardcoded
    const float gap=10.0f;
    w=0.0f;
    h=0.0f;
    for(auto &elem : body_) {
        if(elem->getWidth()>w)
            w=elem->getWidth();
        h+=elem->getHeight();
        h+=gap;
    }
    h-=gap;
    w += 30;
    h+= 30;
    painter->fillRect(boundingRect(), color_);
    //painter->setPen(Qt::white);
    //const auto SquareText = QString("%1\n%2").arg(instructionName_, instructionName_);
    //painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    qint32 factor=0;
    for(auto &elem : body_) {
        elem->setPos(0,factor*(80.0+gap));
        elem->update();
        factor++;
    }


    qDebug()<<"jel si usao: "<<body_.size()<<"\n";
    //TODO:Default case (maybe throw error)
}
QRectF InstructionExprAST::boundingRect() const
{
    return QRect(-w/2,-h/2,w,h);
}
//QRectF AssignExprAST::boundingRect() const
//{
//    float w=160;
//    float h=80;
//    return QRectF(-w/2, 0, w, h);
//}

void BlockExprAST::insert(InstructionExprAST* newinstr, InstructionExprAST* posinstr){
    if (posinstr == nullptr){
        body_.push_back(newinstr);
    }else {
        auto pos = body_.indexOf(posinstr);
        if (pos != -1){
            body_.insert(pos+1, newinstr);
        }else {
            //TODO error handling
        }
    }
}



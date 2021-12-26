#include "inc/ast.h"

//--------------------ACCEPT VISIT--------------------

void PlaceholderExprAST::AcceptVisit(VisitorAST& v){
    v.VisitPlaceholderExprAST(*this);
}
void ValueExprAST::AcceptVisit(VisitorAST& v){
    v.VisitValueExprAST(*this);
}
void VariableExprAST::AcceptVisit(VisitorAST& v){
    v.VisitVariableExprAST(*this);
}
void NotExprAST::AcceptVisit(VisitorAST& v){
    v.VisitNotExprAST(*this);
}
void MulExprAST::AcceptVisit(VisitorAST& v){
    v.VisitMulExprAST(*this);
}
void DivExprAST::AcceptVisit(VisitorAST& v){
    v.VisitDivExprAST(*this);
}
void AddExprAST::AcceptVisit(VisitorAST& v){
    v.VisitAddExprAST(*this);
}
void SubExprAST::AcceptVisit(VisitorAST& v){
    v.VisitSubExprAST(*this);
}
void LtExprAST::AcceptVisit(VisitorAST& v){
    v.VisitLtExprAST(*this);
}
void LeqExprAST::AcceptVisit(VisitorAST& v){
    v.VisitLeqExprAST(*this);
}
void GtExprAST::AcceptVisit(VisitorAST& v){
    v.VisitGtExprAST(*this);
}
void GeqExprAST::AcceptVisit(VisitorAST& v){
    v.VisitGeqExprAST(*this);
}
void EqExprAST::AcceptVisit(VisitorAST& v){
    v.VisitEqExprAST(*this);
}
void NeqExprAST::AcceptVisit(VisitorAST& v){
    v.VisitNeqExprAST(*this);
}
void AndExprAST::AcceptVisit(VisitorAST& v){
    v.VisitAndExprAST(*this);
}
void OrExprAST::AcceptVisit(VisitorAST& v){
    v.VisitOrExprAST(*this);
}

//--------------------OPERATOR=--------------------

//BinaryExprAST& BinaryExprAST::operator= (const BinaryExprAST& be){
//    if(&be != this){
//        delete left_;
//        delete right_;
//        left_ = be.left_->copy();
//        right_ = be.right_->copy();
//    }
//    return *this;
//}

//IfExprAST& IfExprAST::operator= (const IfExprAST& ie){
//    if(&ie != this){
//        delete cond_;
//        delete then_;
//        delete else_;
//        cond_ = ie.cond_->copy();
//        then_ = static_cast<BlockExprAST*>(ie.then_->copy());
//        else_ = static_cast<BlockExprAST*>(ie.else_->copy());
//    }
//    return *this;
//}

//WhileExprAST& WhileExprAST::operator= (const WhileExprAST& we){
//    if(&we != this){
//        delete cond_;
//        delete body_;
//        cond_ = we.cond_->copy();
//        body_ = static_cast<BlockExprAST*>(we.body_->copy());
//    }
//    return *this;
//}

//AssignExprAST& AssignExprAST::operator= (const AssignExprAST& ae){
//    if(&ae != this){
//        delete expr_;
//        expr_ = ae.expr_->copy();
//    }
//    return *this;
//}

//BlockExprAST& BlockExprAST::operator= (const BlockExprAST& be){
//    if(&be != this){
//        for(auto &x : body_){
//            delete x;
//        }
//        body_ = be.body_;
//    }
//    return *this;

//}

//FunctionExprAST& FunctionExprAST::operator= (const FunctionExprAST& fe){
//    if(&fe != this){
//        delete body_;
//        body_ = static_cast<BlockExprAST*>(fe.body_->copy());
//    }
//    return *this;
//}

//--------------------DESTRUCTORS--------------------

NotExprAST::~NotExprAST() {
    delete operand_;
}

BinaryExprAST::~BinaryExprAST(){
    delete left_;
    delete right_;
}

//--------------------COPY CONSTRUCTORS--------------------

//BinaryExprAST::BinaryExprAST(const BinaryExprAST& be){
//    left_ = be.left_->copy();
//    right_ = be.right_->copy();
//}

//IfExprAST::IfExprAST(const IfExprAST& ie){
//    cond_ = ie.cond_->copy();
//    then_ = static_cast<BlockExprAST*>(ie.then_->copy());
//    else_ = static_cast<BlockExprAST*>(ie.else_->copy());
//}

//WhileExprAST::WhileExprAST(const WhileExprAST& we){
//    cond_ = we.cond_->copy();
//    body_ = static_cast<BlockExprAST*>(we.body_->copy());
//}

//AssignExprAST::AssignExprAST(const AssignExprAST& ae){
//    name_ = ae.name_;
//    expr_ = ae.expr_->copy();
//}

//BlockExprAST::BlockExprAST(const BlockExprAST& be){
//    body_ = be.body_;
//}

//FunctionExprAST::FunctionExprAST(const FunctionExprAST& fe){
//    name_ = fe.name_;
//    body_ = static_cast<BlockExprAST*>(fe.body_->copy());
//}

//--------------------COPY--------------------

//ExprAST* ValueExprAST::copy() const{
//    return new ValueExprAST(*this);
//}

//ExprAST* VariableExprAST::copy() const{
//    return new VariableExprAST(*this);
//}

//ExprAST* AddExprAST::copy() const{
//    return new AddExprAST(*this);
//}

//ExprAST* SubExprAST::copy() const{
//    return new SubExprAST(*this);
//}

//ExprAST* MulExprAST::copy() const{
//    return new MulExprAST(*this);
//}

//ExprAST* DivExprAST::copy() const{
//    return new DivExprAST(*this);
//}

//ExprAST* LtExprAST::copy() const{
//    return new LtExprAST(*this);
//}

//ExprAST* GtExprAST::copy() const{
//    return new GtExprAST(*this);
//}


//--------------------------------------------



//TEMP
//unsigned BlockExprAST::size(){
//   return body_.size();
//}

//InstructionContainer* BlockExprAST::at(unsigned i){
//    return body_.at(i);
//}

//--------------------SETTERS--------------------

void BinaryExprAST::setLeft(ExprAST* expr)
{
    delete left_;
    left_ = expr;
}

void BinaryExprAST::setRight(ExprAST* expr)
{
    delete right_;
    right_ = expr;
}

//--------------------------------------------

void ExprAST::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);

    //TODO:Emit signal that the item is moved
    emit Moved();


}
void ExprAST::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

    emit signalSelected();

    QGraphicsObject::mouseDoubleClickEvent(event);
    QGraphicsObject::setSelected(true);
    qDebug()<<"blaaaa"<<"\n";


}

QRectF ExprAST::boundingRect() const
{
    return QRect(-w/2,-h/2,w,h);
}
//QRectF StartExprAST::boundingRect() const
//{
//    return QRect(-w/2,-h/2, w,h-30);
//}

//------------ STRINGIFY ------------
QString PlaceholderExprAST::stringify() {
    // TODO error handling
    return {};
}

QString ValueExprAST::stringify() {
    return QString::number(value_);
}

QString VariableExprAST::stringify() {
    return name_;
}

QString NotExprAST::stringify() {
    QString op = operand_->stringify();
    return operand_->getPriority() > getPriority() ? "!(" + op + ")" : "!" + op;
}

QString BinaryExprAST::stringify() {
    QString l = left_->stringify();
    QString r = right_->stringify();
    QString retVal;
    retVal += left_->getPriority() > getPriority() ? "(" + l + ")" : l;
    retVal += " " + op_ + " ";
    retVal += right_->getPriority() > getPriority() ? "(" + r + ")" : r;

    return retVal;
}

void PlaceholderExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
   //TODO: Pen and colour should also be properties of subclasses
   //FIX: Colour and pen shouldnt be hardcoded
    if(this->isSelected()){
        QBrush selectedBrush = QBrush(Qt::green,Qt::Dense1Pattern);
        painter->fillRect(boundingRect(),selectedBrush);
    }else {
        painter->fillRect(boundingRect(), QColor::fromRgb(128, 0, 0));
    }
    painter->setPen(Qt::white);
    const auto SquareText = QString("[ ]");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //TODO:Default case (maybe throw error)
    //emit ShouldUpdateScene();
}

//TODO implement paint functions

//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//---------------------------------------EXPRPAINTING-------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
void ValueExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

     Q_UNUSED(option)
     Q_UNUSED(widget)


     painter->fillRect(boundingRect(), color_);
     painter->setPen(Qt::white);

     const auto SquareText = QString("%1").arg("+");
     painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
     //idk da l treba ovo ovde | emit ShouldUpdateScene();
}
void VariableExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    const auto SquareText = QString("%1").arg("+");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //idk da l treba ovo ovde | emit ShouldUpdateScene();
}
void NotExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    const auto SquareText = QString("%1").arg("+");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //idk da l treba ovo ovde | emit ShouldUpdateScene();
}
void BinaryExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)

    w = h;
    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    const auto SquareText = QString("%1").arg(op_);
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    left_->setPos(-w/2, -h/2 + left_->getHeight()/2+100);
    right_->setPos(w/2, -h/2 + right_->getHeight()/2+100);
    emit ShouldUpdateScene();
}
/*
void MulExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    const auto SquareText = QString("%1").arg("+");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //idk da l treba ovo ovde | emit ShouldUpdateScene();
}
void DivExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    const auto SquareText = QString("%1").arg("+");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //idk da l treba ovo ovde | emit ShouldUpdateScene();
}
void AddExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    const auto SquareText = QString("%1").arg("+");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //idk da l treba ovo ovde | emit ShouldUpdateScene();
}
void SubExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    const auto SquareText = QString("%1").arg("+");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //idk da l treba ovo ovde | emit ShouldUpdateScene();
}
void LtExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    const auto SquareText = QString("%1").arg("+");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //idk da l treba ovo ovde | emit ShouldUpdateScene();
}
void LeqExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    const auto SquareText = QString("%1").arg("+");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //idk da l treba ovo ovde | emit ShouldUpdateScene();
}
void GtExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    const auto SquareText = QString("%1").arg("+");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //idk da l treba ovo ovde | emit ShouldUpdateScene();
}
void GeqExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    const auto SquareText = QString("%1").arg("+");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //idk da l treba ovo ovde | emit ShouldUpdateScene();
}
void EqExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    const auto SquareText = QString("%1").arg("+");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //idk da l treba ovo ovde | emit ShouldUpdateScene();
}
void NeqExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    const auto SquareText = QString("%1").arg("+");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //idk da l treba ovo ovde | emit ShouldUpdateScene();
}
void AndExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    const auto SquareText = QString("%1").arg("+");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //idk da l treba ovo ovde | emit ShouldUpdateScene();
}
void OrExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)


    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    const auto SquareText = QString("%1").arg("+");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //idk da l treba ovo ovde | emit ShouldUpdateScene();
}
*/

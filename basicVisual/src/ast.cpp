#include "inc/ast.h"
#include <QFontMetrics>

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

UnaryExprAST::~UnaryExprAST() {
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


void ExprAST::propagateSelectItem(ExprAST* item){
    emit selectItem(item);
}
void ExprAST::propagateUpdateSelection(){
    emit updateSelection();
}

void ExprAST::propagateShouldUpdateScene(){
    update();
    emit ShouldUpdateScene();
}

void ExprAST::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);

    //TODO:Emit signal that the item is moved
    emit Moved();


}
void ExprAST::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    emit selectItem(this);

    QGraphicsObject::mouseDoubleClickEvent(event);
}

void ExprAST::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    emit updateSelection();
}

void ExprAST::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    emit updateSelection();
}

QRectF ExprAST::boundingRect() const
{
    float w=150.0f;
    float h=80.0f;
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

QString UnaryExprAST::stringify() {
    QString op = operand_->stringify();
    return operand_->getPriority() > getPriority() ? op_ + "(" + op + ")" : op_ + op;
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

QBrush ExprAST::setBrush() {
    QBrush brush = QBrush(color_);
    if (errorFound) {
        brush.setColor(Qt::red);
        brush.setStyle(Qt::Dense1Pattern);
    }
    if(this->isSelected()){
        brush.setColor(Qt::green);
        brush.setStyle(Qt::Dense1Pattern);
    }
    return brush;
}

QRectF PlaceholderExprAST::boundingRect() const{
    float w=60;
    float h=60;
    return expr_ ? expr_->boundingRect():QRectF(-w/2,-h/2,w,h);
}

void PlaceholderExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
   //TODO: Pen and colour should also be properties of subclasses
   //FIX: Colour and pen shouldnt be hardcoded
    auto br = boundingRect();
    if(expr_){
        expr_->setPos(0,0);
    } else {
        painter->fillRect(br,setBrush());
        painter->setPen(Qt::white);
        painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, QString("[ ]"));   
    }
    emit ShouldUpdateScene();
}


//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//---------------------------------------EXPRPAINTING-------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------

QRectF ValueExprAST::boundingRect() const{
    float w=60;
    float h=60;
    return QRectF(-w/2,-h/2,w,h);
}
void ValueExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    Q_UNUSED(option)
    Q_UNUSED(widget)

    auto br = boundingRect();
    painter->fillRect(br, setBrush());
    painter->setPen(Qt::white);
    const auto SquareText = QString::number(value_);
    painter->drawText(br, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    emit ShouldUpdateScene();
}
QRectF VariableExprAST::boundingRect() const {
    float w=60;
    float h=60;
    return QRectF(-w/2,-h/2,w,h);
}
void VariableExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)

    auto br = boundingRect();
    painter->fillRect(br, setBrush());
    painter->setPen(Qt::white);

    const auto SquareText = name_;
    painter->drawText(br, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    emit ShouldUpdateScene();
}


QRectF UnaryExprAST::boundingRect() const{
    float w=0.0f;
    float h=0.0f;
    float opr = 60.0f;
    const float gap=10.0f;
    w += operand_->getWidth() + 2 * gap;
    h += operand_->getHeight() + gap*2 + opr;
    return QRect(-w/2,-h/2,w,h);
}
void UnaryExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)

    float opr = 60.0f;
    auto br = boundingRect();
    const float gap=10.0f;
    //painter->fillRect(br, color_);
    painter->setPen(Qt::white);
    //opcircle_ = QRect( -opr/2,-br.height()/2 + gap,opr,opr);
    opcircle_ = QRectF( -opr/2,-br.height()/2,opr,opr);
    center_ = QPointF(0, -br.height()/2+opr/2);
    painter->setBrush(setBrush());
    painter->drawEllipse(opcircle_);
    painter->drawText(opcircle_, Qt::AlignHCenter | Qt::AlignVCenter, QString(op_));
    operand_->setPos(-br.width()/2 +operand_->getWidth() + gap, -br.height()/2 +2*gap +opcircle_.height()+ operand_->getHeight()/2);
    emit ShouldUpdateScene();
}

QRectF BinaryExprAST::boundingRect() const
{
    float w=0.0f;
    float h=0.0f;
    float opr = 60.0f;
    const float gap=10.0f;
    w += left_->getWidth() + 100.0f + right_->getWidth();
    h += left_->getHeight() > right_->getHeight() ? left_->getHeight() : right_->getHeight();
    h+= gap + opr;
    return QRect(-w/2,-h/2,w,h);
}

void BinaryExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)

    float opr = 60.0f;
    auto br = boundingRect();
    const float gap=10.0f;
    painter->setPen(Qt::white);
    opcircle_ = QRectF( -opr/2,-br.height()/2,opr,opr);
    center_ = QPointF(0, -br.height()/2+opr/2);
    painter->setBrush(setBrush());
    painter->drawEllipse(opcircle_);
    painter->drawText(opcircle_, Qt::AlignHCenter | Qt::AlignVCenter, QString(op_));
    left_->setPos(-br.width()/2 +left_->getWidth()/2, -br.height()/2 +gap +opcircle_.height()+ left_->getHeight()/2);
    right_->setPos(br.width()/2 -right_->getWidth()/2, -br.height()/2 +gap +opcircle_.height()+ right_->getHeight()/2);
    emit ShouldUpdateScene();
}

void BinaryExprAST::updateChildren(){
    left_->setParentItem(this);
    right_->setParentItem(this);
    left_->updateChildren();
    right_->updateChildren();
};
void UnaryExprAST::updateChildren(){
    operand_->setParentItem(this);
    operand_->updateChildren();
}
void PlaceholderExprAST::updateChildren(){
    if(expr_){
        expr_->setParentItem(this);
        expr_->updateChildren();
    }
}


inline bool isInCircle(QPointF center, QRectF opcircle, QPointF mousePosition){
    return pow(center.x()-mousePosition.x(),2) + pow(center.y()-mousePosition.y(),2) <= pow(opcircle.height()/2,2);
}

void OperatorExprAST::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    auto mousePosition = event->pos();
    emit selectItem(isInCircle(center_,opcircle_,mousePosition)?this:nullptr);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void ExprAST::deleteMe(){
    auto parent = static_cast<PlaceholderExprAST*>(parentItem());
    parent->expr_ = nullptr;
    //deleteLater();
    delete this;
}


//--------------------toVariant--------------------

QVariant PlaceholderExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "PlaceholderExprAST");
    map.insert("isFull", static_cast<bool>(expr_ != nullptr));
    if(expr_){
        map.insert("expr", expr_->toVariant());
    }
    return map;
}

QVariant ValueExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "ValueExprAST");
    map.insert("value", value_);
    return map;
}

QVariant VariableExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "ValueExprAST");
    map.insert("name", name_);
    return map;
}

QVariant NotExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "NotExprAST");
    map.insert("operand", operand_->toVariant());
    return map;
}

QVariant MulExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "MulExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant DivExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "DivExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant AddExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "AddExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant SubExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "SubExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant LtExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "LtExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant LeqExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "LeqExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant GtExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "GtExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant GeqExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "GeqExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant EqExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "EqExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}


QVariant NeqExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "NeqExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant AndExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "AndExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant OrExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "OrExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

//---------------------------------------------------------------

ExprAST* ExprAST::makeFromVariant(const QVariant& v){
        QVariantMap m = v.toMap();
        if(m.empty())
        {
            return nullptr;
        }
        QString type = m.value("type").toString();
        if(type == "PlaceholderExprAST"){
            return new PlaceholderExprAST(v);
        } else if (type == "ValueExprAST") {
            return new ValueExprAST(v);
        } else if (type == "VariableExprAST") {
            return new VariableExprAST(v);
        } else if (type == "NotExprAST") {
            return new NotExprAST(v);
        } else if (type == "NotExprAST") {
            return new MulExprAST(v);
        } else if (type == "MulExprAST") {
            return new DivExprAST(v);
        } else if (type == "DivExprAST") {
            return new AddExprAST(v);
        } else if (type == "AddExprAST") {
            return new SubExprAST(v);
        } else if (type == "SubExprAST") {
            return new LtExprAST(v);
        } else if (type == "LtExprAST") {
            return new LeqExprAST(v);
        } else if (type == "LeqExprAST") {
            return new GtExprAST(v);
        } else if (type == "GtExprAST") {
            return new GeqExprAST(v);
        } else if (type == "GeqExprAST") {
            return new EqExprAST(v);
        } else if (type == "EqExprAST") {
            return new NeqExprAST(v);
        } else if (type == "NeqExprAST") {
            return new AndExprAST(v);
        } else if (type == "AndExprAST") {
            return new AndExprAST(v);
        } else if (type == "OrExprAST") {
            return new OrExprAST(v);
        } else {
            return nullptr;
        }
    }

//-------------------- QVariant constructors --------------------

PlaceholderExprAST::PlaceholderExprAST(const QVariant& v)
{
    QVariantMap map = v.toMap();
    expr_ = (map.value("isFull").toBool())
          ? makeFromVariant(map.value("expr"))
          : nullptr;

    color_= QColor::fromRgb(128,0,0);
}

ValueExprAST::ValueExprAST(const QVariant& v)
{
    QVariantMap map = v.toMap();
    value_ = map.value("value").toDouble();

    color_= QColor::fromRgb(128,0,128);
}

VariableExprAST::VariableExprAST(const QVariant& v)
{
    QVariantMap map = v.toMap();
    name_ = map.value("name").toString();

    color_= QColor::fromRgb(128,0,128);
}

UnaryExprAST::UnaryExprAST(const QVariant& v)
{
    QVariantMap map = v.toMap();
    operand_ = ExprAST::makeFromVariant(map.value("operand"));

    color_ = QColor::fromRgb(36, 17, 100);
}

BinaryExprAST::BinaryExprAST(const QVariant& v)
{
    QVariantMap map = v.toMap();
    left_ = ExprAST::makeFromVariant(map.value("left"));
    right_ = ExprAST::makeFromVariant(map.value("right"));

    color_= QColor::fromRgb(128,0,128);
}

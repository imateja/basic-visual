#include <QFontMetrics>
#include <ast.hpp>
#include <interpret.hpp>
float ExprAST::gap=10.0f;



//--------------------ACCEPT VISIT--------------------

void PlaceholderAST::AcceptVisit(VisitorAST& v){
    v.VisitPlaceholderExprAST(*this);
}
void ValueAST::AcceptVisit(VisitorAST& v){
    v.VisitValueExprAST(*this);
}
void VariableAST::AcceptVisit(VisitorAST& v){
    v.VisitVariableExprAST(*this);
}
void NotAST::AcceptVisit(VisitorAST& v){
    v.VisitNotExprAST(*this);
}
void MulAST::AcceptVisit(VisitorAST& v){
    v.VisitMulExprAST(*this);
}
void DivAST::AcceptVisit(VisitorAST& v){
    v.VisitDivExprAST(*this);
}
void AddAST::AcceptVisit(VisitorAST& v){
    v.VisitAddExprAST(*this);
}
void SubAST::AcceptVisit(VisitorAST& v){
    v.VisitSubExprAST(*this);
}
void LtAST::AcceptVisit(VisitorAST& v){
    v.VisitLtExprAST(*this);
}
void LeqAST::AcceptVisit(VisitorAST& v){
    v.VisitLeqExprAST(*this);
}
void GtAST::AcceptVisit(VisitorAST& v){
    v.VisitGtExprAST(*this);
}
void GeqAST::AcceptVisit(VisitorAST& v){
    v.VisitGeqExprAST(*this);
}
void EqAST::AcceptVisit(VisitorAST& v){
    v.VisitEqExprAST(*this);
}
void NeqAST::AcceptVisit(VisitorAST& v){
    v.VisitNeqExprAST(*this);
}
void AndAST::AcceptVisit(VisitorAST& v){
    v.VisitAndExprAST(*this);
}
void OrAST::AcceptVisit(VisitorAST& v){
    v.VisitOrExprAST(*this);
}

//--------------------DESTRUCTORS--------------------

PlaceholderAST::~PlaceholderAST() {
    delete expr_;
}

UnaryAST::~UnaryAST() {
    delete operand_;
}

BinaryAST::~BinaryAST(){
    delete left_;
    delete right_;
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

}

void ExprAST::propagateUpdateBoundingRect(){
    updateBr();
    emit updateBoundingRect();
}

void ExprAST::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
    //moved()
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

//------------ STRINGIFY ------------
QString PlaceholderAST::stringify() const {
    return expr_? expr_->stringify() : "[]";
}

QString ValueAST::stringify() const {
    return QString::number(value_);
}

QString VariableAST::stringify() const {
    return name_;
}

QString UnaryAST::stringify() const {
    QString op = operand_->stringify();
    return operand_->getPriority() > getPriority() ? getOp() + "(" + op + ")" : getOp() + op;
}

QString BinaryAST::stringify() const {
    QString l = left_->stringify();
    QString r = right_->stringify();
    QString retVal;
    retVal += left_->getPriority() > getPriority() ? "(" + l + ")" : l;
    retVal += " " + getOp() + " ";
    retVal += right_->getPriority() > getPriority() ? "(" + r + ")" : r;
    return retVal;
}

QBrush ExprAST::setBrush() {
    QBrush brush = QBrush(color_);

    if(Interpret::steps){
        auto tmp = dynamic_cast<InstructionAST*>(this);
        if(tmp && tmp->isCurrent){
            brush.setColor(QColor::fromRgb(192, 223, 133));
            brush.setStyle(Qt::Dense2Pattern);
        }
    }
    if (errorFound) {
        brush.setColor(QColor::fromRgb(237, 77, 110));
        brush.setStyle(Qt::Dense1Pattern);
    }
    if(this->isSelected()){
        brush.setColor(QColor::fromRgb(125, 223, 100));
        brush.setStyle(Qt::Dense1Pattern);
        errorFound = false;
    }
    return brush;
}

void PlaceholderAST::setExpr(ExprAST* expr){
    expr_ = expr;
    expr_->setParentItem(this);
    connect(expr_, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
    connect(expr_, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
    connect(expr_, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);
    connect(expr_, &ExprAST::updateBoundingRect, this, &ExprAST::propagateUpdateBoundingRect);
    expr_->propagateUpdateBoundingRect();
}

void PlaceholderAST::updateBr(){
    float w=60;
    float h=60;
    br = expr_ ? expr_->boundingRect() : QRectF(-w/2,-h/2,w,h);
}

void PlaceholderAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(expr_){
        expr_->setPos(0,0);
    } else {
        painter->fillRect(br,setBrush());
        painter->setPen(Qt::white);
        painter->setFont(QFont("Times New Roman", 18));
        painter->drawText(br, Qt::AlignHCenter | Qt::AlignVCenter, QString("[ ]"));
    }

}

void ValueAST::updateBr() {
    float w=60;
    float h=60;
    br = QRectF(-w/2,-h/2,w,h);
}

void ValueAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->fillRect(br, setBrush());
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 18));
    const auto SquareText = QString::number(value_);
    painter->drawText(br, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

}

void VariableAST::updateBr() {
    float w=60;
    float h=60;
    br =  QRectF(-w/2,-h/2,w,h);
}

void VariableAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->fillRect(br, setBrush());
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 18));

    const auto SquareText = name_;
    painter->drawText(br, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

}

void UnaryAST::updateBr() {
    float w=0.0f;
    float h=0.0f;
    float opr = 60.0f;

    w += operand_->getWidth() + 2 * gap;
    h += operand_->getHeight() + gap*2 + opr;
    br = QRect(-w/2,-h/2,w,h);
}

void UnaryAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    float opr = 60.0f;

    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 18));
    opcircle_ = QRectF( -opr/2,-br.height()/2,opr,opr);
    center_ = QPointF(0, -br.height()/2+opr/2);
    painter->setBrush(setBrush());
    painter->drawEllipse(opcircle_);
    painter->drawText(opcircle_, Qt::AlignHCenter | Qt::AlignVCenter, QString(getOp()));
    operand_->setPos(0, -br.height()/2 +2*gap + opcircle_.height()+ operand_->getHeight()/2);
    QPen pen = QPen(Qt::black);
    pen.setWidth(4);
    painter->setPen(pen);
    painter->drawLine(0,-br.height()/2+opr,0, -br.height()/2 +gap*3 +opcircle_.height());

}

void BinaryAST::updateBr() {
    float w=0.0f;
    float h=0.0f;
    float opr = 60.0f;

    w += left_->getWidth() + 100.0f + right_->getWidth();
    h += left_->getHeight() > right_->getHeight() ? left_->getHeight() : right_->getHeight();
    h+= gap*2 + opr;
    br = QRect(-w/2,-h/2,w,h);
}

void BinaryAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    float opr = 60.0f;

    painter->setPen(Qt::white);
    opcircle_ = QRectF( -opr/2,-br.height()/2,opr,opr);
    center_ = QPointF(0, -br.height()/2+opr/2);
    painter->setBrush(setBrush());
    painter->drawEllipse(opcircle_);
    painter->setFont(QFont("Times New Roman", 18));
    painter->drawText(opcircle_, Qt::AlignHCenter | Qt::AlignVCenter, getOp());

    left_->setPos(-br.width()/2 +left_->getWidth()/2, -br.height()/2 +gap*2 +opcircle_.height()+ left_->getHeight()/2);
    right_->setPos(br.width()/2 -right_->getWidth()/2, -br.height()/2 +gap*2 +opcircle_.height()+ right_->getHeight()/2);
    QPen pen = QPen(Qt::black);
    pen.setWidth(4);
    painter->setPen(pen);
    painter->drawLine(0,-br.height()/2+opr,-br.width()/2 +left_->getWidth()/2, -br.height()/2 +gap*2 +opcircle_.height());
    painter->drawLine(0,-br.height()/2+opr,br.width()/2 -right_->getWidth()/2, -br.height()/2 +gap*2 +opcircle_.height());

}

void BinaryAST::updateChildren() {
    left_->setParentItem(this);
    right_->setParentItem(this);
    left_->updateChildren();
    right_->updateChildren();
}

void UnaryAST::updateChildren() {
    operand_->setParentItem(this);
    operand_->updateChildren();
}

void PlaceholderAST::updateChildren() {
    if(expr_){
        expr_->setParentItem(this);
        expr_->updateChildren();
    }
}

inline bool isInCircle(QPointF center, QRectF opcircle, QPointF mousePosition) {
    return pow(center.x()-mousePosition.x(),2) + pow(center.y()-mousePosition.y(),2) <= pow(opcircle.height()/2,2);
}

void OperatorAST::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    auto mousePosition = event->pos();
    emit selectItem(isInCircle(center_,opcircle_,mousePosition)?this:nullptr);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void PlaceholderAST::clear() {
    expr_ = nullptr;
    propagateUpdateBoundingRect();
}

void ExprAST::deleteMe() {
    auto parent = static_cast<PlaceholderAST*>(parentItem());
    parent->clear();
    //deleteLater();
    delete this;
}


//--------------------toVariant--------------------

QVariant PlaceholderAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "PlaceholderExprAST");
    map.insert("isFull", static_cast<bool>(expr_ != nullptr));
    if(expr_){
        map.insert("expr", expr_->toVariant());
    }
    return map;
}

QVariant ValueAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "ValueExprAST");
    map.insert("value", value_);
    return map;
}

QVariant VariableAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "VariableExprAST");
    map.insert("name", name_);
    return map;
}

QVariant NotAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "NotExprAST");
    map.insert("operand", operand_->toVariant());
    return map;
}

QVariant MulAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "MulExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant DivAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "DivExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant AddAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "AddExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant SubAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "SubExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant LtAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "LtExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant LeqAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "LeqExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant GtAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "GtExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant GeqAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "GeqExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant EqAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "EqExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}


QVariant NeqAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "NeqExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant AndAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "AndExprAST");
    map.insert("left", left_->toVariant());
    map.insert("right", right_->toVariant());
    return map;
}

QVariant OrAST::toVariant() const
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
            return new PlaceholderAST(v);
        } else if (type == "ValueExprAST") {
            return new ValueAST(v);
        } else if (type == "VariableExprAST") {
            return new VariableAST(v);
        } else if (type == "NotExprAST") {
            return new NotAST(v);
        } else if (type == "MulExprAST") {
            return new MulAST(v);
        } else if (type == "DivExprAST") {
            return new DivAST(v);
        } else if (type == "AddExprAST") {
            return new AddAST(v);
        } else if (type == "SubExprAST") {
            return new SubAST(v);
        } else if (type == "LtExprAST") {
            return new LtAST(v);
        } else if (type == "LeqExprAST") {
            return new LeqAST(v);
        } else if (type == "GtExprAST") {
            return new GtAST(v);
        } else if (type == "GeqExprAST") {
            return new GeqAST(v);
        } else if (type == "EqExprAST") {
            return new EqAST(v);
        } else if (type == "NeqExprAST") {
            return new NeqAST(v);
        } else if (type == "AndExprAST") {
            return new AndAST(v);
        } else if (type == "OrExprAST") {
            return new OrAST(v);
        } else if (type == "StartExprAST") {
            return new StartAST(v);
        } else if (type == "AssignExprAST") {
            return new AssignAST(v);
        } else if (type == "BlockExprAST") {
            return new BlockAST(v);
        } else if (type == "IfExprAST") {
            return new IfAST(v);
        } else if (type == "WhileExprAST") {
            return new WhileAST(v);
        } else if (type == "PrintAST") {
            return new PrintAST(v);
        } else if (type == "InputAST") {
            return new InputAST(v);
        } else {
            return nullptr;
        }
    }

//-------------------- QVariant constructors --------------------

PlaceholderAST::PlaceholderAST(const QVariant& v)
    : PlaceholderAST()
{
    QVariantMap map = v.toMap();
    auto child = (map.value("isFull").toBool())
               ? makeFromVariant(map.value("expr"))
               : nullptr;
    if(child){
        setExpr(child);
    }
}

ValueAST::ValueAST(const QVariant& v)
    : ValueAST(v.toMap().value("value").toDouble())
{
}

VariableAST::VariableAST(const QVariant& v)
    : VariableAST(v.toMap().value("name").toString())
{
}

UnaryAST::UnaryAST(const QVariant& v)
    : UnaryAST(ExprAST::makeFromVariant(v.toMap().value("operand")))
{
}

BinaryAST::BinaryAST(const QVariant& v)
    : BinaryAST(
          ExprAST::makeFromVariant(v.toMap().value("left")),
          ExprAST::makeFromVariant(v.toMap().value("right"))
          )
{
}

#include <QFontMetrics>
#include <ast.hpp>
#include <interpret.hpp>
float ExprAST::gap=10.0f;

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

//--------------------DESTRUCTORS--------------------

PlaceholderExprAST::~PlaceholderExprAST() {
    delete expr_;
}

UnaryExprAST::~UnaryExprAST() {
    delete operand_;
}

BinaryExprAST::~BinaryExprAST(){
    delete left_;
    delete right_;
}

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
QString PlaceholderExprAST::stringify() const {
    return expr_? expr_->stringify() : "[]";
}

QString ValueExprAST::stringify() const {
    return QString::number(value_);
}

QString VariableExprAST::stringify() const {
    return name_;
}

QString UnaryExprAST::stringify() const {
    QString op = operand_->stringify();
    return operand_->getPriority() > getPriority() ? op_ + "(" + op + ")" : op_ + op;
}

QString BinaryExprAST::stringify() const {
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
    if(Interpret::steps)
        if((dynamic_cast<InstructionExprAST*>(this))->isCurrent){
        brush.setColor(Qt::yellow);
        brush.setStyle(Qt::Dense2Pattern);
    }
    return brush;
}

QRectF PlaceholderExprAST::boundingRect() const{
    float w=60;
    float h=60;
    return expr_ ? expr_->boundingRect() : QRectF(-w/2,-h/2,w,h);
}

void PlaceholderExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    auto br = boundingRect();
    if(expr_){
        expr_->setPos(0,0);
    } else {
        painter->fillRect(br,setBrush());
        painter->setPen(Qt::white);
        painter->setFont(QFont("Times New Roman", 18));
        painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, QString("[ ]"));   
    }
    emit ShouldUpdateScene();
}

//--------------------- EXPRPAINTING ---------------------

QRectF ValueExprAST::boundingRect() const {
    float w=60;
    float h=60;
    return QRectF(-w/2,-h/2,w,h);
}

void ValueExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    Q_UNUSED(option)
    Q_UNUSED(widget)

    auto br = boundingRect();
    painter->fillRect(br, setBrush());
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 18));
    const auto SquareText = QString::number(value_);
    painter->drawText(br, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    emit ShouldUpdateScene();
}

QRectF VariableExprAST::boundingRect() const {
    float w=60;
    float h=60;
    return QRectF(-w/2,-h/2,w,h);
}

void VariableExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    auto br = boundingRect();
    painter->fillRect(br, setBrush());
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 18));

    const auto SquareText = name_;
    painter->drawText(br, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    emit ShouldUpdateScene();
}

QRectF UnaryExprAST::boundingRect() const{
    float w=0.0f;
    float h=0.0f;
    float opr = 60.0f;

    w += operand_->getWidth() + 2 * gap;
    h += operand_->getHeight() + gap*3 + opr;
    return QRect(-w/2,-h/2,w,h);
}

void UnaryExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    float opr = 60.0f;
    auto br = boundingRect();

    //painter->fillRect(br, color_);
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 18));
    //opcircle_ = QRect( -opr/2,-br.height()/2 + gap,opr,opr);
    opcircle_ = QRectF( -opr/2,-br.height()/2,opr,opr);
    center_ = QPointF(0, -br.height()/2+opr/2);
    painter->setBrush(setBrush());
    painter->drawEllipse(opcircle_);
    painter->drawText(opcircle_, Qt::AlignHCenter | Qt::AlignVCenter, QString(op_));
    operand_->setPos(0, -br.height()/2 +3*gap + opcircle_.height()+ operand_->getHeight()/2);
    QPen pen = QPen(Qt::black);
    pen.setWidth(4);
    painter->setPen(pen);
    painter->drawLine(0,-br.height()/2+opr,0, -br.height()/2 +gap*3 +opcircle_.height());
    emit ShouldUpdateScene();
}

QRectF BinaryExprAST::boundingRect() const {
    float w=0.0f;
    float h=0.0f;
    float opr = 60.0f;

    w += left_->getWidth() + 100.0f + right_->getWidth();
    h += left_->getHeight() > right_->getHeight() ? left_->getHeight() : right_->getHeight();
    h+= gap*2 + opr;
    return QRect(-w/2,-h/2,w,h);
}

void BinaryExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    float opr = 60.0f;
    auto br = boundingRect();

    painter->setPen(Qt::white);
    opcircle_ = QRectF( -opr/2,-br.height()/2,opr,opr);
    center_ = QPointF(0, -br.height()/2+opr/2);
    painter->setBrush(setBrush());
    painter->drawEllipse(opcircle_);
    painter->setFont(QFont("Times New Roman", 18));
    painter->drawText(opcircle_, Qt::AlignHCenter | Qt::AlignVCenter, QString(op_));

    left_->setPos(-br.width()/2 +left_->getWidth()/2, -br.height()/2 +gap*2 +opcircle_.height()+ left_->getHeight()/2);
    right_->setPos(br.width()/2 -right_->getWidth()/2, -br.height()/2 +gap*2 +opcircle_.height()+ right_->getHeight()/2);
    QPen pen = QPen(Qt::black);
    pen.setWidth(4);
    painter->setPen(pen);
    painter->drawLine(0,-br.height()/2+opr,-br.width()/2 +left_->getWidth()/2, -br.height()/2 +gap*2 +opcircle_.height());
    painter->drawLine(0,-br.height()/2+opr,br.width()/2 -right_->getWidth()/2, -br.height()/2 +gap*2 +opcircle_.height());
    emit ShouldUpdateScene();
}

void BinaryExprAST::updateChildren() {
    left_->setParentItem(this);
    right_->setParentItem(this);
    left_->updateChildren();
    right_->updateChildren();
}

void UnaryExprAST::updateChildren() {
    operand_->setParentItem(this);
    operand_->updateChildren();
}

void PlaceholderExprAST::updateChildren() {
    if(expr_){
        expr_->setParentItem(this);
        expr_->updateChildren();
    }
}

inline bool isInCircle(QPointF center, QRectF opcircle, QPointF mousePosition) {
    return pow(center.x()-mousePosition.x(),2) + pow(center.y()-mousePosition.y(),2) <= pow(opcircle.height()/2,2);
}

void OperatorExprAST::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    auto mousePosition = event->pos();
    emit selectItem(isInCircle(center_,opcircle_,mousePosition)?this:nullptr);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void ExprAST::deleteMe() {
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
    map.insert("type", "VariableExprAST");
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
        } else if (type == "MulExprAST") {
            return new MulExprAST(v);
        } else if (type == "DivExprAST") {
            return new DivExprAST(v);
        } else if (type == "AddExprAST") {
            return new AddExprAST(v);
        } else if (type == "SubExprAST") {
            return new SubExprAST(v);
        } else if (type == "LtExprAST") {
            return new LtExprAST(v);
        } else if (type == "LeqExprAST") {
            return new LeqExprAST(v);
        } else if (type == "QtExprAST") {
            return new GtExprAST(v);
        } else if (type == "GeqExprAST") {
            return new GeqExprAST(v);
        } else if (type == "EqExprAST") {
            return new EqExprAST(v);
        } else if (type == "NeqExprAST") {
            return new NeqExprAST(v);
        } else if (type == "AndExprAST") {
            return new AndExprAST(v);
        } else if (type == "OrExprAST") {
            return new OrExprAST(v);
        } else if (type == "StartExprAST") {
            return new StartExprAST(v);
        } else if (type == "AssignExprAST") {
            return new AssignExprAST(v);
        } else if (type == "BlockExprAST") {
            return new BlockExprAST(v);
        } else if (type == "IfExprAST") {
            return new IfExprAST(v);
        } else if (type == "WhileExprAST") {
            return new WhileExprAST(v);
        } else if (type == "PrintAST") {
            return new PrintAST(v);
        } else if (type == "InputAST") {
            return new InputAST(v);
        } else {
            return nullptr;
        }
    }

//-------------------- QVariant constructors --------------------

PlaceholderExprAST::PlaceholderExprAST(const QVariant& v)
    : PlaceholderExprAST()
{
    QVariantMap map = v.toMap();
    auto child = (map.value("isFull").toBool())
               ? makeFromVariant(map.value("expr"))
               : nullptr;
    if(child){
        setExpr(child);
    }
}

ValueExprAST::ValueExprAST(const QVariant& v)
    : ValueExprAST(v.toMap().value("value").toDouble())
{
}

VariableExprAST::VariableExprAST(const QVariant& v)
    : VariableExprAST(v.toMap().value("name").toString())
{
}

UnaryExprAST::UnaryExprAST(const QVariant& v)
    : UnaryExprAST(ExprAST::makeFromVariant(v.toMap().value("operand")))
{
}

BinaryExprAST::BinaryExprAST(const QVariant& v)
    : BinaryExprAST(
          ExprAST::makeFromVariant(v.toMap().value("left")),
          ExprAST::makeFromVariant(v.toMap().value("right"))
          )
{
}

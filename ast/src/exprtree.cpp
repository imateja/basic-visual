#include <exprtree.hpp>

void StartAST::AcceptVisit(VisitorAST& v){
    v.VisitStartExprAST(*this);
}
void AssignAST::AcceptVisit(VisitorAST& v){
    v.VisitAssignExprAST(*this);
}
void BlockAST::AcceptVisit(VisitorAST& v){
    v.VisitBlockExprAST(*this);
}
void WhileAST::AcceptVisit(VisitorAST& v){
    v.VisitWhileExprAST(*this);
}
void IfAST::AcceptVisit(VisitorAST& v){
    v.VisitIfExprAST(*this);
}

void PrintAST::AcceptVisit(VisitorAST& v){
    v.VisitPrintAST(*this);
}

void InputAST::AcceptVisit(VisitorAST& v){
    v.VisitInputAST(*this);
}

AssignAST::~AssignAST(){
    delete expr_;
}

BlockAST::~BlockAST(){
   for(auto& next : body_)
       delete next;
}
PrintAST::~PrintAST(){
    delete expr_;
}

void BlockAST::updateChildren()
{
    for(auto elem : body_){
        elem->setParentItem(this);
        elem->updateChildren();
    }
}

void BlockAST::insert(InstructionAST* newinstr, InstructionAST* posinstr){
    if (posinstr == nullptr){
        body_.push_back(newinstr);
    }else {
        auto pos = body_.indexOf(posinstr);
        if (pos != -1){
            body_.insert(pos+1, newinstr);
        }
    }

    newinstr->setParentItem(this);
    connect(newinstr, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
    connect(newinstr, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
    connect(newinstr, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);
    connect(newinstr, &ExprAST::updateBoundingRect, this, &ExprAST::propagateUpdateBoundingRect);

    newinstr->updateBr();
    updateBr();
    propagateUpdateBoundingRect();
}

void BlockAST::remove(InstructionAST* instr){
    auto pos = body_.indexOf(instr);
    body_.remove(pos);
    updateBr();
    propagateUpdateBoundingRect();
}

IfAST::~IfAST(){
    delete cond_;
    delete then_;
    delete else_;
}

void IfAST::updateChildren()
{
    then_->setParentItem(this);
    else_->setParentItem(this);
    then_->updateChildren();
    else_->updateChildren();
}

void IfAST::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    auto mousePosition = event->pos();
    emit selectItem(ifrectangle_.contains(mousePosition)?this:nullptr);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

WhileAST::~WhileAST(){
    delete cond_;
    delete body_;
}

void WhileAST::updateChildren()
{
    body_->setParentItem(this);
    body_->updateChildren();
}

// ---------------------- PAINT -----------------------

void StartAST::updateBr()
{
    float w = 120.0f;
    float h = 60.0f;
    br = QRect(-w/2, -h/2, w, h);
}

void StartAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->fillRect(br,setBrush());
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 15));
    const auto SquareText = QString("Start");
    painter->drawText(br, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

}

void AssignAST::updateBr()
{
    float w = 120.0f;
    float h = 60.0f;
    auto fm=new QFontMetrics(QFont("Times", 10, QFont::Bold));
    const auto fontrect=fm->boundingRect(stringify());
    w+=fontrect.width();
    br = QRectF(-w/2,-h/2,w,h);
}

void AssignAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->fillRect(br,setBrush());
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 15));
    const auto SquareText = QString(instructionName_ + "\n" + stringify());
    painter->drawText(br, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

}

void BlockAST::updateBr()
{
    float w = 0.0f;
    float h = 0.0f;
    for (auto &elem : body_) {
        auto br = elem->boundingRect();
        if (br.width() > w) {
            w=br.width();
        }
        h += br.height();
        h += gap;
    }
    h += gap;
    w += 2*gap;
    br = QRectF(-w/2, -h/2, w, h);
}

void BlockAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->fillRect(br, color_);
    float currenth = -br.height() / 2+gap;
    for(auto elem : body_) {
        elem->setPos(0, currenth + elem->getHeight() / 2);
        currenth += elem->getHeight() + gap;
    }

}

void BlockAST::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit selectItem(nullptr);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void IfAST::updateBr() {
    float w=0.0f;
    float h=0.0f;
    float ifh = 60.0f;

    w += then_->getWidth() + else_->getWidth() + 100.0f;
    h += then_->getHeight() > else_->getHeight() ? then_->getHeight() : else_->getHeight();

    h += ifh * 2 + gap;
    h += gap * 3;
    auto fm = new QFontMetrics(QFont("Times", 10, QFont::Bold));
    const auto fontrect = fm->boundingRect(stringify());
    w += fontrect.width() + 2*gap;

    br = QRectF(-w/2,-h/2, w, h);
}

void IfAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    float ifh = 60;
    painter->fillRect(br, QColor::fromRgb(101, 50, 57));
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 15));

    ifrectangle_ = QRectF(-br.width()/2 + gap, -br.height()/2 + gap, br.width()-2*gap, ifh);
    painter->fillRect(ifrectangle_, setBrush());
    const auto SquareText = QString("%1\n%2").arg(instructionName_, stringify());
    painter->drawText(ifrectangle_, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

    QRectF thenrect = QRectF(-ifrectangle_.width()/2, -br.height()/2 + ifrectangle_.height()+gap*2, then_->getWidth(), ifrectangle_.height());
    painter->fillRect(thenrect, QColor::fromRgb(156, 102, 21));
    painter->drawText(thenrect, Qt::AlignHCenter | Qt::AlignVCenter, "then" );

    QRectF elserect = QRectF(ifrectangle_.width()/2 - else_->getWidth(), -br.height()/2 + ifrectangle_.height() + gap*2, else_->getWidth(), ifrectangle_.height());

    painter->fillRect(elserect, QColor::fromRgb(156, 102, 21));
    painter->drawText(elserect, Qt::AlignHCenter | Qt::AlignVCenter, "else" );

    then_->setPos(
                -ifrectangle_.width()/2 + then_->getWidth()/2,
                -br.height()/2 + ifrectangle_.height()+gap*3 +
                    thenrect.height() + then_->getHeight()/2
                );
    else_->setPos(
                ifrectangle_.width()/2 - else_->getWidth()/2,
                -br.height()/2 + ifrectangle_.height()+gap*2 +
                    elserect.height() + gap + else_->getHeight()/2
                );


}

void WhileAST::updateBr()
{
    float w = 0.0f;
    float h = 0.0f;
    float whileh = 60.0f;

    h += body_->getHeight() + whileh + gap*3;
    w += body_->getWidth() + 2*gap;
    auto fm=new QFontMetrics(QFont("Times", 10, QFont::Bold));
    const auto fontrect=fm->boundingRect(stringify());
    w += fontrect.width();
    br = QRectF(-w/2,-h/2,w,h);
}

void WhileAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    float whileh = 60;
    painter->fillRect(br, QColor::fromRgb(101, 50, 57));
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 15));
    whilerectangle_ = QRectF(-br.width()/2 + gap, -br.height()/2 + gap, br.width() - 2*gap, whileh);
    painter->fillRect(whilerectangle_,setBrush());
    painter->drawText(whilerectangle_, Qt::AlignHCenter | Qt::AlignVCenter, "While\n"+stringify());
    body_->setPos(0,-br.height()/2 + whilerectangle_.height() + 2*gap + body_->getHeight()/2);

}

void PrintAST::updateBr()
{
    float w = 120.0f;
    float h = 60.0f;
    auto fm = new QFontMetrics(QFont("Times", 10, QFont::Bold));
    const auto fontrect = fm->boundingRect(stringify());
    w += fontrect.width();
    br = QRectF(-w/2, -h/2, w, h);
}

void PrintAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->fillRect(br,setBrush());
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 15));
    const auto SquareText = QString(instructionName_ +"\n"+stringify());
    painter->drawText(br, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

}
void InputAST::updateBr()
{
    float w = 120.0f;
    float h = 60.0f;
    auto fm=new QFontMetrics(QFont("Times", 10, QFont::Bold));
    const auto fontrect=fm->boundingRect(stringify());
    w+=fontrect.width();
    br = QRectF(-w/2,-h/2,w,h);
}

void InputAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->fillRect(br,setBrush());
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 15));
    const auto SquareText = QString(instructionName_+ "\n" + name_);
    painter->drawText(br, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

}
void WhileAST::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    auto mousePosition = event->pos();
    emit selectItem(whilerectangle_.contains(mousePosition) ? this : nullptr);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void InstructionAST::deleteMe()
{
    auto parent = static_cast<BlockAST*>(parentItem());
    parent->remove(this);
    delete this;
}

//------------ STRINGIFY ------------

QString StartAST::stringify() const { return {}; }
QString AssignAST::stringify() const { return name_ + " = " + expr_->stringify(); }
QString BlockAST::stringify() const { return {}; }
QString IfAST::stringify() const { return cond_->stringify(); }
QString WhileAST::stringify() const { return cond_->stringify(); }
QString PrintAST::stringify() const { return expr_->stringify(); }
QString InputAST::stringify() const { return {}; }

//------------------ toVariant -------------------

QVariant StartAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "StartExprAST");
    return map;
}

QVariant AssignAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "AssignExprAST");
    map.insert("name", name_);
    map.insert("expr", expr_->toVariant());
    return map;
}

QVariant BlockAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "BlockExprAST");
    QVariantList list;
    for (auto expr : body_) {
        list.append(expr->toVariant());
    }
    map.insert("body", list);
    return map;
}

QVariant IfAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "IfExprAST");
    map.insert("cond", cond_->toVariant());
    map.insert("then", then_->toVariant());
    map.insert("else", else_->toVariant());
    return map;
}

QVariant WhileAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "WhileExprAST");
    map.insert("cond", cond_->toVariant());
    map.insert("body", body_->toVariant());
    return map;
}

QVariant PrintAST::toVariant() const {
    QVariantMap map;
    map.insert("type", "PrintAST");
    map.insert("expr", expr_->toVariant());
    return map;
}

QVariant InputAST::toVariant() const {
    QVariantMap map;
    map.insert("type", "InputAST");
    map.insert("name", name_);
    return map;
}

//-------------------- QVariant constructors --------------------

AssignAST::AssignAST(const QVariant& v)
    : AssignAST(
          v.toMap().value("name").toString(),
          ExprAST::makeFromVariant(v.toMap().value("expr"))
          )
{
}

BlockAST::BlockAST(const QVariant& v)
    : BlockAST()
{
    qDeleteAll(body_);
    body_.clear();
    for(auto& expr : v.toMap().value("body").toList()) {
        insert(dynamic_cast<InstructionAST*>(ExprAST::makeFromVariant(expr)));
    }
}

IfAST::IfAST(const QVariant& v)
    : IfAST(
          ExprAST::makeFromVariant(v.toMap().value("cond")),
          dynamic_cast<BlockAST*>(ExprAST::makeFromVariant(v.toMap().value("then"))),
          dynamic_cast<BlockAST*>(ExprAST::makeFromVariant(v.toMap().value("else")))
          )
{
}

WhileAST::WhileAST(const QVariant& v)
    : WhileAST(
          ExprAST::makeFromVariant(v.toMap().value("cond")),
          dynamic_cast<BlockAST*>(ExprAST::makeFromVariant(v.toMap().value("body")))
          )
{
}

PrintAST::PrintAST(const QVariant& v)
    : PrintAST(ExprAST::makeFromVariant(v.toMap().value("expr")))
{
}

InputAST::InputAST(const QVariant& v)
    : InputAST(v.toMap().value("name").toString())
{}

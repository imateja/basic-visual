#include <exprtree.hpp>

void StartExprAST::AcceptVisit(VisitorAST& v){
    v.VisitStartExprAST(*this);
}
void AssignExprAST::AcceptVisit(VisitorAST& v){
    v.VisitAssignExprAST(*this);
}
void BlockExprAST::AcceptVisit(VisitorAST& v){
    v.VisitBlockExprAST(*this);
}
void WhileExprAST::AcceptVisit(VisitorAST& v){
    v.VisitWhileExprAST(*this);
}
void IfExprAST::AcceptVisit(VisitorAST& v){
    v.VisitIfExprAST(*this);
}
void FunctionExprAST::AcceptVisit(VisitorAST& v){
    v.VisitFunctionExprAST(*this);
}

void PrintAST::AcceptVisit(VisitorAST& v){
    v.VisitPrintAST(*this);
}

void InputAST::AcceptVisit(VisitorAST& v){
    v.VisitInputAST(*this);
}

AssignExprAST::~AssignExprAST(){
    delete expr_;
}

BlockExprAST::~BlockExprAST(){
   for(auto& next : body_)
       delete next;
}
PrintAST::~PrintAST(){
    delete expr_;
}

void BlockExprAST::updateChildren()
{
    for(auto elem : body_){
        elem->setParentItem(this);
        elem->updateChildren();
    }
}

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

    newinstr->setParentItem(this);
    connect(newinstr, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
    connect(newinstr, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
    connect(newinstr, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);
}

void BlockExprAST::remove(InstructionExprAST* instr){
    auto pos = body_.indexOf(instr);
    body_.remove(pos);
}

IfExprAST::~IfExprAST(){
    delete cond_;
    delete then_;
    delete else_;
}

void IfExprAST::updateChildren()
{
    then_->setParentItem(this);
    else_->setParentItem(this);
    then_->updateChildren();
    else_->updateChildren();
}

void IfExprAST::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    auto mousePosition = event->pos();
    emit selectItem(ifrectangle_.contains(mousePosition)?this:nullptr);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

WhileExprAST::~WhileExprAST(){
    delete cond_;
    delete body_;
}

void WhileExprAST::updateChildren()
{
    body_->setParentItem(this);
    body_->updateChildren();
}

FunctionExprAST::~FunctionExprAST(){
    delete body_;
}

// ---------------------- PAINT -----------------------

QRectF InstructionExprAST::boundingRect() const
{
    float w = 120.0f;
    float h = 60.0f;
    return QRect(-w/2, -h/2, w, h);
}

void StartExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    auto br = boundingRect();
    painter->fillRect(br,setBrush());
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 15));
    const auto SquareText = QString("%1\n").arg("start");
    painter->drawText(br, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    emit ShouldUpdateScene();
}

QRectF AssignExprAST::boundingRect() const
{
    float w = 120;
    float h = 60;
    auto fm=new QFontMetrics(QFont("Times", 10, QFont::Bold));
    const auto fontrect=fm->boundingRect(stringify());
    w+=fontrect.width();
    return QRectF(-w/2,-h/2,w,h);
}

void AssignExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    auto br = boundingRect();
    painter->fillRect(br,setBrush());
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 15));
    const auto SquareText = QString(instructionName_ + "\n" + stringify());
    painter->drawText(br, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    emit ShouldUpdateScene();
}

QRectF BlockExprAST::boundingRect() const
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
    return QRectF(-w/2, -h/2, w, h);
}

void BlockExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    auto br = boundingRect();

    painter->fillRect(br, color_);
    float currenth = -br.height() / 2+gap;

    for(auto elem : body_) {
        elem->setPos(0, currenth + elem->getHeight() / 2);
       currenth += elem->getHeight() + gap;
    }
    emit ShouldUpdateScene();

    //TODO:Default case (maybe throw error)
}

void BlockExprAST::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit selectItem(nullptr);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

QRectF IfExprAST::boundingRect() const{
    float w=0.0f;
    float h=0.0f;
    float ifh = 60;

    w += then_->getWidth() + else_->getWidth() + 100.0f;
    h += then_->getHeight() > else_->getHeight() ? then_->getHeight() : else_->getHeight();

    h += ifh * 2 + gap;
    h += gap * 3;
    auto fm = new QFontMetrics(QFont("Times", 10, QFont::Bold));
    const auto fontrect = fm->boundingRect(stringify());
    w += fontrect.width() + 2*gap;

    return QRectF(-w/2,-h/2, w, h);
}

void IfExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QRectF br = boundingRect();
    float ifh = 60;
    painter->fillRect(br, QColor::fromRgb(70, 40, 20));
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 15));

    ifrectangle_ = QRectF(-br.width()/2 + gap, -br.height()/2 + gap, br.width()-2*gap, ifh);
    painter->fillRect(ifrectangle_, setBrush());
    const auto SquareText = QString("%1\n%2").arg(instructionName_, stringify());
    painter->drawText(ifrectangle_, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);

    QRectF thenrect = QRectF(-ifrectangle_.width()/2, -br.height()/2 + ifrectangle_.height()+gap*2, then_->getWidth(), ifrectangle_.height());
    painter->fillRect(thenrect, QColor::fromRgb(128, 0, 0));
    painter->drawText(thenrect, Qt::AlignHCenter | Qt::AlignVCenter, "then" );

    QRectF elserect = QRectF(ifrectangle_.width()/2 - else_->getWidth(), -br.height()/2 + ifrectangle_.height() + gap*2, else_->getWidth(), ifrectangle_.height());

    painter->fillRect(elserect, QColor::fromRgb(128,0,0));
    painter->drawText(elserect, Qt::AlignHCenter | Qt::AlignVCenter, "else" );

    then_->setPos(-ifrectangle_.width()/2 + then_->getWidth()/2, -br.height()/2 + ifrectangle_.height()+gap*2 + thenrect.height() + gap + then_->getHeight()/2);
    else_->setPos(ifrectangle_.width()/2 - else_->getWidth()/2, -br.height()/2 + ifrectangle_.height()+gap*2 + elserect.height() + gap + else_->getHeight()/2);

    emit ShouldUpdateScene();
    //TODO:Default case (maybe throw error)
}

QRectF WhileExprAST::boundingRect() const
{
    float w = 0.0f;
    float h = 0.0f;
    float whileh = 60;

    h += body_->getHeight() + whileh + gap*3;
    w += body_->getWidth() + 2*gap;
    auto fm=new QFontMetrics(QFont("Times", 10, QFont::Bold));
    const auto fontrect=fm->boundingRect(stringify());
    w += fontrect.width();
    return QRectF(-w/2,-h/2,w,h);
}

void WhileExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    auto br = boundingRect();
    float whileh = 60;
    painter->fillRect(br, QColor::fromRgb(20,20,20));
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 15));
    whilerectangle_ = QRectF(-br.width()/2 + gap, -br.height()/2 + gap, br.width() - 2*gap, whileh);
    painter->fillRect(whilerectangle_,setBrush());
    painter->drawText(whilerectangle_, Qt::AlignHCenter | Qt::AlignVCenter, "While\n"+stringify());
    body_->setPos(0,-br.height()/2 + whilerectangle_.height() + 2*gap + body_->getHeight()/2);
    //whilerectangle_.height()/2
    emit ShouldUpdateScene();
}

QRectF PrintAST::boundingRect() const
{
    float w = 120;
    float h = 60;
    auto fm = new QFontMetrics(QFont("Times", 10, QFont::Bold));
    const auto fontrect = fm->boundingRect(stringify());
    w += fontrect.width();
    return QRectF(-w/2, -h/2, w, h);
}

void PrintAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    auto br = boundingRect();
    painter->fillRect(br,setBrush());
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 15));
    const auto SquareText = QString(instructionName_ +"\n"+stringify());
    painter->drawText(br, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    emit ShouldUpdateScene();
}
QRectF InputAST::boundingRect() const
{
    float w = 120;
    float h = 60;
    auto fm=new QFontMetrics(QFont("Times", 10, QFont::Bold));
    const auto fontrect=fm->boundingRect(stringify());
    w+=fontrect.width();
    return QRectF(-w/2,-h/2,w,h);
}

void InputAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    auto br = boundingRect();
    painter->fillRect(br,setBrush());
    painter->setPen(Qt::white);
    painter->setFont(QFont("Times New Roman", 15));
    const auto SquareText = QString(instructionName_+ "\n" + name_);
    painter->drawText(br, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    emit ShouldUpdateScene();
}
void WhileExprAST::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    auto mousePosition = event->pos();
    emit selectItem(whilerectangle_.contains(mousePosition) ? this : nullptr);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void FunctionExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {}

//QRectF AssignExprAST::boundingRect() const
//{
//    float w=160;
//    float h=80;
//    return QRectF(-w/2, 0, w, h);
//}

void InstructionExprAST::deleteMe()
{
    auto parent = static_cast<BlockExprAST*>(parentItem());
    parent->remove(this);
    delete this;
}

//------------ STRINGIFY ------------

QString StartExprAST::stringify() const { return {}; }
QString AssignExprAST::stringify() const { return name_ + " = " + expr_->stringify(); }
QString BlockExprAST::stringify() const { return {}; }
QString IfExprAST::stringify() const { return cond_->stringify(); }
QString WhileExprAST::stringify() const { return cond_->stringify(); }
QString PrintAST::stringify() const { return expr_->stringify(); }
QString InputAST::stringify() const { return {}; }
QString FunctionExprAST::stringify() const { return {}; }

//------------------ toVariant -------------------

QVariant StartExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "StartExprAST");
    return map;
}

QVariant AssignExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "AssignExprAST");
    map.insert("name", name_);
    map.insert("expr", expr_->toVariant());
    return map;
}

QVariant BlockExprAST::toVariant() const
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

QVariant IfExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "IfExprAST");
    map.insert("cond", cond_->toVariant());
    map.insert("then", then_->toVariant());
    map.insert("else", else_->toVariant());
    return map;
}

QVariant WhileExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "WhileExprAST");
    map.insert("cond", cond_->toVariant());
    map.insert("body", body_->toVariant());
    return map;
}

QVariant FunctionExprAST::toVariant() const
{
    QVariantMap map;
    map.insert("type", "FunctionExprAST");
    //???
    return map;
}

QVariant PrintAST::toVariant() const {
    QVariantMap map;
    map.insert("type", "PrintAST");
    //???
    return map;
}

QVariant InputAST::toVariant() const {
    QVariantMap map;
    map.insert("type", "InputAST");
    //???
    return map;
}

//-------------------- QVariant constructors --------------------

AssignExprAST::AssignExprAST(const QVariant& v)
{
    QVariantMap map = v.toMap();
    name_ = map.value("name").toString();
    expr_ = ExprAST::makeFromVariant(map.value("expr"));

    color_ = QColor::fromRgb(64, 120, 7);
}

BlockExprAST::BlockExprAST(const QVariant& v)
{
    QVariantMap map = v.toMap();
    qDeleteAll(body_);
    body_.clear();
    QVariantList list = map.value("body").toList();
    for(auto& expr : list) {
        insert(dynamic_cast<InstructionExprAST*>(ExprAST::makeFromVariant(expr)));
    }

    color_= QColor::fromRgb(0, 0, 128);
}

IfExprAST::IfExprAST(const QVariant& v)
{
    QVariantMap map = v.toMap();
    cond_ = ExprAST::makeFromVariant(map.value("cond"));
    then_ = dynamic_cast<BlockExprAST*>(ExprAST::makeFromVariant(map.value("then")));
    else_ = dynamic_cast<BlockExprAST*>(ExprAST::makeFromVariant(map.value("else")));

    color_= QColor::fromRgb(128, 128, 0);
}

WhileExprAST::WhileExprAST(const QVariant& v)
{
    QVariantMap map = v.toMap();
    cond_ = ExprAST::makeFromVariant(map.value("cond"));
    body_ = dynamic_cast<BlockExprAST*>(ExprAST::makeFromVariant(map.value("body")));

    color_= QColor::fromRgb(60, 60, 0);
}

FunctionExprAST::FunctionExprAST(const QVariant& v)
{
//TODO: ???
    color_= QColor::fromRgb(0, 60, 60);
}

PrintAST::PrintAST(const QVariant&){
    //TODO
}


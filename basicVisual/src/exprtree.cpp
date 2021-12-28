#include "inc/exprtree.h"


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

AssignExprAST::~AssignExprAST(){
    delete expr_;
}

BlockExprAST::~BlockExprAST(){
   for(auto& next : body_)
       delete next;
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


void StartExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   //TODO: check what i can do with this options
    Q_UNUSED(option)
    Q_UNUSED(widget)
   //TODO: Pen and colour should also be properties of subclasses
   //FIX: Colour and pen shouldnt be hardcoded
    if(this->isSelected()){
        QBrush selectedBrush = QBrush(Qt::green,Qt::Dense1Pattern);
        painter->fillRect(boundingRect(),selectedBrush);
    }else
        painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);
    const auto SquareText = QString("%1\n").arg("start");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    emit ShouldUpdateScene();
    //TODO:Default case (maybe throw error)
}

QRectF AssignExprAST::boundingRect() const{
    float w = 100;
    float h = 60;
    return QRectF(-w/2,-h/2,w,h);
}

void AssignExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   //TODO: check what i can do with this options
    Q_UNUSED(option)
    Q_UNUSED(widget)
   //TODO: Pen and colour should also be properties of subclasses
   //FIX: Colour and pen shouldnt be hardcoded
    if(this->isSelected()){
        QBrush selectedBrush = QBrush(Qt::green,Qt::Dense1Pattern);
        painter->fillRect(boundingRect(),selectedBrush);
    }else
        painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);
    const auto SquareText = QString(instructionName_);
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //TODO:Default case (maybe throw error)
    //emit ShouldUpdateScene();
}

QRectF BlockExprAST::boundingRect() const
{
    const float gap=10.0f;
    float w=0.0f;
    float h=0.0f;
    for(auto &elem : body_) {
        auto br = elem->boundingRect();
        if(br.width()>w) {
            w=br.width();
        }
        h+=br.height();
        h+=gap;
    }
    h-=gap;
    return QRectF(-w/2,-h/2,w,h);
}

void BlockExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   //TODO: check what i can do with this options
    Q_UNUSED(option)
    Q_UNUSED(widget)
   //TODO: Pen and colour should also be properties of subclasses
   //FIX: Colour and pen shouldnt be hardcoded
    const float gap=10.0f;
    auto br = boundingRect();

    painter->fillRect(br, color_);
    float currenth = -br.height()/2;

    for(auto elem : body_) {
        elem->setPos(0,currenth + elem->getHeight()/2);
       currenth += elem->getHeight()+gap;
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
    const float gap=10.0f;
    w+= then_->getWidth() + else_->getWidth() + 100.0f;

    h+= then_->getHeight() > else_->getHeight() ? then_->getHeight() : else_->getHeight();

    h+=ifh*2 +gap;
    h+=gap*2;


    return QRectF(-w/2,-h/2,w,h);
}
void IfExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QRectF br = boundingRect();
    float ifh = 60;
    painter->fillRect(br, color_);
    painter->setPen(Qt::white);
    const float gap=10.0f;
    ifrectangle_ = QRectF(-br.width()/2,-br.height()/2 + gap,br.width(),ifh);
    if(this->isSelected()){
        QBrush selectedBrush = QBrush(Qt::green,Qt::Dense1Pattern);
        painter->fillRect(ifrectangle_,selectedBrush);
    }else
        painter->fillRect(ifrectangle_, QColor::fromRgb(128,0,0));
    const auto SquareText = QString("%1").arg(instructionName_);
    painter->drawText(ifrectangle_, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);


    QRectF thenrect=QRectF(-ifrectangle_.width()/2,-br.height()/2 +ifrectangle_.height()+gap*2,then_->getWidth(),ifrectangle_.height());
    //if(this->isSelected()){
       // QBrush selectedBrush = QBrush(Qt::green,Qt::Dense1Pattern);
    //painter->fillRect(thenrect,selectedBrush);
    //}else
    painter->fillRect(thenrect, QColor::fromRgb(128,0,0));
    painter->drawText(thenrect, Qt::AlignHCenter | Qt::AlignVCenter, "then" );


    QRectF elserect=QRectF(ifrectangle_.width()/2 -else_->getWidth() ,-br.height()/2 +ifrectangle_.height()+gap*2,else_->getWidth(),ifrectangle_.height());
    //if(this->isSelected()){
        //QBrush selectedBrush = QBrush(Qt::green,Qt::Dense1Pattern);
    //painter->fillRect(elserect,selectedBrush);
    //}else
    painter->fillRect(elserect, QColor::fromRgb(128,0,0));
    painter->drawText(elserect, Qt::AlignHCenter | Qt::AlignVCenter, "else" );



    then_->setPos(-ifrectangle_.width()/2 + then_->getWidth()/2,-br.height()/2 +ifrectangle_.height()+gap*2 + thenrect.height() + gap + then_->getHeight()/2);
    else_->setPos(ifrectangle_.width()/2 - else_->getWidth()/2, -br.height()/2 +ifrectangle_.height()+gap*2 + elserect.height() + gap + else_->getHeight()/2);

    emit ShouldUpdateScene();
    //TODO:Default case (maybe throw error)
}

QRectF WhileExprAST::boundingRect() const{
    float w=0.0f;
    float h=0.0f;
    float whileh = 60;
    const float gap=10.0f;
    h += body_->getHeight() + whileh+ gap*2;
    w += body_->getWidth();
    return QRectF(-w/2,-h/2,w,h);
}

void WhileExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   //TODO: check what i can do with this options
    Q_UNUSED(option)
    Q_UNUSED(widget)
   //TODO: Pen and colour should also be properties of subclasses
   //FIX: Colour and pen shouldnt be hardcoded
    const float gap=10.0f;
    auto br = boundingRect();
    float whileh = 60;
    painter->fillRect(br, color_);
    painter->setPen(Qt::white);
    whilerectangle_ = QRectF(-br.width()/2,-br.height()/2 + gap,br.width(),whileh);

    //if(this->isSelected()){
       // QBrush selectedBrush = QBrush(Qt::green,Qt::Dense1Pattern);
    //painter->fillRect(rectangle,selectedBrush);
    //}else
    if(this->isSelected()){
        QBrush selectedBrush = QBrush(Qt::green,Qt::Dense1Pattern);
        painter->fillRect(whilerectangle_,selectedBrush);
    }else
        painter->fillRect(whilerectangle_, QColor::fromRgb(128,58,0));
    painter->drawText(whilerectangle_, Qt::AlignHCenter | Qt::AlignVCenter, "While");
    //const auto SquareText = QString("%1\n%2").arg(instructionName_, instructionName_);
    //painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    body_->setPos(0,whilerectangle_.height()/2 + gap);
    emit ShouldUpdateScene();
    //TODO:Default case (maybe throw error)
}

void WhileExprAST::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    auto mousePosition = event->pos();
    emit selectItem(whilerectangle_.contains(mousePosition)?this:nullptr);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

//TODO implement paint
void FunctionExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){}

//QRectF AssignExprAST::boundingRect() const
//{
//    float w=160;
//    float h=80;
//    return QRectF(-w/2, 0, w, h);
//}


void InstructionExprAST::deleteMe(){
    auto parent = static_cast<BlockExprAST*>(parentItem());
    parent->remove(this);
    delete this;
}

//------------ STRINGIFY ------------

QString StartExprAST::stringify() {
    //TODO error handling
    return {};
}

QString AssignExprAST::stringify() {
    return expr_->stringify();
}

QString BlockExprAST::stringify() {
    //TODO error handling
    return {};
}

QString IfExprAST::stringify() {
    return cond_->stringify();
}

QString WhileExprAST::stringify() {
    return cond_->stringify();
}

QString FunctionExprAST::stringify() {
    //TODO error handling
    return {};
}


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
    for(auto expr : body_){
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

//-------------------- QVariant constructors --------------------

AssignExprAST::AssignExprAST(const QVariant& v)
{
    QVariantMap map = v.toMap();
    name_ = map.value("name").toString();
    expr_ = ExprAST::makeFromVariant(map.value("expr"));
}

BlockExprAST::BlockExprAST(const QVariant& v)
{
    QVariantMap map = v.toMap();
    QVariantList list = map.value("body").toList();
    for(auto expr : list){
        insert(dynamic_cast<InstructionExprAST*>(ExprAST::makeFromVariant(expr)));
    }
}

IfExprAST::IfExprAST(const QVariant& v)
{
    QVariantMap map = v.toMap();
    cond_ = ExprAST::makeFromVariant(map.value("cond"));
    then_ = dynamic_cast<BlockExprAST*>(ExprAST::makeFromVariant(map.value("then")));
    else_ = dynamic_cast<BlockExprAST*>(ExprAST::makeFromVariant(map.value("else")));
}

WhileExprAST::WhileExprAST(const QVariant& v)
{
    QVariantMap map = v.toMap();
    cond_ = ExprAST::makeFromVariant(map.value("cond"));
    body_ = dynamic_cast<BlockExprAST*>(ExprAST::makeFromVariant(map.value("body")));
}

FunctionExprAST::FunctionExprAST(const QVariant& v)
{
//TODO: ???
}


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

    painter->fillRect(boundingRect(), QColor::fromRgb(0,128,0));
    painter->setPen(Qt::white);
    const auto SquareText = QString("%1\n").arg("start");
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //emit ShouldUpdateScene();
    //TODO:Default case (maybe throw error)
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
    const auto SquareText = QString("%1\n%2").arg(instructionName_, instructionName_);
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    //TODO:Default case (maybe throw error)
    //emit ShouldUpdateScene();
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
        if(elem->getWidth()>w) {
            w=elem->getWidth();
        }
//        if(auto adds=dynamic_cast<IfExprAST*>(elem)) {
//            w= adds->then_->getWidth()+ adds->else_->getWidth() + elem->getWidth()/2;
//        }

//        h+=elem->getHeight();
//        if(auto adds= dynamic_cast<WhileExprAST*>(elem)) {
//            h+=gap;
//            h+=adds->body_->getHeight();
//        }
//        if(auto adds=dynamic_cast<IfExprAST*>(elem)){
//            h+=gap;
//            h+=adds->then_->getHeight();
//        }
        h+=elem->getHeight();
        h+=gap;
    }
    h-=gap;
    painter->fillRect(boundingRect(), color_);
    //painter->setPen(Qt::white);
    //const auto SquareText = QString("%1\n%2").arg(instructionName_, instructionName_);
    //painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    float currenth = -h/2;

    for(auto elem : body_) {
        elem->setPos(0,currenth + elem->getHeight()/2);
//        if(auto adds = dynamic_cast<WhileExprAST*>(elem)) {
//            adds->body_->setPos(0.0f, elem->y() + 10.0f);
//            currenth += elem->getHeight()+gap;
//            currenth+=adds->body_->getHeight()+gap;

//        }
//        else if(auto adds = dynamic_cast<IfExprAST*>(elem)) {
//            adds->then_->setPos(-getWidth()/2 - 5.0f,elem->y()+ 10.0f);
//            adds->else_->setPos(getWidth()/2 + 5.0f,elem->y()+ 10.0f);
//            currenth += elem->getHeight()+gap;
//            currenth+=adds->then_->getHeight()+gap;
//        }
//        else {
//            currenth += elem->getHeight()+gap;
//        }
       currenth += elem->getHeight()+gap;
    }
    emit ShouldUpdateScene();


    //qDebug()<<"jel si usao: "<<body_.size()<<"\n";
    //TODO:Default case (maybe throw error)
}

void BlockExprAST::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit selectItem(nullptr);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void IfExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    auto ifh=60;
    w=0.0f;
    h=0.0f;
    const float gap=10.0f;
    h+= then_->getHeight() > else_->getHeight() ? then_->getHeight() : else_->getHeight();
    h+=ifh*2 +gap;
    h+=gap*2;

    w+= then_->getWidth() + else_->getWidth() + 100.0f;

    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);

    ifrectangle_ = QRectF(-w/2,-h/2 + gap,w,ifh);

    painter->fillRect(ifrectangle_,QColor::fromRgb(128,0,0));
    const auto SquareText = QString("%1").arg(instructionName_);
    painter->drawText(ifrectangle_, Qt::AlignHCenter | Qt::AlignVCenter, SquareText);


    QRectF thenrect=QRectF(-ifrectangle_.width()/2,-h/2 +ifh+gap*2,then_->getWidth(),ifh);
    //if(this->isSelected()){
       // QBrush selectedBrush = QBrush(Qt::green,Qt::Dense1Pattern);
    //painter->fillRect(thenrect,selectedBrush);
    //}else
    painter->fillRect(thenrect, QColor::fromRgb(128,0,0));
    painter->drawText(thenrect, Qt::AlignHCenter | Qt::AlignVCenter, "then" );


    QRectF elserect=QRectF(ifrectangle_.width()/2 -else_->getWidth() ,-h/2 +ifh+gap*2,else_->getWidth(),ifh);
    //if(this->isSelected()){
        //QBrush selectedBrush = QBrush(Qt::green,Qt::Dense1Pattern);
    //painter->fillRect(elserect,selectedBrush);
    //}else
    painter->fillRect(elserect, QColor::fromRgb(128,0,0));
    painter->drawText(elserect, Qt::AlignHCenter | Qt::AlignVCenter, "else" );



    then_->setPos(-ifrectangle_.width()/2 + then_->getWidth()/2,-h/2 +ifh+gap*2 + thenrect.height() + gap + then_->getHeight()/2);
    else_->setPos(ifrectangle_.width()/2 - else_->getWidth()/2, -h/2 +ifh+gap*2 + elserect.height() + gap + else_->getHeight()/2);

    emit ShouldUpdateScene();
    //TODO:Default case (maybe throw error)
}

void WhileExprAST::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   //TODO: check what i can do with this options
    Q_UNUSED(option)
    Q_UNUSED(widget)
   //TODO: Pen and colour should also be properties of subclasses
   //FIX: Colour and pen shouldnt be hardcoded
    auto whileh = 60;
    w=0.0f;
    h=0.0f;
    const float gap=10.0f;
    h += body_->getHeight() + whileh+ gap*2;
    w += body_->getWidth();


    painter->fillRect(boundingRect(), color_);
    painter->setPen(Qt::white);
    whilerectangle_ = QRectF(-w/2,-h/2 + gap,w,whileh);

    //if(this->isSelected()){
       // QBrush selectedBrush = QBrush(Qt::green,Qt::Dense1Pattern);
    //painter->fillRect(rectangle,selectedBrush);
    //}else
        painter->fillRect(whilerectangle_,QColor::fromRgb(128,0,0));
        painter->drawText(whilerectangle_, Qt::AlignHCenter | Qt::AlignVCenter, "While");
    //const auto SquareText = QString("%1\n%2").arg(instructionName_, instructionName_);
    //painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, SquareText);
    body_->setPos(0,whileh/2 + gap);
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

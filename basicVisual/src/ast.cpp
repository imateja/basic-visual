#include "inc/ast.h"

//--------------------ACCEPT VISIT--------------------

void ValueExprAST::AcceptVisit(VisitorAST& v){
    v.VisitValueExprAST(*this);
}
void VariableExprAST::AcceptVisit(VisitorAST& v){
    v.VisitVariableExprAST(*this);
}
void AddExprAST::AcceptVisit(VisitorAST& v){
    v.VisitAddExprAST(*this);
}
void SubExprAST::AcceptVisit(VisitorAST& v){
    v.VisitSubExprAST(*this);
}
void MulExprAST::AcceptVisit(VisitorAST& v){
    v.VisitMulExprAST(*this);
}
void DivExprAST::AcceptVisit(VisitorAST& v){
    v.VisitDivExprAST(*this);
}
void LtExprAST::AcceptVisit(VisitorAST& v){
    v.VisitLtExprAST(*this);
}
void GtExprAST::AcceptVisit(VisitorAST& v){
    v.VisitGtExprAST(*this);
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
//--------------------OPERATOR=--------------------

BinaryExprAST& BinaryExprAST::operator= (const BinaryExprAST& be){
    if(&be != this){
        delete left_;
        delete right_;
        left_ = be.left_->copy();
        right_ = be.right_->copy();
    }
    return *this;
}

IfExprAST& IfExprAST::operator= (const IfExprAST& ie){
    if(&ie != this){
        delete cond_;
        delete then_;
        delete else_;
        cond_ = ie.cond_->copy();
        then_ = static_cast<BlockExprAST*>(ie.then_->copy());
        else_ = static_cast<BlockExprAST*>(ie.else_->copy());
    }
    return *this;
}

WhileExprAST& WhileExprAST::operator= (const WhileExprAST& we){
    if(&we != this){
        delete cond_;
        delete body_;
        cond_ = we.cond_->copy();
        body_ = static_cast<BlockExprAST*>(we.body_->copy());
    }
    return *this;
}

AssignExprAST& AssignExprAST::operator= (const AssignExprAST& ae){
    if(&ae != this){
        delete expr_;
        expr_ = ae.expr_->copy();
    }
    return *this;
}

BlockExprAST& BlockExprAST::operator= (const BlockExprAST& be){
    if(&be != this){
        for(auto &x : body_){
            delete x;
        }
        body_ = be.body_;
    }
    return *this;
}

FunctionExprAST& FunctionExprAST::operator= (const FunctionExprAST& fe){
    if(&fe != this){
        delete body_;
        body_ = static_cast<BlockExprAST*>(fe.body_->copy());
    }
    return *this;
}

//--------------------DESTRUCTORS--------------------

BinaryExprAST::~BinaryExprAST(){
    delete left_;
    delete right_;
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
    for(auto x : body_){
        delete x;
    }
}

FunctionExprAST::~FunctionExprAST(){
    delete body_;
}
//--------------------COPY CONSTRUCTORS--------------------

BinaryExprAST::BinaryExprAST(const BinaryExprAST& be){
    left_ = be.left_->copy();
    right_ = be.right_->copy();
}

IfExprAST::IfExprAST(const IfExprAST& ie){
    cond_ = ie.cond_->copy();
    then_ = static_cast<BlockExprAST*>(ie.then_->copy());
    else_ = static_cast<BlockExprAST*>(ie.else_->copy());
}

WhileExprAST::WhileExprAST(const WhileExprAST& we){
    cond_ = we.cond_->copy();
    body_ = static_cast<BlockExprAST*>(we.body_->copy());
}

AssignExprAST::AssignExprAST(const AssignExprAST& ae){
    name_ = ae.name_;
    expr_ = ae.expr_->copy();
}

BlockExprAST::BlockExprAST(const BlockExprAST& be){
    body_ = be.body_;
}

FunctionExprAST::FunctionExprAST(const FunctionExprAST& fe){
    name_ = fe.name_;
    body_ = static_cast<BlockExprAST*>(fe.body_->copy());
}

//--------------------COPY--------------------

ExprAST* ValueExprAST::copy() const{
    return new ValueExprAST(*this);
}

ExprAST* VariableExprAST::copy() const{
    return new VariableExprAST(*this);
}

ExprAST* AddExprAST::copy() const{
    return new AddExprAST(*this);
}

ExprAST* SubExprAST::copy() const{
    return new SubExprAST(*this);
}

ExprAST* MulExprAST::copy() const{
    return new MulExprAST(*this);
}

ExprAST* DivExprAST::copy() const{
    return new DivExprAST(*this);
}

ExprAST* LtExprAST::copy() const{
    return new LtExprAST(*this);
}

ExprAST* GtExprAST::copy() const{
    return new GtExprAST(*this);
}

ExprAST* IfExprAST::copy() const{
    return new IfExprAST(*this);
}

ExprAST* WhileExprAST::copy() const{
    return new WhileExprAST(*this);
}

ExprAST* AssignExprAST::copy() const{
    return new AssignExprAST(*this);
}

ExprAST* BlockExprAST::copy() const{
    return new BlockExprAST(*this);
}

ExprAST* FunctionExprAST::copy() const{
    return new FunctionExprAST(*this);
}

//--------------------------------------------

void BlockExprAST::insert(ExprAST* expr, int index){
    body_.insert(index, expr);
}

void BlockExprAST::push_back(ExprAST* expr){
    body_.push_back(expr);
}

#include "ast.h"

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

//--------------------COPY CONSTRUCTORS--------------------

BinaryExprAST::BinaryExprAST(const BinaryExprAST& be){
    left_ = be.left_->copy();
    right_ = be.right_->copy();
}

IfExprAST::IfExprAST(const IfExprAST& ie){
    cond_ = ie.cond_->copy();
    then_ = ie.then_->copy();
    else_ = ie.else_->copy();
}

WhileExprAST::WhileExprAST(const WhileExprAST& we){
    cond_ = we.cond_->copy();
    body_ = we.body_->copy();
}

AssignExprAST::AssignExprAST(const AssignExprAST& ae){
    name_ = ae.name_;
    expr_ = ae.expr_->copy();
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

//--------------------VISITORS--------------------

void Interpret::VisitValueExprAST(ValueExprAST& obj) {
        dValue_= obj.getValue();
}

//TODO
void Interpret::VisitVariableExprAST(VariableExprAST& obj) {
        dValue_=  0;
}

void Interpret::VisitAddExprAST(AddExprAST& obj) {
        dValue_ = Interpret(obj.getLeft()).dValue_ + Interpret(obj.getRight()).dValue_;
}

void Interpret::VisitSubExprAST(SubExprAST& obj) {
        dValue_ = Interpret(obj.getLeft()).dValue_ - Interpret(obj.getRight()).dValue_;
}

void Interpret::VisitMulExprAST(MulExprAST& obj) {
        dValue_ = Interpret(obj.getLeft()).dValue_ * Interpret(obj.getRight()).dValue_;
}

void Interpret::VisitDivExprAST(DivExprAST& obj) {
        dValue_ = Interpret(obj.getLeft()).dValue_ / Interpret(obj.getRight()).dValue_;
}

void Interpret::VisitLtExprAST(LtExprAST& obj) {
        bValue_ =  Interpret(obj.getLeft()).dValue_ < Interpret(obj.getRight()).dValue_;
}

void Interpret::VisitGtExprAST(GtExprAST& obj) {
        bValue_ =  Interpret(obj.getLeft()).dValue_ > Interpret(obj.getRight()).dValue_;
}

void Interpret::VisitIfExprAST(IfExprAST& obj) {
        if (Interpret(obj.getCond()).bValue_) {
                Interpret(obj.getThen());
        } else {
                Interpret(obj.getElse());
        }
}

void Interpret::VisitWhileExprAST(WhileExprAST& obj) {
        while(Interpret(obj.getCond()).bValue_) {
                Interpret(obj.getBody());
        }
}

//TODO
void Interpret::VisitAssignExprAST(AssignExprAST& obj) {
}

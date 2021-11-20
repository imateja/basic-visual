#include "ast.h"



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

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


double Interpret::VisitValueExprAST(ValueExprAST& obj) {
        return obj.getValue();
}

//TODO
double Interpret::VisitVariableExprAST(VariableExprAST& obj) {
    return 0;
}

double Interpret::VisitAddExprAST(AddExprAST& obj) {
        return Interpret(obj.getLeft()) + Interpret(obj.getRight());
}

double Interpret::VisitSubExprAST(SubExprAST& obj) {
        return Interpret(obj.getLeft()) - Interpret(obj.getRight());
}

double Interpret::VisitMulExprAST(MulExprAST& obj) {
        return Interpret(obj.getLeft()) * Interpret(obj.getRight());
}

double Interpret::VisitDivExprAST(DivExprAST& obj) {
        return Interpret(obj.getLeft()) / Interpret(obj.getRight());
}

bool Interpret::VisitLtExprAST(LtExprAST& obj) {
        return Interpret(obj.getLeft()) < Interpret(obj.getRight());
}

bool Interpret::VisitGtExprAST(GtExprAST& obj) {
        return Interpret(obj.getLeft()) > Interpret(obj.getRight());
}

void Interpret::VisitIfExprAST(IfExprAST& obj) {
        if (Interpret(obj.getCond())) {
                Interpret(obj.getThen());
        } else {
                Interpret(obj.getElse());
        }
}

void Interpret::VisitWhileExprAST(WhileExprAST& obj) {
        while(Interpret(obj.getCond())) {
                Interpret(obj.getBody());
        }
}

//TODO
void Interpret::VisitAssignExprAST(AssignExprAST& obj) {
}

#include "interpret.h"


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

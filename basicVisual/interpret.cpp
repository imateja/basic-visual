#include "interpret.h"
#include "state.h"

void Interpret::VisitValueExprAST(ValueExprAST& obj) {
        dValue_= obj.getValue();
}

void Interpret::VisitVariableExprAST(VariableExprAST& obj) {
        dValue_= Interpret(State::Domains().getValue(obj.getName())).dValue_;
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

/* FIX:
 * Ne svidja mi se cast bez ikakve provere tipa.
 * Za sada znamo da ne moze da bude nista osim ValueExprAST,
 * ali kada budemo omogucili dodelu povratne vrednosti funkcije
 * mozda se stvari promene (treba diskutovati o tome)
 */
void Interpret::VisitAssignExprAST(AssignExprAST& obj) {
    State::Domains().assignValue(obj.getName(), dynamic_cast<ValueExprAST*>(obj.getExpr()));
}

void Interpret::VisitBlockExprAST(BlockExprAST& obj){
    //???
    auto body = obj.getBody();
    for(auto e : body){
        Interpret{e};
    }
}

void Interpret::VisitFunctionExprAST(FunctionExprAST& obj){
    Interpret(obj.getBody());
}

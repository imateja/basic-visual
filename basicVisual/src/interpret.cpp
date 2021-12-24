#include "inc/interpret.h"
#include "inc/state.h"

int Interpret::doubleTypeId = QVariant(static_cast<double>(0)).typeId();
int Interpret::boolTypeId = QVariant(static_cast<bool>(true)).typeId();

void Interpret::VisitValueExprAST(ValueExprAST& obj) {
        value_ = obj.getValue();
}

void Interpret::VisitVariableExprAST(VariableExprAST& obj) {
        value_ = State::Domains().getValue(obj.getName());
        if(value_.isNull()){
            //TODO error handling
        }
}

void Interpret::VisitAddExprAST(AddExprAST& obj) {
        auto l = Interpret(obj.getLeft()).value_;
        auto r = Interpret(obj.getRight()).value_;
        if (l.typeId() == doubleTypeId && r.typeId() == doubleTypeId){
            value_ = l.toDouble() + r.toDouble();
        }else {
            //TODO error handling
        }

}

void Interpret::VisitSubExprAST(SubExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    if (l.typeId() == doubleTypeId && r.typeId() == doubleTypeId){
        value_ = l.toDouble() - r.toDouble();
    }else {
        //TODO error handling
    }
}

void Interpret::VisitMulExprAST(MulExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    if (l.typeId() == doubleTypeId && r.typeId() == doubleTypeId){
        value_ = l.toDouble() * r.toDouble();
    }else {
        //TODO error handling
    }
}

void Interpret::VisitDivExprAST(DivExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    if (l.typeId() == doubleTypeId && r.typeId() == doubleTypeId && r.toDouble() != 0){
        value_ = l.toDouble() / r.toDouble();
    }else {
        //TODO error handling
    }
}

void Interpret::VisitLtExprAST(LtExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    if (l.typeId() == doubleTypeId && r.typeId() == doubleTypeId){
        value_ = static_cast<bool>(l.toDouble() < r.toDouble());
    }else {
        //TODO error handling
    }
}

void Interpret::VisitGtExprAST(GtExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    if (l.typeId() == doubleTypeId && r.typeId() == doubleTypeId){
        value_ = static_cast<bool>(l.toDouble() > r.toDouble());
    }else {
        //TODO error handling
    }
}

void Interpret::VisitIfExprAST(IfExprAST& obj) {
    auto cond = Interpret(obj.getCond()).value_;
    if (cond.typeId() == boolTypeId){
        if (cond.toBool()) {
            Interpret(obj.getThen());
        } else {
            Interpret(obj.getElse());
        }
        value_ = QVariant();
    }else{
        //TODO error handling
    }
}

void Interpret::VisitWhileExprAST(WhileExprAST& obj) {
    auto cond = Interpret(obj.getCond()).value_;
    if (cond.typeId() == boolTypeId){
        while(cond.toBool()) {
            Interpret(obj.getBody());
        }
        value_ = QVariant();
    }else{
        //TODO error handling
    }
}


void Interpret::VisitAssignExprAST(AssignExprAST& obj) {
    auto value = Interpret(obj.getExpr()).value_;
    if (value.typeId() == doubleTypeId){
        State::Domains().assignValue(obj.getName(), value);
    }else{
        //TODO error handling
    }
}

void Interpret::VisitBlockExprAST(BlockExprAST& obj){
    State::Domains().createNewDomain();
    for(auto &instr : obj.body_){
        Interpret{instr};
    }
    value_ = QVariant();
    State::Domains().removeCurrentDomain();
}

void Interpret::VisitFunctionExprAST(FunctionExprAST& obj){
    Interpret(obj.getBody());
}

void Interpret::VisitPlaceholderExprAST(PlaceholderExprAST&){}

void Interpret::VisitEndExprAST(EndExprAST&){}

void Interpret::VisitStartExprAST(StartExprAST&){}



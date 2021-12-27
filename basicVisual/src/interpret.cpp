#include <QtMath>
#include "inc/interpret.h"
#include "inc/state.h"

int Interpret::doubleTypeId = QVariant(static_cast<double>(0)).typeId();
int Interpret::boolTypeId = QVariant(static_cast<bool>(true)).typeId();
double Interpret::eps = 0.000001;

void Interpret::VisitPlaceholderExprAST(PlaceholderExprAST&) {
    value_ = QString("Expression not finished :: Placeholder exists");
}

void Interpret::VisitValueExprAST(ValueExprAST& obj) {
    value_ = obj.getValue();
}

void Interpret::VisitVariableExprAST(VariableExprAST& obj) {
    value_ = State::Domains().getValue(obj.getName());
}

void Interpret::VisitNotExprAST(NotExprAST& obj) {
    auto op = Interpret(obj.getOperand()).value_;
    value_ = op.typeId() == boolTypeId ? QVariant(!op.toBool()) : QString("Expression not finished :: Invalid Not operand");
}

void Interpret::VisitMulExprAST(MulExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;

    value_ = l.typeId() == doubleTypeId && r.typeId() == doubleTypeId ?
        QVariant(l.toDouble() * r.toDouble()) : QString("Expression not finished :: Invalid Mul operand(s)");
}

void Interpret::VisitDivExprAST(DivExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    value_ = l.typeId() == doubleTypeId && r.typeId() == doubleTypeId && r.toDouble() != 0 ?
        QVariant(l.toDouble() / r.toDouble()) : QString("Expression not finished :: Invalid Div operand(s)");
}

void Interpret::VisitAddExprAST(AddExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    value_ = l.typeId() == doubleTypeId && r.typeId() == doubleTypeId ?
        QVariant(l.toDouble() + r.toDouble()) : QString("Expression not finished :: Invalid Add operand(s)");
}

void Interpret::VisitSubExprAST(SubExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    value_ = l.typeId() == doubleTypeId && r.typeId() == doubleTypeId ?
        QVariant(l.toDouble() - r.toDouble()) : QString("Expression not finished :: Invalid Sub operand(s)");

}

void Interpret::VisitLtExprAST(LtExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    value_ = l.typeId() == doubleTypeId && r.typeId() == doubleTypeId ?
        QVariant(static_cast<bool>(l.toDouble() < r.toDouble())) :
        QString("Expression not finished :: Invalid Lt operand(s)");
}

void Interpret::VisitLeqExprAST(LeqExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    value_ = l.typeId() == doubleTypeId && r.typeId() == doubleTypeId ?
        QVariant(static_cast<bool>(l.toDouble() <= r.toDouble())) :
        QString("Expression not finished :: Invalid Leq operand(s)");
}

void Interpret::VisitGtExprAST(GtExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    value_ = l.typeId() == doubleTypeId && r.typeId() == doubleTypeId ?
        QVariant(static_cast<bool>(l.toDouble() > r.toDouble())) :
        QString("Expression not finished :: Invalid Gt operand(s)");
}

void Interpret::VisitGeqExprAST(GeqExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    value_ = l.typeId() == doubleTypeId && r.typeId() == doubleTypeId ?
        QVariant(static_cast<bool>(l.toDouble() >= r.toDouble())) :
        QString("Expression not finished :: Invalid Geq operand(s)");
}

void Interpret::VisitEqExprAST(EqExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    if (l.typeId() == doubleTypeId && r.typeId() == doubleTypeId) {
        value_ = static_cast<bool>(qFabs((l.toDouble() - r.toDouble())) < eps);
    }
    else if (l.typeId() == boolTypeId && r.typeId() == boolTypeId) {
        value_ = static_cast<bool>(l.toBool() == r.toBool());
    }
    else {
        value_ = QString("Expression not finished :: Invalid Eq operand(s)");
    }
}

void Interpret::VisitNeqExprAST(NeqExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    if (l.typeId() == doubleTypeId && r.typeId() == doubleTypeId) {
        value_ = static_cast<bool>(qFabs((l.toDouble() - r.toDouble())) > eps);
    }
    else if (l.typeId() == boolTypeId && r.typeId() == boolTypeId) {
        value_ = static_cast<bool>(l.toBool() != r.toBool());
    }
    else {
        value_ = QString("Expression not finished :: Invalid Neq operand(s)");
    }
}

void Interpret::VisitAndExprAST(AndExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    value_ = l.typeId() == boolTypeId && r.typeId() == boolTypeId ?
        QVariant(l.toBool() && r.toBool()) : QString("Expression not finished :: Invalid And operand(s)");
}

void Interpret::VisitOrExprAST(OrExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    auto r = Interpret(obj.getRight()).value_;
    value_ = l.typeId() == boolTypeId && r.typeId() == boolTypeId ?
        QVariant(l.toBool() || r.toBool()) : QString("Expression not finished :: Invalid Or operand(s)");
}

/* --- Following Classes (InstructionExprAST subclasses) set value_ to QVariant() if everything succeds --- */

void Interpret::VisitStartExprAST(StartExprAST&) {
    value_ = QVariant();
}

void Interpret::VisitAssignExprAST(AssignExprAST& obj) {
    value_ = QVariant();

    auto value = Interpret(obj.getExpr()).value_;
    if (value.typeId() == doubleTypeId) {
        State::Domains().assignValue(obj.getName(), value);
    }
    else {
        value_ = QString("Expression not finished :: Invalid Assign expression");
    }
}

void Interpret::VisitBlockExprAST(BlockExprAST& obj) {
    value_ = QVariant();

    State::Domains().createNewDomain();
    for (auto instr : obj.body_) {
        auto value = Interpret{instr}.value_;
        /* it is essential to check if value is not null
         * because it being null suggests that the InstructionExprAST subclass
         * successfully interpreted
         */
        if (!value.isNull() && value.typeId() != doubleTypeId && value.typeId() != boolTypeId)
            value_ = value_.toString() + "\n" + value.toString();
    }
    State::Domains().removeCurrentDomain();
}

void Interpret::VisitIfExprAST(IfExprAST& obj) {
    value_ = QVariant();

    auto cond = Interpret(obj.getCond()).value_;
    if (cond.typeId() == boolTypeId) {
        value_ = cond.toBool() ? Interpret(obj.getThen()).value_ : Interpret(obj.getElse()).value_;
    }
    else {
        value_ = QString("Expression not finished :: Invalid If condition");
    }
}

void Interpret::VisitWhileExprAST(WhileExprAST& obj) {
    value_ = QVariant();

    while (true) {
        auto cond = Interpret(obj.getCond()).value_;
        if (cond.typeId() == boolTypeId) {
            Interpret(obj.getBody());
        }
        else {
            value_ = QString("Expression not finished :: Invalid While condition");
            break;
        }
    }
}

void Interpret::VisitFunctionExprAST(FunctionExprAST& obj) {
    value_ = Interpret(obj.getBody()).value_;   //if Interpret succeds, then value_ is QVariant()
}

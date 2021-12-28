#include <QtMath>
#include "inc/interpret.h"
#include "inc/state.h"

int Interpret::doubleTypeId = QVariant(static_cast<double>(0)).typeId();
int Interpret::boolTypeId = QVariant(static_cast<bool>(true)).typeId();
int Interpret::qstringTypeId = QVariant(static_cast<QString>("")).typeId();
double Interpret::eps = 0.000001;

void Interpret::VisitPlaceholderExprAST(PlaceholderExprAST&) {
    value_ = QString("Expression not finished :: Placeholder exists.");
}

void Interpret::VisitValueExprAST(ValueExprAST& obj) {
    value_ = obj.getValue();
}

void Interpret::VisitVariableExprAST(VariableExprAST& obj) {
    value_ = State::Domains().getValue(obj.getName());
}

void Interpret::VisitNotExprAST(NotExprAST& obj) {
    auto op = Interpret(obj.getOperand()).value_;
    if (op.typeId() == qstringTypeId) {
        value_ = op;
        return;
    }
    if (op.typeId() != boolTypeId) {
        value_ = QString("Not :: Invalid operand, boolean required.");
        return;
    }

    value_ = QVariant(!op.toBool());
}

void Interpret::VisitMulExprAST(MulExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Mul :: Invalid left operand, number required.");
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Mul :: Invalid right operand, number required.");
        return;
    }

    value_ = QVariant(l.toDouble() * r.toDouble());;
}

void Interpret::VisitDivExprAST(DivExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Div :: Invalid left operand, number required.");
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Div :: Invalid right operand, number required.");
        return;
    }

    if (qFabs(r.toDouble()) < eps)
    {
        value_ = QString("Div :: Dividing with 0.");
        return;
    }

    value_ = QVariant(l.toDouble() / r.toDouble());
}

void Interpret::VisitAddExprAST(AddExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Add :: Invalid left operand, number required.");
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Add :: Invalid right operand, number required.");
        return;
    }

    value_ = QVariant(l.toDouble() + r.toDouble());;
}

void Interpret::VisitSubExprAST(SubExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Sub :: Invalid left operand, number required.");
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Sub :: Invalid right operand, number required.");
        return;
    }

    value_ = QVariant(l.toDouble() - r.toDouble());
}

void Interpret::VisitLtExprAST(LtExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Lt :: Invalid left operand, number required.");
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Lt :: Invalid right operand, number required.");
        return;
    }

    value_ = QVariant(static_cast<bool>(l.toDouble() < r.toDouble()));
}

void Interpret::VisitLeqExprAST(LeqExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Leq :: Invalid left operand, number required.");
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Leq :: Invalid right operand, number required.");
        return;
    }

    value_ = QVariant(static_cast<bool>(l.toDouble() <= r.toDouble()));
}

void Interpret::VisitGtExprAST(GtExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Gt :: Invalid left operand, number required.");
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Gt :: Invalid right operand, number required.");
        return;
    }

    value_ = QVariant(static_cast<bool>(l.toDouble() > r.toDouble()));
}

void Interpret::VisitGeqExprAST(GeqExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Geq :: Invalid left operand, number required.");
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Geq :: Invalid right operand, number required.");
        return;
    }

    value_ = QVariant(static_cast<bool>(l.toDouble() >= r.toDouble()));
}

void Interpret::VisitEqExprAST(EqExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }

    if (l.typeId() == doubleTypeId && r.typeId() == doubleTypeId) {
        value_ = static_cast<bool>(qFabs((l.toDouble() - r.toDouble())) < eps);
    }
    else if (l.typeId() == boolTypeId && r.typeId() == boolTypeId) {
        value_ = static_cast<bool>(l.toBool() == r.toBool());
    }
    else {
        value_ = QString("Eq :: Invalid operand(s).");
    }
}

void Interpret::VisitNeqExprAST(NeqExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }

    if (l.typeId() == doubleTypeId && r.typeId() == doubleTypeId) {
        value_ = static_cast<bool>(qFabs((l.toDouble() - r.toDouble())) > eps);
    }
    else if (l.typeId() == boolTypeId && r.typeId() == boolTypeId) {
        value_ = static_cast<bool>(l.toBool() != r.toBool());
    }
    else {
        value_ = QString("Neq :: Invalid operand(s).");
    }
}

void Interpret::VisitAndExprAST(AndExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != boolTypeId) {
        value_ = QString("And :: Invalid left operand, boolean required.");
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != boolTypeId) {
        value_ = QString("And :: Invalid right operand, boolean required.");
        return;
    }

    value_ = QVariant(static_cast<bool>(l.toBool() && r.toBool()));
}

void Interpret::VisitOrExprAST(OrExprAST& obj) {
    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != boolTypeId) {
        value_ = QString("Or :: Invalid left operand, boolean required.");
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != boolTypeId) {
        value_ = QString("Or :: Invalid right operand, boolean required.");
        return;
    }

    value_ = QVariant(static_cast<bool>(l.toBool() || r.toBool()));
}

/* Following Classes (InstructionExprAST subclasses) set value_ to QVariant() if everything succeds, QString otherwise */

void Interpret::VisitStartExprAST(StartExprAST&) {
    value_ = QVariant();
}

void Interpret::VisitAssignExprAST(AssignExprAST& obj) {
    value_ = QVariant();

    auto instrValue = Interpret(obj.getExpr()).value_;
    if (instrValue.typeId() == qstringTypeId) {
        value_ = instrValue;
        return;
    }

    if (instrValue.typeId() == doubleTypeId || instrValue.typeId() == boolTypeId) {
        State::Domains().assignValue(obj.getName(), instrValue);
    }
}

void Interpret::VisitBlockExprAST(BlockExprAST& obj) {
    value_ = QVariant();

    State::Domains().createNewDomain();
    for (auto instr : obj.getBody()) {
        auto instrValue = Interpret{instr}.value_;
        if (instrValue.typeId() == qstringTypeId) {
            value_ = instrValue;
            break;
        }
    }
    State::Domains().removeCurrentDomain();
}

void Interpret::VisitIfExprAST(IfExprAST& obj) {
    value_ = QVariant();

    auto instrCond = Interpret(obj.getCond()).value_;
    if (instrCond.typeId() == qstringTypeId) {
        value_ = instrCond;
        return;
    }
    if (instrCond.typeId() != boolTypeId) {
        value_ = QString("If :: Invalid condition.");
        return;
    }

    value_ = instrCond.toBool() ? Interpret(obj.getThen()).value_ : Interpret(obj.getElse()).value_;
}

void Interpret::VisitWhileExprAST(WhileExprAST& obj) {
    value_ = QVariant();

    while (true) {
        auto instrCond = Interpret(obj.getCond()).value_;
        if (instrCond.typeId() == qstringTypeId) {
            value_ = instrCond;
            return;
        }
        if (instrCond.typeId() != boolTypeId) {
            value_ = QString("While :: Invalid condition.");
            return;
        }

        Interpret(obj.getBody());
    }
}

//if Interpret succeds, then value_ is QVariant(), otherwise it's QString
void Interpret::VisitFunctionExprAST(FunctionExprAST& obj) {
    value_ = Interpret(obj.getBody()).value_;
}

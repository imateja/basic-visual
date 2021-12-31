#include <QtMath>
#include <QMessageBox>
#include <interpret.hpp>
#include <state.hpp>

QMutex Interpret::mutex_ = QMutex();
bool Interpret::steps = false;

int Interpret::doubleTypeId = QVariant(static_cast<double>(0.0f)).typeId();
int Interpret::boolTypeId = QVariant(static_cast<bool>(true)).typeId();
int Interpret::qstringTypeId = QVariant(static_cast<QString>("")).typeId();
double Interpret::eps = 0.000001;
Worker* Interpret::worker = nullptr;
QString Interpret::input = QString();

void Interpret::VisitPlaceholderExprAST(PlaceholderExprAST& obj) {
    obj.errorFound = false;

    if(obj.isEmpty()){
        value_ = QString("Expression not finished :: Placeholder exists.");
        obj.errorFound = true;
        return;
    }

    value_ = Interpret(obj.expr_).value_;
}

void Interpret::VisitValueExprAST(ValueExprAST& obj) {
    value_ = obj.getValue();
}

void Interpret::VisitVariableExprAST(VariableExprAST& obj) {
    obj.errorFound = false;

    value_ = State::Domains().getValue(obj.getName());
    if (value_.typeId() == qstringTypeId) {
        obj.errorFound = true;
    }
}

void Interpret::VisitNotExprAST(NotExprAST& obj) {
    obj.errorFound = false;

    auto op = Interpret(obj.getOperand()).value_;
    if (op.typeId() == qstringTypeId) {
        value_ = op;
        return;
    }
    if (op.typeId() != boolTypeId) {
        value_ = QString("Not :: Invalid operand, boolean required.");
        obj.errorFound = true;
        return;
    }

    value_ = QVariant(!op.toBool());
}

void Interpret::VisitMulExprAST(MulExprAST& obj) {
    obj.errorFound = false;

    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Mul :: Invalid left operand, number required.");
        obj.errorFound = true;
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Mul :: Invalid right operand, number required.");
        obj.errorFound = true;
        return;
    }

    value_ = QVariant(l.toDouble() * r.toDouble());
}

void Interpret::VisitDivExprAST(DivExprAST& obj) {
    obj.errorFound = false;

    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Div :: Invalid left operand, number required.");
        obj.errorFound = true;
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Div :: Invalid right operand, number required.");
        obj.errorFound = true;
        return;
    }

    if (qFabs(r.toDouble()) < eps) {
        value_ = QString("Div :: Dividing with 0.");
        obj.errorFound = true;
        return;
    }

    value_ = QVariant(l.toDouble() / r.toDouble());
}

void Interpret::VisitAddExprAST(AddExprAST& obj) {
    obj.errorFound = false;

    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Add :: Invalid left operand, number required.");
        obj.errorFound = true;
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Add :: Invalid right operand, number required.");
        obj.errorFound = true;
        return;
    }

    value_ = QVariant(l.toDouble() + r.toDouble());
}

void Interpret::VisitSubExprAST(SubExprAST& obj) {
    obj.errorFound = false;

    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Sub :: Invalid left operand, number required.");
        obj.errorFound = true;
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Sub :: Invalid right operand, number required.");
        obj.errorFound = true;
        return;
    }

    value_ = QVariant(l.toDouble() - r.toDouble());
}

void Interpret::VisitLtExprAST(LtExprAST& obj) {
    obj.errorFound = false;

    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Lt :: Invalid left operand, number required.");
        obj.errorFound = true;
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Lt :: Invalid right operand, number required.");
        obj.errorFound = true;
        return;
    }

    value_ = QVariant(static_cast<bool>(l.toDouble() < r.toDouble()));
}

void Interpret::VisitLeqExprAST(LeqExprAST& obj) {
    obj.errorFound = false;

    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Leq :: Invalid left operand, number required.");
        obj.errorFound = true;
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Leq :: Invalid right operand, number required.");
        obj.errorFound = true;
        return;
    }

    value_ = QVariant(static_cast<bool>(l.toDouble() <= r.toDouble()));
}

void Interpret::VisitGtExprAST(GtExprAST& obj) {
    obj.errorFound = false;

    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Gt :: Invalid left operand, number required.");
        obj.errorFound = true;
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Gt :: Invalid right operand, number required.");
        obj.errorFound = true;
        return;
    }

    value_ = QVariant(static_cast<bool>(l.toDouble() > r.toDouble()));
}

void Interpret::VisitGeqExprAST(GeqExprAST& obj) {
    obj.errorFound = false;

    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != doubleTypeId) {
        value_ = QString("Geq :: Invalid left operand, number required.");
        obj.errorFound = true;
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != doubleTypeId) {
        value_ = QString("Geq :: Invalid right operand, number required.");
        obj.errorFound = true;
        return;
    }

    value_ = QVariant(static_cast<bool>(l.toDouble() >= r.toDouble()));
}

void Interpret::VisitEqExprAST(EqExprAST& obj) {
    obj.errorFound = false;

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
        obj.errorFound = true;
    }
}

void Interpret::VisitNeqExprAST(NeqExprAST& obj) {
    obj.errorFound = false;

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
        obj.errorFound = true;
    }
}

void Interpret::VisitAndExprAST(AndExprAST& obj) {
    obj.errorFound = false;

    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != boolTypeId) {
        value_ = QString("And :: Invalid left operand, boolean required.");
        obj.errorFound = true;
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != boolTypeId) {
        value_ = QString("And :: Invalid right operand, boolean required.");
        obj.errorFound = true;
        return;
    }

    value_ = QVariant(static_cast<bool>(l.toBool() && r.toBool()));
}

void Interpret::VisitOrExprAST(OrExprAST& obj) {
    obj.errorFound = false;

    auto l = Interpret(obj.getLeft()).value_;
    if (l.typeId() == qstringTypeId) {
        value_ = l;
        return;
    }
    if (l.typeId() != boolTypeId) {
        value_ = QString("Or :: Invalid left operand, boolean required.");
        obj.errorFound = true;
        return;
    }

    auto r = Interpret(obj.getRight()).value_;
    if (r.typeId() == qstringTypeId) {
        value_ = r;
        return;
    }
    if (r.typeId() != boolTypeId) {
        value_ = QString("Or :: Invalid right operand, boolean required.");
        obj.errorFound = true;
        return;
    }

    value_ = QVariant(static_cast<bool>(l.toBool() || r.toBool()));
}

/* Following Classes (InstructionExprAST subclasses) set value_ to QVariant() if everything succeds, QString otherwise */

void Interpret::VisitStartExprAST(StartExprAST& obj) {
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
    QVector<InstructionExprAST*> b = obj.getBody();
    auto begin = b.begin();
    auto end = b.end();
    worker->current = *begin;
    (*begin)->isCurrent = true;
    auto prev = begin;
    auto instrValue = Interpret{(*begin)}.value_;
    if (instrValue.typeId() == qstringTypeId) {
        value_ = instrValue;
    }else {
        ++begin;
        while(begin != end){
            if(Interpret::steps){
                Interpret::mutex_.lock();
                qDebug() << (*begin) << "\n";
                (*begin)->isCurrent = true;
                worker->current = *begin;
                (*prev)->isCurrent = false;
            }
            auto instrValue = Interpret{(*begin)}.value_;
            if (instrValue.typeId() == qstringTypeId) {
                value_ = instrValue;
                break;
            }
            prev = begin;
            ++begin;
        }
        (*prev)->isCurrent = false;
    }

    State::Domains().removeCurrentDomain();
}

void Interpret::VisitIfExprAST(IfExprAST& obj) {
    obj.errorFound = false;

    value_ = QVariant();

    auto instrCond = Interpret(obj.getCond()).value_;
    if (instrCond.typeId() == qstringTypeId) {
        value_ = instrCond;
        return;
    }
    if (instrCond.typeId() != boolTypeId) {
        value_ = QString("If :: Invalid condition.");
        obj.errorFound = true;
        return;
    }

    value_ = instrCond.toBool() ? Interpret(obj.getThen()).value_ : Interpret(obj.getElse()).value_;
}

void Interpret::VisitWhileExprAST(WhileExprAST& obj) {
    obj.errorFound = false;
    value_ = QVariant();

    while (true) {
        auto instrCond = Interpret(obj.getCond()).value_;
        if (instrCond.typeId() == qstringTypeId) {
            value_ = instrCond;
            return;
        }
        if (instrCond.typeId() != boolTypeId) {
            value_ = QString("While :: Invalid condition.");
            obj.errorFound = true;
            return;
        }

        if(!instrCond.toBool()){
            break;
        }

        auto instrBody = Interpret(obj.getBody()).value_;
        if (instrBody.typeId() == qstringTypeId) {
            value_ = instrCond;
            return;
        }
    }
}

void Interpret::VisitPrintAST(PrintAST& obj) {
    value_ = Interpret(obj.getExpr()).value_;
    if(value_.typeId() == qstringTypeId) {
        worker->print(value_.toString());
        return;
    }
    if(value_.isNull()) {
        value_ = QString("Print :: Invalid print.");
        return;
    }

    worker->print(value_.toString());
    value_ = {};
}

void Interpret::VisitInputAST(InputAST& obj){
    worker->btnsettings(true);
    worker->print("Input variable " + obj.getName() + ":");
    Interpret::mutex_.lock();
    if(input.isEmpty()){
        value_ = QString("Input :: input empty");
        return;
    }
    bool ok;
    auto val = input.toDouble(&ok);
    if(!ok) {
        value_ = QString("Input :: not a valid number");
        return;
    }
    auto tmp = QVariant(val);
    State::Domains().assignValue(obj.getName(),tmp);
    worker->print(input);
    worker->btnsettings(false);
    value_ = {};
}

inline QString Interpret::getValue() {
    return value_.typeId() == qstringTypeId? value_.toString(): "";
}

void Worker::print(QString txt){
    emit sendPrintText(txt);
}

void Worker::process() {
    Interpret::worker = this;
    auto res = Interpret{mainBlock_}.getValue();
    emit sendResult(res);
    emit finished();
}

void Worker::btnsettings(bool enabled) {
    emit changeButtonSettings(enabled);
}

void Worker::kill(){
    State::Domains().clear();
    current->isCurrent = false;
    emit finished();
}

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

void Interpret::VisitPlaceholderExprAST(PlaceholderAST& obj) {
    obj.errorFound = false;

    if(obj.isEmpty()){
        value_ = QString("Expression not finished :: Placeholder exists.");
        obj.errorFound = true;
        return;
    }

    value_ = Interpret(obj.getExpr()).getValue();
}

void Interpret::VisitValueExprAST(ValueAST& obj) {
    value_ = obj.getValue();
}

void Interpret::VisitVariableExprAST(VariableAST& obj) {
    obj.errorFound = false;

    value_ = State::Domains().getValue(obj.getName());
    if (value_.typeId() == qstringTypeId) {
        obj.errorFound = true;
    }
}

void Interpret::VisitNotExprAST(NotAST& obj) {
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

void Interpret::VisitMulExprAST(MulAST& obj) {
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

void Interpret::VisitDivExprAST(DivAST& obj) {
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

void Interpret::VisitAddExprAST(AddAST& obj) {
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

void Interpret::VisitSubExprAST(SubAST& obj) {
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

void Interpret::VisitLtExprAST(LtAST& obj) {
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

void Interpret::VisitLeqExprAST(LeqAST& obj) {
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

void Interpret::VisitGtExprAST(GtAST& obj) {
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

void Interpret::VisitGeqExprAST(GeqAST& obj) {
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

void Interpret::VisitEqExprAST(EqAST& obj) {
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

void Interpret::VisitNeqExprAST(NeqAST& obj) {
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

void Interpret::VisitAndExprAST(AndAST& obj) {
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

void Interpret::VisitOrExprAST(OrAST& obj) {
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

void Interpret::VisitStartExprAST(StartAST& obj) {
    if(Interpret::steps){
        obj.isCurrent = true;
        Interpret::mutex_.lock();
        obj.isCurrent = false;
    }
    value_ = QVariant();
}

void Interpret::VisitAssignExprAST(AssignAST& obj) {
    value_ = QVariant();
    if(Interpret::steps){
        obj.isCurrent = true;
        Interpret::mutex_.lock();
    }
    auto instrValue = Interpret(obj.getExpr()).value_;
    if(Interpret::steps){
        obj.isCurrent = false;
    }

    if (instrValue.typeId() == qstringTypeId) {
        value_ = instrValue;
        return;
    }

    if (instrValue.typeId() == doubleTypeId || instrValue.typeId() == boolTypeId) {
        State::Domains().assignValue(obj.getName(), instrValue);
    }
}

//void Interpret::VisitBlockExprAST(BlockAST& obj) {
//    value_ = QVariant();
//    State::Domains().createNewDomain();
//    QVector<InstructionAST*> b = obj.getBody();
//    auto begin = b.begin();
//    auto end = b.end();
//    if(Interpret::steps){
//        (*begin)->isCurrent = true;
//    }
//    auto prev = begin;
//    auto instrValue = Interpret{(*begin)}.value_;
//    if (instrValue.typeId() == qstringTypeId) {
//        value_ = instrValue;
//    }else {
//        ++begin;
//        while(begin != end){
//            if(Interpret::steps){
//                Interpret::mutex_.lock();
//                (*begin)->isCurrent = true;
//                (*prev)->isCurrent = false;
//            }
//            auto instrValue = Interpret{(*begin)}.value_;
//            if (instrValue.typeId() == qstringTypeId) {
//                value_ = instrValue;
//                break;
//            }
//            prev = begin;
//            ++begin;
//        }
//        Interpret::mutex_.lock();
//        (*prev)->isCurrent = false;

//    }

//    State::Domains().removeCurrentDomain();
//}


void Interpret::VisitBlockExprAST(BlockAST& obj) {
    value_ = QVariant();
    State::Domains().createNewDomain();

    for(auto instruction : obj.getBody()){
        auto instrValue = Interpret{instruction}.value_;
        if (instrValue.typeId() == qstringTypeId) {
            value_ = instrValue;
            break;
        }
    }
    State::Domains().removeCurrentDomain();
}

void Interpret::VisitIfExprAST(IfAST& obj) {
    obj.errorFound = false;

    value_ = QVariant();
    if(Interpret::steps){
        obj.isCurrent = true;
        Interpret::mutex_.lock();
    }
    auto instrCond = Interpret(obj.getCond()).value_;
    if(Interpret::steps){
        obj.isCurrent = false;
    }
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

void Interpret::VisitWhileExprAST(WhileAST& obj) {
    obj.errorFound = false;
    value_ = QVariant();

    while (true) {
        if(Interpret::steps){
            obj.isCurrent = true;
            Interpret::mutex_.lock();
        }
        auto instrCond = Interpret(obj.getCond()).value_;
        if(Interpret::steps){
            obj.isCurrent = false;
        }
        if (instrCond.typeId() == qstringTypeId) {
            value_ = instrCond;
            obj.errorFound = true;
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
    if(Interpret::steps){
        obj.isCurrent = true;
        Interpret::mutex_.lock();
    }
    value_ = Interpret(obj.getExpr()).value_;
    if(Interpret::steps){
        obj.isCurrent = false;
    }
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
    if(Interpret::steps){
        obj.isCurrent = true;
    }
    Interpret::mutex_.lock();
    QString in = input;
    input = "";
    if(in.isEmpty()){
        value_ = QString("Input :: input empty");
        return;
    }
    bool ok;
    auto val = in.toDouble(&ok);
    if(!ok) {
        value_ = QString("Input :: not a valid number");
        return;
    }
    auto tmp = QVariant(val);
    State::Domains().assignValue(obj.getName(),tmp);
    worker->print(in);
    worker->btnsettings(false);
    if(Interpret::steps){
        obj.isCurrent = false;
    }
    value_ = {};
}

QString Interpret::getErrorMsg() {
    return value_.typeId() == qstringTypeId? value_.toString(): "";
}

void Worker::print(QString txt){
    emit sendPrintText(txt);
}

void Worker::process() {
    Interpret::worker = this;
    auto res = Interpret{mainBlock_}.getErrorMsg();
    emit sendResult(res);
    emit finished();
    Interpret::steps = false;
}

void Worker::btnsettings(bool enabled) {
    emit changeButtonSettings(enabled);
}


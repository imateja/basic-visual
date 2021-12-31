#ifndef INTERPRET_H
#define INTERPRET_H

#include <QVariant>
#include <QMutex>
#include <ast.hpp>
#include <exprtree.hpp>

class Worker;

class Interpret final : public VisitorAST
{
public:
    Interpret() {}
    Interpret(ExprAST* expr)
    {
        expr->AcceptVisit(*this);
    }

    void VisitPlaceholderExprAST(PlaceholderAST&) override;
    void VisitValueExprAST(ValueAST&) override;
    void VisitVariableExprAST(VariableAST&) override;

    void VisitNotExprAST(NotAST&) override;
    void VisitMulExprAST(MulAST&) override;
    void VisitDivExprAST(DivAST&) override;
    void VisitAddExprAST(AddAST&) override;
    void VisitSubExprAST(SubAST&) override;
    void VisitLtExprAST(LtAST&) override;
    void VisitLeqExprAST(LeqAST&) override;
    void VisitGtExprAST(GtAST&) override;
    void VisitGeqExprAST(GeqAST&) override;
    void VisitEqExprAST(EqAST&) override;
    void VisitNeqExprAST(NeqAST&) override;
    void VisitAndExprAST(AndAST&) override;
    void VisitOrExprAST(OrAST&) override;

    void VisitStartExprAST(StartAST&) override;
    void VisitAssignExprAST(AssignAST&) override;
    void VisitBlockExprAST(BlockAST&) override;
    void VisitIfExprAST(IfAST&) override;
    void VisitWhileExprAST(WhileAST&) override;
    void VisitPrintAST(PrintAST&) override;
    void VisitInputAST(InputAST&) override;

    inline QString getErrorMsg();

    inline QVariant getValue() { return value_;}

    static int doubleTypeId;
    static int boolTypeId;
    static int qstringTypeId;
    static double eps;
    static QMutex mutex_;
    static bool steps;
    static Worker* worker;
    static QString input;

private:
    QVariant value_;
};

class Worker : public QObject {
    Q_OBJECT

public:
    Worker(BlockAST* mb)
        : mainBlock_(mb)
    {}

    void print(QString);
    void btnsettings(bool);
    InstructionAST* current;

public slots:
    void process();

signals:
    void finished();
    void sendResult(QString result);
    void sendPrintText(QString);
    void changeButtonSettings(bool);

private:
    BlockAST* mainBlock_;

};

#endif // INTERPRET_H

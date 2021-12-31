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

    void VisitPlaceholderExprAST(PlaceholderExprAST&) override;
    void VisitValueExprAST(ValueExprAST&) override;
    void VisitVariableExprAST(VariableExprAST&) override;

    void VisitNotExprAST(NotExprAST&) override;
    void VisitMulExprAST(MulExprAST&) override;
    void VisitDivExprAST(DivExprAST&) override;
    void VisitAddExprAST(AddExprAST&) override;
    void VisitSubExprAST(SubExprAST&) override;
    void VisitLtExprAST(LtExprAST&) override;
    void VisitLeqExprAST(LeqExprAST&) override;
    void VisitGtExprAST(GtExprAST&) override;
    void VisitGeqExprAST(GeqExprAST&) override;
    void VisitEqExprAST(EqExprAST&) override;
    void VisitNeqExprAST(NeqExprAST&) override;
    void VisitAndExprAST(AndExprAST&) override;
    void VisitOrExprAST(OrExprAST&) override;

    void VisitStartExprAST(StartExprAST&) override;
    void VisitAssignExprAST(AssignExprAST&) override;
    void VisitBlockExprAST(BlockExprAST&) override;
    void VisitIfExprAST(IfExprAST&) override;
    void VisitWhileExprAST(WhileExprAST&) override;
    void VisitPrintAST(PrintAST&) override;
    void VisitFunctionExprAST(FunctionExprAST&) override;

    inline QString getValue();

    static int doubleTypeId;
    static int boolTypeId;
    static int qstringTypeId;
    static double eps;
    static QMutex mutex_;
    static bool steps;
    static Worker* worker;

private:
    QVariant value_;
};

class Worker : public QObject {
    Q_OBJECT

public:
    Worker(BlockExprAST* mb)
        : mainBlock_(mb)
    {}

    void print(QString);

public slots:
    void process();

signals:
    void finished();
    void sendResult(QString result);
    void sendPrintText(QString);

private:
    BlockExprAST* mainBlock_;
};

#endif // INTERPRET_H

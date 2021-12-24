#ifndef INTERPRET_H
#define INTERPRET_H

#include <QVariant>
#include <QDebug>
#include "ast.h"
#include "exprtree.h"

class Interpret final : public VisitorAST
{
public:
    Interpret()
    {}
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
    void VisitEndExprAST(EndExprAST&) override;
    void VisitAssignExprAST(AssignExprAST&) override;
    void VisitBlockExprAST(BlockExprAST&) override;
    void VisitIfExprAST(IfExprAST&) override;
    void VisitWhileExprAST(WhileExprAST&) override;
    void VisitFunctionExprAST(FunctionExprAST&) override;

    static int doubleTypeId;
    static int boolTypeId;
    static double eps;

private:
    QVariant value_;
};

#endif // INTERPRET_H

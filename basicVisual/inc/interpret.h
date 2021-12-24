#ifndef INTERPRET_H
#define INTERPRET_H

#include "ast.h"
#include "exprtree.h"
#include <QVariant>
#include <QDebug>

class Interpret final : public VisitorAST
{
public:
    Interpret()
    {}
    Interpret(ExprAST* expr)
    {
        expr->AcceptVisit(*this);
    }


    void VisitValueExprAST(ValueExprAST&) override;
    void VisitVariableExprAST(VariableExprAST&) override;
    void VisitAssignExprAST(AssignExprAST&) override;
    void VisitBlockExprAST(BlockExprAST&) override;

    void VisitAddExprAST(AddExprAST&) override;
    void VisitSubExprAST(SubExprAST&) override;
    void VisitMulExprAST(MulExprAST&) override;
    void VisitDivExprAST(DivExprAST&) override;

    void VisitEqExprAST(EqExprAST&) override;
    void VisitNeqExprAST(NeqExprAST&) override;
    void VisitLtExprAST(LtExprAST&) override;
    void VisitLeqExprAST(LeqExprAST&) override;
    void VisitGtExprAST(GtExprAST&) override;
    void VisitGeqExprAST(GeqExprAST&) override;

    void VisitIfExprAST(IfExprAST&) override;
    void VisitWhileExprAST(WhileExprAST&) override;
    void VisitFunctionExprAST(FunctionExprAST&) override;

    void VisitPlaceholderExprAST(PlaceholderExprAST&) override;
    void VisitEndExprAST(EndExprAST&) override;
    void VisitStartExprAST(StartExprAST&) override;
    static int doubleTypeId;
    static int boolTypeId;
private:
    QVariant value_;
};

#endif // INTERPRET_H

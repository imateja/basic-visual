#ifndef INTERPRET_H
#define INTERPRET_H

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

    //TEMP
    operator double() { return dValue_; }
    operator bool() { return bValue_; }

    void VisitValueExprAST(ValueExprAST&) override;
    void VisitVariableExprAST(VariableExprAST&) override;
    void VisitAddExprAST(AddExprAST&) override;
    void VisitSubExprAST(SubExprAST&) override;
    void VisitMulExprAST(MulExprAST&) override;
    void VisitDivExprAST(DivExprAST&) override;
    void VisitLtExprAST(LtExprAST&) override;
    void VisitGtExprAST(GtExprAST&) override;
    void VisitIfExprAST(IfExprAST&) override;
    void VisitWhileExprAST(WhileExprAST&) override;
    void VisitAssignExprAST(AssignExprAST&) override;
    void VisitBlockExprAST(BlockExprAST&) override;
    void VisitFunctionExprAST(FunctionExprAST&) override;
    void VisitEndExprAST(EndExprAST&) override;
    void VisitStartExprAST(StartExprAST&) override;
    void VisitThenElseExprAST(ThenElseExprAST&) override;

private:
    double dValue_;
    bool bValue_;
};

#endif // INTERPRET_H

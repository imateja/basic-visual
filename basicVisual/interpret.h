#ifndef INTERPRET_H
#define INTERPRET_H

#include "ast.h"

class Interpret : public VisitorAST
{
public:
    Interpret()
    {}
    Interpret(ExprAST* expr)
    {
        expr->AcceptVisit(*this);
    }

    void VisitValueExprAST(ValueExprAST&);
    void VisitVariableExprAST(VariableExprAST&);
    void VisitAddExprAST(AddExprAST&);
    void VisitSubExprAST(SubExprAST&);
    void VisitMulExprAST(MulExprAST&);
    void VisitDivExprAST(DivExprAST&);
    void VisitLtExprAST(LtExprAST&);
    void VisitGtExprAST(GtExprAST&);
    void VisitIfExprAST(IfExprAST&);
    void VisitWhileExprAST(WhileExprAST&);
    void VisitAssignExprAST(AssignExprAST&);

private:
    double dValue_;
    bool bValue_;
};

#endif // INTERPRET_H

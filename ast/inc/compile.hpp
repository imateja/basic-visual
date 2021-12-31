#ifndef COMPILE_H
#define COMPILE_H

#include <QString>
#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/LinkAllPasses.h>
#include <ast.hpp>
#include <exprtree.hpp>

using namespace llvm;

class Compile final : public VisitorAST
{
public:
    Compile()
    {}
    
    Compile(ExprAST* expr)
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

    static void InitializeModuleAndPassManager();
    static void compile(const QString& file);

    QString getValue() const;

private:
    QVariant value_;
};

#endif // COMPILE_H

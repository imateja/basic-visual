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
    void VisitInputAST(InputAST&) override;

    static void InitializeModuleAndPassManager();
    static void compile(const QString& file);

    QString getValue() const;

private:
    QVariant value_;
};

#endif // COMPILE_H

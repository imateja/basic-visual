#ifndef EXPRTREE_H
#define EXPRTREE_H

#include "ast.h"

class ExprTree
{
public:
    static ExprTree& Tree(){
        static ExprTree function {};
        return function;
    }
    ~ExprTree();
private:
    ExprTree(string name = "main"){
        function_ = new FunctionExprAST(name);
    }
    FunctionExprAST* function_;
    ExprTree(const ExprTree&) = delete;
    ExprTree& operator=(const ExprTree&) = delete;
};

#endif // EXPRTREE_H

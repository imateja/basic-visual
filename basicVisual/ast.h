#ifndef AST_H
#define AST_H
#include <string>
using namespace std;

class ValueExprAST;
class VariableExprAST;
class AddExprAST;
class SubExprAST;
class MulExprAST;
class DivExprAST;
class LtExprAST;
class GtExprAST;
class WhileExprAST;
class IfExprAST;
class AssignExprAST;

class VisitorAST
{
public:
    virtual void VisitValueExprAST(ValueExprAST&) = 0;
    virtual void VisitVariableExprAST(VariableExprAST&) = 0;
    virtual void VisitAddExprAST(AddExprAST&) = 0;
    virtual void VisitSubExprAST(SubExprAST&) = 0;
    virtual void VisitMulExprAST(MulExprAST&) = 0;
    virtual void VisitDivExprAST(DivExprAST&) = 0;
    virtual void VisitLtExprAST(LtExprAST&) = 0;
    virtual void VisitGtExprAST(GtExprAST&) = 0;
    virtual void VisitIfExprAST(IfExprAST&) = 0;
    virtual void VisitWhileExprAST(WhileExprAST&) = 0;
    virtual void VisitAssignExprAST(AssignExprAST&) = 0;

};

class ExprAST
{
public:
    virtual ~ExprAST(){}
    virtual void AcceptVisit(VisitorAST& v) = 0;
    virtual ExprAST* copy() const = 0;
};

class ValueExprAST : public ExprAST
{
public:
    ValueExprAST(double value)
        :value_(value)
    {}
    void AcceptVisit(VisitorAST& visitor);
    double getValue() {return value_;}
    ExprAST* copy() const;
private:
    double value_;
};

class VariableExprAST : public ExprAST
{
public:
    VariableExprAST(string name)
        :name_(name)
    {}
    void AcceptVisit(VisitorAST& visitor);
    string getName() {return name_;}
    ExprAST* copy() const;
private:
    string name_;
};

class BinaryExprAST : public ExprAST
{
public:
    BinaryExprAST(ExprAST *left, ExprAST *right)
        :left_(left),right_(right)
    {}
    ~BinaryExprAST();
    BinaryExprAST(const BinaryExprAST&);
    BinaryExprAST& operator= (const BinaryExprAST&);
    virtual ExprAST* getLeft() {return left_;}
    virtual ExprAST* getRight() {return right_;}
protected:
    ExprAST *left_, *right_;
};

class AddExprAST : public BinaryExprAST
{
public:
    AddExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST& visitor);
    ExprAST* copy() const;
};

class DivExprAST : public BinaryExprAST
{
public:
    DivExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST& visitor);
    ExprAST* copy() const;
};

class MulExprAST : public BinaryExprAST
{
public:
    MulExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST& v);
    ExprAST* copy() const;
};

class SubExprAST : public BinaryExprAST
{
public:
    SubExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST& visitor);
    ExprAST* copy() const;
};

class LtExprAST : public BinaryExprAST
{
public:
    LtExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST& visitor);
    ExprAST* copy() const;
};

class GtExprAST : public BinaryExprAST
{
public:
    GtExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST& visitor);
    ExprAST* copy() const;
};

class IfExprAST : public ExprAST
{
public:
    IfExprAST(ExprAST *cond, ExprAST *then, ExprAST *Else)
        :cond_(cond),then_(then),else_(Else)
    {}
    void AcceptVisit(VisitorAST& visitor);
    ~IfExprAST();
    IfExprAST(const IfExprAST&);
    IfExprAST& operator= (const IfExprAST&);
    ExprAST* getCond() {return cond_;}
    ExprAST* getThen() {return then_;}
    ExprAST* getElse() {return else_;}
    ExprAST* copy() const;
private:
    ExprAST *cond_, *then_, *else_;
};

class WhileExprAST : public ExprAST
{
public:
    WhileExprAST(ExprAST *cond,ExprAST *body)
        :cond_(cond),body_(body)
    {}
    void AcceptVisit(VisitorAST& visitor);
    ~WhileExprAST();
    WhileExprAST(const WhileExprAST&);
    WhileExprAST& operator= (const WhileExprAST&);
    ExprAST* getCond() {return cond_;}
    ExprAST* getBody() {return body_;}
    ExprAST* copy() const;
private:
    ExprAST *cond_, *body_;
};

class AssignExprAST : public ExprAST
{
public:
    AssignExprAST(string name, ExprAST *expr)
        :name_(name),expr_(expr)
    {}
    void AcceptVisit(VisitorAST& visitor);
    ~AssignExprAST();
    AssignExprAST(const AssignExprAST&);
    AssignExprAST& operator= (const AssignExprAST&);
    string getName() {return name_;}
    ExprAST* getExpr() {return expr_;}
    ExprAST* copy() const;
private:
    string name_;
    ExprAST* expr_;
};

//----------------visitori---------------------------

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

#endif // AST_H

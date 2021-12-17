#ifndef AST_H
#define AST_H
#include <QString>
#include <QVector>
#include <QColor>

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
class BlockExprAST;
class FunctionExprAST;
class EndExprAST;
class StartExprAST;
class ThenElseExprAST;

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
    virtual void VisitBlockExprAST(BlockExprAST&) = 0;
    virtual void VisitFunctionExprAST(FunctionExprAST&) = 0;
    virtual void VisitEndExprAST(EndExprAST&) = 0;
    virtual void VisitStartExprAST(StartExprAST&) = 0;
    virtual void VisitThenElseExprAST(ThenElseExprAST&) = 0;

};

class ExprAST
{
public:
    virtual ~ExprAST(){}
    virtual void AcceptVisit(VisitorAST&) = 0;
    //virtual ExprAST* copy() const = 0;
};

class ValueExprAST final : public ExprAST
{
public:
    ValueExprAST(double value)
        :value_(value)
    {}
    void AcceptVisit(VisitorAST&) override;
    inline double getValue() {return value_;}
    //ExprAST* copy() const override;
private:
    double value_;
};

class VariableExprAST final : public ExprAST
{
public:
    VariableExprAST(QString name)
        :name_(name)
    {}
    void AcceptVisit(VisitorAST&) override;
    inline QString getName() {return name_;}
    //ExprAST* copy() const override;
private:
    QString name_;
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

class AddExprAST final : public BinaryExprAST
{
public:
    AddExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&) override;
    //ExprAST* copy() const override;
};

class DivExprAST final : public BinaryExprAST
{
public:
    DivExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&) override;
    //ExprAST* copy() const override;
};

class MulExprAST final : public BinaryExprAST
{
public:
    MulExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&) override;
    //ExprAST* copy() const override;
};

class SubExprAST final : public BinaryExprAST
{
public:
    SubExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&) override;
    //ExprAST* copy() const override;
};

class LtExprAST final : public BinaryExprAST
{
public:
    LtExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&) override;
    //ExprAST* copy() const override;
};

class GtExprAST final : public BinaryExprAST
{
public:
    GtExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&) override;
    //ExprAST* copy() const override;
};



#endif // AST_H

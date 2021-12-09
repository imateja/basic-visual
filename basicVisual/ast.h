#ifndef AST_H
#define AST_H
#include <QString>
#include <QVector>

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

};

class ExprAST
{
public:
    virtual ~ExprAST(){}
    virtual void AcceptVisit(VisitorAST&) = 0;
    virtual ExprAST* copy() const = 0;
};

class ValueExprAST : public ExprAST
{
public:
    ValueExprAST(double value)
        :value_(value)
    {}
    void AcceptVisit(VisitorAST&);
    double getValue() {return value_;}
    ExprAST* copy() const;
private:
    double value_;
};

class VariableExprAST : public ExprAST
{
public:
    VariableExprAST(QString name)
        :name_(name)
    {}
    void AcceptVisit(VisitorAST&);
    QString getName() {return name_;}
    ExprAST* copy() const;
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

class AddExprAST : public BinaryExprAST
{
public:
    AddExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&);
    ExprAST* copy() const;
};

class DivExprAST : public BinaryExprAST
{
public:
    DivExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&);
    ExprAST* copy() const;
};

class MulExprAST : public BinaryExprAST
{
public:
    MulExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&);
    ExprAST* copy() const;
};

class SubExprAST : public BinaryExprAST
{
public:
    SubExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&);
    ExprAST* copy() const;
};

class LtExprAST : public BinaryExprAST
{
public:
    LtExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&);
    ExprAST* copy() const;
};

class GtExprAST : public BinaryExprAST
{
public:
    GtExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&);
    ExprAST* copy() const;
};

class BlockExprAST : public ExprAST
{
public:
    BlockExprAST(QVector<ExprAST*> body)
        :body_(body)
    {}
    BlockExprAST()
        :body_(QVector<ExprAST*>())
    {}
    void AcceptVisit(VisitorAST&);
    ~BlockExprAST();
    BlockExprAST(const BlockExprAST&);
    BlockExprAST& operator= (const BlockExprAST&);
    QVector<ExprAST*> getBody() {return body_;}
    ExprAST* copy() const;
    void insert(ExprAST*, int);
    void push_back(ExprAST*);
private:
    QVector<ExprAST*> body_;
};

class IfExprAST : public ExprAST
{
public:
    IfExprAST(ExprAST *cond, BlockExprAST *then, BlockExprAST *Else)
        :cond_(cond),then_(then),else_(Else)
    {}
    IfExprAST(ExprAST *cond)
        :cond_(cond),then_(new BlockExprAST),else_(new BlockExprAST)
    {}
    void AcceptVisit(VisitorAST&);
    ~IfExprAST();
    IfExprAST(const IfExprAST&);
    IfExprAST& operator= (const IfExprAST&);
    ExprAST* getCond() {return cond_;}
    BlockExprAST* getThen() {return then_;}
    BlockExprAST* getElse() {return else_;}
    ExprAST* copy() const;
private:
    ExprAST *cond_;
    BlockExprAST *then_;
    BlockExprAST *else_;
};

class WhileExprAST : public ExprAST
{
public:
    WhileExprAST(ExprAST *cond, BlockExprAST *body)
        :cond_(cond),body_(body)
    {}
    WhileExprAST(ExprAST *cond)
        :cond_(cond),body_(new BlockExprAST())
    {}
    void AcceptVisit(VisitorAST&);
    ~WhileExprAST();
    WhileExprAST(const WhileExprAST&);
    WhileExprAST& operator= (const WhileExprAST&);
    ExprAST* getCond() {return cond_;}
    BlockExprAST* getBody() {return body_;}
    ExprAST* copy() const;
private:
    ExprAST *cond_;
    BlockExprAST *body_;
};

class AssignExprAST : public ExprAST
{
public:
    AssignExprAST(QString name, ExprAST *expr)
        :name_(name),expr_(expr)
    {}
    void AcceptVisit(VisitorAST&);
    ~AssignExprAST();
    AssignExprAST(const AssignExprAST&);
    AssignExprAST& operator= (const AssignExprAST&);
    QString getName() {return name_;}
    ExprAST* getExpr() {return expr_;}
    ExprAST* copy() const;
private:
    QString name_;
    ExprAST* expr_;
};



class FunctionExprAST : public ExprAST
{
public:
    FunctionExprAST(QString name, BlockExprAST* body)
        :name_(name), body_(body)
    {}
    FunctionExprAST(QString name)
        :FunctionExprAST(name, new BlockExprAST())
    {}
    void AcceptVisit(VisitorAST&);
    ~FunctionExprAST();
    FunctionExprAST(const FunctionExprAST&);
    FunctionExprAST& operator= (const FunctionExprAST&);
    QString getName() {return name_;}
    BlockExprAST* getBody() {return body_;}
    ExprAST* copy() const;
private:
    QString name_;
    BlockExprAST* body_;
};

#endif // AST_H

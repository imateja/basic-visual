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

class ValueExprAST final : public ExprAST
{
public:
    ValueExprAST(double value)
        :value_(value)
    {}
    void AcceptVisit(VisitorAST&) override;
    inline double getValue() {return value_;}
    ExprAST* copy() const override;
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
    ExprAST* copy() const override;
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
    ExprAST* copy() const override;
};

class DivExprAST final : public BinaryExprAST
{
public:
    DivExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&) override;
    ExprAST* copy() const override;
};

class MulExprAST final : public BinaryExprAST
{
public:
    MulExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&) override;
    ExprAST* copy() const override;
};

class SubExprAST final : public BinaryExprAST
{
public:
    SubExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&) override;
    ExprAST* copy() const override;
};

class LtExprAST final : public BinaryExprAST
{
public:
    LtExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&) override;
    ExprAST* copy() const override;
};

class GtExprAST final : public BinaryExprAST
{
public:
    GtExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}
    void AcceptVisit(VisitorAST&) override;
    ExprAST* copy() const override;
};

class BlockExprAST final : public ExprAST
{
public:
    BlockExprAST(QVector<ExprAST*> body)
        :body_(body)
    {}
    BlockExprAST()
        :body_(QVector<ExprAST*>())
    {}
    void AcceptVisit(VisitorAST&) override;
    ~BlockExprAST();
    BlockExprAST(const BlockExprAST&);
    BlockExprAST& operator= (const BlockExprAST&);
    inline QVector<ExprAST*> getBody() {return body_;}
    ExprAST* copy() const override;
    void insert(ExprAST*, int);
    void push_back(ExprAST*);
    //TEMP
    unsigned size();
    ExprAST* at(unsigned);
private:
    QVector<ExprAST*> body_;
};

class IfExprAST final : public ExprAST
{
public:
    IfExprAST(ExprAST *cond, BlockExprAST *then, BlockExprAST *Else)
        :cond_(cond),then_(then),else_(Else)
    {}
    IfExprAST(ExprAST *cond)
        :cond_(cond),then_(new BlockExprAST),else_(new BlockExprAST)
    {}
    void AcceptVisit(VisitorAST&) override;
    ~IfExprAST();
    IfExprAST(const IfExprAST&);
    IfExprAST& operator= (const IfExprAST&);
    inline ExprAST* getCond() {return cond_;}
    inline BlockExprAST* getThen() {return then_;}
    inline BlockExprAST* getElse() {return else_;}
    ExprAST* copy() const override;
private:
    ExprAST *cond_;
    BlockExprAST *then_;
    BlockExprAST *else_;
};

class WhileExprAST final : public ExprAST
{
public:
    WhileExprAST(ExprAST *cond, BlockExprAST *body)
        :cond_(cond),body_(body)
    {}
    WhileExprAST(ExprAST *cond)
        :cond_(cond),body_(new BlockExprAST())
    {}
    void AcceptVisit(VisitorAST&) override;
    ~WhileExprAST();
    WhileExprAST(const WhileExprAST&);
    WhileExprAST& operator= (const WhileExprAST&);
    inline ExprAST* getCond() {return cond_;}
    inline BlockExprAST* getBody() {return body_;}
    ExprAST* copy() const override;
private:
    ExprAST *cond_;
    BlockExprAST *body_;
};

class AssignExprAST final : public ExprAST
{
public:
    AssignExprAST(QString name, ExprAST *expr)
        :name_(name),expr_(expr)
    {}
    void AcceptVisit(VisitorAST&) override;
    ~AssignExprAST();
    AssignExprAST(const AssignExprAST&);
    AssignExprAST& operator= (const AssignExprAST&);
    inline QString getName() {return name_;}
    inline ExprAST* getExpr() {return expr_;}
    ExprAST* copy() const override;
private:
    QString name_;
    ExprAST* expr_;
};

class FunctionExprAST final : public ExprAST
{
public:
    FunctionExprAST(QString name, BlockExprAST* body)
        :name_(name), body_(body)
    {}
    FunctionExprAST(QString name)
        :FunctionExprAST(name, new BlockExprAST())
    {}
    void AcceptVisit(VisitorAST&) override;
    ~FunctionExprAST();
    FunctionExprAST(const FunctionExprAST&);
    FunctionExprAST& operator= (const FunctionExprAST&);
    inline QString getName() {return name_;}
    inline BlockExprAST* getBody() {return body_;}
    ExprAST* copy() const override;
private:
    QString name_;
    BlockExprAST* body_;
};

#endif // AST_H

#ifndef EXPRTREE_H
#define EXPRTREE_H

#include <QPainter>
#include <QGraphicsObject>
#include <QVector>
#include <QDebug>
#include <algorithm>
#include "ast.h"
#include "state.h"

class InstructionExprAST : public ExprAST
{
public:
    InstructionExprAST(QGraphicsItem* parent = nullptr)
      :ExprAST(parent)
    {}
    ~InstructionExprAST(){}

    virtual ExprAST* getEditableExpr() = 0;
    virtual void updateChildren() = 0;
    inline unsigned getPriority() final {return 0u;}

    InstructionExprAST* next_; //TODO: remove
};

class StartExprAST : public InstructionExprAST
{
public:
    StartExprAST(QGraphicsItem* parent = nullptr)
        :InstructionExprAST(parent)
    {}
    ~StartExprAST(){};

    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final {}
    ExprAST* getEditableExpr() override { return nullptr; }
    QString stringify() final;
    //ExprAST* copy() const override;

    //QRectF boundingRect() const override;
    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class EndExprAST : public InstructionExprAST
{
public:
    EndExprAST(QGraphicsItem* parent = nullptr)
        :InstructionExprAST(parent)
    {}
    ~EndExprAST(){};

    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final {}
    ExprAST* getEditableExpr() override { return nullptr; }
    QString stringify() final;
    //ExprAST* copy() const override;

    //QRectF boundingRect() const override;
    QColor color_= QColor::fromRgb(128,0,0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class AssignExprAST final : public InstructionExprAST
{
public:
    AssignExprAST(QString name, ExprAST *expr = nullptr,QGraphicsItem* parent = nullptr)
        :InstructionExprAST(parent), name_(name)
        ,expr_(expr!=nullptr?expr:new PlaceholderExprAST)
    {}
    ~AssignExprAST();
    AssignExprAST(const AssignExprAST&);
    AssignExprAST& operator= (const AssignExprAST&);

    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final {}
    ExprAST* getEditableExpr() override { return expr_; }
    inline QString getName() {return name_;}
    inline ExprAST* getExpr() {return expr_;}
    QString stringify() final;
    //ExprAST* copy() const override;

    //QRectF boundingRect() const override;
    QColor color_= QColor::fromRgb(128,0,128);
    QString instructionName_ = QString("Assign");
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QString name_;
    ExprAST* expr_;
};

class BlockExprAST : public InstructionExprAST
{
public:
    BlockExprAST( QGraphicsItem* parent = nullptr)
        : InstructionExprAST(parent)
    {
        body_.push_back(new StartExprAST(this));
    }
    ~BlockExprAST();
    BlockExprAST(const BlockExprAST&);
    //BlockExprAST& operator= (const BlockExprAST&) = default;

    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final;
    void insert(InstructionExprAST*,InstructionExprAST* = nullptr);
    //unsigned size();
    //InstructionContainer* at(unsigned);
    ExprAST* getEditableExpr() override { return nullptr; }
    inline QVector<InstructionExprAST*> getBody() {return body_;}
    QString stringify() final;
    //ExprAST* copy() const override;

    //QRectF boundingRect() const override;
    QColor color_= QColor::fromRgb(0,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QVector<InstructionExprAST*> body_;
};

//class ThenElseExprAST: public InstructionExprAST
//{
//public:
//    ThenElseExprAST(const QString name, BlockExprAST* block = new BlockExprAST(), QObject* parent = nullptr)
//        :name_(name), block_(block), InstructionExprAST(parent)
//    {}
//    QRectF boundingRect() const override;
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
//    inline qint32 getWidth() const { return 100; }
//    inline qint32 getHeight() const { return 70; }
//    void AcceptVisit(VisitorAST&) override;
//    BlockExprAST* block_;
//private:

//    QString name_;

//};

class IfExprAST final : public InstructionExprAST
{
public:
    IfExprAST(ExprAST *cond = nullptr, BlockExprAST *thenblock = nullptr, BlockExprAST *elseblock = nullptr, QGraphicsItem* parent = nullptr)
        :cond_(cond!=nullptr?cond:new PlaceholderExprAST)
        ,then_(thenblock!=nullptr?thenblock:new BlockExprAST(this))
        ,else_(elseblock!=nullptr?elseblock:new BlockExprAST(this))
        ,InstructionExprAST(parent)
    {}
    ~IfExprAST();
    IfExprAST(const IfExprAST&);
    IfExprAST& operator= (const IfExprAST&);

    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final;
    ExprAST* getEditableExpr() override { return cond_; }
    inline ExprAST* getCond() {return cond_;}
    inline BlockExprAST* getThen() {return then_;}
    inline BlockExprAST* getElse() {return else_;}
    QString stringify() final;
    //ExprAST* copy() const override;

    //QRectF boundingRect() const override;
    QColor color_= QColor::fromRgb(128,128,0);
    QString instructionName_ = QString("If");
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    ExprAST *cond_;
    BlockExprAST *then_;
    BlockExprAST *else_;
};

class WhileExprAST final : public InstructionExprAST
{
public:
    WhileExprAST(ExprAST *cond = nullptr, BlockExprAST *body = nullptr, QGraphicsItem* parent = nullptr)
        :cond_(cond!=nullptr?cond:new PlaceholderExprAST)
        ,body_(body!=nullptr?body:new BlockExprAST(this))
        ,InstructionExprAST(parent)
    {}
    ~WhileExprAST();
    WhileExprAST(const WhileExprAST&);
    WhileExprAST& operator= (const WhileExprAST&);

    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final;
    ExprAST* getEditableExpr() override { return cond_; }
    inline ExprAST* getCond() {return cond_;}
    inline BlockExprAST* getBody() {return body_;}
    QString stringify() final;
    //ExprAST* copy() const override;

    //QRectF boundingRect() const override;
    QColor color_= QColor::fromRgb(60,60,0);
    QString instructionName_ = QString("While");
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    BlockExprAST *body_;

private:
    ExprAST *cond_;

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
    ~FunctionExprAST();
    FunctionExprAST(const FunctionExprAST&);
    FunctionExprAST& operator= (const FunctionExprAST&);

    void AcceptVisit(VisitorAST&) override;
    inline unsigned getPriority() final {return 0u;}
    inline QString getName() {return name_;}
    inline BlockExprAST* getBody() {return body_;}
    QString stringify() final;
    //ExprAST* copy() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QString name_;
    BlockExprAST* body_;
};

//class ExprTree final
//{
//public:
//    static ExprTree& Tree(){
//        static ExprTree function {};
//        return function;
//    }
//    ~ExprTree();
//    InstructionExprAST* selected;
//private:
//    ExprTree(){
//        program_ = new BlockExprAST();
//        program_->body_ = new StartExprAST();
//        selected = program_->body_;
//    }
//    BlockExprAST* program_;
//    ExprTree(const ExprTree&) = delete;
//    ExprTree& operator=(const ExprTree&) = delete;
//};

#endif // EXPRTREE_H

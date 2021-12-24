#ifndef EXPRTREE_H
#define EXPRTREE_H

#include "ast.h"
#include <QPainter>
#include <QGraphicsObject>
#include <QVector>
#include "state.h"
#include <algorithm>
#include <QDebug>

class InstructionExprAST : public ExprAST
{
public:
    InstructionExprAST(QGraphicsItem* parent = nullptr)
      :ExprAST(parent)
    {}

    virtual void updateChildren() = 0;

    inline unsigned getPriority() final {return 0u;}

    ~InstructionExprAST(){

    }
    InstructionExprAST* next_; //TODO: remove

    virtual ExprAST* getEditableExpr() = 0;
};

class StartExprAST : public InstructionExprAST
{
public:
    StartExprAST(QGraphicsItem* parent = nullptr)
        :InstructionExprAST(parent)
    {}
    void AcceptVisit(VisitorAST&) override;
    //ExprAST* copy() const override;
    //QRectF boundingRect() const override;
    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    ExprAST* getEditableExpr() override { return nullptr; }

    ~StartExprAST();
    void updateChildren() final {}
};

class EndExprAST : public InstructionExprAST
{
public:
    EndExprAST(QGraphicsItem* parent = nullptr)
        :InstructionExprAST(parent)
    {}
    void AcceptVisit(VisitorAST&) override;
    //ExprAST* copy() const override;
    QColor color_= QColor::fromRgb(128,0,0);
   // QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    ExprAST* getEditableExpr() override { return nullptr; }

    ~EndExprAST();
    void updateChildren() final {}
};

class BlockExprAST : public InstructionExprAST
{
public:
    BlockExprAST( QGraphicsItem* parent = nullptr)
        : InstructionExprAST(parent)
    {
        body_.push_back(new StartExprAST(this));
    }
    void AcceptVisit(VisitorAST&) override;
    ~BlockExprAST();
    void updateChildren() final;
    BlockExprAST(const BlockExprAST&);
    //BlockExprAST& operator= (const BlockExprAST&) = default;
    inline QVector<InstructionExprAST*> getBody() {return body_;}
    //ExprAST* copy() const override;
    void insert(InstructionExprAST*,InstructionExprAST* = nullptr);

    ExprAST* getEditableExpr() override { return nullptr; }

    //TEMP
//    unsigned size();
//    InstructionContainer* at(unsigned);
    QColor color_= QColor::fromRgb(0,0,128);
    //QRectF boundingRect() const override;
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

    void AcceptVisit(VisitorAST&) override;
    ~IfExprAST();
    IfExprAST(const IfExprAST&);
    IfExprAST& operator= (const IfExprAST&);
    inline ExprAST* getCond() {return cond_;}
    inline BlockExprAST* getThen() {return then_;}
    inline BlockExprAST* getElse() {return else_;}
    void updateChildren() final;
    //ExprAST* copy() const override;
    QColor color_= QColor::fromRgb(128,128,0);
    QString instructionName_ = QString("If");
    //QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    ExprAST* getEditableExpr() override { return cond_; }

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
    void AcceptVisit(VisitorAST&) override;
    ~WhileExprAST();
    WhileExprAST(const WhileExprAST&);
    WhileExprAST& operator= (const WhileExprAST&);
    inline ExprAST* getCond() {return cond_;}
    inline BlockExprAST* getBody() {return body_;}

    ExprAST* getEditableExpr() override { return cond_; }
    void updateChildren() final;

    //ExprAST* copy() const override;
    QColor color_= QColor::fromRgb(60,60,0);
    QString instructionName_ = QString("While");
    //QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    BlockExprAST *body_;
private:
    ExprAST *cond_;

};

class AssignExprAST final : public InstructionExprAST
{
public:
    AssignExprAST(QString name, ExprAST *expr = nullptr,QGraphicsItem* parent = nullptr)
        :InstructionExprAST(parent), name_(name)
        ,expr_(expr!=nullptr?expr:new PlaceholderExprAST)
    {}
    void AcceptVisit(VisitorAST&) override;
    ~AssignExprAST();
    AssignExprAST(const AssignExprAST&);
    AssignExprAST& operator= (const AssignExprAST&);
    inline QString getName() {return name_;}
    inline ExprAST* getExpr() {return expr_;}

    ExprAST* getEditableExpr() override { return expr_; }
    void updateChildren() final {}

    //ExprAST* copy() const override;
    QColor color_= QColor::fromRgb(128,0,128);
    QString instructionName_ = QString("Assign");
    //QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
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
    inline unsigned getPriority() final {return 0u;}
    ~FunctionExprAST();
    FunctionExprAST(const FunctionExprAST&);
    FunctionExprAST& operator= (const FunctionExprAST&);
    inline QString getName() {return name_;}
    inline BlockExprAST* getBody() {return body_;}
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

#ifndef EXPRTREE_H
#define EXPRTREE_H

#include <QPainter>
#include <QGraphicsObject>
#include <QVector>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <algorithm>
#include "ast.h"
#include "state.h"

class InstructionExprAST : public ExprAST
{
public:
    InstructionExprAST(QGraphicsItem* parent = nullptr)
      :ExprAST(parent)
    {
        color_= QColor::fromRgb(0,64,128);
    }
    ~InstructionExprAST(){}
    void deleteMe() override;
    virtual ExprAST* getEditableExpr() = 0;
    inline Priority getPriority() final {return Priority::INSTRUCTION;}
};

class StartExprAST : public InstructionExprAST
{
public:
    StartExprAST(QGraphicsItem* parent = nullptr)
        :InstructionExprAST(parent)
    {
        color_= QColor::fromRgb(0,128,0);
    }
    ~StartExprAST(){};

    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final {}
    ExprAST* getEditableExpr() override { return nullptr; }
    QString stringify() final;
    //ExprAST* copy() const override;
    void deleteMe() override {};
    //QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class AssignExprAST final : public InstructionExprAST
{
public:
    AssignExprAST(QString name, ExprAST *expr = nullptr,QGraphicsItem* parent = nullptr)
        :InstructionExprAST(parent), name_(name)
        ,expr_(expr!=nullptr?expr:new PlaceholderExprAST)
    {
        color_ = QColor::fromRgb(64, 120, 7);
    }
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

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QString instructionName_ = QString("Assign");

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
        auto start = new StartExprAST(this);
        insert(start);
        color_= QColor::fromRgb(0,0,128);
    }
    ~BlockExprAST();
    BlockExprAST(const BlockExprAST&);
    //BlockExprAST& operator= (const BlockExprAST&) = default;

    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final;
    void insert(InstructionExprAST*, InstructionExprAST* = nullptr);
    void remove(InstructionExprAST* instr);
    ExprAST* getEditableExpr() override { return nullptr; }
    inline QVector<InstructionExprAST*> getBody() {return body_;}
    QString stringify() final;
    //ExprAST* copy() const override;
    QRectF boundingRect() const override;
    void deleteMe() override {} ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QVector<InstructionExprAST*> body_;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

class IfExprAST final : public InstructionExprAST
{
public:
    IfExprAST(ExprAST *cond = nullptr, BlockExprAST *thenblock = nullptr, BlockExprAST *elseblock = nullptr, QGraphicsItem* parent = nullptr)
        :cond_(cond!=nullptr?cond:new PlaceholderExprAST)
        ,then_(thenblock!=nullptr?thenblock:new BlockExprAST(this))
        ,else_(elseblock!=nullptr?elseblock:new BlockExprAST(this))
        ,InstructionExprAST(parent)
    {
        then_->setParentItem(this);
        connect(then_, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
        connect(then_, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
        connect(then_, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);

        else_->setParentItem(this);
        connect(else_, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
        connect(else_, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
        connect(else_, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);

        color_= QColor::fromRgb(128,128,0);
    }
    ~IfExprAST();
    IfExprAST(const IfExprAST&);
    IfExprAST& operator= (const IfExprAST&);

    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    ExprAST* getEditableExpr() override { return cond_; }
    inline ExprAST* getCond() {return cond_;}
    inline BlockExprAST* getThen() {return then_;}
    inline BlockExprAST* getElse() {return else_;}
    QString stringify() final;
    //ExprAST* copy() const override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QString instructionName_ = QString("If");
    ExprAST *cond_;
    BlockExprAST *then_;
    BlockExprAST *else_;
    QRectF ifrectangle_;
};

class WhileExprAST final : public InstructionExprAST
{
public:
    WhileExprAST(ExprAST *cond = nullptr, BlockExprAST *body = nullptr, QGraphicsItem* parent = nullptr)
        :cond_(cond!=nullptr?cond:new PlaceholderExprAST)
        ,body_(body!=nullptr?body:new BlockExprAST(this))
        ,InstructionExprAST(parent)
    {
        body_->setParentItem(this);
        connect(body_, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
        connect(body_, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
        connect(body_, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);

        color_= QColor::fromRgb(60,60,0);
    }
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

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QString instructionName_ = QString("While");
    BlockExprAST *body_;
    QRectF whilerectangle_;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    ExprAST *cond_;
};

class FunctionExprAST final : public ExprAST
{
public:
    FunctionExprAST(QString name, BlockExprAST* body)
        :name_(name), body_(body)
    {
        color_= QColor::fromRgb(0,60,60);
    }
    FunctionExprAST(QString name)
        :FunctionExprAST(name, new BlockExprAST())
    {}
    ~FunctionExprAST();
    FunctionExprAST(const FunctionExprAST&);
    FunctionExprAST& operator= (const FunctionExprAST&);

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::INSTRUCTION;}
    inline QString getName() {return name_;}
    inline BlockExprAST* getBody() {return body_;}
    QString stringify() final;
    //ExprAST* copy() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QString name_;
    BlockExprAST* body_;
};

#endif // EXPRTREE_H

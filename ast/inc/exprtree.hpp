#ifndef EXPRTREE_H
#define EXPRTREE_H

#include <QPainter>
#include <QGraphicsObject>
#include <QVector>
#include <QFontMetrics>
#include <QFont>
#include <QGraphicsSceneMouseEvent>
#include <ast.hpp>
#include <state.hpp>

class InstructionAST : public ExprAST
{
public:
    InstructionAST(QGraphicsItem* parent = nullptr)
      : ExprAST(parent), isCurrent(false)
    {}
    ~InstructionAST(){}
    void deleteMe() override;
    virtual ExprAST* getEditableExpr() = 0;
    inline Priority getPriority() const final {return Priority::INSTRUCTION;}
    QRectF boundingRect() const override;
    bool isCurrent;
};

class StartAST : public InstructionAST
{
public:
    StartAST(QGraphicsItem* parent = nullptr)
        : InstructionAST(parent)
    {
        color_= QColor::fromRgb(156, 102, 21);
    }
    StartAST(const QVariant&) : StartAST() {}

    ~StartAST(){};

    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final {}
    ExprAST* getEditableExpr() override { return nullptr; }
    QString stringify() const final;
    QVariant toVariant() const override;
    void deleteMe() override {}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    StartAST(const StartAST&) = delete;
    StartAST& operator=(const StartAST&) = delete;
};

class AssignAST final : public InstructionAST
{
public:
    AssignAST(QString name, ExprAST *expr = nullptr,QGraphicsItem* parent = nullptr)
        : InstructionAST(parent), name_(name)
        , expr_(expr != nullptr ? expr : new PlaceholderAST)
    {
        color_ = QColor::fromRgb(156, 102, 21);
    }
    AssignAST(const QVariant&);

    ~AssignAST();

    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final {}
    ExprAST* getEditableExpr() override {return expr_;}
    inline QString getName() const { return name_; }
    inline ExprAST* getExpr() const { return expr_; }
    QString stringify() const final;
    QVariant toVariant() const override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QString instructionName_ = QString("Assign");

private:
    QString name_;
    ExprAST* expr_;

    AssignAST(const AssignAST&) = delete;
    AssignAST& operator=(const AssignAST&) = delete;
};

class BlockAST : public InstructionAST
{
public:
    BlockAST( QGraphicsItem* parent = nullptr)
        : InstructionAST(parent)
    {
        auto start = new StartAST(this);
        insert(start);
        color_= QColor::fromRgb(42, 71, 71);
    }
    BlockAST(const QVariant&);

    ~BlockAST();

    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final;
    void insert(InstructionAST*, InstructionAST* = nullptr);
    void remove(InstructionAST* instr);
    ExprAST* getEditableExpr() override { return nullptr; }
    inline QVector<InstructionAST*> getBody() const {return body_;}
    QString stringify() const final;
    QVariant toVariant() const override;
    QRectF boundingRect() const override;
    void deleteMe() override {} ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    BlockAST(const BlockAST&) = delete;
    BlockAST& operator=(const BlockAST&) = delete;
    QVector<InstructionAST*> body_;
};

class IfAST final : public InstructionAST
{
public:
    IfAST(ExprAST *cond = nullptr, BlockAST *thenblock = nullptr, BlockAST *elseblock = nullptr, QGraphicsItem* parent = nullptr)
        : cond_(cond != nullptr ? cond : new PlaceholderAST())
        , then_(thenblock != nullptr ? thenblock : new BlockAST(this))
        , else_(elseblock != nullptr ? elseblock : new BlockAST(this))
        , InstructionAST(parent)
    {
        then_->setParentItem(this);
        connect(then_, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
        connect(then_, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
        connect(then_, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);

        else_->setParentItem(this);
        connect(else_, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
        connect(else_, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
        connect(else_, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);

        color_= QColor::fromRgb(156, 102, 21);
    }
    IfAST(const QVariant&);

    ~IfAST();

    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    ExprAST* getEditableExpr() override { return cond_; }
    inline ExprAST* getCond() const {return cond_;}
    inline BlockAST* getThen() const {return then_;}
    inline BlockAST* getElse() const {return else_;}
    QString stringify() const final;
    QVariant toVariant() const override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QString instructionName_ = QString("If");
    QRectF ifrectangle_;

private:
    IfAST(const IfAST&) = delete;
    IfAST& operator= (const IfAST&) = delete;
    ExprAST *cond_;
    BlockAST *then_;
    BlockAST *else_;
};

class WhileAST final : public InstructionAST
{
public:
    WhileAST(ExprAST *cond = nullptr, BlockAST *body = nullptr, QGraphicsItem* parent = nullptr)
        : cond_(cond != nullptr ? cond : new PlaceholderAST)
        , body_(body != nullptr ? body : new BlockAST(this))
        , InstructionAST(parent)
    {
        body_->setParentItem(this);
        connect(body_, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
        connect(body_, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
        connect(body_, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);

        color_= QColor::fromRgb(156, 102, 21);
    }
    WhileAST(const QVariant&);

    ~WhileAST();

    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final;
    ExprAST* getEditableExpr() override { return cond_; }
    inline ExprAST* getCond() const {return cond_;}
    inline BlockAST* getBody() const {return body_;}
    QString stringify() const final;
    QVariant toVariant() const override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QString instructionName_ = QString("While");

    QRectF whilerectangle_;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    ExprAST *cond_;
    BlockAST *body_;
    WhileAST(const WhileAST&);
    WhileAST& operator=(const WhileAST&);
};

class PrintAST final : public InstructionAST
{
public:
    PrintAST(ExprAST* expr = nullptr, QGraphicsItem* parent = nullptr)
        : expr_(expr != nullptr ? expr : new PlaceholderAST()), InstructionAST(parent)
    {
        color_= QColor::fromRgb(156, 102, 21);
    }
    PrintAST(const QVariant&);

    ~PrintAST();

    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final {}
    QString stringify() const final;
    QVariant toVariant() const override;
    inline ExprAST* getExpr() const {return expr_;}
    QString instructionName_ = QString("Print");
    ExprAST* getEditableExpr() override { return expr_; }
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    ExprAST* expr_;

    PrintAST(const PrintAST&);
    PrintAST& operator=(const PrintAST&);
};

class InputAST final : public InstructionAST
{
public:
    InputAST(QString name,QGraphicsItem* parent = nullptr)
        :name_(name),InstructionAST(parent)
    {
        color_= QColor::fromRgb(156, 102, 21);
    }
    InputAST(const QVariant&);
    void AcceptVisit(VisitorAST&) override;
    void updateChildren() final {}
    QString stringify() const final;
    QVariant toVariant() const override;
    inline QString getName() const {return name_;}
    ~InputAST(){}
    QString instructionName_ = QString("Input");
    ExprAST* getEditableExpr() override { return nullptr; }
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    QString name_;
};

#endif // EXPRTREE_H

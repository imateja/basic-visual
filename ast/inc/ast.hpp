#ifndef AST_H
#define AST_H
#include <QString>
#include <QVector>
#include <QColor>
#include <QPainter>
#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <serializable.hpp>

class PlaceholderAST;
class ValueAST;
class VariableAST;

class NotAST;
class MulAST;
class DivAST;
class AddAST;
class SubAST;
class LtAST;
class LeqAST;
class GtAST;
class GeqAST;
class EqAST;
class NeqAST;
class AndAST;
class OrAST;

class StartAST;
class AssignAST;
class BlockAST;
class IfAST;
class WhileAST;
class PrintAST;
class InputAST;

class VisitorAST
{
public:
    virtual void VisitPlaceholderExprAST(PlaceholderAST&) = 0;
    virtual void VisitValueExprAST(ValueAST&) = 0;
    virtual void VisitVariableExprAST(VariableAST&) = 0;

    virtual void VisitNotExprAST(NotAST&) = 0;
    virtual void VisitMulExprAST(MulAST&) = 0;
    virtual void VisitDivExprAST(DivAST&) = 0;
    virtual void VisitAddExprAST(AddAST&) = 0;
    virtual void VisitSubExprAST(SubAST&) = 0;
    virtual void VisitLtExprAST(LtAST&) = 0;
    virtual void VisitLeqExprAST(LeqAST&) = 0;
    virtual void VisitGtExprAST(GtAST&) = 0;
    virtual void VisitGeqExprAST(GeqAST&) = 0;
    virtual void VisitEqExprAST(EqAST&) = 0;
    virtual void VisitNeqExprAST(NeqAST&) = 0;
    virtual void VisitAndExprAST(AndAST&) = 0;
    virtual void VisitOrExprAST(OrAST&) = 0;

    virtual void VisitAssignExprAST(AssignAST&) = 0;
    virtual void VisitBlockExprAST(BlockAST&) = 0;
    virtual void VisitIfExprAST(IfAST&) = 0;
    virtual void VisitWhileExprAST(WhileAST&) = 0;
    virtual void VisitPrintAST(PrintAST&) = 0;
    virtual void VisitInputAST(InputAST&) = 0;
    virtual void VisitStartExprAST(StartAST&) = 0;
};

enum class Priority
{
    INSTRUCTION = 0,
    UNARY = 1,
    ARITHMETIC_HIGHER = 2,
    ARITHMETIC_LOWER = 3,
    RELATIONAL_HIGHER = 4,
    RELATIONAL_LOWER = 5,
    LOGICAL = 6
};

class ExprAST : public QGraphicsObject, public Serializable
{
    Q_OBJECT
public:
    ExprAST(QGraphicsItem* parent = nullptr)
        : QGraphicsObject(parent), errorFound(false)
    {
        setFlags(GraphicsItemFlag::ItemIsSelectable);
    }
    virtual ~ExprAST(){}

    virtual void AcceptVisit(VisitorAST&) = 0;
    virtual Priority getPriority() const = 0;
    virtual QString stringify() const = 0;
    virtual void deleteMe();
    inline float getWidth() const { return boundingRect().width(); }
    inline float getHeight() const { return boundingRect().height(); }

    static ExprAST* makeFromVariant(const QVariant& v);

    QColor color_;
    const QString instructionName_;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void updateChildren() {};

    bool errorFound;
    static float gap;
    QBrush setBrush();

signals:
    void selectItem(ExprAST* item);
    void updateSelection();
    void ShouldUpdateScene();

public slots:
    void propagateSelectItem(ExprAST* item);
    void propagateUpdateSelection();
    void propagateShouldUpdateScene();

signals:
    void Moved();
    void signalSelected();
};

class PlaceholderAST final : public ExprAST
{
public:
    PlaceholderAST(){
        expr_ = nullptr;
        color_= QColor::fromRgb(112, 171, 175);
    }
    PlaceholderAST(const QVariant& v);

    void setExpr(ExprAST* expr){
        expr_ = expr;
        expr_->setParentItem(this);
        connect(expr_, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
        connect(expr_, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
        connect(expr_, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);
    }

    ~PlaceholderAST();

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {
        return expr_ ? expr_->getPriority() : Priority::INSTRUCTION;
    }
    QString stringify() const final;
    QVariant toVariant() const override;

    void deleteMe() override {}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    void updateChildren() final;
    inline bool isEmpty() const {return expr_ == nullptr;}
    void clear() {expr_ = nullptr;}
    inline ExprAST* getExpr() const { return expr_; }

private:
    PlaceholderAST(const PlaceholderAST&) = delete;
    PlaceholderAST& operator=(const PlaceholderAST&) = delete;
    ExprAST* expr_;
};

class ValueAST final : public ExprAST
{
public:
    ValueAST(double value)
        : value_(value)
    {
        color_= QColor::fromRgb(107, 39, 55);
    }
    ValueAST(const QVariant& v);

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::INSTRUCTION;}
    inline double getValue() const { return value_; }
    QString stringify() const final;
    QVariant toVariant() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
private:
    double value_;
    ValueAST(const ValueAST&) = delete;
    ValueAST& operator=(const ValueAST&) = delete;
};

class VariableAST final : public ExprAST
{
public:
    VariableAST(QString name)
        : name_(name)
    {
        color_= QColor::fromRgb(107, 39, 55);
    }
    VariableAST(const QVariant& v);

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::INSTRUCTION;}
    inline QString getName() const { return name_; }
    QString stringify() const final;
    QVariant toVariant() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

private:
    QString name_;
    VariableAST(const VariableAST&) = delete;
    VariableAST& operator=(const VariableAST&) = delete;
};

class OperatorAST : public ExprAST
{
public:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
protected:
    QRectF opcircle_;
    QPointF center_;
    QString op_;
};

class UnaryAST : public OperatorAST
{
public:
    UnaryAST(ExprAST *operand = nullptr)
        : operand_(operand != nullptr ? operand : new PlaceholderAST())
    {
        operand_->setParentItem(this);
        connect(operand_, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
        connect(operand_, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
        connect(operand_, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);

        color_ = QColor::fromRgb(175, 122, 109);
    }
    UnaryAST(const QVariant&);
    ~UnaryAST();
    inline Priority getPriority() const final {return Priority::UNARY;}
    inline ExprAST* getOperand() const { return operand_; }
    QString stringify() const final;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;
    QRectF boundingRect() const override;
    void updateChildren() final;

protected:
    ExprAST* operand_;
};

class NotAST final : public UnaryAST
{
public:
    NotAST(ExprAST *operand = nullptr)
        :UnaryAST(operand)
    {
        op_ = QString("!");
    }
    NotAST(const QVariant& v)
        :UnaryAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    QVariant toVariant() const override;

private:
    NotAST(const NotAST&) = delete;
    NotAST& operator=(const NotAST) = delete;
};

class BinaryAST : public OperatorAST
{
public:
    BinaryAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :left_(left!=nullptr?left:new PlaceholderAST())
        ,right_(right!=nullptr?right:new PlaceholderAST())
    {
        left_->setParentItem(this);
        connect(left_, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
        connect(left_, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
        connect(left_, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);

        right_->setParentItem(this);
        connect(right_, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
        connect(right_, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
        connect(right_, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);

        color_= QColor::fromRgb(175, 122, 109);
    }
    BinaryAST(const QVariant&);

    ~BinaryAST();

    virtual ExprAST* getLeft() const {return left_;}
    virtual ExprAST* getRight() const {return right_;}
    QString stringify() const final;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;
    QRectF boundingRect() const override;
    void updateChildren() final;

protected:
    ExprAST *left_, *right_;
};

class MulAST final : public BinaryAST
{
public:
    MulAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryAST(left,right)
    {
        op_ = QString("*");
    }
    MulAST(const QVariant& v)
        :BinaryAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::ARITHMETIC_HIGHER;}
    QVariant toVariant() const override;

private:
    MulAST(const MulAST&) = delete;
    MulAST& operator=(const MulAST) = delete;
};

class DivAST final : public BinaryAST
{
public:
    DivAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryAST(left,right)
    {
        op_ = QString("/");
    }
    DivAST(const QVariant& v)
        :BinaryAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::ARITHMETIC_HIGHER;}
    QVariant toVariant() const override;

private:
    DivAST(const DivAST&) = delete;
    DivAST& operator=(const DivAST) = delete;
};

class AddAST final : public BinaryAST
{
public:
    AddAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryAST(left,right)
    {
        op_ = QString("+");
    }
    AddAST(const QVariant& v)
        :BinaryAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::ARITHMETIC_LOWER;}
    QVariant toVariant() const override;

private:
    AddAST(const AddAST&) = delete;
    AddAST& operator=(const AddAST) = delete;
};

class SubAST final : public BinaryAST
{
public:
    SubAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryAST(left,right)
    {
        op_ = QString("-");
    }
    SubAST(const QVariant& v)
        :BinaryAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::ARITHMETIC_LOWER;}
    QVariant toVariant() const override;

private:
    SubAST(const SubAST&) = delete;
    SubAST& operator=(const SubAST) = delete;
};

class LtAST final : public BinaryAST
{
public:
    LtAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryAST(left,right)
    {
        op_ = QString("<");
    }
    LtAST(const QVariant& v)
        :BinaryAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::RELATIONAL_HIGHER;}
    QVariant toVariant() const override;

private:
    LtAST(const LtAST&) = delete;
    LtAST& operator=(const LtAST) = delete;
};

class LeqAST final : public BinaryAST
{
public:
    LeqAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryAST(left,right)
    {
        op_ = QString("<=");
    }
    LeqAST(const QVariant& v)
        :BinaryAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::RELATIONAL_HIGHER;}
    QVariant toVariant() const override;

private:
    LeqAST(const LeqAST&) = delete;
    LeqAST& operator=(const LeqAST) = delete;
};

class GtAST final : public BinaryAST
{
public:
    GtAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryAST(left,right)
    {
        op_ = QString(">");
    }
    GtAST(const QVariant& v)
        :BinaryAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::RELATIONAL_HIGHER;}
    QVariant toVariant() const override;

private:
    GtAST(const GtAST&) = delete;
    GtAST& operator=(const GtAST) = delete;
};

class GeqAST final : public BinaryAST
{
public:
    GeqAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryAST(left,right)
    {
        op_ = QString(">=");
    }
    GeqAST(const QVariant& v)
        :BinaryAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::RELATIONAL_HIGHER;}
    QVariant toVariant() const override;

private:
    GeqAST(const GeqAST&) = delete;
    GeqAST& operator=(const GeqAST) = delete;
};

class EqAST final : public BinaryAST
{
public:
    EqAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryAST(left,right)
    {
        op_ = QString("==");
    }
    EqAST(const QVariant& v)
        :BinaryAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::RELATIONAL_LOWER;}
    QVariant toVariant() const override;

private:
    EqAST(const EqAST&) = delete;
    EqAST& operator=(const EqAST) = delete;
};

class NeqAST final : public BinaryAST
{
public:
    NeqAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryAST(left,right)
    {
        op_ = QString("!=");
    }
    NeqAST(const QVariant& v)
        :BinaryAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::RELATIONAL_LOWER;}
    QVariant toVariant() const override;

private:
    NeqAST(const NeqAST&) = delete;
    NeqAST& operator=(const NeqAST) = delete;
};

class AndAST final : public BinaryAST
{
public:
    AndAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryAST(left,right)
    {
        op_ = QString("&&");
    }
    AndAST(const QVariant& v)
        :BinaryAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::LOGICAL;}
    QVariant toVariant() const override;

private:
    AndAST(const AndAST&) = delete;
    AndAST& operator=(const AndAST) = delete;
};

class OrAST final : public BinaryAST
{
public:
    OrAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryAST(left,right)
    {
        op_ = QString("||");
    }
    OrAST(const QVariant& v)
        :BinaryAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::LOGICAL;}
    QVariant toVariant() const override;

private:
    OrAST(const OrAST&) = delete;
    OrAST& operator=(const OrAST) = delete;
};

#endif // AST_H

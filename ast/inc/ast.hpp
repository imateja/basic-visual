#ifndef AST_H
#define AST_H
#include <QString>
#include <QVector>
#include <QColor>
#include <QPainter>
#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <serializable.hpp>

class PlaceholderExprAST;
class ValueExprAST;
class VariableExprAST;

class NotExprAST;
class MulExprAST;
class DivExprAST;
class AddExprAST;
class SubExprAST;
class LtExprAST;
class LeqExprAST;
class GtExprAST;
class GeqExprAST;
class EqExprAST;
class NeqExprAST;
class AndExprAST;
class OrExprAST;

class StartExprAST;
class EndExprAST;
class AssignExprAST;
class BlockExprAST;
class IfExprAST;
class WhileExprAST;
class PrintAST;
class InputAST;
class FunctionExprAST;

class VisitorAST
{
public:
    virtual void VisitPlaceholderExprAST(PlaceholderExprAST&) = 0;
    virtual void VisitValueExprAST(ValueExprAST&) = 0;
    virtual void VisitVariableExprAST(VariableExprAST&) = 0;

    virtual void VisitNotExprAST(NotExprAST&) = 0;
    virtual void VisitMulExprAST(MulExprAST&) = 0;
    virtual void VisitDivExprAST(DivExprAST&) = 0;
    virtual void VisitAddExprAST(AddExprAST&) = 0;
    virtual void VisitSubExprAST(SubExprAST&) = 0;
    virtual void VisitLtExprAST(LtExprAST&) = 0;
    virtual void VisitLeqExprAST(LeqExprAST&) = 0;
    virtual void VisitGtExprAST(GtExprAST&) = 0;
    virtual void VisitGeqExprAST(GeqExprAST&) = 0;
    virtual void VisitEqExprAST(EqExprAST&) = 0;
    virtual void VisitNeqExprAST(NeqExprAST&) = 0;
    virtual void VisitAndExprAST(AndExprAST&) = 0;
    virtual void VisitOrExprAST(OrExprAST&) = 0;

    virtual void VisitAssignExprAST(AssignExprAST&) = 0;
    virtual void VisitBlockExprAST(BlockExprAST&) = 0;
    virtual void VisitIfExprAST(IfExprAST&) = 0;
    virtual void VisitWhileExprAST(WhileExprAST&) = 0;
    virtual void VisitPrintAST(PrintAST&) = 0;
    virtual void VisitInputAST(InputAST&) = 0;
    virtual void VisitFunctionExprAST(FunctionExprAST&) = 0;
    virtual void VisitStartExprAST(StartExprAST&) = 0;


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
    inline float getHeight() const { return boundingRect().height();}
    //virtual ExprAST* copy() const = 0;

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

class PlaceholderExprAST final : public ExprAST
{
public:
    PlaceholderExprAST(){
        expr_ = nullptr;
        color_= QColor::fromRgb(128,0,0);
    }
    PlaceholderExprAST(const QVariant& v);
    void setExpr(ExprAST* expr){
        expr_ = expr;
        expr_->setParentItem(this);
        connect(expr_, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
        connect(expr_, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
        connect(expr_, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);
    }
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

    ExprAST* expr_;
};

class ValueExprAST final : public ExprAST
{
public:
    ValueExprAST(double value)
        :value_(value)
    {
        color_= QColor::fromRgb(128,0,128);
    }
    ValueExprAST(const QVariant& v);

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::INSTRUCTION;}
    inline double getValue() {return value_;}
    QString stringify() const final;
    QVariant toVariant() const override;
    //ExprAST* copy() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
private:
    double value_;
};

class VariableExprAST final : public ExprAST
{
public:
    VariableExprAST(QString name)
        :name_(name)
    {
        color_= QColor::fromRgb(128,0,128);
    }
    VariableExprAST(const QVariant& v);

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::INSTRUCTION;}
    inline QString getName() {return name_;}
    QString stringify() const final;  //the same as getName
    QVariant toVariant() const override;
    //ExprAST* copy() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
private:
    QString name_;
};

class OperatorExprAST : public ExprAST
{
public:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
protected:
    QRectF opcircle_;
    QPointF center_;
    QString op_;

};

class UnaryExprAST : public OperatorExprAST
{
public:
    UnaryExprAST(ExprAST *operand = nullptr)
        :operand_(operand!=nullptr?operand:new PlaceholderExprAST())
    {
        operand_->setParentItem(this);
        connect(operand_, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
        connect(operand_, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
        connect(operand_, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);

        color_ = QColor::fromRgb(36, 17, 100);
    }
    UnaryExprAST(const QVariant&);

    inline Priority getPriority() const final {return Priority::UNARY;}
    inline ExprAST* getOperand() {return operand_;}
    QString stringify() const final;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;
    QRectF boundingRect() const override;

    ~UnaryExprAST();
    void updateChildren() final;

protected:
    ExprAST* operand_;

};

class NotExprAST final : public UnaryExprAST
{
public:
    NotExprAST(ExprAST *operand = nullptr)
        :UnaryExprAST(operand)
    {
        op_ = QString("-");
    }
    NotExprAST(const QVariant& v)
        :UnaryExprAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    QVariant toVariant() const override;

    //ExprAST* copy() const override;
};

class BinaryExprAST : public OperatorExprAST
{
public:
    BinaryExprAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :left_(left!=nullptr?left:new PlaceholderExprAST())
        ,right_(right!=nullptr?right:new PlaceholderExprAST())
    {
        left_->setParentItem(this);
        connect(left_, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
        connect(left_, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
        connect(left_, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);

        right_->setParentItem(this);
        connect(right_, &ExprAST::selectItem, this, &ExprAST::propagateSelectItem);
        connect(right_, &ExprAST::updateSelection, this, &ExprAST::propagateUpdateSelection);
        connect(right_, &ExprAST::ShouldUpdateScene, this, &ExprAST::propagateShouldUpdateScene);

        color_= QColor::fromRgb(128,0,128);
    }
    BinaryExprAST(const QVariant&);

    ~BinaryExprAST();
    BinaryExprAST(const BinaryExprAST&);
    BinaryExprAST& operator= (const BinaryExprAST&);

    virtual ExprAST* getLeft() {return left_;}
    virtual ExprAST* getRight() {return right_;}
    void setLeft(ExprAST*);
    void setRight(ExprAST*);
    QString stringify() const final;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;
    QRectF boundingRect() const override;
    void updateChildren() final;


protected:
    ExprAST *left_, *right_;
};

class MulExprAST final : public BinaryExprAST
{
public:
    MulExprAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryExprAST(left,right)
    {
        op_ = QString("*");
    }
    MulExprAST(const QVariant& v)
        :BinaryExprAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::ARITHMETIC_HIGHER;}
    QVariant toVariant() const override;
    //ExprAST* copy() const override;
};

class DivExprAST final : public BinaryExprAST
{
public:
    DivExprAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryExprAST(left,right)
    {
        op_ = QString("/");
    }
    DivExprAST(const QVariant& v)
        :BinaryExprAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::ARITHMETIC_HIGHER;}
    QVariant toVariant() const override;
    //ExprAST* copy() const override;
};

class AddExprAST final : public BinaryExprAST
{
public:
    AddExprAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryExprAST(left,right)
    {
        op_ = QString("+");
    }
    AddExprAST(const QVariant& v)
        :BinaryExprAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::ARITHMETIC_LOWER;}
    QVariant toVariant() const override;
    //ExprAST* copy() const override;
};

class SubExprAST final : public BinaryExprAST
{
public:
    SubExprAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryExprAST(left,right)
    {
        op_ = QString("-");
    }
    SubExprAST(const QVariant& v)
        :BinaryExprAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::ARITHMETIC_LOWER;}
    QVariant toVariant() const override;
    //ExprAST* copy() const override;
};

class LtExprAST final : public BinaryExprAST
{
public:
    LtExprAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryExprAST(left,right)
    {
        op_ = QString("<");
    }
    LtExprAST(const QVariant& v)
        :BinaryExprAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::RELATIONAL_HIGHER;}
    QVariant toVariant() const override;
    //ExprAST* copy() const override;
};

class LeqExprAST final : public BinaryExprAST
{
public:
    LeqExprAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryExprAST(left,right)
    {
        op_ = QString("<=");
    }
    LeqExprAST(const QVariant& v)
        :BinaryExprAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::RELATIONAL_HIGHER;}
    QVariant toVariant() const override;
    //ExprAST* copy() const override;
};

class GtExprAST final : public BinaryExprAST
{
public:
    GtExprAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryExprAST(left,right)
    {
        op_ = QString(">");
    }
    GtExprAST(const QVariant& v)
        :BinaryExprAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::RELATIONAL_HIGHER;}
    QVariant toVariant() const override;
    //ExprAST* copy() const override;
};

class GeqExprAST final : public BinaryExprAST
{
public:
    GeqExprAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryExprAST(left,right)
    {
        op_ = QString(">=");
    }
    GeqExprAST(const QVariant& v)
        :BinaryExprAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::RELATIONAL_HIGHER;}
    QVariant toVariant() const override;
    //ExprAST* copy() const override;
};

class EqExprAST final : public BinaryExprAST
{
public:
    EqExprAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryExprAST(left,right)
    {
        op_ = QString("==");
    }
    EqExprAST(const QVariant& v)
        :BinaryExprAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::RELATIONAL_LOWER;}
    QVariant toVariant() const override;
    //ExprAST* copy() const override;
};

class NeqExprAST final : public BinaryExprAST
{
public:
    NeqExprAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryExprAST(left,right)
    {
        op_ = QString("!=");
    }
    NeqExprAST(const QVariant& v)
        :BinaryExprAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::RELATIONAL_LOWER;}
    QVariant toVariant() const override;
    //ExprAST* copy() const override;
};

class AndExprAST final : public BinaryExprAST
{
public:
    AndExprAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryExprAST(left,right)
    {
        op_ = QString("&&");
    }
    AndExprAST(const QVariant& v)
        :BinaryExprAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::LOGICAL;}
    QVariant toVariant() const override;
    //ExprAST* copy() const override;
};

class OrExprAST final : public BinaryExprAST
{
public:
    OrExprAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryExprAST(left,right)
    {
        op_ = QString("||");
    }
    OrExprAST(const QVariant& v)
        :BinaryExprAST(v)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() const final {return Priority::LOGICAL;}
    QVariant toVariant() const override;
    //ExprAST* copy() const override;
};

#endif // AST_H

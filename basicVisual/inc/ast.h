#ifndef AST_H
#define AST_H
#include <QString>
#include <QVector>
#include <QColor>
#include <QPainter>
#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>

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
    virtual void VisitFunctionExprAST(FunctionExprAST&) = 0;
    virtual void VisitStartExprAST(StartExprAST&) = 0;
    virtual void VisitEndExprAST(EndExprAST&) = 0;

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

class ExprAST : public QGraphicsObject
{
    Q_OBJECT
public:
    ExprAST(QGraphicsItem* parent = nullptr)
        :QGraphicsObject(parent)
    {
        setFlags(GraphicsItemFlag::ItemIsSelectable);
    }
    virtual ~ExprAST(){}

    virtual void AcceptVisit(VisitorAST&) = 0;
    virtual Priority getPriority() = 0;
    virtual QString stringify() = 0;
    inline float getWidth() const { return w; }
    inline float getHeight() const { return h; }
    //virtual ExprAST* copy() const = 0;

    const QColor color_;
    const QString instructionName_;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QRectF boundingRect() const final;

signals:
    void selectItem(ExprAST* item);
    void updateSelection();
    void ShouldUpdateScene();

public slots:
    void propagateSelectItem(ExprAST* item);
    void propagateUpdateSelection();
    void propagateShouldUpdateScene();

protected:
    float w=150.0f;
    float h=80.0f;

signals:
    void Moved();
    void signalSelected();

};

class PlaceholderExprAST final : public ExprAST
{
public:
    PlaceholderExprAST(){}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::INSTRUCTION;}
    QString stringify() final;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class ValueExprAST final : public ExprAST
{
public:
    ValueExprAST(double value)
        :value_(value)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::INSTRUCTION;}
    inline double getValue() {return value_;}
    QString stringify() final;
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

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
    inline Priority getPriority() final {return Priority::INSTRUCTION;}
    inline QString getName() {return name_;}
    QString stringify() final;  //the same as getName
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QString name_;
};

class NotExprAST final : public ExprAST
{
public:
    NotExprAST(ExprAST *operand = nullptr)
        :operand_(operand!=nullptr?operand:new PlaceholderExprAST())
    {}
    ~NotExprAST();

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::UNARY;}
    inline ExprAST* getOperand() {return operand_;}
    QString stringify() final;
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    ExprAST* operand_;
};

class BinaryExprAST : public ExprAST
{
public:
    BinaryExprAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :left_(left!=nullptr?left:new PlaceholderExprAST())
        ,right_(right!=nullptr?right:new PlaceholderExprAST())
    {}
    ~BinaryExprAST();
    BinaryExprAST(const BinaryExprAST&);
    BinaryExprAST& operator= (const BinaryExprAST&);

    virtual ExprAST* getLeft() {return left_;}
    virtual ExprAST* getRight() {return right_;}
    void setLeft(ExprAST*);
    void setRight(ExprAST*);
    QString stringify() final;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;

protected:
    ExprAST *left_, *right_;
    QString op_;
};

class MulExprAST final : public BinaryExprAST
{
public:
    MulExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {
        op_ = QString("*");
    }

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::ARITHMETIC_HIGHER;}
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

class DivExprAST final : public BinaryExprAST
{
public:
    DivExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {
        op_ = QString("/");
    }

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::ARITHMETIC_HIGHER;}
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class AddExprAST final : public BinaryExprAST
{
public:
    AddExprAST(ExprAST *left = nullptr, ExprAST *right = nullptr)
        :BinaryExprAST(left,right)
    {
        op_ = QString("+");
    }

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::ARITHMETIC_LOWER;}
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class SubExprAST final : public BinaryExprAST
{
public:
    SubExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {
        op_ = QString("-");
    }

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::ARITHMETIC_LOWER;}
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class LtExprAST final : public BinaryExprAST
{
public:
    LtExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {
        op_ = QString("<");
    }

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::RELATIONAL_HIGHER;}
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class LeqExprAST final : public BinaryExprAST
{
public:
    LeqExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {
        op_ = QString("<=");
    }

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::RELATIONAL_HIGHER;}
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class GtExprAST final : public BinaryExprAST
{
public:
    GtExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {
        op_ = QString(">");
    }

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::RELATIONAL_HIGHER;}
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class GeqExprAST final : public BinaryExprAST
{
public:
    GeqExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {
        op_ = QString(">=");
    }

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::RELATIONAL_HIGHER;}
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class EqExprAST final : public BinaryExprAST
{
public:
    EqExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {
        op_ = QString("==");
    }

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::RELATIONAL_LOWER;}
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class NeqExprAST final : public BinaryExprAST
{
public:
    NeqExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {
        op_ = QString("!=");
    }

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::RELATIONAL_LOWER;}
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class AndExprAST final : public BinaryExprAST
{
public:
    AndExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {
        op_ = QString("&&");
    }

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::LOGICAL;}
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class OrExprAST final : public BinaryExprAST
{
public:
    OrExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {
        op_ = QString("||");
    }

    void AcceptVisit(VisitorAST&) override;
    inline Priority getPriority() final {return Priority::LOGICAL;}
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // AST_H

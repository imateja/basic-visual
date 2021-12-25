#ifndef AST_H
#define AST_H
#include <QString>
#include <QVector>
#include <QColor>
#include <QPainter>
#include <QGraphicsObject>

class PlaceholderExprAST;//0
class ValueExprAST;//0
class VariableExprAST;//0

class NotExprAST;//1
class MulExprAST;//2
class DivExprAST;//2
class AddExprAST;//3
class SubExprAST;//3
class LtExprAST;//4
class LeqExprAST;//4
class GtExprAST;//4
class GeqExprAST;//4
class EqExprAST;//5
class NeqExprAST;//5
class AndExprAST;//6
class OrExprAST;//6

class StartExprAST;//0
class EndExprAST;//0
class AssignExprAST;//0
class BlockExprAST;//0
class IfExprAST;//0
class WhileExprAST;//0
class FunctionExprAST;//0

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
    virtual unsigned getPriority() = 0;
    virtual QString stringify() = 0;
    inline float getWidth() const { return w; }
    inline float getHeight() const { return h; }
    //virtual ExprAST* copy() const = 0;

    const QColor color_;
    const QString instructionName_;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override ;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {}
    QRectF boundingRect() const final;

protected:
    float w=150.0f;
    float h=80.0f;
signals:
    void Moved();
    void signalSelected();
    void ShouldUpdateScene();

};

class PlaceholderExprAST final : public ExprAST
{
public:
    PlaceholderExprAST(){}

    void AcceptVisit(VisitorAST&) override;
    inline unsigned getPriority() final {return 0u;}
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
    inline unsigned getPriority() final {return 0u;}
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
    inline unsigned getPriority() final {return 0u;}
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

    void AcceptVisit(VisitorAST&) override;
    inline unsigned getPriority() final {return 1u;}
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

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    ExprAST *left_, *right_;
};

class MulExprAST final : public BinaryExprAST
{
public:
    MulExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline unsigned getPriority() final {return 2u;}
    QString stringify() final;
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class DivExprAST final : public BinaryExprAST
{
public:
    DivExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline unsigned getPriority() final {return 2u;}
    QString stringify() final;
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class AddExprAST final : public BinaryExprAST
{
public:
    AddExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline unsigned getPriority() final {return 3u;}
    QString stringify() final;
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class SubExprAST final : public BinaryExprAST
{
public:
    SubExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline unsigned getPriority() final {return 3u;}
    QString stringify() final;
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class LtExprAST final : public BinaryExprAST
{
public:
    LtExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline unsigned getPriority() final {return 4u;}
    QString stringify() final;
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class LeqExprAST final : public BinaryExprAST
{
public:
    LeqExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline unsigned getPriority() final {return 4u;}
    QString stringify() final;
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class GtExprAST final : public BinaryExprAST
{
public:
    GtExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline unsigned getPriority() final {return 4u;}
    QString stringify() final;
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class GeqExprAST final : public BinaryExprAST
{
public:
    GeqExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline unsigned getPriority() final {return 4u;}
    QString stringify() final;
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class EqExprAST final : public BinaryExprAST
{
public:
    EqExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline unsigned getPriority() final {return 5u;}
    QString stringify() final;
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class NeqExprAST final : public BinaryExprAST
{
public:
    NeqExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline unsigned getPriority() final {return 5u;}
    QString stringify() final;
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class AndExprAST final : public BinaryExprAST
{
public:
    AndExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline unsigned getPriority() final {return 6u;}
    QString stringify() final;
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class OrExprAST final : public BinaryExprAST
{
public:
    OrExprAST(ExprAST *left, ExprAST *right)
        :BinaryExprAST(left,right)
    {}

    void AcceptVisit(VisitorAST&) override;
    inline unsigned getPriority() final {return 6u;}
    QString stringify() final;
    //ExprAST* copy() const override;

    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // AST_H

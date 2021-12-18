#ifndef EXPRTREE_H
#define EXPRTREE_H

#include "ast.h"
#include <QPainter>
#include <QGraphicsObject>
#include <QVector>
#include "state.h"

class InstructionExprAST : public QGraphicsObject, public ExprAST
{
    Q_OBJECT
public:
    InstructionExprAST(QGraphicsItem* parent = nullptr)
        :QGraphicsObject(parent)
    {}
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override ;
    const QColor color_;
    const QString instructionName_;
    inline qint32 getWidth() const { return 200; }
    inline qint32 getHeight() const { return 70; }

    ~InstructionExprAST(){

    }
    InstructionExprAST* next_;
signals:
    void Moved();
    void signalSelected();
};

class StartExprAST : public InstructionExprAST
{
public:
    void AcceptVisit(VisitorAST&) override;
    //ExprAST* copy() const override;
    QRectF boundingRect() const override;
    QColor color_= QColor::fromRgb(128,0,128);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    ~StartExprAST();
};

class EndExprAST : public InstructionExprAST
{
public:
    EndExprAST(QGraphicsItem* parent = nullptr)
        :InstructionExprAST(parent)
    {}
    void AcceptVisit(VisitorAST&) override;
    //ExprAST* copy() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    ~EndExprAST();
};

class BlockExprAST : public InstructionExprAST
{
public:
    BlockExprAST( QGraphicsItem* parent = nullptr)
        : InstructionExprAST(parent)
    {
        body_.push_back(new EndExprAST(this));
    }
    void AcceptVisit(VisitorAST&) override;
    ~BlockExprAST();
    BlockExprAST(const BlockExprAST&);
    //BlockExprAST& operator= (const BlockExprAST&) = default;
    inline QVector<InstructionExprAST*> getBody() {return body_;}
    //ExprAST* copy() const override;
    void insert(InstructionExprAST*, int);
    void push_back(InstructionExprAST*);
    //TEMP
//    unsigned size();
//    InstructionContainer* at(unsigned);
    QRectF boundingRect() const override;
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
    IfExprAST(ExprAST *cond, BlockExprAST *thenblock = nullptr, BlockExprAST *elseblock = nullptr, QGraphicsItem* parent = nullptr)
        :cond_(cond),then_(thenblock!=nullptr?thenblock:new BlockExprAST(this)),else_(elseblock!=nullptr?elseblock:new BlockExprAST(this)), InstructionExprAST(parent)
    {}

    void AcceptVisit(VisitorAST&) override;
    ~IfExprAST();
    IfExprAST(const IfExprAST&);
    IfExprAST& operator= (const IfExprAST&);
    inline ExprAST* getCond() {return cond_;}
    inline BlockExprAST* getThen() {return then_;}
    inline BlockExprAST* getElse() {return else_;}
    //ExprAST* copy() const override;
    QColor color_= QColor::fromRgb(128,128,0);
    QString instructionName_ = QString("If");
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    ExprAST *cond_;
    BlockExprAST *then_;
    BlockExprAST *else_;
};

class WhileExprAST final : public InstructionExprAST
{
public:
    WhileExprAST(ExprAST *cond, BlockExprAST *body = nullptr, QGraphicsItem* parent = nullptr)
        :cond_(cond),body_(body!=nullptr?body:new BlockExprAST(this)), InstructionExprAST(parent)
    {}
    void AcceptVisit(VisitorAST&) override;
    ~WhileExprAST();
    WhileExprAST(const WhileExprAST&);
    WhileExprAST& operator= (const WhileExprAST&);
    inline ExprAST* getCond() {return cond_;}
    inline BlockExprAST* getBody() {return body_;}
    //ExprAST* copy() const override;
    QColor color_= QColor::fromRgb(0,128,128);
    QString instructionName_ = QString("While");
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    ExprAST *cond_;
    BlockExprAST *body_;
};

class AssignExprAST final : public InstructionExprAST
{
public:
    AssignExprAST(QString name, ExprAST *expr,QGraphicsItem* parent = nullptr)
        :name_(name),expr_(expr),InstructionExprAST(parent)
    {}
    void AcceptVisit(VisitorAST&) override;
    ~AssignExprAST();
    AssignExprAST(const AssignExprAST&);
    AssignExprAST& operator= (const AssignExprAST&);
    inline QString getName() {return name_;}
    inline ExprAST* getExpr() {return expr_;}
    //ExprAST* copy() const override;
    QColor color_= QColor::fromRgb(128,0,128);
    QString instructionName_ = QString("Assign");
    QRectF boundingRect() const override;
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
    ~FunctionExprAST();
    FunctionExprAST(const FunctionExprAST&);
    FunctionExprAST& operator= (const FunctionExprAST&);
    inline QString getName() {return name_;}
    inline BlockExprAST* getBody() {return body_;}
    //ExprAST* copy() const override;
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

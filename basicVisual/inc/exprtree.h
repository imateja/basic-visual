#ifndef EXPRTREE_H
#define EXPRTREE_H

#include "ast.h"
#include <QPainter>
#include <QGraphicsObject>

class InstructionExprAST : public QGraphicsObject, public ExprAST
{
    Q_OBJECT
public:
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
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    ~StartExprAST();
};

class BlockExprAST : public ExprAST
{
public:
    BlockExprAST(InstructionExprAST* body)
        :body_(body)
    {}
    BlockExprAST()
        :body_(nullptr)
    {}
    void AcceptVisit(VisitorAST&) override;
    ~BlockExprAST();
    BlockExprAST(const BlockExprAST&);
    BlockExprAST& operator= (const BlockExprAST&) = default;
    inline InstructionExprAST* getBody() {return body_;}
    //ExprAST* copy() const override;
//    void insert(InstructionContainer*, int);
//    void push_back(InstructionContainer*);
    //TEMP
//    unsigned size();
//    InstructionContainer* at(unsigned);
    InstructionExprAST* body_;
};



class EndExprAST : public InstructionExprAST
{
public:
    EndExprAST(InstructionExprAST* start)
        :start_(start)
    {}
    void AcceptVisit(VisitorAST&) override;
    //ExprAST* copy() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    InstructionExprAST* start_;
    ~EndExprAST();
};

class ThenElseExprAST: public InstructionExprAST
{
public:
    ThenElseExprAST(const QString name, BlockExprAST* block)
        :name_(name), block_(block)
    {}
    ThenElseExprAST(const QString name)
        :name_(name), block_(new BlockExprAST())
    {}
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    inline qint32 getWidth() const { return 100; }
    inline qint32 getHeight() const { return 70; }
    void AcceptVisit(VisitorAST&) override;
    BlockExprAST* block_;
private:

    QString name_;

};

class IfExprAST final : public InstructionExprAST
{
public:
    IfExprAST(ExprAST *cond, ThenElseExprAST *then, ThenElseExprAST *Else)
        :cond_(cond),then_(then),else_(Else)
    {}
    IfExprAST(ExprAST *cond)
        :IfExprAST(cond,new ThenElseExprAST("then") ,new ThenElseExprAST("else"))
    {
        then_->block_->body_ =  new EndExprAST(this);
        else_->block_->body_ =  new EndExprAST(this);
    }
    void AcceptVisit(VisitorAST&) override;
    ~IfExprAST();
    IfExprAST(const IfExprAST&);
    IfExprAST& operator= (const IfExprAST&);
    inline ExprAST* getCond() {return cond_;}
    inline ThenElseExprAST* getThen() {return then_;}
    inline ThenElseExprAST* getElse() {return else_;}
    //ExprAST* copy() const override;
    QColor color_= QColor::fromRgb(128,128,0);
    QString instructionName_ = QString("If");
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    ExprAST *cond_;
    ThenElseExprAST *then_;
    ThenElseExprAST *else_;
};

class WhileExprAST final : public InstructionExprAST
{
public:
    WhileExprAST(ExprAST *cond, BlockExprAST *body)
        :cond_(cond),body_(body)
    {}
    WhileExprAST(ExprAST *cond)
        :WhileExprAST(cond, new BlockExprAST())
    {
        body_->body_ = new EndExprAST(this);
    }
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
    AssignExprAST(QString name, ExprAST *expr)
        :name_(name),expr_(expr)
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

class ExprTree final
{
public:
    static ExprTree& Tree(){
        static ExprTree function {};
        return function;
    }
    ~ExprTree();
    InstructionExprAST* selected;
private:
    ExprTree(){
        program_ = new BlockExprAST();
        program_->body_ = new StartExprAST();
        selected = program_->body_;
    }
    BlockExprAST* program_;
    ExprTree(const ExprTree&) = delete;
    ExprTree& operator=(const ExprTree&) = delete;
};

#endif // EXPRTREE_H

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

class BlockExprAST final : public ExprAST
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

class IfExprAST final : public InstructionExprAST
{
public:
    IfExprAST(ExprAST *cond, BlockExprAST *then, BlockExprAST *Else)
        :cond_(cond),then_(then),else_(Else)
    {}
    IfExprAST(ExprAST *cond)
        :IfExprAST(cond,new BlockExprAST() ,new BlockExprAST())
    {
        then_->body_ =  new EndExprAST(this);
        else_->body_ =  new EndExprAST(this);
    }
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

#ifndef STATE_H
#define STATE_H

#include <QVector>
#include <QHash>
#include <QString>
#include "ast.h"

class State final
{
public:
    static State& Domains(){
        static State state {};
        return state;
    }
    QHash<QString, ValueExprAST*>* getCurrentDomain();
    void createNewDomain();
    void removeCurrentDomain();
    void assignValue(const QString&,ValueExprAST*);
    ValueExprAST* getValue(const QString&);
    ~State();
private:
    State() = default;
    QVector<QHash<QString, ValueExprAST*>*> domains_;
    State(const State&) = delete;
    State& operator=(const State&) = delete;
};

#endif // STATE_H

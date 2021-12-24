#ifndef STATE_H
#define STATE_H

#include <QVector>
#include <QHash>
#include <QString>
#include <QVariant>
#include "ast.h"
#include <QDebug>

class State final
{
public:
    static State& Domains(){
        static State state {};
        return state;
    }
    QHash<QString, QVariant>* getCurrentDomain();
    void createNewDomain();
    void removeCurrentDomain();
    void assignValue(const QString&, QVariant&);
    QVariant getValue(const QString&);
    ~State();
private:
    State() = default;
    QVector<QHash<QString, QVariant>*> domains_;
    State(const State&) = delete;
    State& operator=(const State&) = delete;
};

#endif // STATE_H

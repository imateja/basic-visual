#ifndef STATE_H
#define STATE_H

#include <QVector>
#include <QHash>
#include <QString>
#include <QVariant>
#include <QDebug>
#include <ast.hpp>

class State final
{
public:
    static State& Domains(){
        static State state {};
        return state;
    }
    void createNewDomain();
    void removeCurrentDomain();
    void assignValue(const QString&, QVariant&);
    QHash<QString, QVariant> getCurrentDomain();
    QVariant getValue(const QString&);

private:
    State() = default;
    State(const State&) = delete;
    State& operator=(const State&) = delete;

    QVector<QHash<QString, QVariant>> domains_;
};

#endif // STATE_H

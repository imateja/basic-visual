#include "state.h"


QHash<QString, ValueExprAST*>* State::getCurrentDomain()
{
    return domains_.back();
}

void State::createNewDomain()
{
    domains_.push_back(new QHash<QString, ValueExprAST*>);
}

void State::removeCurrentDomain()
{
    if(domains_.empty()){
        //TODO error handling
        return;
    }

    auto oldDomain = getCurrentDomain();
    domains_.pop_back();
    if(domains_.empty()){
        delete oldDomain;
        return;
    }
    auto currentDomain = getCurrentDomain();

    auto begin = oldDomain->begin();
    auto end = oldDomain->end();
    while(begin != end){
        if(currentDomain->contains(begin.key())){
            currentDomain->key(begin.value());
        }

        begin++;
    }

    delete oldDomain;
}

void State::assignValue(const QString& variable, ValueExprAST* value)
{
    auto currentDomain = getCurrentDomain();
    if(currentDomain->find(variable) != currentDomain->end()){
        delete (*currentDomain)[variable];
    }
    (*currentDomain)[variable] = value;
}

ValueExprAST* State::getValue(const QString& variable){
    auto rit = domains_.rbegin();
    auto end = domains_.rend();
    while(rit != end){
        if((*rit)->find(variable) != (*rit)->end()){
            return (*(*rit))[variable];
        }
        ++rit;
    }
    //TODO error handling
    return nullptr;
}

State::~State()
{
    while(!domains_.empty()){
        auto currentDomain = getCurrentDomain();

        auto begin = currentDomain->begin();
        auto end = currentDomain->end();
        while(begin != end){
            delete begin.value();

            begin++;
        }

        delete currentDomain;
        domains_.pop_back();
    }
}

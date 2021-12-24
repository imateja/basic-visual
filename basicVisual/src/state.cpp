#include "inc/state.h"


QHash<QString, QVariant>* State::getCurrentDomain()
{
    if (domains_.size() == 0) {
        State::Domains().createNewDomain();
    }
    return domains_.back();
}

void State::createNewDomain()
{
    domains_.push_back(new QHash<QString, QVariant>);
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
            (*currentDomain)[begin.key()]=begin.value();
        }

        begin++;
    }

    delete oldDomain;
}

void State::assignValue(const QString& variable,QVariant& value)
{
    auto currentDomain = getCurrentDomain();
    if(currentDomain->find(variable) != currentDomain->end()){
        //TODO error handling
    }
    (*currentDomain)[variable] = value;
}

QVariant State::getValue(const QString& variable){
    auto rit = domains_.rbegin();
    auto end = domains_.rend();
    while(rit != end){
        if((*rit)->find(variable) != (*rit)->end()){
            return (*(*rit))[variable];
        }
        ++rit;
    }
    //TODO error handling
    return {};
}

State::~State()
{
    for(auto domain : domains_){
        delete domain;
    }
}

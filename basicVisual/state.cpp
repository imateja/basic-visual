#include "state.h"


std::unordered_map<std::string, ValueExprAST*>* State::getCurrentDomain()
{
    return domains_.back();
}

void State::createNewDomain()
{
    domains_.push_back(new std::unordered_map<std::string, ValueExprAST*>);
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
    for(auto &element : *oldDomain){
        if(currentDomain->find(element.first) != currentDomain->end()){
            (*currentDomain)[element.first] = element.second;
        }
    }

    delete oldDomain;
}

void State::assignValue(const std::string& variable, ValueExprAST* value)
{
    auto currentDomain = getCurrentDomain();
    if(currentDomain->find(variable) != currentDomain->end()){
        delete (*currentDomain)[variable];
    }
    (*currentDomain)[variable] = value;
}

ValueExprAST* State::getValue(const std::string& variable){
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
        for(auto &element : *currentDomain){
            delete element.second;
        }
        delete currentDomain;
        domains_.pop_back();
    }
}

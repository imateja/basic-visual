#include "state.h"


std::unordered_map<std::string, ValueExprAST*>* State::getCurrentDomain()
{
    return domains_.top();
}

void State::createNewDomain()
{
    auto newDomain = new std::unordered_map<std::string, ValueExprAST*>;
    if(!domains_.empty()){
        auto currentDomain = getCurrentDomain();
        for(auto &element : *currentDomain){
            (*newDomain)[element.first] = element.second;
        }
    }
    domains_.push(newDomain);
}

void State::removeCurrentDomain()
{
    if(domains_.empty()){
        //TODO error handling
        return;
    }

    auto oldDomain = getCurrentDomain();
    domains_.pop();
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
    auto currentDomain = getCurrentDomain();
    if(currentDomain->find(variable) == currentDomain->end()){
        //TODO error handling
        return nullptr;
    }
    else{
        return (*currentDomain)[variable];
    }
}

State::~State()
{
    while(!domains_.empty()){
        auto currentDomain = getCurrentDomain();
        for(auto &element : *currentDomain){
            delete element.second;
        }
        delete currentDomain;
        domains_.pop();
    }
}

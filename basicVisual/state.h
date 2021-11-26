#ifndef STATE_H
#define STATE_H

#include <vector>
#include <unordered_map>
#include <string>
#include "ast.h"

class State
{
public:
    static State& Domains(){
        static State state {};
        return state;
    }
    std::unordered_map<std::string, ValueExprAST*>* getCurrentDomain();
    void createNewDomain();
    void removeCurrentDomain();
    void assignValue(const std::string&,ValueExprAST*);
    ValueExprAST* getValue(const std::string&);
    ~State();
private:
    State() = default;
    std::vector<std::unordered_map<std::string, ValueExprAST*>*> domains_;
    State(const State&) = delete;
    State& operator=(const State&) = delete;
};

#endif // STATE_H

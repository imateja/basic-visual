#include <state.hpp>

void State::createNewDomain()
{
    domains_.push_back(QHash<QString, QVariant> ());
}

void State::removeCurrentDomain()
{
    if (!domains_.isEmpty()) {
       domains_.pop_back();
    }
}

void State::assignValue(const QString& variable, QVariant value)
{
    for (auto rit = domains_.rbegin(); rit != domains_.rend(); rit++) {
        if ((*rit).find(variable) != (*rit).end()) {
            (*rit)[variable] = value;
            break;
        }
    }

    domains_.back().insert(variable, value);
}

auto State::getCurrentDomain() -> QHash<QString, QVariant>
{
    if (domains_.empty()) {
        State::Domains().createNewDomain();
    }
    return domains_.back();
}

auto State::getValue(const QString& variable) -> QVariant
{
    for (auto rit = domains_.rbegin(); rit != domains_.rend(); rit++) {
        if ((*rit).find(variable) != (*rit).end()) {
            return (*rit)[variable];
        }
    }

    return QString("Variable :: " + variable + " does not exist");
}

void State::clear()
{
    domains_.clear();
}

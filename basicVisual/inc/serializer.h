#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QString>
#include "serializable.h"
#include "ast.h"

class Serializer
{
public:
    Serializer();
    void save(const Serializable& serializable, const QString& filepath);
    void load(ExprAST* serializable, const QString& filepath);
};

#endif // SERIALIZER_H

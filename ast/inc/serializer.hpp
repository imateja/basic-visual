#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QString>
#include <serializable.hpp>
#include <ast.hpp>

class Serializer
{
public:
    Serializer();
    void save(const Serializable& serializable, const QString& filepath);
    void load(ExprAST* serializable, const QString& filepath);
};

#endif // SERIALIZER_H

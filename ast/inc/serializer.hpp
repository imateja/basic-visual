#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QString>
#include <serializable.hpp>
#include <ast.hpp>

class Serializer
{
public:
    Serializer() = default;
    void save(const Serializable& serializable, const QString& filepath);
    QVariant load(const QString& filepath);
};

#endif // SERIALIZER_H

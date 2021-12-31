#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QString>
#include <serializable.hpp>
#include <ast.hpp>

class Serializer
{
public:
    Serializer() = default;
    static void save(const Serializable& serializable, const QString& filepath);
    static QVariant load(const QString& filepath);
};

#endif // SERIALIZER_H

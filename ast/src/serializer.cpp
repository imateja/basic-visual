#include <QJsonDocument>
#include <QFile>
#include <serializer.hpp>
#include <ast.hpp>

void Serializer::save(const Serializable& serializable, const QString& filepath)
{
    QJsonDocument doc = QJsonDocument::fromVariant(serializable.toVariant());
    QFile file(filepath);
    file.open(QFile::WriteOnly);
    file.write(doc.toJson(QJsonDocument::JsonFormat::Indented));
    file.close();
}

QVariant Serializer::load(const QString& filepath)
{
    QFile file(filepath);
    file.open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    return doc.toVariant();
}

#include <QJsonDocument>
#include <QFile>
#include "inc/serializer.h"
#include "inc/ast.h"

Serializer::Serializer()
{

}

void Serializer::save(const Serializable& serializable, const QString& filepath)
{
    QJsonDocument doc = QJsonDocument::fromVariant(serializable.toVariant());
    QFile file(filepath);
    file.open(QFile::WriteOnly);
    file.write(doc.toJson(QJsonDocument::JsonFormat::Indented));
    file.close();
}

void Serializer::load(ExprAST* serializable, const QString& filepath)
{
    QFile file(filepath);
    file.open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    serializable = ExprAST::makeFromVariant(doc.toVariant()); //is this good ???
}

#include <maingraphicsscene.hpp>
#include <exprtree.hpp>

mainGraphicsScene::mainGraphicsScene(QObject *parent)
    :QGraphicsScene(parent), selectedItem_(nullptr)
{}

void mainGraphicsScene::clearItems()
{
    for (auto elem : items()) {
        removeItem(elem);
    }
}

void mainGraphicsScene::setSelectedItem(ExprAST *item)
{
    selectedItem_ = item;
}

void mainGraphicsScene::selectItem()
{
    clearSelection();
    if (selectedItem_ != nullptr) {
        selectedItem_->setSelected(true);
    }
}

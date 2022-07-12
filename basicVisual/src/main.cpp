#include <QApplication>
#include <mainwindow.hpp>

auto main(int argc, char *argv[]) -> int
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

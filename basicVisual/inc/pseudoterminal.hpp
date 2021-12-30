#ifndef PSEUDOTERMINAL_H
#define PSEUDOTERMINAL_H

#include <QDialog>

namespace Ui {
class PseudoTerminal;
}

class PseudoTerminal : public QDialog
{
    Q_OBJECT

public:
    explicit PseudoTerminal(QWidget *parent = nullptr);
    ~PseudoTerminal();

private:
    Ui::PseudoTerminal *ui;
};

#endif // PSEUDOTERMINAL_H

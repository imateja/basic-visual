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

public slots:
    void addLine(QString);
    void input();
    void changeBtnSettings(bool);

signals:
    void killInterpret();
};


#endif // PSEUDOTERMINAL_H

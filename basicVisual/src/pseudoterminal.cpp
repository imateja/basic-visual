#include <pseudoterminal.hpp>
#include "ui_pseudoterminal.h"

PseudoTerminal::PseudoTerminal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PseudoTerminal)
{
    ui->setupUi(this);
}

PseudoTerminal::~PseudoTerminal()
{
    delete ui;
}

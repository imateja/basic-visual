#include <pseudoterminal.hpp>
#include "ui_pseudoterminal.h"
#include <interpret.hpp>

PseudoTerminal::PseudoTerminal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PseudoTerminal)
{
    ui->setupUi(this);
    connect(ui->submitBtn,&QPushButton::clicked,this,&PseudoTerminal::input);
    ui->submitBtn->setEnabled(false);
}

PseudoTerminal::~PseudoTerminal()
{
    delete ui;
}

void PseudoTerminal::addLine(QString txt){
    ui->outputTF->append(txt);
}

void PseudoTerminal::input(){
    QString txt = ui->inputTF->text();
    ui->inputTF->clear();
    Interpret::input = txt;
    Interpret::mutex_.unlock();
}

void PseudoTerminal::changeBtnSettings(bool enabled){
    ui->submitBtn->setEnabled(enabled);
}





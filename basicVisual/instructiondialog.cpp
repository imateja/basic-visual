#include "instructiondialog.h"
#include "ui_instructiondialog.h"
//TODO: Find a way to dinamicly create dialogs for every instruction class
//TODO: Make dialogs pass parametars only able to do that after merge with AST
InstructionDialog::InstructionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InstructionDialog)
{
    ui->setupUi(this);
}

InstructionDialog::~InstructionDialog()
{
    delete ui;
}

void InstructionDialog::on_pushButton_clicked()
{
    condition = ui->condField->text();
    accept();
}


void InstructionDialog::on_pushButton_2_clicked()
{
    reject();
}

const QString &InstructionDialog::getCondition() const
{
    return condition;
}


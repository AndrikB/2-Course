#include "bell.h"
#include "ui_bell.h"

bell::bell(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bell)
{
    ui->setupUi(this);
}

bell::~bell()
{
    delete ui;
}

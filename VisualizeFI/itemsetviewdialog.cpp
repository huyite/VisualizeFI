#include "itemsetviewdialog.h"
#include "ui_itemsetviewdialog.h"


ItemSetViewDialog::ItemSetViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemSetViewDialog)
{
    ui->setupUi(this);
}

ItemSetViewDialog::~ItemSetViewDialog()
{
    delete ui;
}

void ItemSetViewDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

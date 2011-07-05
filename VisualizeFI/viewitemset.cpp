#include "viewitemset.h"
#include "ui_viewitemset.h"

ViewItemSet::ViewItemSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewItemSet)
{
    ui->setupUi(this);
}

ViewItemSet::~ViewItemSet()
{
    delete ui;
}

void ViewItemSet::changeEvent(QEvent *e)
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

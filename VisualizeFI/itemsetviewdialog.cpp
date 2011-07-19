#include "itemsetviewdialog.h"
#include "ui_itemsetviewdialog.h"


ItemSetViewDialog::ItemSetViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemSetViewDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(viewitemset()));
    //QObject::connect(this, SIGNAL(itemsetChange(const QString&)),this, SLOT(updateLabel(const QString&)));

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

void ItemSetViewDialog::viewitemset(){
	QString its=ui->lineEdit->text();
	ItemSet itemset;
	itemset.addItems(its.toStdString(),";");
	itemset.sortItems();
    emit itemsetChange(itemset,this->ui->checkBox->checkState()==Qt::Checked);
}
void ItemSetViewDialog::updateFrItemSet(double fr){
    QVariant temp(fr);
    ui->label->setText(temp.toString());

}

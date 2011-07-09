#ifndef ITEMSETVIEWDIALOG_H
#define ITEMSETVIEWDIALOG_H

#include <QDialog>
#include "ItemSet.h"
namespace Ui {
    class ItemSetViewDialog;
}

class ItemSetViewDialog : public QDialog{
    Q_OBJECT
public:
    ItemSetViewDialog(QWidget *parent = 0);
    ~ItemSetViewDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ItemSetViewDialog *ui;
signals:
    void itemsetChange(const ItemSet &);
public slots:
   void viewitemset();
   // void updateLabel(const QString& its);

};

#endif // ITEMSETVIEWDIALOG_H

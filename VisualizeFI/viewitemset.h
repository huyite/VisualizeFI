#ifndef VIEWITEMSET_H
#define VIEWITEMSET_H

#include <QDialog>

namespace Ui {
    class ViewItemSet;
}

class ViewItemSet : public QDialog {
    Q_OBJECT
public:
    ViewItemSet(QWidget *parent = 0);
    ~ViewItemSet();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ViewItemSet *ui;
};

#endif // VIEWITEMSET_H

/********************************************************************************
** Form generated from reading UI file 'ItemSetViewDialogyJ8613.ui'
**
** Created: Wed Jul 6 18:52:32 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef ITEMSETVIEWDIALOGYJ8613_H
#define ITEMSETVIEWDIALOGYJ8613_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ItemSetViewDialog
{
public:
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 300);
        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(90, 110, 191, 27));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 230, 91, 41));
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(140, 170, 93, 27));

        retranslateUi(Dialog);
        QObject::connect(pushButton, SIGNAL(clicked()), lineEdit, SLOT(copy()));
        QObject::connect(pushButton, SIGNAL(clicked()), label, SLOT(update()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "rtrtretertertretret", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Dialog", "PushButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};


namespace Ui {
    class ItemSetViewDialog: public Ui_ItemSetViewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ITEMSETVIEWDIALOGYJ8613_H


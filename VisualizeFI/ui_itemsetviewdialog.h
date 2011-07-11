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
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;


    void setupUi(QDialog *Dialog)
    {
    	 if (Dialog->objectName().isEmpty())
    	            Dialog->setObjectName(QString::fromUtf8("Dialog"));
    	        Dialog->resize(400, 300);
    	        lineEdit = new QLineEdit(Dialog);
    	        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    	        lineEdit->setGeometry(QRect(120, 100, 191, 27));
    	        label = new QLabel(Dialog);
    	        label->setObjectName(QString::fromUtf8("label"));
    	        label->setGeometry(QRect(160, 220, 91, 41));
    	        pushButton = new QPushButton(Dialog);
    	        pushButton->setObjectName(QString::fromUtf8("pushButton"));
    	        pushButton->setGeometry(QRect(160, 160, 93, 27));
    	        label_2 = new QLabel(Dialog);
    	        label_2->setObjectName(QString::fromUtf8("label_2"));
    	        label_2->setGeometry(QRect(10, 100, 101, 20));
    	        label_3 = new QLabel(Dialog);
    	        label_3->setObjectName(QString::fromUtf8("label_3"));
    	        label_3->setGeometry(QRect(40, 220, 91, 41));
    	        label_4 = new QLabel(Dialog);
    	        label_4->setObjectName(QString::fromUtf8("label_4"));
    	        label_4->setGeometry(QRect(120, 30, 181, 17));

    	        retranslateUi(Dialog);
    	       // QObject::connect(pushButton, SIGNAL(clicked()), lineEdit, SLOT(copy()));
    	        //QObject::connect(pushButton, SIGNAL(clicked()), label, SLOT(update()));

    	        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
            Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
            label->setText(QString());
            pushButton->setText(QApplication::translate("Dialog", "OK", 0, QApplication::UnicodeUTF8));
            label_2->setText(QApplication::translate("Dialog", "Input ItemSet :", 0, QApplication::UnicodeUTF8));
            label_3->setText(QApplication::translate("Dialog", "Frequency:", 0, QApplication::UnicodeUTF8));
            label_4->setText(QApplication::translate("Dialog", "Visualize Frequent ItemSet", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};


namespace Ui {
    class ItemSetViewDialog: public Ui_ItemSetViewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ITEMSETVIEWDIALOGYJ8613_H


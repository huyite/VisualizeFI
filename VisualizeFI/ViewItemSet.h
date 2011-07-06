/*
 * ViewItemSet.h
 *
 *  Created on: Jul 6, 2011
 *      Author: root
 */

#ifndef VIEWITEMSET_H_
#define VIEWITEMSET_H_

#include "itemsetviewdialog.h"
#include <tulip/GlMainView.h>
using namespace tlp;

class ViewItemSet : public GlMainView{

Q_OBJECT;
protected:
     ItemSetViewDialog *itemsetviewdialog;
public:
	ViewItemSet();
	virtual ~ViewItemSet();
	virtual QWidget *construct(QWidget* parent);
	virtual void setData(Graph *graph,DataSet dataSet);
	virtual void getData(Graph **graph,DataSet *dataSet);
    virtual std::list<std::pair<QWidget *,std::string> > getConfigurationWidget();
public slots:
    virtual void draw();
    virtual void refresh();
    virtual void init();
    void setGraph(Graph *graph);
};

#endif /* VIEWITEMSET_H_ */

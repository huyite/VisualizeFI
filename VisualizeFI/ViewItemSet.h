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
#include "ItemSet.h"
using namespace tlp;
using namespace std;
class ViewItemSet : public GlMainView{

Q_OBJECT;

protected:
     ItemSetViewDialog *itemsetviewdialog;
     vector<node> leave;
    //
public:
	ViewItemSet();
	virtual ~ViewItemSet();
	virtual QWidget *construct(QWidget* parent);
	virtual void setData(Graph *graph,DataSet dataSet);
	virtual void getData(Graph **graph,DataSet *dataSet);
    virtual std::list<std::pair<QWidget *,std::string> > getConfigurationWidget();
    void getLeave(const Graph *,vector<node> &);
protected:
    bool checkItemSet(node nodeleaf,vector<node> &nodeitemset,const ItemSet& its);
signals:
    void freqItemSet(double );
public slots:
    virtual void draw();
    virtual void refresh();
    virtual void init();
    void setGraph(Graph *graph);
    void findItemSet(const ItemSet& i);

};

#endif /* VIEWITEMSET_H_ */

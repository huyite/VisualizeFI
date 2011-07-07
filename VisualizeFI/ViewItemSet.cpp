/*
 * ViewItemSet.cpp
 *
 *  Created on: Jul 6, 2011
 *      Author: root
 */

#include "ViewItemSet.h"
#include "itemsetviewdialog.h"
using namespace std;
using namespace tlp;

#include <tulip/GlMainWidget.h>
VIEWPLUGIN(ViewItemSet, "ItemSet view", "Huy Nguyen Van", "06/07/2011", "ItemSet view", "1.0");

ViewItemSet::ViewItemSet():GlMainView() {
	// TODO Auto-generated constructor stub

}

ViewItemSet::~ViewItemSet() {
	// TODO Auto-generated destructor stub
}
QWidget *ViewItemSet::construct(QWidget* parent){
	QWidget *widget=GlMainView::construct(parent);
	itemsetviewdialog=new ItemSetViewDialog();
	QObject::connect(itemsetviewdialog,SIGNAL(itemsetChange()),this,SLOT(findItemSet()));
	return widget;
}
void ViewItemSet::setData(Graph *graph,DataSet dataSet){
	DataSet data;
	if(dataSet.exist("glMainWidgetData"))
	dataSet.get("glMainWidgetData",data);
	getGlMainWidget()->setData(graph,data);

}
void ViewItemSet::getData(Graph **graph, DataSet *dataSet){
	dataSet->set<DataSet>("glMainWidgetData",mainWidget->getData());
	*graph=getGlMainWidget()->getGraph();

}
std::list<std::pair<QWidget *,std::string> > ViewItemSet::getConfigurationWidget() {
  std::list<std::pair<QWidget *,std::string> > widgetList;
  widgetList.push_back(std::pair<QWidget*,std::string>(itemsetviewdialog,"View ItemSet"));
  return widgetList;
}
void ViewItemSet::draw(){
   GlMainView::draw();
}
void ViewItemSet::refresh(){
	GlMainView::refresh();
}
void ViewItemSet::init(){
	GlMainView::refresh();
}
void ViewItemSet::setGraph(Graph *graph){
	mainWidget->setGraph(graph);
	this->draw();
}
void ViewItemSet::findItemSet(){
	Graph *graph=getGlMainWidget()->getGraph();
	Iterator<node> *itNodes = graph->getNodes();
	BooleanProperty *select = graph->getLocalProperty<BooleanProperty>("viewSelection");
	while(itNodes->hasNext()) {
	node n = itNodes->next();
	select->setNodeValue(n,true);
	}

	this->draw();
}

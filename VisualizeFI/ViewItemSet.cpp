/*
 * ViewItemSet.cpp
 *
 *  Created on: Jul 6, 2011
 *      Author: root
 */

#include "ViewItemSet.h"
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
	return widget;
}
void ViewItemSet::setData(Graph *graph,DataSet dataset){
	DataSet data;
	string stringData;
	//We check if glMainWidgetData exist because getData can be call with empty data s
	if(data.exist("data"))
	data.get("data",data);
	if(data.exist("owndata"))
	data.get("owndata",stringData);
	getGlMainWidget()->setData(graph,data);

}
void ViewItemSet::getData(Graph **graph, DataSet *dataSet){
	dataSet->set<string>("myString","toto");
	dataSet->set<string>("owndata","an example of own data");
	*graph=getGlMainWidget()->getGraph();

}
std::list<std::pair<QWidget *,std::string> > ViewItemSet::getConfigurationWidget() {
  std::list<std::pair<QWidget *,std::string> > widgetList;
  return widgetList;
}
void ViewItemSet::draw(){
   GlMainView::draw();
}
void ViewItemSet::refresh(){

}
void ViewItemSet::init(){

}
void ViewItemSet::setGraph(Graph *graph){
	mainWidget->setGraph(graph);
	this->draw();
}

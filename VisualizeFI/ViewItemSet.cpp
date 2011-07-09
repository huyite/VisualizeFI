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

void ViewItemSet::getLeave(const Graph *graph,vector<node> & leave){
	Iterator<node> *itNodes = graph->getNodes();
	while(itNodes->hasNext()) {
		node n = itNodes->next();
        if(graph->outdeg(n)==0)
        	leave.push_back(n);
		}delete itNodes;
}
ViewItemSet::ViewItemSet():GlMainView() {
	// TODO Auto-generated constructor stub
   this->graph=getGlMainWidget()->getGraph();
   getLeave(graph,leave);
}

ViewItemSet::~ViewItemSet() {
	// TODO Auto-generated destructor stub
}
QWidget *ViewItemSet::construct(QWidget* parent){
	QWidget *widget=GlMainView::construct(parent);
	itemsetviewdialog=new ItemSetViewDialog();
	QObject::connect(itemsetviewdialog,SIGNAL(itemsetChange(const ItemSet&)),this,SLOT(findItemSet(const ItemSet&)));
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
	//GlMainView::refresh();
}
void ViewItemSet::setGraph(Graph *graph){
	//mainWidget->setGraph(graph);
	//this->draw();
}
bool checkItemSet(node nodeleaf,vector<node> &itemset,const ItemSet& it){
	StringProperty *name =ViewItemSet::graph->getLocalProperty<StringProperty>("viewLabel");
	string leaf=nam->//;
	Item *itemleaf=new Item(leaf);
	for(int j=0;j<its.numberOfItem();j++){
	    	   if(itemleaf<its.getItem(j))
	               return false;
	    	   if(==)
	    	   else


	    	}
}
void ViewItemSet::findItemSet(const ItemSet &its){
	BooleanProperty *select = graph->getLocalProperty<BooleanProperty>("viewSelection");
	StringProperty *name = graph->getLocalProperty<StringProperty>("viewLabel");
    vector<node> temp;

	graph->holdObservers();
	node cursor;
	vector<node> itemset; //
    for(int i=0;i<this->leave.size();i++){
    	leaf=name->get(leave[i]);
    	cursor=leave[i];


    }
	graph->unholdObservers();
}


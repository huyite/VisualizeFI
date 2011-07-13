/*
 * ViewItemSet.cpp
 *
 *  Created on: Jul 6, 2011
 *      Author: root
 */

#include "ViewItemSet.h"
#include "itemsetviewdialog.h"
#include <tulip/Interactor.h>
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

}

ViewItemSet::~ViewItemSet() {
	// TODO Auto-generated destructor stub
}
QWidget *ViewItemSet::construct(QWidget* parent){
	QWidget *widget=GlMainView::construct(parent);
	itemsetviewdialog=new ItemSetViewDialog();
	QObject::connect(itemsetviewdialog,SIGNAL(itemsetChange(const ItemSet&)),this,SLOT(findItemSet(const ItemSet&)));
	QObject::connect(this,SIGNAL(freqItemSet(double )),itemsetviewdialog,SLOT(updateFrItemSet(double )));
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
bool ViewItemSet::checkItemSet(node nodeleaf,vector<node> &nodeitemset,const ItemSet& its){
	Graph *graph=getGlMainWidget()->getGraph();
	StringProperty *name =graph->getLocalProperty<StringProperty>("viewLabel");
	string leaf=name->getNodeStringValue(nodeleaf);
	Item *itemleaf=new Item(leaf);
	node cursor=nodeleaf;
	for(int j=its.numberOfItem()-1;j>-1;j--){
		      while(!graph->indeg(cursor)==0){
		    	  if(*itemleaf<its.getItem(j))
		    	 	       return false;

		    	  if(*(itemleaf)==its.getItem(j)){
		    		  nodeitemset.push_back(cursor);
		    		  cursor=graph->getInNode(cursor,1);
		    		  leaf=name->getNodeStringValue(cursor);
		    		  itemleaf->setName(leaf);
		    		  break;
		    	  }else{
		    		  cursor=graph->getInNode(cursor,1);
		    		  leaf=name->getNodeStringValue(cursor);
		    		  itemleaf->setName(leaf);
		    	  }
		      }
	}
	if(nodeitemset.size()==its.numberOfItem())
		return true;
	else return false;
}
void ViewItemSet::findItemSet(const ItemSet &its){
	getLeave(getGlMainWidget()->getGraph(),leave);
	Graph *graph=getGlMainWidget()->getGraph();
	BooleanProperty *select = graph->getLocalProperty<BooleanProperty>("viewSelection");
	DoubleProperty *frequent = graph->getLocalProperty<DoubleProperty>("viewFrequent");
    vector<node> temp;
    node n;
    double fr=0.0;
  	graph->holdObservers();
	select->setAllNodeValue(false);
	 fr=0;
	for(int i=0;i<this->leave.size();i++){

		if(checkItemSet(leave[i],temp,its)){
			for(int j=0;j<temp.size();j++)
    	      { n=temp[j];
    	        select->setNodeValue(n,true);
    	      }
			fr=fr+frequent->getNodeValue(leave[i]);
		   }

		  temp.clear();

	}

	emit freqItemSet(fr);
     leave.clear();
	graph->unholdObservers();
}
INTERACTORPLUGINVIEWEXTENSION(ViewItemSetNavigation,"ViewItemSetNavigation","InteractorNavigation","ItemSet view","","","Navigation","1")

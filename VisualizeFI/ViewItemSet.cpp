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
	QObject::connect(itemsetviewdialog,SIGNAL(itemsetChange(const ItemSet&,bool)),this,SLOT(findItemSet(const ItemSet&,bool)));
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
bool ViewItemSet::checkItemSet(node nodeleaf,vector<node> &nodeitemset,vector<edge> &path,const ItemSet& its){
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

	if(nodeitemset.size()>1)
	{	cursor=nodeitemset[0];
		while(cursor!=nodeitemset[nodeitemset.size()-1]){
		path.push_back((graph->getInEdges(cursor))->next());
		cursor=graph->getInNode(cursor,1);
		}
	}
	if(nodeitemset.size()==its.numberOfItem())
		return true;
	else return false;
}
void ViewItemSet::findItemSet(const ItemSet &its,bool reb){
	if(reb)
		this->reBuildTree(its);
	getLeave(getGlMainWidget()->getGraph(),leave);
	Graph *graph=getGlMainWidget()->getGraph();
	BooleanProperty *select = graph->getLocalProperty<BooleanProperty>("viewSelection");
	DoubleProperty *frequent = graph->getLocalProperty<DoubleProperty>("viewFrequent");
    vector<node> temp;
    vector<edge> path;
    double fr=0.0;
  	graph->holdObservers();
	select->setAllNodeValue(false);
	select->setAllEdgeValue(false);
	 fr=0;
	for(int i=0;i<this->leave.size();i++){
    	if(checkItemSet(leave[i],temp,path,its)){
			for(int j=0;j<temp.size();j++)
    	         select->setNodeValue(temp[j],true);

			for(int k=0;k<path.size();k++)
			     select->setEdgeValue(path[k],true);

			fr=fr+frequent->getNodeValue(leave[i]);
		   }

		  temp.clear();
          path.clear();
	}

	emit freqItemSet(fr);
    leave.clear();
	graph->unholdObservers();
}
node ViewItemSet::isNodeSon(const string & name,const node &curNode){
	Graph *graph=getGlMainWidget()->getGraph();
	StringProperty *labelItemSet=graph->getLocalProperty<StringProperty>("viewLabel");
	DoubleProperty *frequentItemSet=graph->getLocalProperty<DoubleProperty>("viewFrequent");
	Iterator<node> *itNodes = graph->getOutNodes(curNode);
	unsigned int id=0;
	node pointer;
	node nodeNull;
	while(itNodes->hasNext())
	{
		pointer= itNodes->next();
		if(strcmp(labelItemSet->getNodeValue(pointer).c_str(),name.c_str())==0)
		{
			delete itNodes;
			return pointer;
		}
	}delete itNodes;

	return nodeNull;
}
void ViewItemSet::reBuildTree(const ItemSet& it){
	Graph *graph=getGlMainWidget()->getGraph();
	graph->unholdObservers();
	//graph->delAllNode();
	//graph->delEdge();
	graph->unholdObservers();
	/*StringProperty *labelItemSet=graph->getLocalProperty<StringProperty>("viewLabel");
	DoubleProperty *frequentItemSet=graph->getLocalProperty<DoubleProperty>("viewFrequent");
	DataSet dataset;
	vector<ItemSet> data;
	ItemSet itemset;
	node nodeNull=graph->addNode();
	node curNode;
	node pointerSon;
	labelItemSet->setNodeValue(nodeNull,"NULL");
	frequentItemSet->setNodeValue(nodeNull,0);
	dataset.get("ItemSet datastructure", data);
	for(int i=0;i<data.size();i++){
		    itemset=data[i];
			int size=itemset.numberOfItem();
			double fr= atof(itemset.getItem(size-1).getName().c_str());
			itemset.removeItem(size);
			if(size!=0){
					curNode=nodeNull;   //cursor node
					for(int i=0;i<size-1;i++)
						if(it.isExitItem(itemset.getItem(i)))
							itemset.getItem(i).setPriority(true);

					itemset.sortItems();
					for(int i=0;i<size-1;i++)
					{
						pointerSon=isNodeSon(itemset.getItem(i).getName(),curNode);
						if(!pointerSon.isValid()){
							node n= node();
							n=graph->addNode();
							labelItemSet->setNodeStringValue(n,itemset.getItem(i).getName());
							frequentItemSet->setNodeValue(n,fr);
							edge e=graph->addEdge(curNode,n);
							curNode=n;

						}else{
							curNode= pointerSon;
							frequentItemSet->setNodeValue(curNode,frequentItemSet->getNodeValue(curNode)+fr);

						}
					}


				}
			itemset.clear();
	}*/
}
INTERACTORPLUGINVIEWEXTENSION(ViewItemSetNavigation,"ViewItemSetNavigation","InteractorNavigation","ItemSet view","","","Navigation","1")

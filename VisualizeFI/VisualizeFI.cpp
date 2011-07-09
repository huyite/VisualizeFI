/*
 * VisualizeFI.cpp
 *
 *  Created on: 22 Jun 2011
 *      Author: huy
 */

#include "VisualizeFI.h"
#include <iostream>
#include <fstream>
#include <tulip/StringProperty.h>
#include <tulip/TulipPlugin.h>
using namespace std;
using namespace tlp;

IMPORTPLUGINOFGROUP(VisualizeFI, "VisualizeFI", "huy Nguyen Van", "25/06/2011", "", "1.0", "File");

namespace{
  const char
    *paramHelp[]={
    HTML_HELP_OPEN()
    HTML_HELP_DEF("type","file name")
    HTML_HELP_BODY()
    "Please chose a CSV file"
    HTML_HELP_CLOSE(),
    HTML_HELP_OPEN()
    HTML_HELP_DEF("type", "StringCollection")
    HTML_HELP_DEF("values", "2 <br> 1")
    HTML_HELP_DEF("default", "2")
    HTML_HELP_BODY()
    "Please select model 1 or 2."
    HTML_HELP_CLOSE(),
    HTML_HELP_OPEN()
    HTML_HELP_DEF("type","separator")
    HTML_HELP_BODY()
    "Please chose a separator"
    HTML_HELP_CLOSE(),
  };
}
VisualizeFI::VisualizeFI(AlgorithmContext context):ImportModule(context) {
  // TODO Auto-generated constructor stub
  addParameter<string>("file::filename",paramHelp[0]);
  addParameter<StringCollection> ("model", paramHelp[1], "2;1");
  addParameter<string>("Separator",paramHelp[2], ";");
}

VisualizeFI::~VisualizeFI() {
  // TODO Auto-generated destructor stub
}

double getDoubleVal(string strConvert) {
  double doubleReturn;
  doubleReturn = atof(strConvert.c_str());
  return(doubleReturn);
}
node VisualizeFI::isNodeSon(const string & name,const node &curNode){
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
void swapitem(string &it1,string &it2){
	string temp;
	temp=it1;
	it1=it2;
	it2=temp;
}
void sortitem(vector<string>& itemset){
	 for(int i=0;i<itemset.size()-1;i++)
		  for(int j=i;j<itemset.size()-1;j++)
			  if(getDoubleVal(itemset[i])>getDoubleVal(itemset[j]))
				  swap(itemset[i],itemset[j]);
}

void VisualizeFI::readFile(const string &file){
  StringProperty *labelItemSet=graph->getLocalProperty<StringProperty>("viewLabel");
  DoubleProperty *frequentItemSet=graph->getLocalProperty<DoubleProperty>("viewFrequent");
  ifstream ifile1(file.c_str(),ifstream::in);
  string line1;
  int nbLines = 0;
  while(getline(ifile1,line1)){
    ++nbLines;
  }
  stringstream s;
  s << nbLines;
  string msg = "Parsing itemset number ";
  string endmsg = " of "+ s.str() + " itemsets";
  ifstream ifile(file.c_str(),ifstream::in);
  string line;
  vector<string> buf;

  node nodeNull=graph->addNode();
  node curNode;
  node pointerSon;
  labelItemSet->setNodeValue(nodeNull,"NULL");
  frequentItemSet->setNodeValue(nodeNull,0);
  int curLineNb = 0;
  ItemSet itemset;
  while(getline(ifile,line)){
    ++curLineNb;
    itemset.addItem(line);
    int size=itemset.numberOfItem();
    if(size!=0)
      if(this->model==1)
      {  }//this->FI.buildItemsetM1(buf);
      else
      {
    	         curNode=nodeNull;   //cursor node
    	     	 double fr=getDoubleVal(buf[size-1]);
    	     	 itemset.removeItem(size-1);
    	     	 //sortitem(buf);
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
    buf.clear();
    stringstream s2;
    s2 << curLineNb;
    pluginProgress->setComment(msg+s2.str()+endmsg);
    pluginProgress->progress(curLineNb, nbLines);
  }
}

bool VisualizeFI::import(const std::string &){
  string filename;
  string sep = ";";
  StringCollection model;
  if(dataSet!=0){
    dataSet->get<string>("file::filename",filename);
    dataSet->get<string>("Separator",sep);
    dataSet->get<StringCollection>("model", model);
  }
  this->separator=sep;

  if (model.getCurrentString().compare("1") == 0)
    this->model = 1;
  else
    this->model = 2;
  this->readFile(filename);
  if(this->model==1){
  this->FI.sortItemsets();
  this->buildNodes();
  this->buildEdges();
  }
  return true;
}

void VisualizeFI::buildNodes(){
  pluginProgress->setComment("Adding nodes");
  pluginProgress->progress(0, 100);
  StringProperty *labelItemSet=graph->getLocalProperty<StringProperty>("viewLabel");
  DoubleProperty *frequentItemSet=graph->getLocalProperty<DoubleProperty>("viewFrequent");
  LayoutProperty *layout=graph->getProperty<LayoutProperty>("viewLayout");
  int size=this->FI.getSize();
  this->nodes.reserve(size+1);
  //this node is Null
  this->nodes[size]=graph->addNode();
  labelItemSet->setNodeValue(this->nodes[size],"Null");
  frequentItemSet->setNodeValue(this->nodes[size],-1.0);
  for(int i=0;i<size;i++){
    this->nodes[i]= graph->addNode();
    labelItemSet->setNodeValue(this->nodes[i],this->FI.getItemSet(i)->getName());
    frequentItemSet->setNodeValue(this->nodes[i],this->FI.getItemSet(i)->getFrequency());
    pluginProgress->progress(i, size);
  }
}
bool VisualizeFI::isEdge(int j, int i)
{
   return this->FI.getItemSet(j)->checkSubSet(*(this->FI.getItemSet(i)))&
      (this->FI.getItemSet(j)->numberOfItem()-this->FI.getItemSet(i)->numberOfItem()==1);
}

void VisualizeFI::buildEdges(){
  pluginProgress->setComment("Adding edges");
  int index=0;
  while(this->FI.getItemSet(index)->numberOfItem()==1){
    edge e=graph->addEdge(this->nodes[this->FI.getSize()],this->nodes[index]);
    this->edges.push_back(e);
    index++;
  }
  int maxIter = this->FI.getSize() * (this->FI.getSize()-1) / 2;
  int cpt = 0;
  for(int i=0;i<this->FI.getSize()-1;i++)
    for(int j=i+1;j<this->FI.getSize();j++)
      {
	if(isEdge(j, i)){
	  edge e=graph->addEdge(this->nodes[i],this->nodes[j]);
	  this->edges.push_back(e);
	}
	pluginProgress->progress(cpt, maxIter);
	++cpt;

      }
}

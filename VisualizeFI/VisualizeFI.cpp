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
		// Tree or Map layout
		HTML_HELP_OPEN() \
		HTML_HELP_DEF( "type", "StringCollection" ) \
		HTML_HELP_DEF("values", "Tree <br> Map")
		HTML_HELP_DEF( "default", "tree" ) \
		HTML_HELP_BODY() \
		"This parameter indicated to show by TreeLayOut." \
		HTML_HELP_CLOSE(),


};
}
VisualizeFI::VisualizeFI(AlgorithmContext context):ImportModule(context) {
	// TODO Auto-generated constructor stub
	addParameter<string>("file::filename",paramHelp[0]);
	addParameter<StringCollection> ("model", paramHelp[1], "2;1");
	addParameter<string>("Separator",paramHelp[2], ";");
	addParameter<StringCollection>("Layout",paramHelp[3], "Tree;Map");

}

VisualizeFI::~VisualizeFI() {
	// TODO Auto-generated destructor stub
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

void InitConfigure(char *vars,int n){
	for(int i=0;i<n;i++)
		vars[i]='0';
}
void NextConfigure(char *vars,int n){
	int i=n-1;
	while((i>=0) & (vars[i]=='1')){
		vars[i]='0';
		i--;
	}
	vars[i]='1';
}

bool LastConfigure(char * vars,int n){
	for(int i=0;i<n;i++)
		if(vars[i]=='0') return false;
	return true;
	}

ItemSet createItemset(char* vars,ItemSet arrItem,int frequency){
    ItemSet itemset;
  	for(int i=0;i<arrItem.numberOfItem();i++)
         if(vars[i]=='1')
        	itemset.addItem(arrItem.getItem(i));

  	 itemset.IncrFrequency(frequency);
    return itemset;

 }
bool VisualizeFI::isExitItemSet(ItemSet &itemset ){
   for(int i=0;i<this->itemsets.size();i++)
	   if(itemset.isEqual(this->itemsets[i])){
		   this->itemsets[i].IncrFrequency(itemset.getFrequency());
		   return true;
	   }
	return false;
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

	node nodeNull=graph->addNode();
	node curNode;
	node pointerSon;
	labelItemSet->setNodeValue(nodeNull,"NULL");
	frequentItemSet->setNodeValue(nodeNull,0);
	int curLineNb = 0;
	ItemSet itemset;
	vector<ItemSet> data;
	DataSet dataset;
	while(getline(ifile,line)){
		++curLineNb;
		itemset.addItems(line,";");
		data.push_back(itemset);
		int size=itemset.numberOfItem();
		double fr= atof(itemset.getItem(size-1).getName().c_str());
		itemset.removeItem(size);
		if(size!=0)
			if(this->model==1)
			{

					char* buf=new char[size-1];
				    bool stop=false;
				    InitConfigure(buf,size-1);
				    while(!stop){
				    	 NextConfigure(buf,size-1);
				         ItemSet it=createItemset(buf,itemset,fr);
				         if(!this->isExitItemSet(it))
				       	 this->itemsets.push_back(it);
				         stop=LastConfigure(buf,size-1);
				    }

				   delete[] buf;
			}
			else
			{
				curNode=nodeNull;   //cursor node
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
		stringstream s2;
		s2 << curLineNb;
		pluginProgress->setComment(msg+s2.str()+endmsg);
		pluginProgress->progress(curLineNb, nbLines);
	}
	dataset.set("ItemSet datastructure",data);
}

bool VisualizeFI::import(const std::string &){
	string filename;
	string sep = ";";
	StringCollection model;
	StringCollection implayout;
	if(dataSet!=0){
		dataSet->get<string>("file::filename",filename);
		dataSet->get<string>("Separator",sep);
		dataSet->get<StringCollection>("model", model);
		dataSet->get<StringCollection>("Layout",implayout);
	}
	this->separator=sep;
	if (model.getCurrentString().compare("1") == 0)
		this->model = 1;
	else
		this->model = 2;

	this->readFile(filename);
	if(this->model==1){
		this->orderItemsets();
	    this->buildNodes();
		this->buildEdges();
	}

	  bool resultBool;
	  string erreurMsg;
	  LayoutProperty * layout = graph->getLocalProperty<LayoutProperty>("viewLayout"); // get the viewLayout property of your graph
      SizeProperty * nodeSize = graph->getLocalProperty<SizeProperty>("viewSize"); // same for viewSize
      nodeSize->setAllNodeValue(Size(1,1,1));
      nodeSize->setAllEdgeValue(Size(1,1,1));
	  ColorProperty* color=graph->getLocalProperty<ColorProperty>("viewColor");
      DataSet tmp; // datastructure to store the parameters to send to the plugin
	  if (implayout.getCurrentString().compare("Tree") == 0)
	  {
			  StructDef structDef = LayoutProperty::factory->getPluginParameters("Hierarchical Tree (R-T Extended)");
			  structDef.buildDefaultDataSet(tmp,graph);
		      //tmp.set("node size", nodeSize);
		  	  //tmp.set<float>("layer spacing", 64.);
		  	  //tmp.set<float>("node spacing", 18.);
		  	  //tmp.set("orthogonal", true);
		  	  StringCollection tmpS("vertical;horizontal;");
		  	  tmp.set("orientation", tmpS);

		  	  LayoutProperty tempLayout(graph);
		  	  tempLayout = *layout;
		  	  resultBool = graph->computeProperty<LayoutProperty>("Hierarchical Tree (R-T Extended)", &tempLayout,   //"Squarified Tree Map","Hierarchical Graph"
		  			                              erreurMsg, 0, &tmp); // call to the plugin.
		  	  *layout = tempLayout;
		  	  assert(resultBool);
	  }
	  		else
	  			{
	  			      tmp.set("node size", nodeSize);
	  				  tmp.set("layer spacing", 64);
	  				  tmp.set("node spacing", 18);
	  				  StringCollection tmpS("vertical;horizontal;");
	  				  tmp.set("orientation", tmpS);
	  				  LayoutProperty tempLayout(graph);
	  				  tempLayout = *layout;
	  				  resultBool = graph->computeProperty<LayoutProperty>("Squarified Tree Map", &tempLayout,   //,"Hierarchical Graph"
	  						                              erreurMsg, 0, &tmp); // call to the plugin.
	  				  *layout = tempLayout;
	  				  assert(resultBool);
	  			}

	  DataSet colorMappingDataset;

	  StructDef def = ColorProperty::factory->getPluginParameters("Color Mapping");
	  def.buildDefaultDataSet(colorMappingDataset,graph);
	  colorMappingDataset.set("linear/uniform\nproperty",graph->getLocalProperty<DoubleProperty>("viewFrequent"));
      if(!graph->computeProperty<ColorProperty>("Color Mapping",color,erreurMsg,0,&colorMappingDataset)){
    	std::cerr<<__PRETTY_FUNCTION__<<" "<<__LINE__<<std::endl;
      }

	return resultBool;
}

void swap(ItemSet &it1,ItemSet &it2){
	ItemSet temp;
	temp=it1;
	it1=it2;
	it2=temp;
}
void VisualizeFI::orderItemsets(){
	 for(int i=0;i<this->itemsets.size();i++)
		  for(int j=i;j<this->itemsets.size();j++)
			  if(this->itemsets[i].numberOfItem()>this->itemsets[j].numberOfItem())
				  swap(this->itemsets[i],this->itemsets[j]);
}
void VisualizeFI::buildNodes(){
	pluginProgress->setComment("Adding nodes");
	pluginProgress->progress(0, 100);
	StringProperty *labelItemSet=graph->getLocalProperty<StringProperty>("viewLabel");
	DoubleProperty *frequentItemSet=graph->getLocalProperty<DoubleProperty>("viewFrequent");
	LayoutProperty *layout=graph->getProperty<LayoutProperty>("viewLayout");
	int size=this->itemsets.size();
	this->nodes.reserve(size+1);
	//this node is Null
	this->nodes[size]=graph->addNode();
	labelItemSet->setNodeValue(this->nodes[size],"Null");
	frequentItemSet->setNodeValue(this->nodes[size],-1.0);
	for(int i=0;i<size;i++){
		this->nodes[i]= graph->addNode();
		labelItemSet->setNodeValue(this->nodes[i],this->itemsets[i].getName());
		frequentItemSet->setNodeValue(this->nodes[i],this->itemsets[i].getFrequency());
		pluginProgress->progress(i, size);
	}
}
bool VisualizeFI::isEdge(int j, int i)
{
	return this->itemsets[j].checkSubSet((this->itemsets[i]))&
			(this->itemsets[j].numberOfItem()-this->itemsets[i].numberOfItem()==1);
}

void VisualizeFI::buildEdges(){
	pluginProgress->setComment("Adding edges");
	int index=0;
	while(this->itemsets[index].numberOfItem()==1){
		edge e=graph->addEdge(this->nodes[this->itemsets.size()],this->nodes[index]);
		this->edges.push_back(e);
		index++;
	}
	int maxIter = this->itemsets.size() * (this->itemsets.size()-1) / 2;
	int cpt = 0;
	for(int i=0;i<this->itemsets.size()-1;i++)
		for(int j=i+1;j<this->itemsets.size();j++)
		{
			if(isEdge(j, i)){
				edge e=graph->addEdge(this->nodes[i],this->nodes[j]);
				this->edges.push_back(e);
			}
			pluginProgress->progress(cpt, maxIter);
			++cpt;

		}
}

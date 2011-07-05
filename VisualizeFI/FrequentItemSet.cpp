/*
 * FrequentItemSet.cpp
 *
 *  Created on: 25 Jun 2011
 *      Author: huy
 */

#include "FrequentItemSet.h"
#include <stdlib.h>
FrequentItemSet::FrequentItemSet() {
	// TODO Auto-generated constructor stub

}

FrequentItemSet::~FrequentItemSet() {
	// TODO Auto-generated destructor stub
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

ItemSet addItems(char* vars,vector<string> arrItem,int frequency){
    ItemSet itemset;
  	for(int i=0;i<arrItem.size();i++)
         if(vars[i]=='1'){
        	 Item it(arrItem[i]);
        	 itemset.addItem(it);
        }
  	 itemset.IncrFrequency(frequency);
    return itemset;

 }

double GetDoubleVal(string strConvert) {
  double doubleReturn;
  doubleReturn = atof(strConvert.c_str());
  return(doubleReturn);
}
/////////////////////////////////////////////////////
void FrequentItemSet::buildItemsetM1(const vector<string> &arrItem){
    int size=arrItem.size()-1;
	char* buf=new char[size];
    double frItemSet=GetDoubleVal(arrItem[size]);
    bool stop=false;
    InitConfigure(buf,size);
    while(!stop){
    	 NextConfigure(buf,size);
         ItemSet it=addItems(buf,arrItem,frItemSet);
         if(!this->isExitItemSet(it))
       	 this->addItemset(it);
         stop=LastConfigure(buf,size);
    }

   delete[] buf;
}
void sortItem(vector<string>&arrItem){
	string temp="";
	for(int i=0;i<arrItem.size()-2;i++)
		for(int j=i+1;j<arrItem.size()-1;j++)
			if(strcmp (arrItem[i].c_str(),arrItem[j].c_str())>0){
				temp=arrItem[i];
				arrItem[i]=arrItem[j];
				arrItem[j]=temp;
			}
}


void swap(ItemSet &it1,ItemSet &it2){
	ItemSet temp;
	temp=it1;
	it1=it2;
	it2=temp;
}
// check itemset Exit or not in intemsets
bool FrequentItemSet::isExitItemSet(ItemSet &itemset ){
   for(int i=0;i<this->getSize();i++)
	   if(itemset.isEqual(this->itemsets[i])){
		   this->itemsets[i].IncrFrequency(itemset.getFrequency());
		   return true;
	   }
	return false;
}
void FrequentItemSet::sortItemsets(){
	 for(int i=0;i<this->getSize();i++)
		  for(int j=i;j<this->getSize();j++)
			  if(this->itemsets[i].numberOfItem()>this->itemsets[j].numberOfItem())
				  swap(this->itemsets[i],this->itemsets[j]);
}

void FrequentItemSet::addItemset(ItemSet it){
	this->itemsets.push_back(it);
}
int FrequentItemSet::getSize(){
	return this->itemsets.size();
}
ItemSet* FrequentItemSet::getItemSet(int index){
	return &this->itemsets[index];
}

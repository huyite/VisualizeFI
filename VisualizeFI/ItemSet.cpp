/*
 * ItemSet.cpp
 *
 *  Created on: 22 Jun 2011
 *      Author: huy
 */

#include "ItemSet.h"
#include <stdio.h>

ItemSet::ItemSet() {
	// TODO Auto-generated constructor stub
    this->frequency=0;
}

ItemSet::~ItemSet() {
	// TODO Auto-generated destructor stub
}
void ItemSet::addItem(Item item){
         this->items.push_back(item);
}
void ItemSet::removeItem(int index){
	this->items.erase(items.begin()+index);
}
bool ItemSet::checkSubSet(ItemSet &it){
	for(int i=0;i<it.numberOfItem();i++)
		if(!this->isExitItem(it.getItem(i)))
			return false;
	return true;
}
//////////////////////////////////////////////////
//
bool ItemSet::isEqual(ItemSet &it){
    if(this->numberOfItem()!=it.numberOfItem())
    	return false;
	for(int i=0;i<(it.numberOfItem());i++)
    	if(!this->isExitItem(it.getItem(i)))
    			return false;
	return true;
}
bool ItemSet::isExitItem(Item it){
	const char *st1;
    const char *st2;
	for(int i=0;i<this->numberOfItem();i++){
		st1=it.getName().c_str();
		st2=this->getItem(i).getName().c_str();
		if( strcmp (st1,st2)==0)
					return true;
	}

		return false;
}
Item ItemSet::getItem(int index){
	return items[index];
}
int ItemSet::numberOfItem(){
	return this->items.size();
}
string ItemSet::getName(){
	string s=this->getItem(0).getName();
	for(int i=1;i<this->numberOfItem();i++)
		s+=";"+this->getItem(i).getName();
	return s;
}
double ItemSet::getFrequency(){
	return this->frequency;
}
void ItemSet::IncrFrequency(double fr){
	this->frequency+=fr;
}

void tokenize(const string& str,
	      vector<string>& tokens,
	      const string& delimiters = " ") {
  if (str.length() == 0) return;
  string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  string::size_type pos     = str.find_first_of(delimiters, lastPos);
  while (string::npos != pos || string::npos != lastPos) {
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    string::size_type pos_tmp = str.find_first_of(delimiters, pos+1);
    if(pos_tmp - pos == 1){
      lastPos = pos_tmp;
      pos = pos_tmp;
    }
    else {
      lastPos = str.find_first_not_of(delimiters, pos);
      pos = str.find_first_of(delimiters, lastPos);
    }
  }
}
void ItemSet::addItems(const string& st,const string& delimiters){
	vector<string> itemset;
	tokenize(st,itemset,delimiters);
	this->addItems(itemset);
	}
void ItemSet::addItems(const vector<string> &items){

    for(int i=0;i<items.size();i++){
    	Item item(items[i]);
    	this->addItem(item);
    }
}
void ItemSet::addItems(const vector<Item>& its){
	  for(int i=0;i<its.size();i++){
	    	this->addItem(its[i]);
	    }
}
void swap(ItemSet &it1,ItemSet &it2){
	ItemSet temp;
	temp=it1;
	it1=it2;
	it2=temp;
}
void ItemSet::sortItems(){
    for(int i=0;i<this->items.size()-1;i++)
      for(int j=0;j<this->items.size();i++)
    	if(items[i]>items[j])
    		swap(items[i],items[j]);

}

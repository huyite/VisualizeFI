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
bool ItemSet::removeItem(int index){
	return true;
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


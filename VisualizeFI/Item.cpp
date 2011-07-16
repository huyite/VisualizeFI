/*
 * Item.cpp
 *
 *  Created on: 27 Jun 2011
 *      Author: Nguyen Van Huy
 */

#include "Item.h"
#include <stdlib.h>
#include <string.h>

Item::Item() {
	// TODO Auto-generated constructor stub
    this->name="";
}
Item::Item(string name){//this is itemset
	this->name=name;

}
Item::~Item() {
	// TODO Auto-generated destructor stub
}
 string Item::getName()const{
	return this->name;
}
void Item::setName(string name){
	this->name=name;
}


bool Item::operator > (const Item& it )const{
return strcmp(this->getName().c_str(),it.getName().c_str())>0;

}
bool Item::operator ==(const Item& it)const{
	return strcmp(this->getName().c_str(),it.getName().c_str())==0;

}
bool Item::operator <(const Item& it)const{
	return strcmp(this->getName().c_str(),it.getName().c_str())<0;;
}

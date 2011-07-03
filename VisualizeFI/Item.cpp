/*
 * Item.cpp
 *
 *  Created on: 27 Jun 2011
 *      Author: Nguyen Van Huy
 */

#include "Item.h"

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
string Item::getName(){
	return this->name;
}
void Item::setName(string name){
	this->name=name;
}


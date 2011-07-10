/*
 * Item.cpp
 *
 *  Created on: 27 Jun 2011
 *      Author: Nguyen Van Huy
 */

#include "Item.h"
#include <stdlib.h>

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

double GetDoubleVal(const string& strConvert) {
  double doubleReturn;
  doubleReturn = atof(strConvert.c_str());
  return(doubleReturn);
}
bool Item::operator > (const Item& it )const{
return GetDoubleVal(this->getName())>GetDoubleVal(it.getName());

}
bool Item::operator ==(const Item& it)const{
	return GetDoubleVal(this->getName())==GetDoubleVal(it.getName());

}
bool Item::operator <(const Item& it)const{
	return GetDoubleVal(this->getName())<GetDoubleVal(it.getName());
}

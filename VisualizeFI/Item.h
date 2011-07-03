/*
 * Item.h
 *
 *  Created on: 27 Jun 2011
 *      Author: huy
 */

#ifndef ITEM_H_
#define ITEM_H_
#include <string>
using namespace std;
class Item {
private:
	string name;

public:
	Item();
	Item(string);
	virtual ~Item();
	void setName(string);
	string getName();

};

#endif /* ITEM_H_ */

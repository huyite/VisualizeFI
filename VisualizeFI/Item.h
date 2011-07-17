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
class Item
{
private:
	string name;
	bool priority;  // be use to define the ordering
public:
	Item();
	Item(string);
	virtual ~Item();
	void setName(string);
	string getName() const;
	void setPriority(bool);
	bool operator > (const Item&) const;
	bool operator < (const Item&) const;
	bool operator == (const Item&) const;
};

#endif /* ITEM_H_ */

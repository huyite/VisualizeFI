/*
 * ItemSet.h
 *
 *  Created on: 22 Jun 2011
 *      Author: huy
 */

#ifndef ITEMSET_H_
#define ITEMSET_H_
#include <vector>
#include <string.h>
#include "Item.h"
using namespace std;
class ItemSet {
private:
	vector<Item> items;
	double frequency;
public:
	ItemSet();
	virtual ~ItemSet();
	void addItem(Item);
	bool removeItem(int);
	bool checkSubSet(ItemSet &it);
	bool isEqual(ItemSet &it);
	int numberOfItem();
	Item getItem(int);
    bool isExitItem(Item);
    string getName();
    double getFrequency();
    void IncrFrequency(double);

};

#endif /* ITEMSET_H_ */

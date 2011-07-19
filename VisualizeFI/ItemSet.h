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
#include <iterator>
using namespace std;
class ItemSet {
private:
	vector<Item> items;
	double frequency;
public:
	ItemSet();
	virtual ~ItemSet();
	void addItem(Item);
	void addItems(const vector<Item>&);
	void addItems(const vector<string>&);
	void addItems(const string&,const string&);
	void removeItem(int);
	bool checkSubSet(ItemSet &it);
	bool isEqual(ItemSet &it);
	int numberOfItem()const;
	Item getItem(int) const;
    bool isExitItem(Item)const;
    string getName()const;
    double getFrequency() const;
    void IncrFrequency(double);
    void sortItems();
    void clear();
};

#endif /* ITEMSET_H_ */

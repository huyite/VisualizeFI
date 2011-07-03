/*
 * FrequentItemSet.h
 *
 *  Created on: 25 Jun 2011
 *      Author: huy
 */

#ifndef FREQUENTITEMSET_H_
#define FREQUENTITEMSET_H_
#include "ItemSet.h"
#include "Item.h"
class FrequentItemSet {
private:
    vector<ItemSet> itemsets;
public:
	FrequentItemSet();
	virtual ~FrequentItemSet();
	void buildItemsetM1(const vector<string>&);
	void buildItemsetM2(vector<string>&);
	bool isExitItemSet(ItemSet&);
	void addItemset(ItemSet);
	void sortItemsets();
	int getSize();
	ItemSet* getItemSet(int index);
};

#endif /* FREQUENTITEMSET_H_ */

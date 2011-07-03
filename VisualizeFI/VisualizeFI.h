/*
 * VisualizeFI.h
 *
 *  Created on: 22 Jun 2011
 *      Author: huy
 */

#ifndef VISUALIZEFI_H_
#define VISUALIZEFI_H_


#include <tulip/TulipPlugin.h>
#include <tulip/ImportModule.h>
#include "FrequentItemSet.h"
#include <vector>
using namespace std;
using namespace tlp;

class VisualizeFI: public ImportModule {
private:
      FrequentItemSet FI;
      vector<node> nodes;
      vector<edge> edges;
      string separator;
      int model;
    bool isEdge(int j, int i);
public:
	VisualizeFI(AlgorithmContext);
	virtual ~VisualizeFI();
	void buildNodes();
	void buildEdges();
    virtual bool import(const string &);
    void readFile(const string &file);
    node isNodeSon(const string &,const node &);

};

#endif /* VISUALIZEFI_H_ */

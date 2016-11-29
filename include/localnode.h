#ifndef __LOCALNODE_H_INCLUDED__   // if localnode.h hasn't been included yet...
#define __LOCALNODE_H_INCLUDED__

#include <string>
#include <vector>
#include <ostream>
#include <algorithm>
#include "interval.h"

using namespace std;
using std::vector;

class LocalNode {
  public:
    string seq;
    Interval pos;
    uint32_t id;
    uint32_t nested_level;
    uint32_t covg; // covg by hits
    vector<LocalNode*> outNodes; // representing edges from this node to the nodes in the vector
    LocalNode(string, Interval, uint32_t, uint32_t n=0);
    bool operator == (const LocalNode& y) const;
  friend ostream& operator<< (ostream& out, const LocalNode& n);  
  friend class LocalGraph;
};
#endif

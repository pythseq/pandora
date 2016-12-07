#ifndef __LOCALPRG_H_INCLUDED__   // if localPRG.h hasn't been included yet...
#define __LOCALPRG_H_INCLUDED__

#include <string>
#include <vector>
#include <set>
#include <ostream>
#include "minimizer.h"
#include "interval.h"
#include "localgraph.h"
#include "path.h"
#include "index.h"
#include "minihits.h"

using namespace std;

class LocalPRG {
    uint32_t next_id;
    string buff;
  public:
    uint32_t next_site;

    uint32_t id;
    string name;
    string seq;
    LocalGraph prg;
    vector<Path> kmer_paths;
    //uint32_t max_level; // maximum number of levels of bubbles on bubbles
    //uint32_t num_minis; //number of minimizers in sketch of PRG total
    //set<Minimizer*, pMiniComp> sketch;
    LocalPRG(uint32_t, string, string);
    //~LocalPRG();
    bool isalpha_string(const string&);
    string string_along_path(const Path&);
    vector<Interval> splitBySite(const Interval&);	
    vector<uint32_t> build_graph(const Interval&, const vector<uint32_t>&, uint32_t current_level=0);
    void minimizer_sketch (Index* idx, const uint32_t w, const uint32_t k);
    //void get_covgs(MinimizerHits* minimizer_hits);
    void update_covg_with_hit(MinimizerHit* mh);
    //void update_covg_with_hits(deque<MinimizerHit*>& mhs);
    void update_minimizer_counts_for_nodes(Path& p);
  friend ostream& operator<< (ostream& out, const LocalPRG& data);  
};

#endif

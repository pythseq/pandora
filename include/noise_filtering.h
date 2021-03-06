#ifndef __NOISEFILTERING_H_INCLUDED__   // if noise_filtering.h hasn't been included yet...
#define __NOISEFILTERING_H_INCLUDED__

#include <string>
#include <cstdint>
#include "pangenome/pangraph.h"
#include "de_bruijn/graph.h"

#define assert_msg(x) !(std::cerr << "Assertion failed: " << x << std::endl)

uint16_t node_plus_orientation_to_num(const uint16_t, const bool);

void num_to_node_plus_orientation(uint16_t &, bool &, const uint16_t);

uint16_t rc_num(const uint16_t &);

void hashed_node_ids_to_ids_and_orientations(const deque<uint16_t> &, std::vector<uint16_t> &, std::vector<bool> &);

bool overlap_forwards(const deque<uint16_t> &, const deque<uint16_t> &);

bool overlap_backwards(const deque<uint16_t> &, const deque<uint16_t> &);

deque<uint16_t> rc_hashed_node_ids(const deque<uint16_t> &);

void dbg_node_ids_to_ids_and_orientations(const debruijn::Graph &, const deque<uint32_t> &, std::vector<uint16_t> &,
                                          std::vector<bool> &);

void construct_debruijn_graph(const pangenome::Graph *pg, debruijn::Graph &dbg);

void remove_leaves(pangenome::Graph *, debruijn::Graph &, uint16_t covg_thresh = 1);

void filter_unitigs(pangenome::Graph *, debruijn::Graph &, const uint16_t &);

void detangle_pangraph_with_debruijn_graph(pangenome::Graph *, debruijn::Graph &);

void
clean_pangraph_with_debruijn_graph(pangenome::Graph *, const uint16_t, const uint16_t, const bool illumina = false);

void write_pangraph_gfa(const string &, const pangenome::Graph *);

#endif

#include "gtest/gtest.h"
#include "minihits.h"
#include "minihit.h"
#include "minimizer.h"
#include "minirecord.h"
#include "interval.h"
#include "path.h"
#include <stdint.h>
#include <iostream>

using namespace std;

class MinimizerHitsTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }
  MinimizerHits mh = MinimizerHits();
};

TEST_F(MinimizerHitsTest,addHit){
    Minimizer* m;
    m = new Minimizer("hello", 1,6);
    deque<Interval> d = {Interval(7,8), Interval(10, 14)};
    Path p = Path();
    p.initialize(d);
    MiniRecord mr = MiniRecord(0,p);
    mh.add_hit(1, m, mr, 0);
    mh.add_hit(2, m, mr, 0);

    m = new Minimizer("hello", 0,5);
    mh.add_hit(1, m, mr, 0);

    d = {Interval(6,10), Interval(11, 12)};
    p.initialize(d);
    mr = MiniRecord(0,p);
    mh.add_hit(1, m, mr, 0);

    d = {Interval(6,10), Interval(12, 13)};
    p.initialize(d);
    mr = MiniRecord(0,p);
    mh.add_hit(1, m, mr, 0);

    uint32_t j = 5;
    EXPECT_EQ(j, mh.hits.size());
}

TEST_F(MinimizerHitsTest, pCompCheck) {
    vector<MinimizerHit> expected;

    Minimizer* m;
    m = new Minimizer("hello", 1,6);
    deque<Interval> d = {Interval(7,8), Interval(10, 14)};
    Path p = Path();
    p.initialize(d);
    MiniRecord mr = MiniRecord(0,p);
    mh.add_hit(1, m, mr, 0);
    expected.push_back(MinimizerHit(1, m, mr, 0));
    mh.add_hit(2, m, mr, 0);
    expected.push_back(MinimizerHit(2, m, mr, 0));

    m = new Minimizer("hello", 0,5);
    mh.add_hit(1, m, mr, 0);
    expected.push_back(MinimizerHit(1, m, mr, 0));

    d = {Interval(6,10), Interval(11, 12)};
    p.initialize(d);
    mr = MiniRecord(0,p);
    mh.add_hit(1, m, mr, 0);
    expected.push_back(MinimizerHit(1, m, mr, 0));

    d = {Interval(6,10), Interval(12, 13)};
    p.initialize(d);
    mr = MiniRecord(0,p);
    mh.add_hit(1, m, mr, 0);
    expected.push_back(MinimizerHit(1, m, mr, 0));

    uint32_t j = 0;
    for (set<MinimizerHit*, pComp>::iterator it=mh.hits.begin(); it!=mh.hits.end(); ++it)
    {
        EXPECT_EQ(expected[j], **it);
        j++;
    }
}

TEST_F(MinimizerHitsTest, clusterCompCheck){
    set<set<MinimizerHit*>,clusterComp> clusters_of_hits;
    set<MinimizerHit*> current_cluster;

    vector<MinimizerHit*> expected1, expected2;

    Minimizer* m;
    m = new Minimizer("hello", 1,6);
    deque<Interval> d = {Interval(7,8), Interval(10, 14)};
    Path p = Path();
    p.initialize(d);
    MiniRecord mr = MiniRecord(0,p);
    MinimizerHit* mh;
    mh = new MinimizerHit(1, m, mr, 0);
    current_cluster.insert(mh);
    expected1.push_back(mh);

    mh = new MinimizerHit(2, m, mr, 0);
    current_cluster.insert(mh);
    expected1.push_back(mh);
    clusters_of_hits.insert(current_cluster);

    current_cluster.clear();
    m = new Minimizer("hello", 0,5);
    mh = new MinimizerHit(1, m, mr, 0);
    current_cluster.insert(mh);
    expected2.push_back(mh);

    d = {Interval(6,10), Interval(11, 12)};
    p.initialize(d);
    mr = MiniRecord(0,p);
    mh = new MinimizerHit(1, m, mr, 0);
    current_cluster.insert(mh);
    expected2.push_back(mh);

    d = {Interval(6,10), Interval(12, 13)};
    p.initialize(d);
    mr = MiniRecord(0,p);
    mh = new MinimizerHit(1, m, mr, 0);
    current_cluster.insert(mh);
    expected2.push_back(mh);

    clusters_of_hits.insert(current_cluster);

    // have inserted 2 clusters
    uint32_t j = 2;
    EXPECT_EQ(j, clusters_of_hits.size());
    // expect the cluster of 3 added second to be first
    j=3;
    EXPECT_EQ(j, clusters_of_hits.begin()->size());
    
    // check that this is indeed the cluster we think
    j = 0;
    for (set<MinimizerHit*>::iterator it=clusters_of_hits.begin()->begin(); it!=clusters_of_hits.begin()->end(); ++it)
    {
        EXPECT_EQ(expected2[j], *it);
        j++;
    }
}
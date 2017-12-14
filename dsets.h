#ifndef DISJOINTSETS_H_
#define DISJOINTSETS_H_

#include <vector>

using std::vector;

class DisjointSets {

    public:

        void addelements(int num);

        int find(int elem);

        void setunion(int a, int b);

    // we currently dont want this private
    //private:
    
        vector<int> set;
};

#endif

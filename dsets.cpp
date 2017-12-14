#include "dsets.h"
#include <iostream>

void DisjointSets::addelements(int num){

    for(int i = 0; i < num; i++){

        set.push_back(-1);
    }
}

int DisjointSets::find(int elem){

    //potentially do a out of bounds check here
    //

    if(set[elem] < 0){

        return elem;
    } else {

        return set[elem] = find(set[elem]);
    }
}

void DisjointSets::setunion(int a, int b){


    int aRoot = find(a);
    int bRoot = find(b);

    //if they are already in the same set dont bother doing anything
    if(aRoot == bRoot){
        return;
    }

    int newSize = set[aRoot] + set[bRoot];

    if(set[aRoot] <= set[bRoot]){

        set[bRoot] = aRoot;
        set[aRoot] = newSize;
    } else {

        set[aRoot] = bRoot;
        set[bRoot] = newSize;
    }
}

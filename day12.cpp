#include <iostream>
#include "../IO/io.h"
#include <vector>
#include <string>
#include <map>


// disjoint sets from cs225/mp7

class DisjointSets {

    public:

        void addelements(int num);

        int find(int elem);

        void setunion(int a, int b);

    //private:
    
        vector<int> set;
};

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

/*

For example, suppose you go door-to-door like a travelling salesman and record the following list:

0 <-> 2
1 <-> 1
2 <-> 0, 3, 4
3 <-> 2, 4
4 <-> 2, 3, 6
5 <-> 6
6 <-> 4, 5
In this example, the following programs are in the group that contains program ID 0:

Program 0 by definition.
Program 2, directly connected to program 0.
Program 3 via program 2.
Program 4 via program 2.
Program 5 via programs 6, then 4, then 2.
Program 6 via programs 4, then 2.
Therefore, a total of 6 programs are in this group; all but program 1, which has a pipe that connects it to itself.

How many programs are in the group that contains program ID 0?

*/

void day12(){

    vector<vector<int> > input_matrix;
    int result;
    input_matrix = int_matrix_from_file_with_separator("day12.txt", ' ');

    // here we will use disjoint sets to solve this problem
    DisjointSets ds;
    ds.addelements(input_matrix.size());

    for(int i = 0; i < input_matrix.size(); i++){
        for(int j = 2; j < input_matrix[i].size(); j++){
            ds.setunion(input_matrix[i][0], input_matrix[i][j]);
        }
    }

    result = -ds.set[ds.find(0)];
    answer_int(result);
}



/*

How many groups are there in total?

*/

void day12_bonus(){

    vector<vector<int> > input_matrix;
    int result;
    input_matrix = int_matrix_from_file_with_separator("day12.txt", ' ');

    // here we will use disjoint sets to solve this problem
    DisjointSets ds;
    ds.addelements(input_matrix.size());

    for(int i = 0; i < input_matrix.size(); i++){
        for(int j = 2; j < input_matrix[i].size(); j++){
            ds.setunion(input_matrix[i][0], input_matrix[i][j]);
        }
    }

    for(int i = 0; i < input_matrix.size(); i++) if(ds.set[i] < 0) result++;
    answer_int(result);
}

#include <iostream>
#include "../IO/io.h"
#include <vector>
#include <string>
#include <map>
#include "dsets.h"


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

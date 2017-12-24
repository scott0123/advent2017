#include <iostream>
#include "../IO/io.h"
#include <vector>
#include <string>
#include <map>

int strongest_bridge(vector<vector<int> > &input, map<int, int> m, int last);
tuple<int, int> longest_bridge(vector<vector<int> > &input, map<int, int> m, int last, int length);

/*

Each component has two ports, one on each end. The ports come in all different types, and only matching types can be connected. You take an inventory of the components by their port types (your puzzle input). Each port is identified by the number of pins it uses; more pins mean a stronger connection for your bridge. A 3/7 component, for example, has a type-3 port on one side, and a type-7 port on the other.

Your side of the pit is metallic; a perfect surface to connect a magnetic, zero-pin port. Because of this, the first port you use must be of type 0. It doesn't matter what type of port you end with; your goal is just to make the bridge as strong as possible.

The strength of a bridge is the sum of the port types in each component. For example, if your bridge is made of components 0/3, 3/7, and 7/4, your bridge has a strength of 0+3 + 3+7 + 7+4 = 24.

For example, suppose you had the following components:

0/2
2/2
2/3
3/4
3/5
0/1
10/1
9/10
With them, you could make the following valid bridges:

0/1
0/1--10/1
0/1--10/1--9/10
0/2
0/2--2/3
0/2--2/3--3/4
0/2--2/3--3/5
0/2--2/2
0/2--2/2--2/3
0/2--2/2--2/3--3/4
0/2--2/2--2/3--3/5
(Note how, as shown by 10/1, order of ports within a component doesn't matter. However, you may only use each port on a component once.)

Of these bridges, the strongest one is 0/1--10/1--9/10; it has a strength of 0+1 + 1+10 + 10+9 = 31.

What is the strength of the strongest bridge you can make with the components you have available?

*/

void day24(){

    vector<vector<int> > input;
    int result = 0;
    input = int_matrix_from_file_with_separator("day24.txt", '/');

    // we will store the indices of the components we have already used in a map
    map<int, int> m;

    // recursively search for the largest sum of components (strongest)
    result = strongest_bridge(input, m, 0);

    answer_int(result);
}



/*

The bridge you've built isn't long enough; you can't jump the rest of the way.

In the example above, there are two longest bridges:

0/2--2/2--2/3--3/4
0/2--2/2--2/3--3/5
Of them, the one which uses the 3/5 component is stronger; its strength is 0+2 + 2+2 + 2+3 + 3+5 = 19.

What is the strength of the longest bridge you can make? If you can make multiple bridges of the longest length, pick the strongest one.

*/

void day24_bonus(){

    vector<vector<int> > input;
    int result = 0;
    input = int_matrix_from_file_with_separator("day24.txt", '/');

    // we will store the indices of the components we have already used in a map
    map<int, int> m;

    // recursively search for the longest length of components (longest)
    tuple<int, int> t = longest_bridge(input, m, 0, 0);
    result = get<0>(t);

    answer_int(result);
}



// helper functions
int strongest_bridge(vector<vector<int> > &input, map<int, int> m, int last){

    int strongest = 0;
    for(int i = 0; i < input.size(); i++){
        // skip index if its already included
        if(m.find(i) != m.end()){
            if(m[i] == 1) continue;
        }
        // check if one of the entries match the previous last entry
        if(input[i][0] == last){
            m[i] = 1;
            int curr = input[i][0] + input[i][1];
            curr += strongest_bridge(input, m, input[i][1]);
            m[i] = 0;
            if(curr > strongest) strongest = curr;
        } else if (input[i][1] == last){
            m[i] = 1;
            int curr = input[i][0] + input[i][1];
            curr += strongest_bridge(input, m, input[i][0]);
            m[i] = 0;
            if(curr > strongest) strongest = curr;
        }
    }
    return strongest;
}
// <strength, length>
tuple<int, int> longest_bridge(vector<vector<int> > &input, map<int, int> m, int last, int length){

    int strongest = 0;
    int longest = 0;
    for(int i = 0; i < input.size(); i++){
        // skip index if its already included
        if(m.find(i) != m.end()){
            if(m[i] == 1) continue;
        }
        // check if one of the entries match the previous last entry
        if(input[i][0] == last){
            m[i] = 1;
            tuple<int, int> t = longest_bridge(input, m, input[i][1], length + 1);
            int curr = input[i][0] + input[i][1];
            curr += get<0>(t);
            m[i] = 0;
            if(get<1>(t) > longest){
                longest = get<1>(t);
                strongest = curr;
            } else if (get<1>(t) == longest){
                longest = get<1>(t);
                if(curr > strongest) strongest = curr;
            }
        } else if (input[i][1] == last){
            m[i] = 1;
            tuple<int, int> t = longest_bridge(input, m, input[i][0], length + 1);
            int curr = input[i][0] + input[i][1];
            curr += get<0>(t);
            m[i] = 0;
            if(get<1>(t) > longest){
                longest = get<1>(t);
                strongest = curr;
            } else if (get<1>(t) == longest){
                longest = get<1>(t);
                if(curr > strongest) strongest = curr;
            }
        }
    }
    return make_tuple(strongest, longest + 1);
}

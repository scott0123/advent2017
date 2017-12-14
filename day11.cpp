#include <iostream>
#include "../IO/io.h"
#include <vector>
#include <string>

/*

Crossing the bridge, you've barely reached the other side of the stream when a program comes up to you, clearly in distress. "It's my child process," she says, "he's gotten lost in an infinite grid!"

Fortunately for her, you have plenty of experience with infinite grids.

Unfortunately for you, it's a hex grid.

The hexagons ("hexes") in this grid are aligned such that adjacent hexes can be found to the north, northeast, southeast, south, southwest, and northwest:

  \ n  /
nw +--+ ne
  /    \
-+      +-
  \    /
sw +--+ se
  / s  \
You have the path the child process took. Starting where he started, you need to determine the fewest number of steps required to reach him. (A "step" means to move from the hex you are in to any adjacent hex.)

For example:

    ne,ne,ne is 3 steps away.
    ne,ne,sw,sw is 0 steps away (back where you started).
    ne,ne,s,s is 2 steps away (se,se).
    se,sw,se,sw,sw is 3 steps away (s,s,sw).

*/

void day11(){

    vector<string> input;
    int result = 0;
    input = string_vector_from_file_with_separator("day11.txt", ',');

    int n = 0;
    int se = 0;
    int sw = 0;

    for(int i = 0; i < input.size(); i++){
        if(input[i].compare("n") == 0){
            n++;
        } else if(input[i].compare("se") == 0){
            se++;
        } else if(input[i].compare("sw") == 0){
            sw++;
        } else if(input[i].compare("s") == 0){
            n--;
        } else if(input[i].compare("nw") == 0){
            se--;
        } else if(input[i].compare("ne") == 0){
            sw--;
        }
    }
cout << "n: " << n << ", se: " << se << ", sw: " << sw << endl;

    int pos = 0;
    if(n > 0) pos++;
    if(se > 0) pos++;
    if(sw > 0) pos++;
    while(pos > 1){
        pos = 0;
        n--;
        se--;
        sw--;
        if(n > 0) pos++;
        if(se > 0) pos++;
        if(sw > 0) pos++;
    }
cout << "n: " << n << ", se: " << se << ", sw: " << sw << endl;

    int neg = 0;
    if(n < 0) neg++;
    if(se < 0) neg++;
    if(sw < 0) neg++;
    while(neg > 1){
        neg = 0;
        n++;
        se++;
        sw++;
        if(n < 0) neg++;
        if(se < 0) neg++;
        if(sw < 0) neg++;
    }
cout << "n: " << n << ", se: " << se << ", sw: " << sw << endl;

    int abs_n = n < 0 ? -n : n;
    int abs_se = se < 0 ? -se : se;
    int abs_sw = sw < 0 ? -sw : sw;
    
    result = abs_n + abs_se + abs_sw;

    answer_int(result);
}



/*

How many steps away is the furthest he ever got from his starting position?

 */

void day11_bonus(){

    vector<string> input;
    int result = 0;
    input = string_vector_from_file_with_separator("day11.txt", ',');

    int n = 0;
    int se = 0;
    int sw = 0;

    int max_dist = 0;

    for(int i = 0; i < input.size(); i++){
        if(input[i].compare("n") == 0){
            n++;
        } else if(input[i].compare("se") == 0){
            se++;
        } else if(input[i].compare("sw") == 0){
            sw++;
        } else if(input[i].compare("s") == 0){
            n--;
        } else if(input[i].compare("nw") == 0){
            se--;
        } else if(input[i].compare("ne") == 0){
            sw--;
        }

        int dist = 0;

        int pos = 0;
        if(n > 0) pos++;
        if(se > 0) pos++;
        if(sw > 0) pos++;
        while(pos > 1){
            pos = 0;
            n--;
            se--;
            sw--;
            if(n > 0) pos++;
            if(se > 0) pos++;
            if(sw > 0) pos++;
        }

        int neg = 0;
        if(n < 0) neg++;
        if(se < 0) neg++;
        if(sw < 0) neg++;
        while(neg > 1){
            neg = 0;
            n++;
            se++;
            sw++;
            if(n < 0) neg++;
            if(se < 0) neg++;
            if(sw < 0) neg++;
        }

        int abs_n = n < 0 ? -n : n;
        int abs_se = se < 0 ? -se : se;
        int abs_sw = sw < 0 ? -sw : sw;

        dist = abs_n + abs_se + abs_sw;

        if(dist > max_dist) max_dist = dist;
    }

    result = max_dist;
    answer_int(result);
}

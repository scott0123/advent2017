#include <iostream>
#include "../IO/io.h"
#include <vector>
#include <string>
#include <map>

vector<string> rotate2(vector<string> in);
vector<string> rotate3(vector<string> in);
vector<string> flip2(vector<string> in);
vector<string> flip3(vector<string> in);

/*

The image consists of a two-dimensional square grid of pixels that are either on (#) or off (.). The program always begins with this pattern:

.#.
..#
###
Because the pattern is both 3 pixels wide and 3 pixels tall, it is said to have a size of 3.

Then, the program repeats the following process:

If the size is evenly divisible by 2, break the pixels up into 2x2 squares, and convert each 2x2 square into a 3x3 square by following the corresponding enhancement rule.
Otherwise, the size is evenly divisible by 3; break the pixels up into 3x3 squares, and convert each 3x3 square into a 4x4 square by following the corresponding enhancement rule.
Because each square of pixels is replaced by a larger one, the image gains pixels and so its size increases.

The artist's book of enhancement rules is nearby (your puzzle input); however, it seems to be missing rules. The artist explains that sometimes, one must rotate or flip the input pattern to find a match. (Never rotate or flip the output pattern, though.) Each pattern is written concisely: rows are listed as single units, ordered top-down, and separated by slashes. For example, the following rules correspond to the adjacent patterns:

../.#  =  ..
          .#

                .#.
.#./..#/###  =  ..#
                ###

                        #..#
#..#/..../#..#/.##.  =  ....
                        #..#
                        .##.
When searching for a rule to use, rotate and flip the pattern as necessary. For example, all of the following patterns match the same rule:

.#.   .#.   #..   ###
..#   #..   #.#   ..#
###   ###   ##.   .#.
Suppose the book contained the following two rules:

../.# => ##./#../...
.#./..#/### => #..#/..../..../#..#
As before, the program begins with this pattern:

.#.
..#
###
The size of the grid (3) is not divisible by 2, but it is divisible by 3. It divides evenly into a single square; the square matches the second rule, which produces:

#..#
....
....
#..#
The size of this enhanced grid (4) is evenly divisible by 2, so that rule is used. It divides evenly into four squares:

#.|.#
..|..
--+--
..|..
#.|.#
Each of these squares matches the same rule (../.# => ##./#../...), three of which require some flipping and rotation to line up with the rule. The output for the rule is the same in all four cases:

##.|##.
#..|#..
...|...
---+---
##.|##.
#..|#..
...|...
Finally, the squares are joined into a new grid:

##.##.
#..#..
......
##.##.
#..#..
......
Thus, after 2 iterations, the grid contains 12 pixels that are on.

How many pixels stay on after 5 iterations?

*/

void day21(){

    vector<string> input;
    int result = 0;
    input = string_vector_from_file("day21.txt");

    // this will store the pattern
    vector<string> pattern;
    pattern.push_back(".#.");
    pattern.push_back("..#");
    pattern.push_back("###");

    // this will store the translations
    map<vector<string>, vector<string>> m;
    // populate the translation table
    for(int i = 0; i < input.size(); i++){
        vector<string> from;
        vector<string> to;
        if(input[i].size() == 20){ // from 2x2 to 3x3
            from.push_back(input[i].substr(0, 2));
            from.push_back(input[i].substr(3, 2));
            to.push_back(input[i].substr(9, 3));
            to.push_back(input[i].substr(13, 3));
            to.push_back(input[i].substr(17, 3));
            // add all 8 variations
            for(int j = 0; j < 4; j++){
                if(m.find(from) == m.end()) m[from] = to;
                from = flip2(from);
                if(m.find(from) == m.end()) m[from] = to;
                from = flip2(from);
                from = rotate2(from);
            }
        } else if (input[i].size() == 34){ // from 3x3 to 4x4
            from.push_back(input[i].substr(0, 3));
            from.push_back(input[i].substr(4, 3));
            from.push_back(input[i].substr(8, 3));
            to.push_back(input[i].substr(15, 4));
            to.push_back(input[i].substr(20, 4));
            to.push_back(input[i].substr(25, 4));
            to.push_back(input[i].substr(30, 4));
            for(int j = 0; j < 4; j++){
                if(m.find(from) == m.end()) m[from] = to;
                from = flip3(from);
                if(m.find(from) == m.end()) m[from] = to;
                from = flip3(from);
                from = rotate3(from);
            }
        } else {
        }
    }

    // simulate the iterations
    for(int i = 0; i < 18; i++){

        if((pattern.size() % 2) == 0){
            // if its divisible by 2
            int blocks = pattern.size() / 2;
            vector<string> new_pattern;
            vector<vector<string> > container;
            // loop through the chunks and put the translated chunks into the container
            for(int j = 0; j < blocks; j++){
                for(int k = 0; k < blocks; k++){
                    vector<string> chunk;
                    string s = "";
                    s += pattern[j*2][k*2];
                    s += pattern[j*2][k*2 + 1];
                    chunk.push_back(s);
                    s = "";
                    s += pattern[j*2 + 1][k*2];
                    s += pattern[j*2 + 1][k*2 + 1];
                    chunk.push_back(s);
                    container.push_back(m[chunk]);
                }
            }
            // create the new pattern using values from the container
            for(int j = 0; j < blocks * 3; j++){
                string s = "";
                for(int k = 0; k < blocks * 3; k++){
                    s += container[j/3*blocks + k/3][j%3][k%3];
                }
                new_pattern.push_back(s);
            }
            pattern = new_pattern;
        } else {
            // otherwise it has to be divisible by 3
            int blocks = pattern.size() / 3;
            vector<string> new_pattern;
            vector<vector<string> > container;
            // loop through the chunks and put the translated chunks into the container
            for(int j = 0; j < blocks; j++){
                for(int k = 0; k < blocks; k++){
                    vector<string> chunk;
                    string s = "";
                    s += pattern[j*3][k*3];
                    s += pattern[j*3][k*3 + 1];
                    s += pattern[j*3][k*3 + 2];
                    chunk.push_back(s);
                    s = "";
                    s += pattern[j*3 + 1][k*3];
                    s += pattern[j*3 + 1][k*3 + 1];
                    s += pattern[j*3 + 1][k*3 + 2];
                    chunk.push_back(s);
                    s = "";
                    s += pattern[j*3 + 2][k*3];
                    s += pattern[j*3 + 2][k*3 + 1];
                    s += pattern[j*3 + 2][k*3 + 2];
                    chunk.push_back(s);
                    container.push_back(m[chunk]);
                }
            }
            // create the new pattern using values from the container
            for(int j = 0; j < blocks * 4; j++){
                string s = "";
                for(int k = 0; k < blocks * 4; k++){
                    s += container[j/4*blocks + k/4][j%4][k%4];
                }
                new_pattern.push_back(s);
            }
            pattern = new_pattern;
        }
    }

    // finally compute the answer
    for(int i = 0; i < pattern.size(); i++){
        for(int j = 0; j < pattern[i].size(); j++){
            if(pattern[i][j] == '#') result++;
        }
    }

    answer_int(result);
}



/*

How many pixels stay on after 18 iterations?

*/

void day21_bonus(){
// no point doing this, just change the iteration number in day21() to 18
}

// helper functions
vector<string> rotate2(vector<string> in){

    vector<string> out;
    string s = "";
    s += in[1][0];
    s += in[0][0];
    out.push_back(s);
    s = "";
    s += in[1][1];
    s += in[0][1];
    out.push_back(s);
    return out;
}

vector<string> rotate3(vector<string> in){

    vector<string> out;
    string s = "";
    s += in[2][0];
    s += in[1][0];
    s += in[0][0];
    out.push_back(s);
    s = "";
    s += in[2][1];
    s += in[1][1];
    s += in[0][1];
    out.push_back(s);
    s = "";
    s += in[2][2];
    s += in[1][2];
    s += in[0][2];
    out.push_back(s);
    return out;
}

vector<string> flip2(vector<string> in){

    vector<string> out;
    out.push_back(in[1]);
    out.push_back(in[0]);
    return out;
}

vector<string> flip3(vector<string> in){

    vector<string> out;
    out.push_back(in[2]);
    out.push_back(in[1]);
    out.push_back(in[0]);
    return out;
}

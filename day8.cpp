#include <iostream>
#include "../IO/io.h"
#include <string>
#include <vector>
#include <map>

/*

Each instruction consists of several parts: the register to modify, whether to increase or decrease that register's value, the amount by which to increase or decrease it, and a condition. If the condition fails, skip the instruction without modifying the register. The registers all start at 0. The instructions look like this:

b inc 5 if a > 1
a inc 1 if b < 5
c dec -10 if a >= 1
c inc -20 if c == 10
These instructions would be processed as follows:

    Because a starts at 0, it is not greater than 1, and so b is not modified.
    a is increased by 1 (to 1) because b is less than 5 (it is 0).
    c is decreased by -10 (to 10) because a is now greater than or equal to 1 (it is 1).
    c is increased by -20 (to -10) because c is equal to 10.
    After this process, the largest value in any register is 1.

You might also encounter <= (less than or equal to) or != (not equal to). However, the CPU doesn't have the bandwidth to tell you what all the registers are named, and leaves that to you to determine.

What is the largest value in any register after completing the instructions in your puzzle input?

*/

void day8(){

    // retreive input
    vector<vector<string> > input_matrix;
    int result = 0;
    int max = 0;

    input_matrix = string_matrix_from_file_with_separator("day8.txt", ' ');

    // we still use a map to map to "register" values and use the register names as keys
    map<string, int> m;

    for(int i = 0; i < input_matrix.size(); i++){

        string reg1 = input_matrix[i][0];
        int inc = string_to_int(input_matrix[i][2]); // amount to increment
        string reg2 = input_matrix[i][4];
        string op = input_matrix[i][5]; // comparator operation string value
        int opcode = 0;    // 0 for eval false, positive for eval true:
                            // 1 for ==, 2 for !=, 3 for <, 4 for <=, 5 for >, 6 for >=
        int val = string_to_int(input_matrix[i][6]); // value were comparing to
        if(input_matrix[i][1].compare("dec") == 0){
            inc = -inc;
        }

        // do reg2 first
        // if the value exists in the map, use it
        if(m.find(reg2) != m.end()){

            if(op.compare("==") == 0){
                if(m[reg2] == val) opcode = 1;
            } else if(op.compare("!=") == 0){
                if(m[reg2] != val) opcode = 2;
            } else if(op.compare("<") == 0){
                if(m[reg2] < val) opcode = 3;
            } else if(op.compare("<=") == 0){
                if(m[reg2] <= val) opcode = 4;
            } else if(op.compare(">") == 0){
                if(m[reg2] > val) opcode = 5;
            } else if(op.compare(">=") == 0){
                if(m[reg2] >= val) opcode = 6;
            }
        } else { // if the value dont not exist in the map, its 0

            if(op.compare("==") == 0){
                if(0 == val) opcode = 1;
            } else if(op.compare("!=") == 0){
                if(0 != val) opcode = 2;
            } else if(op.compare("<") == 0){
                if(0 < val) opcode = 3;
            } else if(op.compare("<=") == 0){
                if(0 <= val) opcode = 4;
            } else if(op.compare(">") == 0){
                if(0 > val) opcode = 5;
            } else if(op.compare(">=") == 0){
                if(0 >= val) opcode = 6;
            }
        }

        // now its time to change reg1 depending on what op is
        if(opcode > 0){
            // check to see if it exists
            if(m.find(reg1) != m.end()){
                m[reg1] += inc;
            } else {
                m[reg1] = inc;
            }
        }
    }

    // loop through the values in the map to find the max
    for(auto it = m.begin(); it != m.end(); it++){
        if(it->second > max) max = it->second;
    }
    result = max;
    answer_int(result);
}


/*

To be safe, the CPU also needs to know the highest value held in any register during this process so that it can decide how much memory to allocate to these operations. For example, in the above instructions, the highest value ever held was 10 (in register c after the third instruction was evaluated).

*/

void day8_bonus(){

    // retreive input
    vector<vector<string> > input_matrix;
    int result = 0;
    int highest_ever = 0;

    input_matrix = string_matrix_from_file_with_separator("day8.txt", ' ');

    // we still use a map to map to "register" values and use the register names as keys
    map<string, int> m;

    for(int i = 0; i < input_matrix.size(); i++){

        string reg1 = input_matrix[i][0];
        int inc = string_to_int(input_matrix[i][2]); // amount to increment
        string reg2 = input_matrix[i][4];
        string op = input_matrix[i][5]; // comparator operation string value
        int opcode = 0;    // 0 for eval false, positive for eval true:
                            // 1 for ==, 2 for !=, 3 for <, 4 for <=, 5 for >, 6 for >=
        int val = string_to_int(input_matrix[i][6]); // value were comparing to
        if(input_matrix[i][1].compare("dec") == 0){
            inc = -inc;
        }

        // do reg2 first
        // if the value exists in the map, use it
        if(m.find(reg2) != m.end()){

            if(op.compare("==") == 0){
                if(m[reg2] == val) opcode = 1;
            } else if(op.compare("!=") == 0){
                if(m[reg2] != val) opcode = 2;
            } else if(op.compare("<") == 0){
                if(m[reg2] < val) opcode = 3;
            } else if(op.compare("<=") == 0){
                if(m[reg2] <= val) opcode = 4;
            } else if(op.compare(">") == 0){
                if(m[reg2] > val) opcode = 5;
            } else if(op.compare(">=") == 0){
                if(m[reg2] >= val) opcode = 6;
            }
        } else { // if the value dont not exist in the map, its 0

            if(op.compare("==") == 0){
                if(0 == val) opcode = 1;
            } else if(op.compare("!=") == 0){
                if(0 != val) opcode = 2;
            } else if(op.compare("<") == 0){
                if(0 < val) opcode = 3;
            } else if(op.compare("<=") == 0){
                if(0 <= val) opcode = 4;
            } else if(op.compare(">") == 0){
                if(0 > val) opcode = 5;
            } else if(op.compare(">=") == 0){
                if(0 >= val) opcode = 6;
            }
        }

        // now its time to change reg1 depending on what op is
        if(opcode > 0){
            // check to see if it exists
            if(m.find(reg1) != m.end()){
                m[reg1] += inc;
            } else {
                m[reg1] = inc;
            }
			if(m[reg1] > highest_ever) highest_ever = m[reg1];
        }
    }

    result = highest_ever;
    answer_int(result);
}

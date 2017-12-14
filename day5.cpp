#include <iostream>
#include "../IO/io.h"
#include <vector>


/*

The message includes a list of the offsets for each jump. Jumps are relative: -1 moves to the previous instruction, and 2 skips the next one. Start at the first instruction in the list. The goal is to follow the jumps until one leads outside the list.

In addition, these instructions are a little strange; after each jump, the offset of that instruction increases by 1. So, if you come across an offset of 3, you would move three instructions forward, but change it to a 4 for the next time it is encountered.

For example, consider the following list of jump offsets:

0
3
0
1
-3
Positive jumps ("forward") move downward; negative jumps move upward. For legibility in this example, these offset values will be written all on one line, with the current instruction marked in parentheses. The following steps would be taken before an exit is found:

    (0) 3  0  1  -3  - before we have taken any steps.
    (1) 3  0  1  -3  - jump with offset 0 (that is, don't jump at all). Fortunately, the instruction is then incremented to 1.
     2 (3) 0  1  -3  - step forward because of the instruction we just modified. The first instruction is incremented again, now to 2.
     2  4  0  1 (-3) - jump all the way to the end; leave a 4 behind.
     2 (4) 0  1  -2  - go back to where we just were; increment -3 to -2.
     2  5  0  1  -2  - jump 4 steps forward, escaping the maze.
In this example, the exit is reached in 5 steps.

*/

void day5(){

    vector<vector<int> > input_matrix;
    vector<int> input;
    int result;

    // we start at the 0th index
    int curr_index = 0;
    int jumps = 0;

    // read from file into a matrix
    input_matrix = int_matrix_from_file_with_separator("day5.txt", ' ');

    // set up the input
    for(int i = 0; i < input_matrix.size(); i++){
        input.push_back(input_matrix[i][0]);
    }
    
    // now we start jumping the maze
    while(curr_index >= 0 && curr_index < input.size()){
        //for(int i = 0; i < input.size(); i++){
        //    cout << input[i] << " ";
        //}
        //cout << endl;
        int old_index = curr_index;
        jumps++;
        //cout << "jumps from index " << curr_index;
        curr_index += input[curr_index];
        //cout << " to index " << curr_index << endl;
        input[old_index]++;
    }

    result = jumps;
    answer_int(result);
}


/*

Now, the jumps are even stranger: after each jump, if the offset was three or more, instead decrease it by 1. Otherwise, increase it by 1 as before.

Using this rule with the above example, the process now takes 10 steps, and the offset values after finding the exit are left as 2 3 2 3 -1.

How many steps does it now take to reach the exit?

*/

void day5_bonus(){

    vector<vector<int> > input_matrix;
    vector<int> input;
    int result;

    // we start at the 0th index
    int curr_index = 0;
    int jumps = 0;

    // read from file into a matrix
    input_matrix = int_matrix_from_file_with_separator("day5.txt", ' ');

    // set up the input
    for(int i = 0; i < input_matrix.size(); i++){
        input.push_back(input_matrix[i][0]);
    }
    
    // now we start jumping the maze
    while(curr_index >= 0 && curr_index < input.size()){
        //for(int i = 0; i < input.size(); i++){
        //    cout << input[i] << " ";
        //}
        //cout << endl;
        int old_index = curr_index;
        int jump_size = 0;
        jumps++;
        //cout << "jumps from index " << curr_index;
        jump_size = input[curr_index];
        curr_index += jump_size;
        //cout << " to index " << curr_index << endl;
        if (jump_size >= 3){
            input[old_index]--;
        } else {
            input[old_index]++;
        }
    }

    result = jumps;
    answer_int(result);
}

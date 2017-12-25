#include <iostream>
#include "../IO/io.h"
#include <vector>
#include <string>
#include <map>

/*

You find the Turing machine blueprints (your puzzle input) on a tablet in a nearby pile of debris. Looking back up at the broken Turing machine above, you can start to identify its parts:

A tape which contains 0 repeated infinitely to the left and right.
A cursor, which can move left or right along the tape and read or write values at its current position.
A set of states, each containing rules about what to do based on the current value under the cursor.
Each slot on the tape has two possible values: 0 (the starting value for all slots) and 1. Based on whether the cursor is pointing at a 0 or a 1, the current state says what value to write at the current position of the cursor, whether to move the cursor left or right one slot, and which state to use next.

For example, suppose you found the following blueprint:

Begin in state A.
Perform a diagnostic checksum after 6 steps.

In state A:
  If the current value is 0:
    - Write the value 1.
    - Move one slot to the right.
    - Continue with state B.
  If the current value is 1:
    - Write the value 0.
    - Move one slot to the left.
    - Continue with state B.

In state B:
  If the current value is 0:
    - Write the value 1.
    - Move one slot to the left.
    - Continue with state A.
  If the current value is 1:
    - Write the value 1.
    - Move one slot to the right.
    - Continue with state A.
Running it until the number of steps required to take the listed diagnostic checksum would result in the following tape configurations (with the cursor marked in square brackets):

... 0  0  0 [0] 0  0 ... (before any steps; about to run state A)
... 0  0  0  1 [0] 0 ... (after 1 step;     about to run state B)
... 0  0  0 [1] 1  0 ... (after 2 steps;    about to run state A)
... 0  0 [0] 0  1  0 ... (after 3 steps;    about to run state B)
... 0 [0] 1  0  1  0 ... (after 4 steps;    about to run state A)
... 0  1 [1] 0  1  0 ... (after 5 steps;    about to run state B)
... 0  1  1 [0] 1  0 ... (after 6 steps;    about to run state A)
The CPU can confirm that the Turing machine is working by taking a diagnostic checksum after a specific number of steps (given in the blueprint). Once the specified number of steps have been executed, the Turing machine should pause; once it does, count the number of times 1 appears on the tape. In the above example, the diagnostic checksum is 3.

Recreate the Turing machine and save the computer! What is the diagnostic checksum it produces once it's working again?

*/

void day25(){

    vector<vector<string> > input;
    int result = 0;
    input = string_matrix_from_file_with_separator("day25.txt", ' ');

    // we will store the turing machine's memory as a map
    map<int, int> m;
    // the position of the cursor
    int pointer = 0;
    char state = '\0';

    // get the state
    state = input[0][3][0];
    // loop for the specified amount of times before the checksum
    int loops = string_to_int(input[1][5]);

    cout << "the detected state is " << state << endl;
    cout << "the detected amount of loops is " << loops << endl;

    // start looping
    for(int i = 0; i < loops; i++){

        // find the current state in the input
        int state_index = 2 + (state - 'A') * 9;
        // check the current value
        bool is_one = false;
        // if its one, do the second thing
        if(m.find(pointer) != m.end()){
            if(m[pointer] == 1){
                is_one = true;
                // write a value
                m[pointer] = input[state_index + 6][8][0] - '0';
                // move the pointer
                if(input[state_index + 7][10].compare("right.") == 0){
                    pointer++;
                } else {
                    pointer--;
                }
                // get next state
                state = input[state_index + 8][8][0];
            }
        }
        // if its not one, do the first thing
        if(!is_one){
            // write a value
            m[pointer] = input[state_index + 2][8][0] - '0';
            // move the pointer
            if(input[state_index + 3][10].compare("right.") == 0){
                pointer++;
            } else {
                pointer--;
            }
            // get next state
            state = input[state_index + 4][8][0];
        }
    }

    // count the number of ones
    for(auto it = m.begin(); it != m.end(); it++){
        result += it->second;
    }
    answer_int(result);
}



/*




*/

void day25_bonus(){

}

#include <iostream>
#include "../IO/io.h"
#include <string>
#include <vector>
#include <map>

/*

There aren't that many instructions, so it shouldn't be hard to figure out what they do. Here's what you determine:

snd X plays a sound with a frequency equal to the value of X.
set X Y sets register X to the value of Y.
add X Y increases register X by the value of Y.
mul X Y sets register X to the result of multiplying the value contained in register X by the value of Y.
mod X Y sets register X to the remainder of dividing the value contained in register X by the value of Y (that is, it sets X to the result of X modulo Y).
rcv X recovers the frequency of the last sound played, but only when the value of X is not zero. (If it is zero, the command does nothing.)
jgz X Y jumps with an offset of the value of Y, but only if the value of X is greater than zero. (An offset of 2 skips the next instruction, an offset of -1 jumps to the previous instruction, and so on.)
Many of the instructions can take either a register (a single letter) or a number. The value of a register is the integer it contains; the value of a number is that number.

After each jump instruction, the program continues with the instruction to which the jump jumped. After any other instruction, the program continues with the next instruction. Continuing (or jumping) off either end of the program terminates it.

For example:

set a 1
add a 2
mul a a
mod a 5
snd a
set a 0
rcv a
jgz a -1
set a 1
jgz a -2
The first four instructions set a to 1, add 2 to it, square it, and then set it to itself modulo 5, resulting in a value of 4.
Then, a sound with frequency 4 (the value of a) is played.
After that, a is set to 0, causing the subsequent rcv and jgz instructions to both be skipped (rcv because a is 0, and jgz because a is not greater than 0).
Finally, a is set to 1, causing the next jgz instruction to activate, jumping back two instructions to another jump, which jumps again to the rcv, which ultimately triggers the recover operation.
At the time the recover operation is executed, the frequency of the last sound played is 4.

What is the value of the recovered frequency (the value of the most recently played sound) the first time a rcv instruction is executed with a non-zero value?

*/

void day18(){

    vector<vector<string> > input_matrix;
    int result = 0;
    input_matrix = string_matrix_from_file_with_separator("day18.txt", ' ');

    // there was a trap where using ints would screw me over
    map<char, long> m;
    long last_played;
    long last_received;
    for(int i = 0; i < input_matrix.size() && i >= 0; i++){
        // get first two arguments
        string arg_0 = input_matrix[i][0];
        string arg_1 = input_matrix[i][1];
        long arg_1_val = 0;
        if(arg_1[0] >= 'a' && arg_1[0] <= 'z'){
            if(m.find(arg_1[0]) != m.end()){
                arg_1_val = m[arg_1[0]];
            } else {
                m[arg_1[0]] = 0;
            }
        } else {
            arg_1_val = string_to_int(arg_1);
        }

        // the following commands only require 1 argument
        if(arg_0.compare("snd") == 0){
            last_played = arg_1_val;
            continue;
        } else if (arg_0.compare("rcv") == 0){
            if(arg_1_val != 0){
                last_received = last_played;
                break;
            }
            continue;
        }

        // get the third argument
        string arg_2 = input_matrix[i][2];
        long arg_2_val = 0;
        if(arg_2[0] >= 'a' && arg_2[0] <= 'z'){
            if(m.find(arg_2[0]) != m.end()){
                arg_2_val = m[arg_2[0]];
            } else {
                m[arg_2[0]] = 0;
            }
        } else {
            arg_2_val = string_to_int(arg_2);
        }

        // the rest of the commands all require two arguments
        if(arg_0.compare("set") == 0){
            m[arg_1[0]] = arg_2_val;
        } else if(arg_0.compare("add") == 0){
            m[arg_1[0]] += arg_2_val;
        } else if(arg_0.compare("mul") == 0){
            m[arg_1[0]] *= arg_2_val;
        } else if(arg_0.compare("mod") == 0){
            // had to change the following line cos of how c++ handles mods
            m[arg_1[0]] = (m[arg_1[0]] % arg_2_val + arg_2_val) % arg_2_val;
        } else if(arg_0.compare("jgz") == 0){
            if(arg_1_val > 0){
                i += (arg_2_val - 1);
            }
        }
    }

    result = last_received;
    answer_int(result);
}



/*



*/

void day18_bonus(){

}

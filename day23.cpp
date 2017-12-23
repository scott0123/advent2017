#include <iostream>
#include "../IO/io.h"
#include <string>
#include <vector>
#include <map>
#include <queue>

bool is_prime(int a);

/*

You decide to head directly to the CPU and fix the printer from there. As you get close, you find an experimental coprocessor doing so much work that the local programs are afraid it will halt and catch fire. This would cause serious issues for the rest of the computer, so you head in and see what you can do.

The code it's running seems to be a variant of the kind you saw recently on that tablet. The general functionality seems very similar, but some of the instructions are different:

set X Y sets register X to the value of Y.
sub X Y decreases register X by the value of Y.
mul X Y sets register X to the result of multiplying the value contained in register X by the value of Y.
jnz X Y jumps with an offset of the value of Y, but only if the value of X is not zero. (An offset of 2 skips the next instruction, an offset of -1 jumps to the previous instruction, and so on.)
Only the instructions listed above are used. The eight registers here, named a through h, all start at 0.

The coprocessor is currently set to some kind of debug mode, which allows for testing, but prevents it from doing any meaningful work.

If you run the program (your puzzle input), how many times is the mul instruction invoked?

*/

void day23(){

    // code copied mostly from day18
    vector<vector<string> > input_matrix;
    int result = 0;
    input_matrix = string_matrix_from_file_with_separator("day23.txt", ' ');

    // there was a trap where using ints would screw me over
    map<char, long> m;
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
        } else if(arg_0.compare("sub") == 0){
            m[arg_1[0]] -= arg_2_val;
        } else if(arg_0.compare("mul") == 0){
            m[arg_1[0]] *= arg_2_val;
            result++;
        } else if(arg_0.compare("mod") == 0){
            // had to change the following line cos of how c++ handles mods
            m[arg_1[0]] = (m[arg_1[0]] % arg_2_val + arg_2_val) % arg_2_val;
        } else if(arg_0.compare("jnz") == 0){
            if(arg_1_val != 0){
                i += (arg_2_val - 1);
            }
        } else if(arg_0.compare("jgz") == 0){
            if(arg_1_val > 0){
                i += (arg_2_val - 1);
            }
        }
    }

    answer_int(result);
}



/*

Now, it's time to fix the problem.

The debug mode switch is wired directly to register a. You flip the switch, which makes register a now start at 1 when the program is executed.

Immediately, the coprocessor begins to overheat. Whoever wrote this program obviously didn't choose a very efficient implementation. You'll need to optimize the program if it has any hope of completing before Santa needs that printer working.

The coprocessor's ultimate goal is to determine the final value left in register h once the program completes. Technically, if it had that... it wouldn't even need to run the program.

After setting register a to 1, if the program were to run to completion, what value would be left in register h?

*/

void day23_bonus(){

    // this was a tricky one:
    // see my analysis (photo) in the same folder "day23analysis.jpg"
    int result = 0;

    for(int i = 108100; i <= 125100; i += 17){
        if(!is_prime(i)) result++;
    }

    answer_int(result);
}


// helper
bool is_prime(int a){

    for(int i = 2; i * i <= a; i++){
        if(a % i == 0) return false;
    }
    return true;
}

#include <iostream>
#include "../IO/io.h"
#include <string>
#include <vector>
#include <queue>

#define A_FACTOR 16807
#define B_FACTOR 48271
#define JUDGE_1 40000000
#define JUDGE_2 5000000

/*

The generators both work on the same principle. To create its next value, a generator will take the previous value it produced, multiply it by a factor (generator A uses 16807; generator B uses 48271), and then keep the remainder of dividing that resulting product by 2147483647. That final remainder is the value it produces next.

To calculate each generator's first value, it instead uses a specific starting value as its "previous value" (as listed in your puzzle input).

For example, suppose that for starting values, generator A uses 65, while generator B uses 8921. Then, the first five pairs of generated values are:

    --Gen. A--   --Gen. B--
    1092455      430625591
    1181022009   1233683848
    245556042    1431495498
    1744312007   137874439
    1352636452   285222916

    In binary, these pairs are (with generator A's value first in each pair):

    00000000000100001010101101100111
    00011001101010101101001100110111

    01000110011001001111011100111001
    01001001100010001000010110001000

    00001110101000101110001101001010
    01010101010100101110001101001010

    01100111111110000001011011000111
    00001000001101111100110000000111

    01010000100111111001100000100100
    00010001000000000010100000000100

    Here, you can see that the lowest (here, rightmost) 16 bits of the third value match: 1110001101001010. Because of this one match, after processing these five pairs, the judge would have added only 1 to its total.

    To get a significant sample, the judge would like to consider 40 million pairs. (In the example above, the judge would eventually find a total of 588 pairs that match in their lowest 16 bits.)

    After 40 million pairs, what is the judge's final count?

*/

void day15(){

    vector<vector<string> > input;
    input = string_matrix_from_file_with_separator("day15.txt", ' ');
    int result = 0;

    int a = string_to_int(input[0][4]);
    int b = string_to_int(input[1][4]);

    /*
        There are many interesting realizations to make here
        1. since were only interested in the last 16 bits anyway, why dont we mask off the rest
        2. if the rest are masked off, why mod 2.147 billion anyway, it wont exceed this

        These two facts allow us to use standard 32 bit integers to speed up the calculations
    */

    long long_a = a;
    long long_b = b;
    for(int i = 0; i < JUDGE_1; i++){
        long_a *= A_FACTOR;
        long_a %= 2147483647;
        //printf("long_a hex: %4lx\n", long_a & 0xFFFF);
        long_b *= B_FACTOR;
        long_b %= 2147483647;
        //cout << long_a << " " << long_b << endl;
        if((long_a & 0xFFFF) == (long_b & 0xFFFF)) result++;
    }
/* 
// this works if the mod number is 1<<31 instead of (1<<31)-1
// but im running out of time to figure out the trick, so were gonna use brute force :(
    a = 65;
    b = 8921;
    for(int i = 0; i < ITERATIONS + 1; i++){
        a &= 0xFFFF;
        b &= 0xFFFF;
        printf("a hex: %4x\n", a);
        if(a == b && i != 0) result++;
        a *= A_FACTOR;
        b *= B_FACTOR;
    }
*/
    answer_int(result);
}


/*



*/

void day15_bonus(){

    vector<vector<string> > input;
    input = string_matrix_from_file_with_separator("day15.txt", ' ');
    int result = 0;

    int a = string_to_int(input[0][4]);
    int b = string_to_int(input[1][4]);

    queue<int> q_a;
    queue<int> q_b;

    long long_a = a;
    long long_b = b;
    for(int i = 0; i < JUDGE_2;){
        long_a *= A_FACTOR;
        long_a %= 2147483647;
        //printf("long_a hex: %4lx\n", long_a & 0xFFFF);
        long_b *= B_FACTOR;
        long_b %= 2147483647;
        //cout << long_a << " " << long_b << endl;
        if(((long_a & 0xFFFF) % 4) == 0){
            q_a.push(long_a & 0xFFFF);
        }
        if(((long_b & 0xFFFF) % 8) == 0){
            q_b.push(long_b & 0xFFFF);
        }
        // if both queues arent empty, take one out of each and compare
        if(!q_a.empty() && !q_b.empty()){
            if(q_a.front() == q_b.front()) result++;
            q_a.pop();
            q_b.pop();
            i++;
        }
    }
    
    answer_int(result);
}

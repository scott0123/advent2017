#include <iostream>
#include <string>
#include "../IO/io.h"
#include "days.h"

using namespace std;

/*

The captcha requires you to review a sequence of digits (your puzzle input) and find the sum of all digits that match the next digit in the list. The list is circular, so the digit after the last digit is the first digit in the list.

For example:

    1122 produces a sum of 3 (1 + 2) because the first digit (1) matches the second digit and the third digit (2) matches the fourth digit.
    1111 produces 4 because each digit (all 1) matches the next.
    1234 produces 0 because no digit matches the next.
    91212129 produces 9 because the only digit that matches the next one is the last digit, 9.
    What is the solution to your captcha?

*/

void day1(){

    cout << "--- Day 1 ---" << endl;
        
    string input;
    //prompt_string(input);
    input = readfile("day1.txt", 0);
    
    int curr = -1;
    int prev = -1;
    int result = 0;

    // parse the string
    for(int i = 0; i < input.length(); i++){
        
        curr = input[i] - '0';
        if(curr == prev){
            result += curr;
        }
        prev = curr;
    }
    if(curr == input[0] - '0'){
        result += curr;
    }

    answer_int(result);
}

/*

--- Part Two ---

You notice a progress bar that jumps to 50% completion. Apparently, the door isn't yet satisfied, but it did emit a star as encouragement. The instructions change:

Now, instead of considering the next digit, it wants you to consider the digit halfway around the circular list. That is, if your list contains 10 items, only include a digit in your sum if the digit 10/2 = 5 steps forward matches it. Fortunately, your list has an even number of elements.

For example:

    1212 produces 6: the list contains 4 items, and all four digits match the digit 2 items ahead.
    1221 produces 0, because every comparison is between a 1 and a 2.
    123425 produces 4, because both 2s match each other, but no other digit has a match.
    123123 produces 12.
    12131415 produces 4.

What is the solution to your new captcha?

*/

void day1_bonus(){

    cout << "--- Day 1 bonus ---" << endl;
    
    string input;
    //prompt_string(input);
    input = readfile("day1.txt", 0);

    int curr = -1;
    int next = -1;
    int length = input.length();
    int half_length = length / 2;
    int result = 0;

    // parse the string
    for(int i = 0; i < length; i++){
        
        curr = input[i] - '0';
        next = input[(i + half_length) % length] - '0';
        if(curr == next){
            result += curr;
        }
    }

    answer_int(result);
}

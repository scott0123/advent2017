#include  <iostream>
#include "../IO/io.h"
#include <vector>
#include <map>

/*

The debugger would like to know how many redistributions can be done before a blocks-in-banks configuration is produced that has been seen before.

For example, imagine a scenario with only four memory banks:

    The banks start with 0, 2, 7, and 0 blocks. The third bank has the most blocks, so it is chosen for redistribution.
    Starting with the next bank (the fourth bank) and then continuing to the first bank, the second bank, and so on, the 7 blocks are spread out over the memory banks. The fourth, first, and second banks get two blocks each, and the third bank gets one back. The final result looks like this: 2 4 1 2.
    Next, the second bank is chosen because it contains the most blocks (four). Because there are four memory banks, each gets one block. The result is: 3 1 2 3.
    Now, there is a tie between the first and fourth memory banks, both of which have three blocks. The first bank wins the tie, and its three blocks are distributed evenly over the other three banks, leaving it with none: 0 2 3 4.
    The fourth bank is chosen, and its four blocks are distributed such that each of the four banks receives one: 1 3 4 1.
    The third bank is chosen, and the same thing happens: 2 4 1 2.
    At this point, we've reached a state we've seen before: 2 4 1 2 was already seen. The infinite loop is detected after the fifth block redistribution cycle, and so the answer in this example is 5.

*/

void day6(){

    vector<int> input;
    input = int_vector_from_file_with_separator("day6.txt", '\t');

    int result = 0;

    // we create a map that will be used to remember which vector formations we've already seen
    map<vector<int>, int> m;
    m[input] = 1;

    // keep looping while we havent found a repeat
    while(m.find(input) != m.end()){

        result++;
        // first find the index at which the largest number resides
        int largest = input[0];
        int index_largest = 0;
        for(int i = 0; i < input.size(); i++){
            if(input[i] > largest){
                largest = input[i];
                index_largest = i;
            }
        }

        // clear the largest number because we will be redistributing it
        input[index_largest] = 0;
        // now since we have the index and the number, simply redistribute it
        for(int i = 0; i < largest; i++){
            input[(index_largest + i + 1) % input.size()]++;
        }

        //check to see if we have a repeat
        if(m.find(input) != m.end()) break;

        // save the vector formation
        m[input] = 1;

        //debug: print to see what we got
        for(int i = 0; i < input.size(); i++) cout << input[i] << " ";
        cout << endl;
    }

    answer_int(result);
}


/*

Out of curiosity, the debugger would also like to know the size of the loop: starting from a state that has already been seen, how many block redistribution cycles must be performed before that same state is seen again?

In the example above, 2 4 1 2 is seen again after four cycles, and so the answer in that example would be 4.

How many cycles are in the infinite loop that arises from the configuration in your puzzle input?

*/

void day6_bonus(){

    vector<int> input;
    input = int_vector_from_file_with_separator("day6.txt", '\t');

    int result = 0;

    // we create a map that will be used to remember which vector formations we've already seen
    map<vector<int>, int> m;
    m[input] = 1;

    // we create a bool to indicate if its the second time seeing it
    bool second_run = false;
    vector<int> offending_vector;

    // keep looping while we havent found a repeat
    while(m.find(input) != m.end()){

        if(second_run) result++;
        // first find the index at which the largest number resides
        int largest = input[0];
        int index_largest = 0;
        for(int i = 0; i < input.size(); i++){
            if(input[i] > largest){
                largest = input[i];
                index_largest = i;
            }
        }

        // clear the largest number because we will be redistributing it
        input[index_largest] = 0;
        // now since we have the index and the number, simply redistribute it
        for(int i = 0; i < largest; i++){
            input[(index_largest + i + 1) % input.size()]++;
        }

        //check to see if we have a repeat
        if(m.find(input) != m.end()){
            if(!second_run){
                second_run = true;
                offending_vector = input;
            } else if (input == offending_vector){
                break;
            }
        }

        // save the vector formation
        m[input] = 1;

        //debug: print to see what we got
        for(int i = 0; i < input.size(); i++) cout << input[i] << " ";
        cout << endl;
    }

    answer_int(result);
}



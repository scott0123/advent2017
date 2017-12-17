#include <iostream>
#include "../IO/io.h"
#include <vector>

#define LAST_VAL_P1 2017
#define LAST_VAL_P2 50000000

/*

It repeats this process of stepping forward, inserting a new value, and using the location of the inserted value as the new current position a total of 2017 times, inserting 2017 as its final operation, and ending with a total of 2018 values (including 0) in the circular buffer.

For example, if the spinlock were to step 3 times per insert, the circular buffer would begin to evolve like this (using parentheses to mark the current position after each iteration of the algorithm):

(0), the initial state before any insertions.
0 (1): the spinlock steps forward three times (0, 0, 0), and then inserts the first value, 1, after it. 1 becomes the current position.
0 (2) 1: the spinlock steps forward three times (0, 1, 0), and then inserts the second value, 2, after it. 2 becomes the current position.
0  2 (3) 1: the spinlock steps forward three times (1, 0, 2), and then inserts the third value, 3, after it. 3 becomes the current position.
And so on:

0  2 (4) 3  1
0 (5) 2  4  3  1
0  5  2  4  3 (6) 1
0  5 (7) 2  4  3  6  1
0  5  7  2  4  3 (8) 6  1
0 (9) 5  7  2  4  3  8  6  1
Eventually, after 2017 insertions, the section of the circular buffer near the last insertion looks like this:

1512  1134  151 (2017) 638  1513  851
Perhaps, if you can identify the value that will ultimately be after the last value written (2017), you can short-circuit the spinlock. In this example, that would be 638.

What is the value after 2017 in your completed circular buffer?

*/

void day17(){

    int input;
    int result;
    prompt_int(input);

    // we will be using a vector, as its properties are very very useful for todays problem
    vector<int> v;
    int pos = 0;
    v.push_back(0);

    for(int i = 1; i < LAST_VAL_P1 + 1; i++){
        // calculate new postion (need to add one due to how c++ vectors work: they insert at the front)
        pos = (pos + input) % v.size() + 1;
        // insert the element
        v.insert(v.begin() + pos, i);
        /*
        // debug: print the array
        for(int j = 0; j < v.size(); j++){
            if(j == pos) cout << "( ";
            cout << v[j] << " ";
            if(j == pos) cout << ") ";
        }
        cout << endl;
        */
    }

    result = v[pos + 1];
    answer_int(result);
}



/*

You have good news and bad news.

The good news is that you have improved calculations for how to stop the spinlock. They indicate that you actually need to identify the value after 0 in the current state of the circular buffer.

The bad news is that while you were determining this, the spinlock has just finished inserting its fifty millionth value (50000000).

What is the value after 0 the moment 50000000 is inserted?

*/

void day17_bonus(){

    int input;
    int result;
    prompt_int(input);

    int pos = 0;
    int second_element = -1;

    for(int i = 1; i < LAST_VAL_P2 + 1; i++){
        // calculate new postion (need to add one due to how c++ vectors work: they insert at the front)
        //pos = (pos + input) % i;
        pos = (pos + input) % i + 1;
        // instead of actually inserting the element, just check if the second one wouldve been replaced
        if(pos == 1) second_element = i;
        /*
        // debug: print the array
        for(int j = 0; j < v.size(); j++){
            if(j == pos) cout << "( ";
            cout << v[j] << " ";
            if(j == pos) cout << ") ";
        }
        cout << endl;
        */
    }

    result = second_element;
    answer_int(result);
}

#include <iostream>
#include "../IO/io.h"
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#define LETTER_NUM 16
#define DANCE_IT 1000000000

/*

There are sixteen programs in total, named a through p. They start by standing in a line: a stands in position 0, b stands in position 1, and so on until p, which stands in position 15.

The programs' dance consists of a sequence of dance moves:

Spin, written sX, makes X programs move from the end to the front, but maintain their order otherwise. (For example, s3 on abcde produces cdeab).
Exchange, written xA/B, makes the programs at positions A and B swap places.
Partner, written pA/B, makes the programs named A and B swap places.
For example, with only five programs standing in a line (abcde), they could do the following dance:

s1, a spin of size 1: eabcd.
x3/4, swapping the last two programs: eabdc.
pe/b, swapping programs e and b: baedc.
After finishing their dance, the programs end up in order baedc.

You watch the dance for a while and record their dance moves (your puzzle input). In what order are the programs standing after their dance?

*/

void day16(){

    vector<string> input;
    string result;
    input = string_vector_from_file_with_separator("day16.txt", ',');

    // we will put the letters in a vector
    vector<char> v;
    for(int i = 0; i < LETTER_NUM; i++){
        v.push_back('a' + i);
    }

    // loop through the input and execute the instructions
    for(int i = 0; i < input.size(); i++){
        if(input[i][0] == 's'){
            // swap
            int count = string_to_int(input[i]);
            for(int j = 0; j < LETTER_NUM - count; j++){
                v.push_back(v.front());
                v.erase(v.begin());
            }
        } else if (input[i][0] == 'x'){
            // exchange
            string s1 = input[i];
            string s2 = input[i];
            while(s1.back() != '/') s1.pop_back();
            while(s2.front() != '/') s2.erase(s2.begin());
            int n1 = string_to_int(s1);
            int n2 = string_to_int(s2);
            iter_swap(v.begin() + n1, v.begin() + n2);
        } else if (input[i][0] == 'p'){
            // partner
            int index1;
            int index2;
            for(int j = 0; j < LETTER_NUM; j++){
                if(v[j] == input[i][1]) index1 = j;
                if(v[j] == input[i][3]) index2 = j;
            }
            iter_swap(v.begin() + index1, v.begin() + index2);
        }
    }

    // form output
    for(int i = 0; i < LETTER_NUM; i++){
        result += v[i];
    }
    answer_string(result);
}



/*

Keeping the positions they ended up in from their previous dance, the programs perform it again and again: including the first dance, a total of one billion (1000000000) times.

In the example above, their second dance would begin with the order baedc, and use the same dance moves:

s1, a spin of size 1: cbaed.
x3/4, swapping the last two programs: cbade.
pe/b, swapping programs e and b: ceadb.
In what order are the programs standing after their billion dances?

*/

void day16_bonus(){

    vector<string> input;
    string result;
    input = string_vector_from_file_with_separator("day16.txt", ',');

    // we will put the letters in a vector
    vector<char> v;
    for(int i = 0; i < LETTER_NUM; i++){
        v.push_back('a' + i);
    }

    // make a map to remember if this combo is seen before
    map<vector<char>, int> m;
    int period = -1;

    for(int k = DANCE_IT; k > 0; k--){
        // skip all the periods
        if(period > 0 && k > period){
            k %= period;
            //cout << "new k is " << k << endl;
        } else if (period < 0) {
            // have we seen this before?
            if(m.find(v) != m.end()){
                // if we have, we can skip every period from now on
                if(period < 0) period = DANCE_IT - k;
                //cout << "cycle found at " << period << endl;
            } else {
                // otherwise map it
                m[v] = 1;
                //cout << k << ": no cycle" << endl;
            }
        }
        // loop through the input and execute the instructions
        for(int i = 0; i < input.size(); i++){
            if(input[i][0] == 's'){
                // swap
                int count = string_to_int(input[i]);
                for(int j = 0; j < LETTER_NUM - count; j++){
                    v.push_back(v.front());
                    v.erase(v.begin());
                }
            } else if (input[i][0] == 'x'){
                // exchange
                string s1 = input[i];
                string s2 = input[i];
                while(s1.back() != '/') s1.pop_back();
                while(s2.front() != '/') s2.erase(s2.begin());
                int n1 = string_to_int(s1);
                int n2 = string_to_int(s2);
                iter_swap(v.begin() + n1, v.begin() + n2);
            } else if (input[i][0] == 'p'){
                // partner
                int index1;
                int index2;
                for(int j = 0; j < LETTER_NUM; j++){
                    if(v[j] == input[i][1]) index1 = j;
                    if(v[j] == input[i][3]) index2 = j;
                }
                iter_swap(v.begin() + index1, v.begin() + index2);
            }
        }
    }
    // form output
    for(int i = 0; i < LETTER_NUM; i++){
        result += v[i];
    }
    answer_string(result);
}

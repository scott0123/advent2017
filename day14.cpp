#include <iostream>
#include "../IO/io.h"
#include <vector>
#include <string>
#include <algorithm>
#include "dsets.h"

#define NUM_LIST_SIZE 256

/*

This segment is literally copy pasted from day10_bonus(), with some minor modifications

Input: a string
Output: a char vector of size 16 containing the hash

*/

vector<char> knot_hash(string input){

    vector<char> result;
    input.push_back(17);
    input.push_back(31);
    input.push_back(73);
    input.push_back(47);
    input.push_back(23);

    int skip_size = 0;
    int pos = 0;

    // create the number list from 0 to 255
    vector<int> number_list;
    for(int i = 0; i < NUM_LIST_SIZE; i++) number_list.push_back(i);

    // repeat 64 times
    for(int j = 0; j < 64; j++){
        for(int i = 0; i < input.size(); i++){

            int start = pos;
            int end = ((pos + input[i] - 1) % NUM_LIST_SIZE);
            /*
            for(int i = 0; i < NUM_LIST_SIZE; i++){
                if(i == start) cout << "[ ";
                cout << number_list[i] << " ";
                if(i == end) cout << "] ";
            }
            cout << endl;
            */
            bool first_it = true;
            if(input[i] != 0){
                while((start != end) && (((start-1+NUM_LIST_SIZE) % NUM_LIST_SIZE != end) || first_it)){
                    swap(number_list[start], number_list[end]);
                    start++;
                    start %= NUM_LIST_SIZE;
                    end--;
                    end += NUM_LIST_SIZE;
                    end %= NUM_LIST_SIZE;
                    first_it = false;
                }
            }
            pos += input[i];
            pos += skip_size;
            pos %= NUM_LIST_SIZE;
            skip_size++;
            //cout << "pos " << pos << endl;
            //cout << "skip_size " << skip_size << endl;
            //for(int i = 0; i < NUM_LIST_SIZE; i++) cout << number_list[i] << " ";
            //cout << endl;
        }
    }

    int start_index = 0;
    // now find the dense hash from the sparse hash
    for(int i = 0; i < 16; i++){

        int block = number_list[start_index];
        for(int j = 1; j < 16; j++){
            block ^= number_list[start_index + j];
        }
        start_index += 16;
        result.push_back((char)block);
    }
    return result;
}


/*
helper function to count the number of 1's in a char's binary representation
*/

int get_ones(char c){
    int val = 0;
    for(int i = 0; i < 8; i++){
        if(c & (1 << i)) val++;
    }
    return val;
}


/*

The disk in question consists of a 128x128 grid; each square of the grid is either free or used. On this disk, the state of the grid is tracked by the bits in a sequence of knot hashes.

A total of 128 knot hashes are calculated, each corresponding to a single row in the grid; each hash contains 128 bits which correspond to individual grid squares. Each bit of a hash indicates whether that square is free (0) or used (1).

The hash inputs are a key string (your puzzle input), a dash, and a number from 0 to 127 corresponding to the row. For example, if your key string were flqrgnkx, then the first row would be given by the bits of the knot hash of flqrgnkx-0, the second row from the bits of the knot hash of flqrgnkx-1, and so on until the last row, flqrgnkx-127.

The output of a knot hash is traditionally represented by 32 hexadecimal digits; each of these digits correspond to 4 bits, for a total of 4 * 32 = 128 bits. To convert to bits, turn each hexadecimal digit to its equivalent binary value, high-bit first: 0 becomes 0000, 1 becomes 0001, e becomes 1110, f becomes 1111, and so on; a hash that begins with a0c2017... in hexadecimal would begin with 10100000110000100000000101110000... in binary.

Continuing this process, the first 8 rows and columns for key flqrgnkx appear as follows, using # to denote used squares, and . to denote free ones:

##.#.#..-->
.#.#.#.#   
....#.#.   
#.#.##.#   
.##.#...   
##..#..#   
.#...#..   
##.#.##.-->
|      |   
V      V   
In this example, 8108 squares are used across the entire 128x128 grid.

Given your actual key string, how many squares are used?

*/

void day14(){

    string input;
    int result = 0;
    prompt_string(input);

    // we need to parse 128 entries
    for(int i = 0; i < 128; i++){

        vector<char> hash = knot_hash(input + "-" + to_string(i));
        // the hash contains 16 chars
        for(int j = 0; j < 16; j++){
            result += get_ones(hash[j]);
        }
    }

    answer_int(result);
}


/*

Now, all the defragmenter needs to know is the number of regions. A region is a group of used squares that are all adjacent, not including diagonals. Every used square is in exactly one region: lone used squares form their own isolated regions, while several adjacent squares all count as a single region.

How many regions are present given your key string?

*/

void day14_bonus(){

    string input;
    int result = 0;
    prompt_string(input);

    // hashes will be stored here
    vector<vector<char> > hashes;

    // we will be using disjoint sets for this problem
    DisjointSets ds;
    ds.addelements(128 * 128);

    // we need to store the hashes
    for(int i = 0; i < 128; i++){
        hashes.push_back(knot_hash(input + "-" + to_string(i)));
    }

    int zeros = 0;

    // now we need to parse the hashes
    for(int i = 0; i < 128; i++){
        // the hash contains 16 chars
        for(int j = 0; j < 16; j++){
            // each char is 8 bits
            for(int k = 0; k < 8; k++){
                // if the current one is a 1
                if(hashes[i][j] & (1 << k)){
                    // check top
                    if(i != 0){
                        if(hashes[i-1][j] & (1 << k)) ds.setunion(i*128+j*8+k, (i-1)*128+j*8+k);
                    }
                    // check right
                    if(k != 0){
                        if(hashes[i][j] & (1 << (k-1))) ds.setunion(i*128+j*8+k, i*128+j*8+k-1);
                    } else if(j != 15){
                        if(hashes[i][j+1] & (1 << 7)) ds.setunion(i*128+j*8+k, i*128+(j+1)*8+7);
                    }
                    // check down
                    if(i != 127){
                        if(hashes[i+1][j] & (1 << k)) ds.setunion(i*128+j*8+k, (i+1)*128+j*8+k);
                    }
                    // check left
                    if(k != 7){
                        if(hashes[i][j] & (1 << (k+1))) ds.setunion(i*128+j*8+k, i*128+j*8+k+1);
                    } else if(j != 0){
                        if(hashes[i][j-1] & 1) ds.setunion(i*128+j*8+k, i*128+(j-1)*8);
                    }
                } else {
                    zeros++;
                }
            }
        }
    }
    
    for(int i = 0; i < 128 * 128; i++){
        if(ds.set[i] < 0) result++;
    }
    result -= zeros;
    answer_int(result);
}

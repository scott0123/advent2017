#include <iostream>
#include "../IO/io.h"
#include <vector>
#include <string>
#include <algorithm>

/*

A new system policy has been put in place that requires all accounts to use a passphrase instead of simply a password. A passphrase consists of a series of words (lowercase letters) separated by spaces.

To ensure security, a valid passphrase must contain no duplicate words.

For example:
    aa bb cc dd ee is valid.
    aa bb cc dd aa is not valid - the word aa appears more than once.
    aa bb cc dd aaa is valid - aa and aaa count as different words.

*/

void day4(){

    vector<vector<string> > input_matrix;
    int result = 0;
    int invalid = 0;

    input_matrix = string_matrix_from_file_with_separator("day4.txt", ' ');

    for(int i = 0; i < input_matrix.size(); i++){
        // sort the row
		sort(input_matrix[i].begin(), input_matrix[i].end());
		for(int j = 0; j < input_matrix[i].size() - 1; j++){
            if(strcmp(input_matrix[i][j].c_str(), input_matrix[i][j+1].c_str()) == 0){
                invalid++;
                break;
            }
        }
    }

    result = input_matrix.size() - invalid;

    answer_int(result);
}


/*

For added security, yet another system policy has been put in place. Now, a valid passphrase must contain no two words that are anagrams of each other - that is, a passphrase is invalid if any word's letters can be rearranged to form any other word in the passphrase.

For example:
    abcde fghij is a valid passphrase.
    abcde xyz ecdab is not valid - the letters from the third word can be rearranged to form the first word.
    a ab abc abd abf abj is a valid passphrase, because all letters need to be used when forming another word.
    iiii oiii ooii oooi oooo is valid.
    oiii ioii iioi iiio is not valid - any of these words can be rearranged to form any other word.

*/

void day4_bonus(){

    vector<vector<string> > input_matrix;
    int result = 0;
    int invalid = 0;

    input_matrix = string_matrix_from_file_with_separator("day4.txt", ' ');

    for(int i = 0; i < input_matrix.size(); i++){
		for(int j = 0; j < input_matrix[i].size(); j++){
            // sort the string into alphabetacal order
		    sort(input_matrix[i][j].begin(), input_matrix[i][j].end());
        }
        // sort the row
		sort(input_matrix[i].begin(), input_matrix[i].end());
		for(int j = 0; j < input_matrix[i].size() - 1; j++){
            if(strcmp(input_matrix[i][j].c_str(), input_matrix[i][j+1].c_str()) == 0){
                invalid++;
                break;
            }
        }
    }

    result = input_matrix.size() - invalid;

    answer_int(result);
}

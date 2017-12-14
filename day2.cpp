#include <iostream>
#include <vector>
#include "../IO/io.h"
#include "days.h"

/*

The spreadsheet consists of rows of apparently-random numbers. To make sure the recovery process is on the right track, they need you to calculate the spreadsheet's checksum. For each row, determine the difference between the largest value and the smallest value; the checksum is the sum of all of these differences.

For example, given the following spreadsheet:

5 1 9 5
7 5 3
2 4 6 8
The first row's largest and smallest values are 9 and 1, and their difference is 8.
The second row's largest and smallest values are 7 and 3, and their difference is 4.
The third row's difference is 6.
In this example, the spreadsheet's checksum would be 8 + 4 + 6 = 18.

What is the checksum for the spreadsheet in your puzzle input?

*/

void day2(){

    int result = 0;
    vector<vector<int> > input_matrix;
    input_matrix = int_matrix_from_file_with_separator("day2.txt", '\t');

   //test input matrix
    cout << "Attempting to parse into matrix..." << endl;
    cout << "Printing matrix: (debug)" << endl;
    for(int i = 0; i < input_matrix.size(); i++){
        for(int j = 0; j < input_matrix[i].size(); j++){
            cout << input_matrix[i][j] << " ";
        }
        cout << endl;
    }

    for(int i = 0; i < input_matrix.size(); i++){
        
        int largest = -1000000;
        int smallest = 1000000;

        for(int j = 0; j < input_matrix[i].size(); j++){
            if(input_matrix[i][j] > largest) largest = input_matrix[i][j];
            if(input_matrix[i][j] < smallest) smallest = input_matrix[i][j];
        }
        result += largest;
        result -= smallest;
    }

    answer_int(result);
}

/*

It sounds like the goal is to find the only two numbers in each row where one evenly divides the other - that is, where the result of the division operation is a whole number. They would like you to find those numbers on each line, divide them, and add up each line's result.

For example, given the following spreadsheet:

5 9 2 8
9 4 7 3
3 8 6 5
In the first row, the only two numbers that evenly divide are 8 and 2; the result of this division is 4.
In the second row, the two numbers are 9 and 3; the result is 3.
In the third row, the result is 2.
In this example, the sum of the results would be 4 + 3 + 2 = 9.

What is the sum of each row's result in your puzzle input?

*/

void day2_bonus(){

    int result = 0;
    vector<vector<int> > input_matrix;
    input_matrix = int_matrix_from_file_with_separator("day2.txt", '\t');

   //test input matrix
    cout << "Attempting to parse into matrix..." << endl;
    cout << "Printing matrix: (debug)" << endl;
    for(int i = 0; i < input_matrix.size(); i++){
        for(int j = 0; j < input_matrix[i].size(); j++){
            cout << input_matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    for(int i = 0; i < input_matrix.size(); i++){
        
        sort(input_matrix[i].begin(), input_matrix[i].end());
        //cout << "testing row " << i << endl;
        bool found = false;
        // start from the largest end, and go down
        for(int j = input_matrix[i].size() - 1; j >= 0; j--){
            // only check up until half of the largest number
            for(int k = 0; input_matrix[i][k] * 2 <= input_matrix[i][j] && !found; k++){
                // if they are divisible and not equal
                //cout << "          testing " << input_matrix[i][j] << " / " << input_matrix[i][k] << endl;
                if(input_matrix[i][j] % input_matrix[i][k] == 0 && input_matrix[i][j] != input_matrix[i][k]){
                    found = true;
                    int quotient = input_matrix[i][j] / input_matrix[i][k];
                    //cout << "quotient of row " << i << " is " << quotient << endl;
                    result += quotient;
                }
            }
        }
    }

    answer_int(result);
}

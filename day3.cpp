#include <iostream>
#include <tuple>
#include <map>
#include "../IO/io.h"

// header
void move_direction(int dir, int &x, int &y);

void day3(){

    int input = 0;
    prompt_int(input);
    int result = 0;

    // starting direction is right
    int dir = 0;
    // steps per change in direction
    int step_limit = 1;
    int step_counter = 0;
    int new_limit_reached_count = 0;

    // x > 0 for right, y > 0 for up
    int x = 0;
    int y = 0;

    // do the following process "input-1" times
    for(int i = 0; i < input-1; i++){

        dir %= 4;
        move_direction(dir, x, y);

        // for the next step
        step_counter++;
        if(step_counter < step_limit){
        } else {
            // reset counter
            step_counter = 0;
            dir++;
            new_limit_reached_count++;
            // change step limit every two times the limit is hit
            if(new_limit_reached_count >= 2){
                new_limit_reached_count = 0;
                step_limit++;
            }
        }
    }

    int x_abs = x < 0 ? -x : x;
    int y_abs = y < 0 ? -y : y;
    result = x_abs + y_abs;

    answer_int(result);
}

void move_direction(int dir, int &x, int &y){

    // right = 0, up = 1, left = 2, down = 3
    switch(dir){
    case 0:
        x++;
        //cout << "Moving right" << endl;
        break;
    case 1:
        y++;
        //cout << "Moving up" << endl;
        break;
    case 2:
        x--;
        //cout << "Moving left" << endl;
        break;
    case 3:
        y--;
        //cout << "Moving down" << endl;
        break;
    default:
        cout << "Something went wrong in move_direction" << endl;
    }
}



void day3_bonus(){

    int input = 0;
    prompt_int(input);
    int result = 0;

    // starting direction is right
    int dir = 0;
    // steps per change in direction
    int step_limit = 1;
    int step_counter = 0;
    int new_limit_reached_count = 0;
    // value at the location
    int val = 0;
    // map and tuple
    map<tuple<int, int>, int> m;

    // by default the first position is mapped to 1
    m[make_tuple(0, 0)] = 1;

    // x > 0 for right, y > 0 for up
    int x = 0;
    int y = 0;

    // do the following process "input-1" times
    for(int i = 0; i < 10000000; i++){

        val = 0;
        // figure out the value by looking at values around this point
        y++;
        if(m.find(make_tuple(x, y)) != m.end()) val += m[make_tuple(x, y)];
        x++;
        if(m.find(make_tuple(x, y)) != m.end()) val += m[make_tuple(x, y)];
        y--;
        if(m.find(make_tuple(x, y)) != m.end()) val += m[make_tuple(x, y)];
        y--;
        if(m.find(make_tuple(x, y)) != m.end()) val += m[make_tuple(x, y)];
        x--;
        if(m.find(make_tuple(x, y)) != m.end()) val += m[make_tuple(x, y)];
        x--;
        if(m.find(make_tuple(x, y)) != m.end()) val += m[make_tuple(x, y)];
        y++;
        if(m.find(make_tuple(x, y)) != m.end()) val += m[make_tuple(x, y)];
        y++;
        if(m.find(make_tuple(x, y)) != m.end()) val += m[make_tuple(x, y)];

        // restore x, y back to orig x, y
        x++; y--;

        if(i != 0){ // we already assigned i = 0 case
            m[make_tuple(x, y)] = val;
        }
        if(val > input){
            result = val;
            break;
        }

        dir %= 4;
        move_direction(dir, x, y);

        // for the next step
        step_counter++;
        if(step_counter < step_limit){
        } else {
            // reset counter
            step_counter = 0;
            dir++;
            new_limit_reached_count++;
            // change step limit every two times the limit is hit
            if(new_limit_reached_count >= 2){
                new_limit_reached_count = 0;
                step_limit++;
            }
        }
    }

    answer_int(result);
}

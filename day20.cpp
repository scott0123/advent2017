#include <iostream>
#include "../IO/io.h"
#include <vector>
#include <string>
#include <stdlib.h> //abs
#include <tuple>
#include <map>

#define SIMULATION_LIMIT 50

/*

It transmits to you a buffer (your puzzle input) listing each particle in order (starting with particle 0, then particle 1, particle 2, and so on). For each particle, it provides the X, Y, and Z coordinates for the particle's position (p), velocity (v), and acceleration (a), each in the format <X,Y,Z>.

Each tick, all particles are updated simultaneously. A particle's properties are updated in the following order:

Increase the X velocity by the X acceleration.
Increase the Y velocity by the Y acceleration.
Increase the Z velocity by the Z acceleration.
Increase the X position by the X velocity.
Increase the Y position by the Y velocity.
Increase the Z position by the Z velocity.
Because of seemingly tenuous rationale involving z-buffering, the GPU would like to know which particle will stay closest to position <0,0,0> in the long term. Measure this using the Manhattan distance, which in this situation is simply the sum of the absolute values of a particle's X, Y, and Z position.

For example, suppose you are only given two particles, both of which stay entirely on the X-axis (for simplicity). Drawing the current states of particles 0 and 1 (in that order) with an adjacent a number line and diagram of current X positions (marked in parenthesis), the following would take place:

p=< 3,0,0>, v=< 2,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
p=< 4,0,0>, v=< 0,0,0>, a=<-2,0,0>                         (0)(1)

p=< 4,0,0>, v=< 1,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
p=< 2,0,0>, v=<-2,0,0>, a=<-2,0,0>                      (1)   (0)

p=< 4,0,0>, v=< 0,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
p=<-2,0,0>, v=<-4,0,0>, a=<-2,0,0>          (1)               (0)

p=< 3,0,0>, v=<-1,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
p=<-8,0,0>, v=<-6,0,0>, a=<-2,0,0>                         (0)   
At this point, particle 1 will never be closer to <0,0,0> than particle 0, and so, in the long run, particle 0 will stay closest.

Which particle will stay closest to position <0,0,0> in the long term?

*/

void day20(){

    vector<vector<int> > input_matrix;
    int result = 0;
    input_matrix = int_matrix_from_file_with_separator("day20.txt", ',');

    int lowest_vel = abs(input_matrix[0][3]) + abs(input_matrix[0][4]) + abs(input_matrix[0][5]);
    int lowest_acc = abs(input_matrix[0][6]) + abs(input_matrix[0][7]) + abs(input_matrix[0][8]);

    for(int i = 0; i < input_matrix.size(); i++){
        int abs_vel = abs(input_matrix[i][3]) + abs(input_matrix[i][4]) + abs(input_matrix[i][5]);
        int abs_acc = abs(input_matrix[i][6]) + abs(input_matrix[i][7]) + abs(input_matrix[i][8]);
        if(lowest_acc > abs_acc){
            lowest_acc = abs_acc;
            result = i;
        } else if (lowest_acc == abs_acc && lowest_vel > abs_vel) {
            lowest_vel = abs_vel;
            result = i;
        }
    }
    cout << "lowest acceleration: " << lowest_acc << endl;
    answer_int(result);
}



/*

To simplify the problem further, the GPU would like to remove any particles that collide. Particles collide if their positions ever exactly match. Because particles are updated simultaneously, more than two particles can collide at the same time and place. Once particles collide, they are removed and cannot collide with anything else after that tick.

For example:

p=<-6,0,0>, v=< 3,0,0>, a=< 0,0,0>    
p=<-4,0,0>, v=< 2,0,0>, a=< 0,0,0>    -6 -5 -4 -3 -2 -1  0  1  2  3
p=<-2,0,0>, v=< 1,0,0>, a=< 0,0,0>    (0)   (1)   (2)            (3)
p=< 3,0,0>, v=<-1,0,0>, a=< 0,0,0>

p=<-3,0,0>, v=< 3,0,0>, a=< 0,0,0>    
p=<-2,0,0>, v=< 2,0,0>, a=< 0,0,0>    -6 -5 -4 -3 -2 -1  0  1  2  3
p=<-1,0,0>, v=< 1,0,0>, a=< 0,0,0>             (0)(1)(2)      (3)   
p=< 2,0,0>, v=<-1,0,0>, a=< 0,0,0>

p=< 0,0,0>, v=< 3,0,0>, a=< 0,0,0>    
p=< 0,0,0>, v=< 2,0,0>, a=< 0,0,0>    -6 -5 -4 -3 -2 -1  0  1  2  3
p=< 0,0,0>, v=< 1,0,0>, a=< 0,0,0>                       X (3)      
p=< 1,0,0>, v=<-1,0,0>, a=< 0,0,0>

------destroyed by collision------    
------destroyed by collision------    -6 -5 -4 -3 -2 -1  0  1  2  3
------destroyed by collision------                      (3)         
p=< 0,0,0>, v=<-1,0,0>, a=< 0,0,0>
In this example, particles 0, 1, and 2 are simultaneously destroyed at the time and place marked X. On the next tick, particle 3 passes through unharmed.

How many particles are left after all collisions are resolved?

*/

void day20_bonus(){

    vector<vector<int> > input_matrix;
    int result = 0;
    input_matrix = int_matrix_from_file_with_separator("day20.txt", ',');

    map<int, int> removed;

    vector<tuple<int, int, int> > v_p;
    vector<tuple<int, int, int> > v_v;
    vector<tuple<int, int, int> > v_a;
    
    for(int i = 0; i < input_matrix.size(); i++){
        auto p = make_tuple(input_matrix[i][0], input_matrix[i][1], input_matrix[i][2]);
        auto v = make_tuple(input_matrix[i][3], input_matrix[i][4], input_matrix[i][5]);
        auto a = make_tuple(input_matrix[i][6], input_matrix[i][7], input_matrix[i][8]);
        v_p.push_back(p);
        v_v.push_back(v);
        v_a.push_back(a);
    }

    for(int i = 0; i < SIMULATION_LIMIT; i++){
        // check if any are overlapping
        for(int j = 0; j < v_p.size(); j++){
            if(removed.find(j) != removed.end()) continue;
            bool found_collision;
            for(int k = 0; k < v_p.size(); k++){
                if(removed.find(k) != removed.end()) continue;
                if(j == k) continue;
                if(v_p[j] == v_p[k]){
                    removed[k] = 1;
                    //cout << "removed " << k << endl;
                    found_collision = true;
                }
            }
            if(found_collision){
                removed[j] = 1;
                found_collision = false;
                //cout << "removed " << j << endl;
            }
        }
        // simulate every particle once
        for(int j = 0; j < v_p.size(); j++){
            if(removed.find(j) != removed.end()) continue;
            auto v= make_tuple(get<0>(v_v[j]) + get<0>(v_a[j]), get<1>(v_v[j]) + get<1>(v_a[j]), get<2>(v_v[j]) + get<2>(v_a[j]));
            v_v[j] = v;
            auto p= make_tuple(get<0>(v_p[j]) + get<0>(v_v[j]), get<1>(v_p[j]) + get<1>(v_v[j]), get<2>(v_p[j]) + get<2>(v_v[j]));
            v_p[j] = p;
        }
    }
    // find how many are not removed
    for(int i = 0; i < v_p.size(); i++){
        if(removed.find(i) != removed.end()) continue;
        result++;
    }
    answer_int(result);
}

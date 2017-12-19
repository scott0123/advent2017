#include <iostream>
#include "../IO/io.h"
#include <vector>
#include <string>

// headers
bool can_move_dir(int &x, int &y, int &dir, vector<string> &graph);
void move_dir(int &x, int &y, int &dir);

/*

Its starting point is just off the top of the diagram. Lines (drawn with |, -, and +) show the path it needs to take, starting by going down onto the only line connected to the top of the diagram. It needs to follow this path until it reaches the end (located somewhere within the diagram) and stop there.

Sometimes, the lines cross over each other; in these cases, it needs to continue going the same direction, and only turn left or right when there's no other option. In addition, someone has left letters on the line; these also don't change its direction, but it can use them to keep track of where it's been. For example:

     |          
     |  +--+    
     A  |  C    
 F---|----E|--+ 
     |  |  |  D 
     +B-+  +--+ 

Given this diagram, the packet needs to take the following path:

Starting at the only line touching the top of the diagram, it must go down, pass through A, and continue onward to the first +.
Travel right, up, and right, passing through B in the process.
Continue down (collecting C), right, and up (collecting D).
Finally, go all the way left through E and stopping at F.
Following the path to the end, the letters it sees on its path are ABCDEF.

The little packet looks up at you, hoping you can help it find the way. What letters will it see (in the order it would see them) if it follows the path? (The routing diagram is very wide; make sure you view it without line wrapping.)

*/

void day19(){

    vector<string> input;
    string result;
    input = string_vector_from_file("day19.txt");

    // variables
    int x = 0;
    int y = 0;
    // up = 0; right = 1; down = 2; left = 3;
    int dir = 2; // initially its down

    // find starting x
    for(int i = 0; i < input[0].size(); i++){
        if(input[0][i] == '|'){
            x = i;
            break;
        }
    }

    // follow the lines
    while(true){
        char on = input[y][x];
//cout << "x: " << x << " y: " << y << " dir: " << dir << endl;
        if('A' <= on && on <= 'Z') result += on;
        // try to move forward
        if(can_move_dir(x, y, dir, input)){
            move_dir(x, y, dir);
            continue;
        }
        // try to move left
        dir += 3;
        dir %= 4;
        if(can_move_dir(x, y, dir, input)){
            move_dir(x, y, dir);
            continue;
        }
        // try to move right
        dir += 2;
        dir %= 4;
        if(can_move_dir(x, y, dir, input)){
            move_dir(x, y, dir);
            continue;
        }
        break;
    }

    answer_string(result);
}



/*

The packet is curious how many steps it needs to go.

For example, using the same routing diagram from the example above...

     |          
     |  +--+    
     A  |  C    
 F---|--|-E---+ 
     |  |  |  D 
     +B-+  +--+ 

...the packet would go:

6 steps down (including the first line at the top of the diagram).
3 steps right.
4 steps up.
3 steps right.
4 steps down.
3 steps right.
2 steps up.
13 steps left (including the F it stops on).
This would result in a total of 38 steps.

How many steps does the packet need to go?

*/

void day19_bonus(){

    vector<string> input;
    int result;
    input = string_vector_from_file("day19.txt");

    // variables
    int x = 0;
    int y = 0;
    // up = 0; right = 1; down = 2; left = 3;
    int dir = 2; // initially its down
    int steps = 0;

    // find starting x
    for(int i = 0; i < input[0].size(); i++){
        if(input[0][i] == '|'){
            x = i;
            break;
        }
    }

    // follow the lines
    while(true){
        char on = input[y][x];
        steps++;
//cout << "x: " << x << " y: " << y << " dir: " << dir << endl;
        if('A' <= on && on <= 'Z') result += on;
        // try to move forward
        if(can_move_dir(x, y, dir, input)){
            move_dir(x, y, dir);
            continue;
        }
        // try to move left
        dir += 3;
        dir %= 4;
        if(can_move_dir(x, y, dir, input)){
            move_dir(x, y, dir);
            continue;
        }
        // try to move right
        dir += 2;
        dir %= 4;
        if(can_move_dir(x, y, dir, input)){
            move_dir(x, y, dir);
            continue;
        }
        break;
    }
    result = steps;
    answer_int(result);
}


// helper functions
bool can_move_dir(int &x, int &y, int &dir, vector<string> &graph){

    int check_x = x;
    int check_y = y;
    switch(dir){
        case 0: // up
            check_y--;
            break;
        case 1: // right
            check_x++;
            break;
        case 2: // down
            check_y++;
            if(check_y >= graph.size()) return false;
            break;
        case 3: // left
            check_x--;
            break;
    }
    return (graph[check_y][check_x] != ' ');
}
void move_dir(int &x, int &y, int &dir){

    switch(dir){
        case 0: // up
            y--;
            break;
        case 1: // right
            x++;
            break;
        case 2: // down
            y++;
            break;
        case 3: // left
            x--;
            break;
    }
}

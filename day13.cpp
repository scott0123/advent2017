#include <iostream>
#include "../IO/io.h"
#include <vector>
#include <cmath>

/*

For example, suppose you've recorded the following:

0: 3
1: 2
4: 4
6: 4
This means that there is a layer immediately inside the firewall (with range 3), a second layer immediately after that (with range 2), a third layer which begins at depth 4 (with range 4), and a fourth layer which begins at depth 6 (also with range 4). Visually, it might look like this:

 0   1   2   3   4   5   6
[ ] [ ] ... ... [ ] ... [ ]
[ ] [ ]         [ ]     [ ]
[ ]             [ ]     [ ]
                [ ]     [ ]
Within each layer, a security scanner moves back and forth within its range. Each security scanner starts at the top and moves down until it reaches the bottom, then moves up until it reaches the top, and repeats. A security scanner takes one picosecond to move one step.

Your plan is to hitch a ride on a packet about to move through the firewall. The packet will travel along the top of each layer, and it moves at one layer per picosecond. Each picosecond, the packet moves one layer forward (its first move takes it into layer 0), and then the scanners move one step. If there is a scanner at the top of the layer as your packet enters it, you are caught. (If a scanner moves into the top of its layer while you are there, you are not caught: it doesn't have time to notice you before you leave.)

In this situation, you are caught in layers 0 and 6, because your packet entered the layer when its scanner was at the top when you entered it. You are not caught in layer 1, since the scanner moved into the top of the layer once you were already there.

The severity of getting caught on a layer is equal to its depth multiplied by its range. (Ignore layers in which you do not get caught.) The severity of the whole trip is the sum of these values. In the example above, the trip severity is 0*3 + 6*4 = 24.

Given the details of the firewall you've recorded, if you leave immediately, what is the severity of your whole trip?

*/

void day13(){

    vector<vector<int> > input;
    int result = 0;
    input = int_matrix_from_file_with_separator("day13.txt", ' ');

    for(int i = 0; i < input.size(); i++){
        int step = input[i][0];
        int cycle = input[i][1] - 1;
        // fancy math to figure out where we are at that step
        if(cycle - abs((step % (2 * cycle)) - cycle) == 0) result += step * (cycle + 1);
    }
    answer_int(result);
}



/*

Now, you need to pass through the firewall without being caught - easier said than done.

You can't control the speed of the packet, but you can delay it any number of picoseconds. For each picosecond you delay the packet before beginning your trip, all security scanners move one step. You're not in the firewall during this time; you don't enter layer 0 until you stop delaying the packet.

Because all smaller delays would get you caught, the fewest number of picoseconds you would need to delay to get through safely is 10.

What is the fewest number of picoseconds that you need to delay the packet to pass through the firewall without being caught?

*/

void day13_bonus(){

    vector<vector<int> > input;
    int result = 0;
    input = int_matrix_from_file_with_separator("day13.txt", ' ');
    int can_be_caught = false;

    while(true){
        for(int i = 0; i < input.size(); i++){
            int step = input[i][0] + result;
            int cycle = input[i][1] - 1;
            // fancy math to figure out where we are at that step
            if(cycle - abs((step % (2 * cycle)) - cycle) == 0){
                result++;
                can_be_caught = true;
                break;
            } else {
                can_be_caught = false;
            }
        }
        if(can_be_caught == false){
            break;
        }
    }
    answer_int(result);
}

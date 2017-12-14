#include <iostream>
#include "../IO/io.h"
#include <vector>
#include <map>

/*

One program at the bottom supports the entire tower. It's holding a large disc, and on the disc are balanced several more sub-towers. At the bottom of these sub-towers, standing on the bottom disc, are other programs, each holding their own disc, and so on. At the very tops of these sub-sub-sub-...-towers, many programs stand simply keeping the disc below them balanced but with no disc of their own.

You offer to help, but first you need to understand the structure of these towers. You ask each program to yell out their name, their weight, and (if they're holding a disc) the names of the programs immediately above them balancing on that disc. You write this information down (your puzzle input). Unfortunately, in their panic, they don't do this in an orderly fashion; by the time you're done, you're not sure which program gave which information.

For example, if your list is the following:

pbga (66)
xhth (57)
ebii (61)
havc (66)
ktlj (57)
fwft (72) -> ktlj, cntj, xhth
qoyq (66)
padx (45) -> pbga, havc, qoyq
tknk (41) -> ugml, padx, fwft
jptl (61)
ugml (68) -> gyxo, ebii, jptl
gyxo (61)
cntj (57)
...then you would be able to recreate the structure of the towers that looks like this:

                gyxo
              /     
         ugml - ebii
       /      \
      |         jptl
      |        
      |         pbga
     /        /
tknk --- padx - havc
     \        \
      |         goyq
      |             
      |         ktlj
       \      /     
         fwft - cntj
              \
                xhth
In this example, tknk is at the bottom of the tower (the bottom program), and is holding up ugml, padx, and fwft. Those programs are, in turn, holding up other programs; in this example, none of those programs are holding up any other programs, and are all the tops of their own towers. (The actual tower balancing in front of you is much larger.)

Before you're ready to help them, you need to make sure your information is correct. What is the name of the bottom program?

*/

class disc {

    public:
        string name;
        int weight;
        vector<string> children;
};

void day7(){

    vector<vector<string> > input_matrix;
    string result = "";
    input_matrix = string_matrix_from_file_with_separator("day7.txt", ' ');

    // we'll use a map to associate a string with its correponding disc
    map<string, disc> name_to_disc;
    map<string, string> name_to_parent;

    // head of disc
    //disc head;

    // we will need to parse the input matrix now
    // the first term is the name, second weight, third useless. if 4+ exists, put them as children, remove commas except last
    for(int i = 0; i < input_matrix.size(); i++){

        // create a disc
        disc curr;
        curr.name = input_matrix[i][0];
        curr.weight = 0;
        for(int j = 1; j < input_matrix[i][1].size() - 1; j++){
            curr.weight *= 10;
            curr.weight += input_matrix[i][1][j] - '0';
        }

        // add children entries if it has any children
        if(input_matrix[i].size() > 3){
            for(int j = 3; j < input_matrix[i].size(); j++){
                if(j != input_matrix[i].size() - 1) input_matrix[i][j].pop_back();
                curr.children.push_back(input_matrix[i][j]);
                name_to_parent[input_matrix[i][j]] = curr.name;
            }
        }

        // map name to disc
        name_to_disc[curr.name] = curr;
    }

    string head = input_matrix[0][0];
    // repeatedly find its parent until it doesnt have a parent
    while(name_to_parent.find(head) != name_to_parent.end()){
        head = name_to_parent[head];
    }

    result = head;
    answer_string(result);
}


/*

For any program holding a disc, each program standing on that disc forms a sub-tower. Each of those sub-towers are supposed to be the same weight, or the disc itself isn't balanced. The weight of a tower is the sum of the weights of the programs in that tower.

In the example above, this means that for ugml's disc to be balanced, gyxo, ebii, and jptl must all have the same weight, and they do: 61.

However, for tknk to be balanced, each of the programs standing on its disc and all programs above it must each match. This means that the following sums must all be the same:

    ugml + (gyxo + ebii + jptl) = 68 + (61 + 61 + 61) = 251
    padx + (pbga + havc + qoyq) = 45 + (66 + 66 + 66) = 243
    fwft + (ktlj + cntj + xhth) = 72 + (57 + 57 + 57) = 243
As you can see, tknk's disc is unbalanced: ugml's stack is heavier than the other two. Even though the nodes above ugml are balanced, ugml itself is too heavy: it needs to be 8 units lighter for its stack to weigh 243 and keep the towers balanced. If this change were made, its weight would be 60.

Given that exactly one program is the wrong weight, what would its weight need to be to balance the entire tower?

*/

int get_combined_weight(disc d, map<string, disc> &name_to_disc){

    // base case
    if(d.children.size() == 0) return d.weight;
    
    int combined_weight = d.weight;
    for(int i = 0; i < d.children.size(); i++){
        combined_weight += get_combined_weight(name_to_disc[d.children[i]], name_to_disc);
    }
    return combined_weight;
}

bool is_balanced(disc d, map<string, disc> &name_to_disc){
    // if it doesnt have children or has just 1 child, balanced is vacuously true
    if(d.children.size() <= 1) return true;
    int lowest = get_combined_weight(name_to_disc[d.children[0]], name_to_disc);
    int highest = lowest;
    for(int i = 0; i < d.children.size(); i++){
        int curr_weight = get_combined_weight(name_to_disc[d.children[i]], name_to_disc);
        if(curr_weight < lowest) lowest = curr_weight;
        if(curr_weight > highest) highest = curr_weight;
    }
    return lowest == highest;
}

void day7_bonus(){

    vector<vector<string> > input_matrix;
    int result = 0;
    input_matrix = string_matrix_from_file_with_separator("day7.txt", ' ');

    // we'll use a map to associate a string with its correponding disc
    map<string, disc> name_to_disc;
    map<string, string> name_to_parent;

    // head of disc
    //disc head;

    // we will need to parse the input matrix now
    // the first term is the name, second weight, third useless. if 4+ exists, put them as children, remove commas except last
    for(int i = 0; i < input_matrix.size(); i++){

        // create a disc
        disc curr;
        curr.name = input_matrix[i][0];
        curr.weight = 0;
        for(int j = 1; j < input_matrix[i][1].size() - 1; j++){
            curr.weight *= 10;
            curr.weight += input_matrix[i][1][j] - '0';
        }

        // add children entries if it has any children
        if(input_matrix[i].size() > 3){
            for(int j = 3; j < input_matrix[i].size(); j++){
                if(j != input_matrix[i].size() - 1) input_matrix[i][j].pop_back();
                curr.children.push_back(input_matrix[i][j]);
                name_to_parent[input_matrix[i][j]] = curr.name;
            }
        }

        // map name to disc
        name_to_disc[curr.name] = curr;
    }

    string find_head = input_matrix[0][0];
    // repeatedly find its parent until it doesnt have a parent
    while(name_to_parent.find(find_head) != name_to_parent.end()){
        find_head = name_to_parent[find_head];
    }

    disc head = name_to_disc[find_head];
    result = get_combined_weight(head, name_to_disc);

    // the wrong weight is the one with imbalanced parents but balanced children
    disc imba = head;
    int imba_index = -2;
    while(imba_index != -1){
        imba_index = -1;
        for(int i = 0; i < imba.children.size(); i++){
            // find the first imbalanced child
            if(!is_balanced(name_to_disc[imba.children[i]], name_to_disc)){
                imba_index = i;
                imba = name_to_disc[imba.children[imba_index]];
                break;
            }
        }
    }
    // after this imba should be the disc with a direct child containing the incorrect weight
    // find the odd one out
    map<int, int> weight_to_frequency;
    map<int, int> index_to_weight;
    for(int i = 0; i < imba.children.size(); i++){
        index_to_weight[i] = get_combined_weight(name_to_disc[imba.children[i]], name_to_disc);
        if(weight_to_frequency.find(index_to_weight[i]) != weight_to_frequency.end()){
            weight_to_frequency[index_to_weight[i]]++;
        } else {
            weight_to_frequency[index_to_weight[i]] = 1;
        }
    }
    // find the index of the bad child, it only occurs once in the map
    int index_of_bad_child = 0;
    for(int i = 0; i < imba.children.size(); i++){
        if(weight_to_frequency[index_to_weight[i]] == 1){
            index_of_bad_child = i;
            break;
        };
    }
    // finally, we can compute the correct child weight
    int right_weight = index_to_weight[(index_of_bad_child + 1) % imba.children.size()];
    int wrong_weight = index_to_weight[index_of_bad_child];
    int correct_child_weight = name_to_disc[imba.children[index_of_bad_child]].weight - wrong_weight + right_weight;
    result = correct_child_weight;
    cout << "the final imba (parent) we found is: " << imba.name << endl;
    cout << "the offending (child) we found is: " << name_to_disc[imba.children[index_of_bad_child]].name << endl;
    cout << "to fix the balance, we need to replace " << name_to_disc[imba.children[index_of_bad_child]].weight << " with " << correct_child_weight << endl << endl;
    answer_int(result);
}

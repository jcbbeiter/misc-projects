#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <queue>
#include <climits>
#include <algorithm>
#include <fstream>
using namespace std;

struct block {
    string name;
    int weight;
    set<string> above_me;
    string below_me;
    int total_weight;
};

string find_bottom(map<string,block> blocks) {
    queue<string> to_remove;

    for (const pair<string,block>& p : blocks) {
        if (p.second.above_me.empty()) {
            to_remove.push(p.first);
        }
    }

    int count = 0;
    while (count < (int)blocks.size()-1) {
        count++;
        block b = blocks[to_remove.front()];
        to_remove.pop();
        blocks[b.below_me].above_me.erase(b.name);
        if (blocks[b.below_me].above_me.empty()) {
            to_remove.push(b.below_me);
        }
    }

    return to_remove.front();
}

int sum_weights(map<string,block> &blocks, string b) {
    int total = blocks[b].weight;

    for (auto s : blocks[b].above_me) {
        blocks[s].total_weight = sum_weights(blocks,s);
        total += blocks[s].total_weight;
    }

    return total;
}

bool is_balanced(map<string,block> &blocks, string bottom) {
    int weight = -1;
    for (string s : blocks[bottom].above_me) {
        if (weight == -1) {
            weight = blocks[s].total_weight;
            continue;
        }
        if (blocks[s].total_weight != weight) {
            return false;
        }
    }
    return true;
}

string find_wrong(map<string,block> &blocks, string bottom) {

    for (string s : blocks[bottom].above_me) {
        if (!is_balanced(blocks,s)) {
            return find_wrong(blocks,s);
        }
    }

    //all balanced, so this one has the odd one out on top of it
    vector<pair<int,string>> weights;
    for (string s : blocks[bottom].above_me) {
        weights.push_back({blocks[s].total_weight,s});
    }

    //sort by weights
    sort(weights.begin(),weights.end());

    //odd one out will either be back or front
    if (weights[0].first == weights[1].first) {
        return weights.back().second;
    } else {
        return weights.front().second;
    }
}

int proper_weight(map<string,block> &blocks, string wrong) {
    string below = blocks[wrong].below_me;

    int correct_total;
    for (string s : blocks[below].above_me) {
        if (s == wrong) {
            continue;
        }
        correct_total = blocks[s].total_weight;
        break;
    }

    return correct_total - (blocks[wrong].total_weight - blocks[wrong].weight);
}

int main() {
    string line;
    ifstream ifs("input/07_input.txt");

    if (!ifs.is_open()) {
        cerr << "Error opening input file" << endl;
        return 1;
    }

    map<string,block> blocks;
    while (getline(ifs,line)) {
        stringstream ss(line);
        block b;
        ss >> b.name;
        
        string temp;
        ss >> temp;
        b.weight = stoi(temp.substr(1,temp.length()-2));

        // consume arrow
        ss >> temp;

        while (ss >> temp) {
            if (temp[temp.length()-1] == ',') {
                temp = temp.substr(0,temp.length()-1);
            }
            b.above_me.insert(temp);
        }
        blocks[b.name] = b;
    }

    //get connections the other way
    for (pair<string,block> b : blocks) {
        for (auto s : b.second.above_me) {
            blocks[s].below_me = b.first;
        }
    }

    //find and print bottom
    string bottom = find_bottom(blocks);
    cout << bottom << " is the bottom of the stack" << endl;

    //recursively calculate total weights
    blocks[bottom].total_weight = sum_weights(blocks,bottom);

    //find block that's the wrong weight
    string wrong = find_wrong(blocks, bottom);

    //calculate and print proper weight
    cout << wrong << " is the wrong weight, should be " << proper_weight(blocks,wrong) << endl;
}

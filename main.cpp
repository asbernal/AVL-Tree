#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include "ArgumentManager.h"
#include "AVL.h"
using namespace std;

//gets the height of the tree
int getHeight(node* n){
    if(n == nullptr){
        return -1;
    }
    int leftHeight = getHeight(n->left);
    int rightHeight = getHeight(n->right);
    if(leftHeight > rightHeight){
        return leftHeight + 1;
    }
    return rightHeight + 1;
}

//finds the difference of the left and right side
int getBalanceFactor(node* n){
    if(n == nullptr){
        return 0;
    }
    return getHeight(n->left) - getHeight(n->right);
}
//returns T if difference is -1, 0, 1
bool check_In_Range(int dif){
    if(dif >= -1 && dif <= 1){
        return true;
    }
    return false;
}

int main(int argc, char* argv[]){
    ArgumentManager am(argc, argv);
    string input = am.get("input");
    string output = am.get("output");
    ifstream fin(input);
    ofstream fout(output);

    // ifstream fin("input3.txt");
    // ofstream fout("output3.txt");

    string line;
    getline(fin,line);
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    //number of nodes to be inserted
    int size = stoi(line);

    AVL avl;
    //reading file
    while(getline(fin, line)){
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    line.erase(remove(line.begin(), line.end(), ' '), line.end());

    //avl.addNode(avl.getRoot(), stoi(line));
    avl.add(stoi(line));

    }
    avl.print_Level_Order(avl.getRoot(), fout);

    fin.close();
    fout.close();
    return 0;
}
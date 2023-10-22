#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <queue>
using namespace std;

struct node{
    int num;
    node* left;
    node* right;
    int height;
    node(int _num){
        num = _num;
        left = nullptr;
        right = nullptr;
        height = 0;
    }
};

class AVL{
    private:
        node* root;
    
    public:
        AVL(){
            root = nullptr;
        }
        node* getRoot(){return root;}
        /*
        void addNode(node* _root,int val){
            //node* temp = new node(val);
            if(root == nullptr){
                node* temp = new node(val);
                root = temp;
            }
            else if(_root->num < val){
                if(_root->right == nullptr){
                    node* temp = new node(val);
                    _root->right = temp;
                }
                else{
                    addNode(_root->right, val);
                }
            }
            else if(_root->num > val){
                if(_root->left == nullptr){
                    node* temp = new node(val);
                    _root->left = temp;
                }
                else{
                    addNode(_root->left, val);
                }
            }
        }
        */
       void add(int data) {root = insert(root, data);}

        node* insert(node* rt, int val){
            if(rt == nullptr){
                rt = new node(val);
            }
            else if(val < rt->num){
                rt->left = insert(rt->left, val);
                if(getBalanceFactor(rt) == 2){
                    if(val < rt->left->num){
                        rt = singleRight(rt);
                    }
                    else{
                        rt = leftRight(rt);
                    }
                }
            }
            else if(val > rt->num){
                rt->right = insert(rt->right, val);
                if(getBalanceFactor(rt) == -2){
                    if(val > rt->right->num){
                        rt = singleLeft(rt);
                    }
                    else{
                        rt = rightLeft(rt);
                    }
                }
            }
            rt->height = max(getHeight(rt->left), getHeight(rt->right) + 1);
            return rt;
        }

        int max(int a, int b){
            if(a > b){
                return a;
            }
            else{
                return b;
            }
        }

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

        node* singleRight(node* rt){
            node* temp = rt->left;
            rt->left = temp->right;
            temp->right = rt;
            rt->height = max(getHeight(rt->left), getHeight(rt->right)) + 1;
            temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
            return temp;
        }

        node* singleLeft(node* rt){
            node* temp = rt->right;
            rt->right = temp->left;
            temp->left = rt;
            rt->height = max(getHeight(rt->left), getHeight(rt->right)) + 1;
            temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
            return temp;
        }

        node* leftRight(node* rt){
            rt->left = singleLeft(rt->left);
            return singleRight(rt);
        }

        node* rightLeft(node* rt){
            rt->right = singleRight(rt->right);
            return singleLeft(rt);
        }

        void print_Level_Order(node* n, ofstream &fout){
            if(n == nullptr){
                return;
            }
            queue<node*> q;
            q.push(n);
            while(!q.empty()){
                int levelSize = q.size();
                for(int i = 0; i < levelSize; i++){
                    node* cu = q.front();
                    q.pop();
                    cout << cu->num << " ";
                    fout << cu->num << " ";
                    if(cu->left != nullptr){
                        q.push(cu->left);
                    }
                    if(cu->right != nullptr){
                        q.push(cu->right);
                    }
                }
                //cout << endl;
                //fout << endl;
            }
        }
};
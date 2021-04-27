/*  Author: Myles Wright
    Project: 2-3 tree
    CS452 Spring 2021
*/

/*
Guides Used: https://www.cprogramming.com/tutorial/computersciencetheory/twothree.html
             https://www.geeksforgeeks.org/2-3-trees-search-and-insert/                     Basically these are BS for this project in particular lol
             http://pages.cs.wisc.edu/~paton/readings/Old/fall01/2-3Tree.html
             https://www.geeksforgeeks.org/level-order-tree-traversal/
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;


class Node{
    Node * parent;
    int value[6];
    Node * child[6];


    public:
    Node();
    Node(int val);
    int numChildren();
    void absorb(Node * newChild);
    void discard(Node * removeChild);
    int getMaxVal();
    Node * getChild(int childToGet);
    int getValue(int valToGet);
    void setParent(Node * node);
    void addVal(int val);
    void removeVal(int val);
};
    Node::Node(){
        //literally do nothing
        for(int i=0; i<6; i++){
            this->value[i] = 0;
        }
        for(int i=0; i<6; i++){
            cout << "Node value " << i << ": " << this->value[i] << endl;
        }
    }
    Node::Node(int val){
        this->value[0] = val; //wtf is the point of having this length 6? I guess I will have to find out. Or google idk.
        for(int i=1; i<6; i++){
            this->value[i] = 0;
        }
        for(int i=0; i<6; i++){
            cout << "Node+1 value " << i << ": " << this->value[i] << endl;
        }
    }
    
    void Node::setParent(Node * node){
        this->parent = node;
    }

    Node * Node::getChild(int childToGet){
        
        Node * child = this->child[childToGet];
        if(child != 0){
            return child;
        }
        else{
            cout << "Holy shit batman its broke! .__." << endl;
            return new Node();
        }
    }

    int Node::getValue(int valToGet){
        int val = this->value[valToGet];
        if(val != 0){
            return val;
        }
        else{
            cout << "Holy shit batman its broke! .__." << endl;
            val = -1;
            return val;
        }
    }

    int Node::numChildren(){
        int count =0;
        for(int i=0; i<6; i++){
            if(this->child[i]->getMaxVal() != 0){
                count++;
            }
        }
        return count;
    }


    int Node::getMaxVal(){ 
        int max = this->value[0];
        for(int i = 1; i < int(sizeof(this->value)); i++){
            if(this->value[i-1] < this->value[i]){
                max = this->value[i];
            }
            else{
                //do nothing
                
            }
        }
        cout << "Max function returns " << max << endl;
        return max;
    }

    void Node::addVal(int val){
        for(int i = 0; i < 3; i++){
            if(this->value[i] == 0){ //go until you hit a 0.
                this->value[i] = val;  
                return;
            }
            else{
                //do nothing
            }
        }
    }


    void Node::absorb(Node * newChild){
         cout << "In absorb" << endl;
         for(int i = 0; i < 3; i++){
             cout << "in for loop" << endl;
             cout << "the child value = " << this->child[i]->getValue(i);
             if(this->child[i]->getValue(i) == 0){ //go until you hit a 0.
                 //cout << "the child value = " << this->child[i]->getValue(i);
                 this->child[i] = newChild;  
                 
             }
                 //do nothing
            
             
        }
    }

    void Node::discard(Node * removeChild){
        Node * blankNode = new Node();
        for(int i = 0; i < 3; i++){
            if(this->child[i]->getMaxVal() == removeChild->getMaxVal()){ //go until they have same max values
                this->child[i] = blankNode; //blank it out.
            }
            else{
                //do nothing
            }
        }
        removeVal(removeChild->getMaxVal()); //remove the max value of the child that is stored in this node
    }

    void Node::removeVal(int val){
        for(int i = 0; i < 6; i++){
            if(this->value[i] == val){ //go until you hit a 0.
                this->value[i] = 0;  
                return;
            }
            else{
                //do nothing
            }
        }
    }








class Tree{
    Node * root;
    void print(Node * start, int level);
    int height(Node * node);

    public:
    Tree();
    Tree(int * arr, int size);
    Node * search(int valToFind);
    bool insert(int valToAdd);
    bool del(int valToKill); //delete is a keyword in C++ so maybe rename this in the prompt so people dont get confused when they get "Expected Unqualified-Id before 'delete' function" error message when trying to compile
    void print();

    void buildTree(Node * leaves, int size);
};

    Tree::Tree(int * arr, int size){
        //First, make each value into a node. These are the leaves. They have no children. :)
        Node * init = new Node[size];
        for(int i = 0; i < size; i++){ //create node, assign the value to it. bam. SO SORRY FOR DOING SOMETHING THAT IS O(n)!
            Node * oof = new Node(arr[i]);
            init[i] = *oof;
        } 
        /*Then, assign each one a parent node, and shove the values into the parent node (will be either 2 or 3 values, I am following Uzi's diagram for this.) 
          Actually I lied I'm using the same numbers but organizing the tree differently because I really don't enjoy how he has it. It's dumb, like take every 3 values, shove them into
          a node and if youre left with one value at the end, move one of the other numbers over so the last two nodes have 2 values its not that hard jesus and its the exact same height like get a grip Uzi
        */

        this->buildTree(init, size);
    }


    int Tree::height(Node * node){
        if(node->getMaxVal() == 0){
            return 0;
        }
        else{
            int max = 0;
            int l[3] = {0, 0, 0};
            
            for(int i = 0; i < node->numChildren(); i++){ //will only go through # of children
                l[i] = height(node->getChild(i));
            }
            for(int j=1; j < 3; j++){ //comparison to get max
                if(l[j]>l[j-1]){
                    max = l[j];
                }
            }
            return (max+1);
        }
    }


    void Tree::buildTree(Node * leaves, int size){
        cout << "Inside buildTree" << endl;
        int sizeround = ceil(size/3);
        int itemstravelled = 0;
        int itemsleft = size;
        Node * p1 = new Node[sizeround];

        for(int i = 0; i < sizeround; i++){
            Node * oof = new Node();
            p1[i] = *oof;
        }

        for(int j = 0; j < sizeround; j++){ //OKAY so basically this is going to have itemsleft and if it is >=3 all items get added to parent node, if it is =2, only those ones are added, if it is =1, then the last item in the node before gets removed and added to make it 2 ya feel?
            cout << "In for loop" << endl;
            if(itemsleft >= 3){
                cout << "Items left:" << itemsleft << endl;
                for(int h = 0; h < 3; h++){
                    cout << "Items traversed:" << itemstravelled << endl;
                    p1[j].addVal(leaves[itemstravelled].getMaxVal());
                    cout << "Added leaf value" << p1[j] endl;
                    leaves[itemstravelled].setParent(&p1[j]); //setting connections for two way traversal
                    cout << "Set Parent" << endl;
                    p1[j].absorb(&leaves[itemstravelled]);
                    cout << "absorbed" <<  endl;
                    itemstravelled++;
                }
                itemsleft -= 3;
            }
            if(itemsleft == 2){
                cout << "Items left:" << itemsleft << endl;
                for(int h = 0; h < 2; h++){
                    cout << "Items traversed:" << itemstravelled << endl;
                    p1[j].addVal(leaves[itemstravelled].getMaxVal());
                    leaves[itemstravelled].setParent(&p1[j]); //setting connections for two way traversal
                    p1[j].absorb(&leaves[itemstravelled]);
                    itemstravelled++;
                }
                itemsleft -= 2;
            }
            if(itemsleft == 1){ //this is the shitty one. have to go to previous p node and remove an element, then insert it into pi then insert the last element.
                cout << "Items left:" << itemsleft << endl;
                p1[j-1].discard(&leaves[itemstravelled-1]); //removing previous value.
                p1[j].addVal(leaves[itemstravelled-1].getMaxVal()); //inserting it into pi.
                p1[j].addVal(leaves[itemstravelled].getMaxVal()); //inserting current element into pi
                leaves[itemstravelled].setParent(&p1[j-1]);
                leaves[itemstravelled].setParent(&p1[j]); //setting connections for two way traversal
                p1[j].absorb(&leaves[itemstravelled]);

            }
        }

        //Now we get to do this all over again, but instead of the leaves, use the level we just made, and the size of the level which is always round(size/3) :)
        if(sizeround > 1){
            cout << "Recursing" << endl;
            buildTree(p1, sizeround);
        }
        else{
            //you are done. set the root node and be done with it.
            cout << "At root node" << endl;
            this->root = &p1[0];
        }
    }


    Node * Tree::search(int valToFind){
        //let root be root of T
        //Base case for leaf
        if(this->root->numChildren() == 0){//root has no children
            return this->root;
        } 
        if(valToFind <= this->root->getChild(0)->getMaxVal()){
            //root.leftchild.Search(valToFind);
        }
        if(valToFind <= this->root->getChild(1)->getMaxVal()){
            //root.midchild.Search(valToFind);
        }
        if(valToFind <= this->root->getChild(2)->getMaxVal()){
            //root.rightchild.Search(valToFind);
        }
        else{
            //return largest element of arrray
        }
        return root; //dont really do this.
    }

    bool Tree::insert(int valToAdd){
        Node * b = this->search(valToAdd);
        for(int i=0; i<6; i++){
            if(0 != b->getValue(i)){
                if(b->getValue(i)==valToAdd){
                    return 0;
                }   
            }
        }
        
        b->absorb(b); //is function of node.
        return 1;
    }

    bool Tree::del(int valToKill){
        Node * b = this->search(valToKill);
        for(int i=0; i<6; i++){
            if(b->getValue(i) == valToKill){
                b->removeVal(valToKill); //function of node
            return 1;
            }
        }
        
        return 0;
    }

    void Tree::print(Node * start, int level){ //using breadth first traversal
        if(root->getMaxVal() == 0){
            return;
        }
        if(level == 1){
            for(int i=0; i<6; i++){
                if((start->getValue(i)) != 0){
                    cout << start->getValue(i);
                }
            }
            cout << endl;
        }
        else{
            for(int j=0; j< start->numChildren(); j++){
                print(start->getChild(j), (level-1));
            }
            
        }
        
    }

    void Tree::print(){
        int h = height(this->root);
        for(int i=0; i<h; i++){
            print(this->root, i);
        }
        
    }




int main(){
    //first we need to build this little shit.
    int size = 15;
    int seq[size] = {1, 3, 5, 8, 11, 14, 17, 19, 21, 24, 28, 31, 33, 36, 39};
    cout << "Making tree" << endl;
    //and now we pass it to the helper function I made because why do this all in main???? thats dumb.
    Tree * tr = new Tree(seq, size);
    cout << "Made tree" << endl;
    tr->print();

}
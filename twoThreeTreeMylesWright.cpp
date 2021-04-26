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
    void discard(Node * removeChild)
    int getMaxVal();
    int setParent(Node node);
    void addVal(int val);
    void removeVal(int val);

    Node(){
        //literally do nothing
    }
    Node(int val){
        this.value[0] = val; //wtf is the point of having this length 6? I guess I will have to find out. Or google idk.
    }

    int numChildren(){
        int count =0;
        for(int i=0; i<6; i++){
            if(child[i] != NULL){
                count++;
            }
        }
        return count;
    }


    int getMaxVal(){ 
        int max = this.value[0];
        for(int i = 1; i < sizeof(this.value); i++){
            if(this.value[i-1] < this.value[i]){
                max = this.value[i];
            }
            else{
                //do nothing
            }
        }

        return max;
    }

    void addVal(int val){
        for(int i = 0; i < 6; i++){
            if(this.value[i] == NULL){ //go until you hit a null.
                this.value[i] = val;  
                return;
            }
            else{
                //do nothing
            }
        }
    }


    void absorb(Node * newChild){
         
         for(int i = 0; i < 6; i++){
            if(this.child[i] == NULL){ //go until you hit a null.
                this.child[i] = newChild;  
                return;
            }
            else{
                //do nothing
            }
        }
    }

    void discard(Node * removeChild){
        Node blankNode = new Node();
        for(int i = 0; i < 6; i++){
            if(this.child[i].getMaxVal() == removeChild.getMaxVal()){ //go until they have same max values
                this.child[i] = blankNode; //blank it out.
            }
            else{
                //do nothing
            }
        }
        removeVal(removeChild.getMaxVal()); //remove the max value of the child that is stored in this node
    }

    void removeVal(int val){
        for(int i = 0; i < 6; i++){
            if(this.value[i] == val){ //go until you hit a null.
                this.value[i] = 0;  
                return;
            }
            else{
                //do nothing
            }
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
    bool delete(int valToKill);
    void print();

    void buildTree(Node * leaves, int size);


    Tree(int * arr, int size){
        //First, make each value into a node. These are the leaves. They have no children. :)
        Node * init = new Node[size];
        for(int i = 0; i < size; i++){ //create node, assign the value to it. bam. SO SORRY FOR DOING SOMETHING THAT IS O(n)!
            init[i] = Node(arr[i]);
        } 

        /*Then, assign each one a parent node, and shove the values into the parent node (will be either 2 or 3 values, I am following Uzi's diagram for this.) 
          Actually I lied I'm using the same numbers but organizing the tree differently because I really don't enjoy how he has it. It's dumb, like take every 3 values, shove them into
          a node and if youre left with one value at the end, move one of the other numbers over so the last two nodes have 2 values its not that hard jesus and its the exact same height like get a grip Uzi
        */

        self.buildTree(init, size);
    }


    int height(Node * node){
        if(node == NULL){
            return 0;
        }
        else{
            int max = 0;
            int l[3] = {0, 0, 0};
            
            for(int i = 0; i < node.numChildren(); i++){ //will only go through # of children
                l[i] = height(node.child[i]);
            }
            for(int j=1; j < 3; j++){ //comparison to get max
                if(l[j]>l[j-1]){
                    max = l[j];
                }
            }
            return (max+1);
        }
    }


    void buildTree(Node * leaves, int size){
        int sizeround = ceil(size/3);
        int itemstravelled = 0;
        int itemsleft = size;
        Node * p1 = Node[sizeround];
        for(int j = 0; j < sizeround; j++){ //OKAY so basically this is going to have itemsleft and if it is >=3 all items get added to parent node, if it is =2, only those ones are added, if it is =1, then the last item in the node before gets removed and added to make it 2 ya feel?
            p1[j] = new Node();
            if(itemsleft >= 3){
                for(int h = 0; h < 3; h++){
                    p1[j].addVal(leaves[itemstravelled].getMaxVal())
                    leaves[itemstravelled].setParent(p1[j]); //setting connections for two way traversal
                    p1[j].absorb(leaves[itemstravelled]);
                    itemstravelled++;
                }
                itemsleft -= 3;
            }
            if(itemsleft == 2){
                for(int h = 0; h < 2; h++){
                    p1[j].addVal(leaves[itemstravelled].getMaxVal())
                    leaves[itemstravelled].setParent(p1[j]); //setting connections for two way traversal
                    p1[j].absorb(leaves[itemstravelled]);
                    itemstravelled++;
                }
                itemsleft -= 2;
            }
            if(itemsleft == 1){ //this is the shitty one. have to go to previous p node and remove an element, then insert it into pi then insert the last element.
                p1[j-1].discard(leaves[itemstravelled-1]); //removing previous value.
                p1[j].addVal(leaves[itemstravelled-1].getMaxVal()); //inserting it into pi.
                p1[j].addVal(leaves[itemstravelled].getMaxVal()); //inserting current element into pi
                leaves[itemstravelled].setParent(p1[j-1]);
                leaves[itemstravelled].setParent(p1[j]); //setting connections for two way traversal
                p1[j].absorb(leaves[itemstravelled]);

            }
        }

        //Now we get to do this all over again, but instead of the leaves, use the level we just made, and the size of the level which is always round(size/3) :)
        if(sizeround > 1){
            buildTree(p1, sizeround);
        }
        else{
            //you are done. set the root node and be done with it.
            this.root = p1[0];
        }
    }


    Node * search(int valToFind){
        //let root be root of T
        //Base case for leaf
        if(){//root has no children
            return root;
        } 
        else if(valToFind <= root.left){
            root.leftchild.Search(valToFind);
        }
        else if(valToFind <= root.mid){
            root.midchild.Search(valToFind);
        }
        else if(valToFind <= root.right){
            root.rightchild.Search(valToFind);
        }
        else
            //return largest element of arrray
    }

    bool insert(int valToAdd){
        let b = T.search(valToAdd);
        if(b==valToFind){
            return 0;
        }
        T.absorb(valToAdd, b); //is function of node.
        return 1;
    }

    bool delete(int valToKill){
        Node * b = T.search(valToKill);
        if(b == valToKill){
            T.discard(valToKill); //function of node
            return 1;
        }
        return 0;
    }

    void print(Node * start, int level){ //using breadth first traversal
        if(root == NULL){
            return;
        }
        if(level == 1){
            for(int i=0; i<6; i++){
                if(start.value[i] != NULL){
                    cout << start.value[i];
                }
            }
            cout << endl;
        }
        else{
            for(int j=0; j<start.numChildren(); j++){
                print(start.child[j], (level-1));
            }
            
        }
        
    }

    void print(){
        int h = height(this.root);
        for(int i=0; i<h; i++){
            print(this.root, i);
        }
        
    }
}



int main(int argc, char * argv[]){
    //first we need to build this little shit.
    int size = 15;
    int * seq = new int[size];
    seq = {1, 3, 5, 8, 11, 14, 17, 19, 21, 24, 28, 31, 33, 36, 39};

    //and now we pass it to the helper function I made because why do this all in main???? thats dumb.
    Tree tr = new Tree(seq, size);



}
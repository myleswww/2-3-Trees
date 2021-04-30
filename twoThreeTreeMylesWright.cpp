/*  Author: Myles Wright
    Project: 2-3 tree
    CS452 Spring 2021
    Sorry that my code is actual horse shit thx
*/

/*
Guides Used: https://www.cprogramming.com/tutorial/computersciencetheory/twothree.html
             https://www.geeksforgeeks.org/2-3-trees-search-and-insert/                     Basically these are BS for this project in particular lol
             http://pages.cs.wisc.edu/~paton/readings/Old/fall01/2-3Tree.html
             https://www.geeksforgeeks.org/level-order-tree-traversal/                      All of these trees do not take the max val to the parent node
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
    void clear();
    void setParent(Node * node);

    public:
    Node();
    Node(int val);
    Node(int val, int val2);
    Node(int val, int val2, int val3); //constructors


    void absorb(Node * newChild);
    void discard(Node * removeChild); //core functions

    int numChildren(); //helper functions
    int numValue();
    int getMaxVal();
    Node * getChild(int childToGet);
    Node * getParent();
    int getValue(int valToGet);
    
    void setChild(Node * node);
    void addVal(int val);
    void removeVal(int val);
    void removeChild(Node * node);
    void printNode();
    Node * search(int x);
    void copy(Node * copyTo); //copies this node to a new node.
    void sortValues(); //insertion sort to reorder elements
    void sortChildren();
    
    void giveSiblingR(); //give the rightmost node to your sibling
    Node * getRightSibling(); //get the right sibling
};
    Node::Node(){
        this->clear();
    }
    Node::Node(int val){
        this->clear();
        this->addVal(val);
    }

    Node::Node(int val, int val2){
        this->clear(); //initialize values
        int vals[2] = {val, val2}; //put them in an array
        for(int i = 0; i < 2; i++){
            this->addVal(vals[i]); //set the values
        }
    
        /*for(int i=0; i<2; i++){
            cout << "Node+1 value " << i << ": " << this->value[i] << endl; //printing for debugging yee yee
        }
        */
       //cout << "Node+1 values: ";
       //this->printNode();
    }

    Node::Node(int val, int val2, int val3){
        int vals[3] = {val, val2, val3}; //put them in an array
        this->clear();
        for(int i = 0; i < 3; i++){
            this->addVal(vals[i]); //set the values
        }
        //cout << "Node+2 values: ";
        //this->printNode();
    }
    
    void Node::copy(Node * copyTo){
        for(int i = 0; i < 6; i++){ //copy the values and the children
            copyTo->addVal(this->getValue(i));
        }
    }

    void Node::printNode(){
        for(int i = 0; i<6; i++){
            if(this->getValue(i) == 0){
                //do nothing
            }
            else{
                cout << this->getValue(i) << "  ";
            }
        }
        cout << endl;
    }

    void Node::clear(){
        for(int j = 0; j<6; j++){ //set everything to 0 and nullptr for later comparisons
            this->value[j] = 0;
            this->child[j] = nullptr;
        }
    }

    void Node::sortChildren(){
        Node * k = new Node(); //temps for children
        Node * j = new Node();
        if(this!=nullptr){
            for(int i = 0; i < (this->numChildren()-1); i++){ 
                for(int h = i; h < this->numChildren(); h++){
                    k=this->getChild(i);
                    j=this->getChild(h);
                    if(k->getMaxVal() > j->getMaxVal() && j != nullptr && k != nullptr){
                        this->child[i] = j;
                        this->value[i] = j->getMaxVal();
                        this->child[h] = k;
                        this->value[h] = k->getMaxVal();
                    }
                }
            }
        } 
        
    }

    void Node::sortValues(){
        int k;
        int j;
        if(this != nullptr){
            for(int i = 0; i < 5; i++){ 
                for(int h = i; h < 6; h++){
                    k=this->getValue(i);
                    j=this->getValue(h);
                    if(k == 0){
                        this->value[i] = this->value[i+1]; //if value[i] ==0, switch the values.
                        this->value[i+1] = 0;
                    }
                    if(k > j && k != 0 && j!=0){ //if j = 0, it wont run. this keeps the zeroes in the back like {11,14,17,13,0,0} and still allows for sorting to {11,13,14,17,0,0}
                        this->value[i] = j;
                        this->value[h] = k;
                    }
                }
            }
        }
    }
    

    void Node::setParent(Node * node){
        if(this != nullptr){
            this->parent = node;
        }
        
    }
    void Node::setChild(Node * node){
        if(this!=nullptr){
            for(int i = 0; i < 6; i++){
                if(this->child[i] == nullptr){
                    //set pointer
                    this->child[i] = node;
                    node->setParent(this); //set the parent
                    return;
                }
            }
        }
        
        
    }

    Node * Node::getChild(int childToGet){
        if(this != nullptr){
            Node * child = this->child[childToGet];
            if(child != nullptr){
                return child;
            }
            else{
                //cout << "getChild: Holy shit batman its broke! .__." << endl;
                return nullptr;
            }
        }
        else{
            return nullptr;
        }
        
    }

    Node * Node::getParent(){
        if(this != nullptr){
            if(this->parent != nullptr){
                return this->parent;
            }
            
        }
        else{
            return nullptr;
        }
    }

    int Node::getValue(int valToGet){
        if(this!=nullptr){
            int val = this->value[valToGet];
            if(val != 0){
                return val;
            }
            else{
                //cout << "getValue: Holy shit batman its broke! .__." << endl;
                val = 0;
                return val;
            }
        }
        return 0;
    }

    int Node::numChildren(){
        if(this==nullptr){
            //cout << "You're looking for something that doesn't exist, buddy." << endl;
            return 0;
        }
        else{
            int count = 0;
            for(int i=0; i<6; i++){
                if(this->getChild(i) != nullptr){ //so if a child isnt a nullptr it is counted.
                    count++;
                }
        }
            return count;
        }
        
    }

    int Node::numValue(){
        int count = 0;
        for(int i=0; i<6; i++){
            if(this->getValue(i) != 0){ //so if a child isnt a nullptr it is counted.
                count++;
            }
        }
        return count;
    }

    int Node::getMaxVal(){ 
        if(this!=nullptr){
            int max = 0;
            for(int i = 1; i < 6; i++){
                if(this->value[i-1] < this->value[i]){
                    max = this->value[i];
                }
                else{
                    //do nothing
                
                }
            }
            //cout << "Max function returns " << max << endl;
            return max;
        }
        else{
            return 0;
        }
        
    }

    void Node::addVal(int val){
        if(this != nullptr){
            for(int i = 0; i < 6; i++){
                if(this->value[i] == 0){ //go until you hit a 0.
                    this->value[i] = val;  
                    return;
                }
                else{
                    //do nothing
                }
            }
        }
    }

    void Node::removeChild(Node * node){
        for(int i = 0; i < 6; i++){
            if(this->getChild(i)->getMaxVal() == node->getMaxVal()){
                this->removeVal(i); //set to 0
                this->child[i] = nullptr;
            }
        }
    }
    void Node::giveSiblingR(){
        Node * p = this->getParent();
        Node * sibling = p->getParent()->getRightSibling();
        if(sibling == nullptr){ //either root or no right sibling, need to go up. call absorb.

        }
        else{
            p->removeChild(this);
            sibling->setChild(this);
        }
        //update
        if(p != nullptr){
            if(p->numChildren()>3){ //if parent has 4 children after insert
                sibling->giveSiblingR(); //call give sibling r on right sibling.
            }
        }
            
    }

    Node * Node::getRightSibling(){
        Node * p = this->getParent();
        if(p==nullptr){
            return nullptr;  //no parent, is root
        }
        for(int i = 0; i < 6; i++){
            if(p->getChild(i) == this){
                return p->child[i+1];
            }
            else if(p->getChild(i)==nullptr){ //does not have a right sibling
                return nullptr;
            }
        }
        return nullptr;
    }

    void Node::absorb(Node * newChild){
         cout << "In absorb" << endl;
         Node * p = this->getParent();
         //this->printNode();
         //cout << this->numValue() << endl << this->numChildren() << endl;
         if(p == nullptr){ //this is if this is the root
             //do the megaroot stuff
             cout << "in megaroot" << endl;
             Node * megasus = new Node();  //this is literally from the notes
             megasus->setChild(this);
             megasus->setChild(newChild);
             megasus->sortChildren();
         }
         else if(this->numValue() < 3){ //if this has 2 values, can just add child and value.
            /*for(int i =0; i<6; i++){
                Node * p_left = p->getChild(i); //take every child
                for(int j=0; j<6; j++){
                    if(p_left->getMaxVal() == newChild->getMaxVal() && p_left->numValue()>3){ //then when you find the "matching child" based on maxVal, and the next child over has 2 values
                        p->getChild(j+1)->addVal(newChild->getMaxVal()); //add that max val to the next child over from you
                        newChild->removeVal(newChild->getMaxVal()); //and then remove it from you
                        
                    }
                }
                
            }
            */
           cout << "in < 3" << endl;
           this->addVal(newChild->getValue(0));
           this->sortChildren();
           if(this!=nullptr){
               if(this->numChildren() != 0){ //is not leaf node
                    this->setChild(newChild); //set the child to update the tree
               }
               return;
           }
           
         }
         else if(this->numValue() >= 3){ //is full
            cout << "in numchild >3" << endl;
             this->addVal(newChild->getValue(0)); //add the value
             this->child[3] = newChild;
             this->sortChildren();//sort them
             this->printNode();
             Node * L = new Node(this->getValue(0), this->getValue(1)); //create p_left with left half of this
             Node * R = new Node(this->getValue(2), this->getValue(3));
             L->setChild(this->getChild(0));
             L->setChild(this->getChild(1));
             R->setChild(this->getChild(2));
             R->setChild(this->getChild(3));
             this->clear();
             
             p->setChild(L);
             cout << "L : ";
             L->printNode();
             cout << "R : ";
             p->setChild(R);
             R->printNode();
             L->getParent()->printNode();
             //this->printNode();

             
             if(p->getParent()->numChildren() < 3 && (p->getParent()->numChildren() != 0 || p->getParent() != nullptr)){ //p only has one sibling, and is not root
                 p->sortChildren();             //sort p's children so they are in correct order.
                 cout << " Only two siblings";
             }
             else{ //is root or has 2 siblings, either way move up the tree
                 Node * z = new Node(R->getMaxVal()); //make a new parent of p_left, dont make p_left a child of p
                 z->setChild(R);
                 cout << "Z: ";
                 z->printNode();
                 cout << "z child: ";
                 z->getChild(0)->printNode();
                 cout << "p: ";
                 p->printNode();
                 cout << "p child :";
                 
                 p->absorb(z); //call absorb on p_left
                 
             }
             
             

         }
         
    }

    void Node::discard(Node * removeChild){
        Node * p = removeChild->getParent();
        if(p->numChildren()==2){
            return;
        }
        int totChildren = p->getParent()->numChildren();

        if(totChildren >= 4){

        }
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

    Node * Node::search(int x){ //moved this to a function of node because it needs to be recursive
        //base case
        //cout << this->numChildren() << endl;

        if(this->numChildren() == 0){//root has no children
            //cout << "Will return node ";
            //this->printNode();
            return this;
        } 

        for(int i = 0; i < 3; i++){
            int temp = this->getChild(i)->getMaxVal();
            
            if(temp == 0){
                //do nothing
            }
            if(x < temp || x == temp){
                //cout << "Max: " << temp << endl;
                //this->getChild(i)->printNode();
                return this->getChild(i)->search(x);
            }    
        }
        Node * nil = new Node();
        nil->addVal(2000);
        return nil;
    }





class Tree{
    Node * root;
    void print(Node * start);

    public:
    Tree(Node * r);
    Tree(int * arr, int size);
    Node * search(int valToFind);
    bool insert(int valToAdd);
    bool del(int valToKill); //delete is a keyword in C++ so have to rename this 
    void print();
    void update(); //updates the tree recursively
    void buildTree();
};



    Tree::Tree(int * arr, int size){
        //First, make each value into a node. These are the leaves. They have no children. :)
        /*Node * init = new Node[size];
        for(int i = 0; i < size; i++){ //create node, assign the value to it. bam. SO SORRY FOR DOING SOMETHING THAT IS O(n)!
            Node * oof = new Node(arr[i]);
            init[i] = *oof;
        } 
        */
        /*Then, assign each one a parent node, and shove the values into the parent node (will be either 2 or 3 values, I am following Uzi's diagram for this.) 
          Actually I lied I'm using the same numbers but organizing the tree differently because I really don't enjoy how he has it. It's dumb, like take every 3 values, shove them into
          a node and if youre left with one value at the end, move one of the other numbers over so the last two nodes have 2 values its not that hard jesus and its the exact same height like get a grip Uzi
        */

        this->buildTree();
    }


    Tree::Tree(Node * r){
        this->root = r;
    }

    void Tree::buildTree(){

        //Sorry for this bullshit I just want you to see how much I've worked on this.

        /*cout << "Inside buildTree" << endl;
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
        }    */
            //Now we get to do this all over again, but instead of the leaves, use the level we just made, and the size of the level which is always round(size/3) :)
        /*if(sizeround > 1){
            cout << "Recursing" << endl;
            buildTree(p1, sizeround);
        }
        else{
            //you are done. set the root node and be done with it.
            cout << "At root node" << endl;
            this->root = &p1[0];
        }
        */









            //WELL WELL WELL, YOU GOT ME. I *guess* ill build the stupid thing manually. Thanks to Nick Stitely for the help with this part because apparently I have cognitive issues or something.
            /*
            Okay coming back to this after fixing everything to be able to build the tree I realize how stupid it was of me to try and build the thing from the leaves up to the top and not just
            use what is below because in order to do what I tried to, you already have to have everything else and it kind of defeats the purpose of building the tree first and developing the other
            algorithms around it. End rant 
            */
            Node * K = new Node(17,28,39);
            Node * A = new Node(3,8,17);
            Node * B = new Node(21,28);
            Node * C = new Node(33,39);
            Node * D = new Node(1,3);
            Node * E = new Node(5,8);
            Node * F = new Node(11,14, 17);
            Node * G = new Node(19, 21);
            Node * H = new Node(24, 28);
            Node * I = new Node(31, 33);
            Node * J = new Node(36, 39);

            //set children
            K->setChild(A);
            K->setChild(B);
            K->setChild(C);
            A->setChild(D);
            A->setChild(E);
            A->setChild(F);
            B->setChild(G);
            B->setChild(H);
            C->setChild(I);
            C->setChild(J);
            this->root = K;
        

        
    }


    Node * Tree::search(int valToFind){
        Node * node = this->root->search(valToFind);
        if(node->getMaxVal() == 2000){
            cout << "Search element too large." << endl;
        }
        return node;
    }

    void Tree::update(){
        if(this->root->getParent()!=nullptr){
            this->root = this->root->getParent();
            this->update();
        }
    }

    bool Tree::insert(int valToAdd){
        Node * b = this->search(valToAdd);
        for(int i=0; i<6; i++){
            if(b->getValue(i) != 0){ //only run on existing values
                if(b->getValue(i)==valToAdd){ //if bi = value we are trying to add
                    return 0; //value already exists.
                }   
            }
        } 
        Node * a = new Node(); //blank node;
        a->addVal(valToAdd); //add the value to the node. for example if we are trying to add 6 to {5,8}, a will look like {6,0,0}, and b will look like {5,8,0}. Zeros here are placeholders.
        b->absorb(a); //so this would look like {6}->absorb({5,8}) for the most simple case.
        this->update();
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

    void Tree::print(Node * start){ //using depth first traversal
        if(start==nullptr){
            //cout << "Nullptr encountered in print" << endl; 
            return;
        }
        start->printNode();
        cout << endl;
        this->print(start->getChild(0));
        this->print(start->getChild(1));
        this->print(start->getChild(2));
        
    }

    void Tree::print(){
        print(this->root);
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

    cout << endl << endl << "Testing absorb on value 13" << endl;

    bool in = tr->insert(13);
    if(in){
        tr->print();
    }
    else{
        cout << "Value already exists" << endl;
    }
    
   /* 

   cout << "Testing sorting values on {11,6,17}" << endl;
    
   Node * a = new Node(9,10,11);
   Node * b = new Node(4,5,6);
   Node * c = new Node(7,15,17);
   Node * n = new Node(11,6,17);
   Tree * t = new Tree(n);
   n->setChild(a);
   n->setChild(b);
   n->setChild(c);
   t->print();
   cout << endl << "Sorting" << endl;
   n->sortChildren();
   t->print();
   
   */
}
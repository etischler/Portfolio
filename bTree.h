#ifndef BTREE_H
#define BTREE_H
#include <string>
#include <iostream>

using namespace std;

//Node for bTree
class node{

private:
    
  string *keys;
  string *values;
  string result;
  node **children; 

   
  int mindegree;
  int size;
  int numkeys;
  bool isLeaf; 

public:

  //node constructor
  node(int min, bool leafans){

      mindegree = min; 
      isLeaf = leafans; 
      
      keys = new string [(2*mindegree)-1];
      values = new string [(2*mindegree)-1];
      children = new node *[mindegree];

      // Initialize the number of keys to 0
      numkeys = 0;

      
      result = "";
  }

    //destructor
    ~node(){
      delete [] keys;
      delete [] values;
      delete [] children;
    }
     
    string getPrev(int);
    string getNew(int);
    string getPrevVal(int);
    string getNewVal(int);

    
    string traverse();//traverses the length of the btree
    
    void moveFoward(int); //moves child pointers one place
    
    void moveBack(int);//moves child pointers one place

    bool search(string _key, string* _Val); //verifies if there is a value in the b tree

    
    void fill(int); //fills the children

    
    void remove(string removevalue);

    void merge(int); //merges two index positions with children

    
    void split(int index, node* fullNode); //will split node when full

    void insertNode(string _key, string value); //insers element into node

    friend class bTree;
};

class bTree{

private:
    node *root; // pointer to the root
    int mindegree, size;      // Minimum degree

public:
    // Constructor
    bTree(int _size){
        root = NULL; // initialize root pointer to point to nothing
        size = _size;
        if(size % 2 == 0) mindegree = size/2;  // Even number of links
        else mindegree = (size-1)/2;      // Odd number of links
    }

    // Destructor
    ~bTree(){
        delete[] root;
    }

  
  void insert(string key, string val); //inserts value into b tree

  
  bool find(string key, string *value); //searches for value in tree. if true returns true, if not false

  bool delete_key(string key); //deletes a key in b tree

  string toStr(); //goes through tree and makes keys into a single return string

};

void bTree::insert(string key, string val){
    
    if(root == NULL){//root case
        
        root = new node(mindegree, true);
        root->keys[0] = key;    
        root->values[0] = val; 
        root->numkeys = 1; 
    }
    else{ //if tree not full
        if(root->numkeys == (2 * mindegree)-1){
        
            node *nroot = new node(mindegree, false); //allocates memory for new root
            nroot -> children[0] = root;
            nroot -> split(0, root);
      int i = 0;
            if(nroot->keys[0] < key){
                i++;
            }
            nroot->children[i]->insertNode(key, val);
            root = nroot;
        }
        
        else{
            root -> insertNode(key, val); //if its not full it will insert new value into node
        }
    }
}

bool bTree::find(string key, string *value){ //self explanatory
    if (root == NULL){
        return false;
    }
    else{
        return root->search(key, value);
    }
}

bool bTree::delete_key(string key){
    if(!root){
        return false;
    }

    
    root->remove(key);

    //if node has zero keys it will make its child the new root
    if(root -> numkeys == 0){
        node *temp = root;
        if(root->isLeaf){
            root = NULL;
        }
        else{
            root = root->children[0];
        }
        
        delete temp; //delete the old root
    }
    return true;
}


string bTree::toStr(){ //makes the print out into one return string
    string output = ""; 
    if(root!= NULL){
        //if(root->traverse()==""){
        output += root->  traverse();
       // }
    }
    return output;
}


string node::getPrev(int index){
   
    node *tempcurrent = children[index];

    while(!tempcurrent->isLeaf){
        tempcurrent = tempcurrent->children[tempcurrent->numkeys]; //recurses through until it gets leaf and then gets value in leaf
    }
    
    return tempcurrent->keys[tempcurrent->numkeys - 1];
}

string node::getPrevVal(int index){
    
    node *current = children[index];
    while(!current->isLeaf){
        current = current->children[current->numkeys]; //same as last method but opposite
    }
    
    return current->values[current->numkeys - 1];
}

string node::getNew(int index){
    
    node *current = children[index + 1];
    while (!current->isLeaf){
        current = current->children[0]; //recurses until it gets to new leaf and gets value
    }
  
    return current->keys[0];
}

string node::getNewVal(int index){
    
    node *current = children[index + 1];
    while(!current->isLeaf){
        current = current->children[0]; //recurses through until it gets the new value
    }
    
    return current->values[0];
}
 
string node::traverse(){ //necessary for toStr, it goes through nodes in tree and gets values
    string tempval = "";
    int i;
    
    for(i = 0; i < numkeys; i++){
        if(!isLeaf){
            tempval += children[i]->traverse(); //goes thorugh tree and appends the values to string
        }
        tempval += keys[i] + "\n";
    }
    if(!isLeaf){
        tempval += children[i]->traverse();
    }
    return tempval;
}


bool node::search(string key, string* value){ //searches for value
    int j = 0;

    
    while(j < numkeys && key > keys[j]){ //where location would be search
        j++;
    }

   
    if(j != numkeys && !keys[j].compare(key)){ //check if key there
        *value = values[j];
        return true;
    }
    
    if(isLeaf){
        return false; //if it reaches the end then key not there
    }
    return children[j]->search(key, value);
}

void node::insertNode(string key, string value){
    
    int j = numkeys -1;
    
    if(isLeaf){
       
        while(j>=0 && keys[j]>key){ //insertion into the node
            keys[j + 1] = keys [j];
            values[j + 1] = values[j];
            j--;
        }
    
    keys[j + 1] = key;
    values[j + 1] = value;
    numkeys = numkeys + 1;
    }
    else {
        
        while (j>= 0 && keys[j]>key){//finds the child that the key will be assigned to
            j--;
        }
            
            if(children[j + 1]->numkeys == (2*mindegree -1)){ //if child full split
                
                split(j+1, children[j + 1]);
                
                if(keys[j + 1] < key){ //middle key goes up and children are split
                    j++;
                }
            }
        children[j + 1]->insertNode(key, value);
    }
}


void node::moveFoward(int index){//move child pointers forward one place
    node *child = children[index];
    node *sibling= children[index-1];
    
    for(int j = child->numkeys-1; j >= 0; j++){
        child->keys[j+1] = child->keys[j];
        child->values[j+1] = child->values[j];
    }
    
    if (!child->isLeaf){
        for(int j = child->numkeys; j >= 0; j++){ //moves all child pointers too
            child->children[j + 1] = child->children[j];
        }
    }
    
    child->keys[0] = keys[index-1]; //sets first child's key to keys[index-1]
    child->values[0] = values[index-1];
    
    if(!isLeaf){
        child->children[0] = sibling->children[sibling->numkeys];
    }
   
    keys[index-1] = sibling->keys[sibling->numkeys-1]; //moves key from sibling to parent
    child->numkeys += 1;
    sibling->numkeys -= 1;
    return;
}
void node::moveBack(int index){ 
//move child pointer back one place
    node *child = children[index];
    node *sibling = children[index+1];

    child->keys[(child->numkeys)] = keys[index];
    child->values[(child->numkeys)] = values[index];
    // insert the first child pointer of sibling's to the children of the child's pointer
    if(!(child->isLeaf)){
        child->children[(child->numkeys) + 1] = sibling->children[0];
    }
    //the first key from sibling is inserted into keys[index]
    keys[index] = sibling->keys[0];
    values[index] = sibling->values[0];
    // move sibling keys and values back one position
    for(int j = 1; j< sibling->numkeys; ++j){
        sibling->keys[j-1] = sibling->keys[j];
        sibling->values[j-1] = sibling->values[j];
    }
    // move child pointers back one position
    if(!sibling->isLeaf){
        for(int j = 1; j <= sibling->numkeys; ++j){
            sibling->children[j-1] = sibling->children[j];
        }
    }
    
    child->numkeys += 1; //increases keys in child but removes from sibling
    sibling->numkeys -= 1;
    return;
}

void node::split(int index, node *fullNode){ //if node full split
    
    node *newNode = new node(fullNode->mindegree, fullNode->isLeaf);
    newNode->numkeys = mindegree - 1;
    //Copy keys from full node to newNode
    for(int i = 0; i< mindegree -1; i++){
        newNode->keys[i] = fullNode->keys[i + mindegree];
        newNode->values[i] = fullNode->values[i + mindegree];
    }
    //Copy children of full node --> newNode
    if(fullNode->isLeaf == false){
        for(int i = 0; i < mindegree; i++) {
            newNode ->children[i] = fullNode ->children [i + mindegree];
        }
    }
    // Update the number of keys in full Node
    fullNode ->numkeys = mindegree - 1;
    // Shift everything in children to the right
    for(int i = numkeys; i >= index + 1; i--){
        children [i + 1] = children [i];
    }
    // Needs to know who its parent is
    // Set new child equal to new node.
    children[index + 1] = newNode;
    // Move all keys and values over one position
    for (int i = numkeys - 1; i >= index; i--){
        keys [i + 1] = keys[i];
        values [i + 1] = values[i];
    }
    // Copy initial middle key and value of fullNode
    keys[index] = fullNode->keys[mindegree - 1];
    values[index] = fullNode->values[mindegree - 1];
    // Increment # of keys
    numkeys++;
}


void node::merge(int index){ //merges two nodes together
    node *child = children[index];
    node *sibling = children[index+1];
    // Move the key and value backward one place in the child array
    child->keys[mindegree-1] = keys[index];
    child->values[mindegree-1] = values[index];
    // Copy the keys and values from the sibling to the child
    for (int j = 0; j < sibling->numkeys; ++j){
        child->keys[j + mindegree] = sibling->keys[j];
        child->values[j + mindegree] = sibling->values[j];
    }
    //Move child pointers to the right one index position
    if(!child->isLeaf){
        for(int j = 0; j <= sibling->numkeys; ++j){
            child->children[j + mindegree] = sibling->children[j];
        }
    }
    //fills gap after moving child pointers
    for(int j = index+1; j < numkeys; ++j){
        keys[j-1] = keys[j];
        values[j-1] = values[j];
    }

    //moves child pointer to index+1
    for(int j = index + 2; j <= numkeys; ++j){
        children[j-1] = children[j];
    }
    // Updating the number of keys for the child
    child->numkeys += sibling->numkeys + 1;
    numkeys--;

    // delete the sibling because you no longer need it
    delete(sibling);
    return;
}
// A function to fill child's child pointers
void node::fill(int index){
    // if the index-1 position has enough space, borrow one of their child pointers
    if(index!=0 && children[index - 1]->numkeys >= mindegree){
        moveFoward(index);
    }
    // otherwise take from the other side of the index position
    else if(index != numkeys && children[index + 1]->numkeys >= mindegree){
        moveBack(index);
    }
    // Merge child and sibling
    else{
        if(index != numkeys){
            merge(index);
        }
        else{
            merge(index-1);
        }
    }
    return;
}
// remove the key from the sub-tree rooted with this node
void node::remove(string key){
  int index = 0;
  while(index<numkeys && keys[index] < key){
    ++index;
  }
    // check if the key that will be removed is present
    if(index < numkeys && keys[index] == key){
        // check if the node is a leaf
        // remove it and shift everything back a position
        // which replaces the old values
        if(isLeaf){
                //Replace values
            for(int j = (index + 1); j < numkeys; j++){
                keys[j-1] = keys[j];
                values[j-1] = values[j];
            }
        // Reduce count of keys
        numkeys--;
        //break
        return;
        }
        // if it is not a leaf
        // consider everything under this node
        else {
            string tempKey = keys[index];
            string tempValue = values[index];
            // check if there are keys in the child pointer array
            // get the values and overwrite what is at
            // the index position with what
            if(children[index]->numkeys >= mindegree){
                string prev = getPrev(index);
                string prevVal = getPrevVal(index);
                keys[index] = prev;
                values[index] = prevVal;
                children[index]->remove(prev);
            }
            // check to see if the next position meets the
            // same requirements and if it does you must overwrite with
            // the succeeding values
            else if(children[index + 1]->numkeys >= mindegree){
                string New = getNew(index);
                string newVal = getNew(index);
                keys[index] = New;
                values[index] = newVal;
                children[index + 1]->remove(New);
            }
            // otherwise neither of the children have many keys so they can be removed and then you can remove what is at the child pointer at the given index position
            else{
                merge(index);
                children[index]->remove(key);
            }
            //break
            return;
        }
    }

    // possibility key is not in the tree
    else{
        //the key is not present in tree
        if (isLeaf){
            return;
        }
        // check if The key to be removed is rooted in a subtree
        bool flag = ((index==numkeys)? true : false );
        // fill the child where the key belongs
        if (children[index]->numkeys < mindegree)
            fill(index);
        // determines if the past child has been merged and removes the child at the appropriate index position
        if(flag && index > numkeys){
            children[index-1]->remove(key);
        }
        else{
            children[index]->remove(key);
        } 
    }
}

#endif // BTREE_H
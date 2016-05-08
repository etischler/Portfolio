#include <iostream>
#include <string>
using namespace std;
class node{ // this will create new nodes for the linked list
public:
	
    int index;
	string elementstored; //necessary private variables
	node* next;

    node(int index, string elementstored){ //to make new node it must have index and element to be stored
        
	    this->index = index; //the current index
		this->elementstored = elementstored; //the current element stored in this index
	    this->next = NULL; //setting the next pointer to null so the program knows that it has reached the end of the array
    }
};

class HashTable{  //code for hashtable with chaining
private:
/*typedef struct node{
string elementstored;
node*next;
}* node*;*/
					//ended up not being neccessary
//node* head;
//node* current;
//node* temp;

node** htable; //must make double pointer to make an array of pointers

//node* n;

int hash_table_size;

public:

HashTable(int size){ //constructor for hashtable
	//hasharray[size];
	//head[size];
	//current[size];
	//temp[size];
	hash_table_size = size;
	//cout<<"size: "<<size<<	endl;
	/*for(int i = 0; i<size;i++){
		head[i]=NULL;
		current[i]=NULL; //otherwise will point to random places
		temp[i]=NULL;
	}
	for(int i =0; i<size;i++){
		cout<<"head i: "<<head[i]<<endl;
	}*/
	//head=NULL;
	//current=NULL;

	htable = new node*[size]; //makes the array of pointers
	for(int i = 0; i<size;i++){
		htable[i]=NULL;				//neccessary for c++ otherwise pointers would be random
	}

}

~HashTable(){
/*delete[] hasharray;
delete[] head;
delete[] current;
delete[] temp;*/
//delete[] hasharray;
//delete next;
	for (int i = 0; i < hash_table_size; i++){
  		node* current = htable[i];
    	while (current != NULL){
        	node* previous = current;					//sets all pointers to null to prevent memory leaks
    		current = current->next;
        	delete previous;
    	}
   	}
    delete[] htable; //neccessary to not have memory leaks
}
void AddNode(string newstring, int hashvalue){ //will add a node into the linked list
	
	/*node* n = new node;
	n->next = NULL;
	n->elementstored = newstring;
	//cout << "head[hv]=" << head[hashvalue] << endl;
	if(head[hashvalue] != NULL){
		cout<<"this is somehow happening"<<endl;
		current[hashvalue] = head[hashvalue];
		while(current[hashvalue]->next != NULL){
			current[hashvalue] = current[hashvalue]->next;
		}
		current[hashvalue]->next = n;
	}															//ended up not being neccessary
	else{
		head[hashvalue] = n;
		//head[0]=NULL;
		cout<<"head[hashvalue]:  "<<head[hashvalue]<<endl;
	}
	//delete n;
	for(int i =0; i<10;i++){
		cout<<"head i: "<<i<<"\t"<<head[i]<<endl;
		/*for(node* curr = head[i]; curr!=NULL; curr=curr->next){
			cout<<current<<"\t";
		}
	}*/


    node* previous = NULL;
    node* current = htable[hashvalue]; //inserts new node into the begginning of the linked list
    while (current != NULL){
        previous = current;
        current = current->next;
    }
    if (current == NULL){
        current = new node(hashvalue,newstring);
        if (previous == NULL){
            htable[hashvalue] = current;			//updates pointers once new node is inputted
        }
    else{
            previous->next = current;
        }
    }
    else{
        current->elementstored = newstring;
    }
    /*for(int i =0; i<10;i++){
		while(current!=NULL){
			//cout<<current->elementstored<<endl;
			current->next;

		}
		
	}*/

}

bool Determination(string searchvalue,int index){ //will determine wether
	bool valuefound = false;
    node* current = htable[index];
    while (current != NULL){
        if (current->elementstored == searchvalue){  //goes through elements to see if value is found, if it is it returns yes
            valuefound = true;
            return true;
        }
        current = current->next;
    }
        if (valuefound==false){
            return false;
        }
}



int hash_function(string key, int hash_table_size){				//code given to us in the prompt
	int index = 0;
		for (int i=0; i<key.length(); i++){
			index += key[i];
			
		}
		//cout<<"this happens"<<endl;
		//cout<<"Hash function index: "<<index % hash_table_size<<endl;
		return index % hash_table_size;
}

};

int main(){
	//HashTableWithLinkedList hash;
	int hash_table_size;
	cin>>hash_table_size; // this will take in the first intiger being the initial number of elements
	//HashTable hash(hash_table_size); //this will pass the size of the hash table
	HashTable *hash = new HashTable(hash_table_size);
	int choice;
	cin>>choice; //must be at begginning of while loop to accept first selection of choice
	while(choice==1 || choice==2){
		if(choice==1){
			string hashinput;
			cin>>hashinput;
			int index = hash->hash_function(hashinput,hash_table_size);
			hash->AddNode(hashinput, index);

		}													//rather self explanatory, either searches or adds node
		if(choice==2){
			string searchinput;
			cin>>searchinput;												
			int index = hash->hash_function(searchinput,hash_table_size);
			if(hash->Determination(searchinput, index) == true){
				cout<<"Yes"<<endl;
			}
			else{
				cout<<"No"<<endl;
			}
		}


		cin>>choice; //must be at the end of while loop to get the new value of choice
	}
	//delete hash;
	delete hash;
	return 0;	
}
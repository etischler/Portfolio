#include <iostream>
#include <stdio.h>
using namespace std;

class UnionFind
{
	
	public:
	
	

		

		
	
	
	int Find(int p, int q , int n){  //finds the value of p in id array
	int i;
	int id[n];
	for(i=0; i <n; i++) id[i]=i;
		int t = id[p];
		if(t=id[q]){
		for(i=0;i<n;i++)
			if(id[i]==t){ id[i] = id[q];}
			
			return id[p];
			
		}
	}
	int Find2(int p, int q , int n){//finds value of q in id array
	int i;
	int id[n];
	for(i=0; i <n; i++) id[i]=i;
		int t = id[p];
		if(t=id[q]){
		for(i=0;i<n;i++)
			if(id[i]==t){ id[i] = id[q];}
			
			return id[q];
			
		}
	}


	void Union(int p, int q, int n){//implementation of weighted quick union based on the book 
		int i, j, id[n], sz[n];
		for (i=0;i<n;i++) {id[i]=i; sz[i]=1;}
			for(i=p; i!= id[i]; i=id[i])
				id[i] = id[id[i]] ;
			for(j=q; j!=id[j]; j=id[j])
				id[j] = id[id[j]] ;
			if(i==j);

		if(sz[i] < sz[j]){    // beginning of weight implementation
			id[i] = j;
			sz[j] += sz[i];
		}
		else{
			id[j] = i;
			sz[i] += sz[j];
		}
		cout<<"Union made"<<endl;  // lets user know union has been made


	}	
	// Connected(x, y)?
	bool Connected(int x, int y, int n){ //gives the boolean of whether there is a "connection" between the asked about computers
	if(Find(x,y,n)==Find2(x,y,n)){
		cout<<"true"<<"\n";
		return true;
		

	}
	else{
		cout<<"false"<<"\n";
		return false;

	}
	}
};

int main(void){
 int n;
 int op, x, y, inputchoice;
cout<<"If you are using an input file input 1. If you are inputting yourself, input 2"<<"\n"; //allows user to decide type of input
cin>>inputchoice;
if(inputchoice==1){ //file input
 string str;
 cin>>str;
const char * c = str.c_str(); //allows user to type filename in terminal
 freopen(c ,"r", stdin);
 scanf("%d", &n);
UnionFind uf;
 while (3 == scanf("%d %d %d", &op, &x, &y)){

 //printf("%d %d %d\n", op, x, y); // prints all numbers from input file
 if (op == -1 && x == -1 && y == -1) break; // -1 -1 -1 is the last line and will break when it reaches this line

 if (op==0) // Connect/ Union
 {
 	uf.Union(x,y,n);
 }
 if(op==1) // Connected/ Find
 {
uf.Connected(x,y,n);
 		

 }
 }
}
if(inputchoice==2){ // allows user to manipulate with own numbers
	UnionFind uf;
 cin>>n;
 while(true){
 	cin>>op>>x>>y;
 if (op == -1 && x == -1 && y == -1) break; // -1 -1 -1 is the last line and will break when it reaches this line

 if (op==0) // Connect/ Union
 {
 	uf.Union(x,y,n);
 }
 if(op==1) // Connected/ Find
 {
uf.Connected(x,y,n);
 		

 }
 }
}

 return 0;
}


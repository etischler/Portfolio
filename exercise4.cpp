#include <iostream>
#include <limits.h>
using namespace std;
const int inf = INT_MAX/2-1;




void floydWarshall(int n, int ** graph, int **parent){ //changes the array of graph to be the cost of going from i to j
	for(int i =0; i < n;i++){							//also changes the array of parent to recurse to get path
		for(int j = 0; j <n; j++){
			if(i==j || graph[i][j]==inf){
				parent[i][j]=-1;
			}
				
			else{
				parent[i][j]=i+1;
				//cout<<i<<endl;
			}
		}
	}

	for(int k = 0; k < n; k++){
		for(int i = 0; i < n; i++){
			for( int j = 0; j < n; j++ ){
				int newD = graph[i][k] + graph[k][j];
				//cout<<"newD = graph[i][k] + graph[k][j]: "<<newD<<" = "<<graph[i][k]<<" + "<<graph[k][j]<<endl;
				if(newD < graph[i][j] ){
					if(newD>=inf/2){
						graph[i][j] = inf;
						//parent[i][j] = parent[k][j]; //same as top comment
					}
					else{
						graph[i][j] = newD;
						parent[i][j] = parent[k][j];
					}
				}
			}
		}
	}

}






int main(){
	
//first input
int n;
int e;
int q;
cin>>n;
cin>>e;
cin>>q;
int **graph;
int **parent;
graph = new int *[n];
parent = new int *[n];
for(int i=0;i<n;i++){
	graph[i]= new int [n];
	parent[i]= new int[n]; //necessary to make pass a two dimensional array to a function
}

//for loop must be here for the description of the E edges
for(int i = 0; i < n; i++){
	for(int j=0;j<n;j++){
		if(i==j){
			graph[i][j]=0;
		}
		else{
			graph[i][j]=inf;		//in this case it will set all values to infinity or zero as necessary. infinity will be removed if edges are put in
		}
	}

}
//cout<<"exits first loop"<<endl;
for(int k =0; k <e;k++){
	int _i; //the edges selected to be placed in the i and j spots.
	int _j;
	int weight;
	cin>>_i;
	cin>>_j;
	cin>>weight;
	_i-=1;
	_j-=1;

	for(int i =0; i <n; i++){
		for(int j =0;j<n;j++){
			if(i!=j){
				if(_i<n && _j <n){
					graph[_i][_j]=weight; //will set all other values to the weight
				}
			}
		}
	}
}
//cout<<"exits second loop"<<endl;
/*
cout<<"first graph print"<<endl;
for(int i = 0; i <n;i++){ //printing to make sure input entered corretly;
	for(int j=0;j<n;j++){
		if(graph[i][j]!=inf)
			cout<<graph[i][j]<<"\t";
		else
			cout<<"inf"<<"\t";
	}
	cout<<endl;
}
cout<<"\n\n\n"<<endl; //this will allow for there to be space before the other print*/

floydWarshall(n,graph,parent);/*
cout<<"second graph print"<<endl;
for(int i = 0; i <n;i++){ //printing to make sure input entered corretly;
	cout<<"i: "<<i+1<<"|"<<"\t";
	for(int j=0;j<n;j++){
		if(graph[i][j]!=inf)
			cout<<graph[i][j]<<"\t";
		else
			cout<<"inf"<<"\t";
	}
	cout<<endl;
}
//cout<<"\n"<<inf<<"\t"<<inf/2<<endl;
cout<<"\n\n\n"<<endl;
cout<<"parent print"<<endl;
for(int i = 0; i <n;i++){ //printing to make sure input entered corretly;
	cout<<"i: "<<i+1<<"|\t";
	for(int j=0;j<n;j++){
		if(parent[i][j]!=inf)
			cout<<parent[i][j]<<"\t";
		else
			//cout<<
			cout<<"inf"<<"\t";
	}
	cout<<endl;
}*/
int pathtracker[n];
int numinpath;
bool nopath;
for(int k=0; k<q;k++){ //for number of queries
	nopath=false;
	int _i;
	int _j;
	cin>>_i;
	cin>>_j;
	pathtracker[0]=_j; //first value won't be picked up in for loop
	//cout<<pathtracker[0]<<endl;;
	numinpath=1;
	_i-=1;
	_j-=1;
	for(int b = 1;b<n;b++){
		//cout<<"this happens"<<endl;
		pathtracker[b]=parent[_i][_j];
		if(_i==_j){
			cout<<"cost = 0"<<endl;
			nopath=true;
			if(k==q-1){
				cout<<_i+1<<"-"<<_j+1; //if i equals j then path to itself
				break;
			}
			cout<<_i+1<<"-"<<_j+1<<endl;

			break;
		}
		if(parent[_i][_j]==-1){
			if(k==q-1){
				cout<<"NO PATH"; //if parent is -1 then no path
			nopath=true;
				break;
			}
			cout<<"NO PATH"<<endl; //same but space issue so this also needed
			nopath=true;
			break;
		}
		//cout<<parent[_i][_j]<<endl;
		//cout<<_i<<endl;
		//cout<<"passes"<<endl;
		numinpath+=1;
		_j=parent[_i][_j]-1;
		//cout<<_j<<"cdscs"<<endl;
		if(_j==_i){
			//cout<<"happens"<<endl; //stops other stuff from happening
			break;
		}
	}
	if(!nopath){
		int cost = 0;
		//cout<<"fault no here"<<endl;
		for(int r=0;r<q;r++){
			cost=0;
			
			for(int b=numinpath-1;b>0;b--){
				//cout<<pathtracker[b]<<endl;
				//cout<<graph[pathtracker[b]-1][pathtracker[b-1]-1]<<endl;
				cost+=graph[pathtracker[b]-1][pathtracker[b-1]-1]; //sums up the cost after path figured out
			}
		}
		cout<<"cost = "<<cost<<endl;

		for(int z =numinpath-1;z>-1;z--){
			if(z==0){
				if(k==q-1){
					cout<<pathtracker[0];
					break;
				}
				cout<<pathtracker[0]<<endl; //prints the path
				break;
			}
			cout<<pathtracker[z]<<"-";

		}
	}
}

cout<<endl;

	return 0;
}
#include <iostream>
#include <algorithm> //necessary for sort of numbers
#include <cstdlib>   //necessary for stuff like exit
#include <ctime>	//necessary for time calculations in code
#include <time.h>

using namespace std;


void LinearSearch(int list[],int searchnumbersarray[],int numberofelements, int amountsearchnumbers){
	/*for(int i = 0; i<numberofelements;i++){ //was used to make sure array was being created correctly
		cout<<list[i]<<"  ";
		if(i==numberofelements-1){			
			cout<<endl;
		}
	}
	for(int i = 0; i<amountsearchnumbers;i++){ //was used to make sure array was being created correctly
		cout<<searchnumbersarray[i]<<"  ";
		if(i==amountsearchnumbers-1){			
			cout<<endl;
		}
	}*/ //this was necessary for debugging ^

	cout<<"Linear Search:"<<endl;
	bool avaluefound;
	

	for(int i = 0; i<amountsearchnumbers;i++){	
		avaluefound=false;				//as it iterates through the list of elements it will check if any
		//clock_t startTime = clock();
		for(int j =0; j < numberofelements; j++){		// of the search numbers matches
			if(list[j]==searchnumbersarray[i]){
				if(avaluefound==false){ //if a value hasn't already been found it will print yes
					cout<<"Yes"<<endl;
					avaluefound = true;		
					j=numberofelements; //this will end the loop if a match is found
					//cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
				}
			}
			if(avaluefound==false && j==numberofelements-1){
				cout<<"No"<<endl;								//if no match found it will print no at end
				//cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
			}
		}
	}
	
}

void BinarySearch(int list[],int searchnumbersarray[],int numberofelements, int amountsearchnumbers){
	cout<<"Binary Search: "<<endl;
	//sort(list,list + numberofelements); //this will now sort the list necessary for binary search
	//cout<<"test"<<endl;
	for(int i = 0; i<amountsearchnumbers;i++){//will do binary search each time for every value in search array
		//clock_t startTime = clock(); //will start new clock time here 	Edit: this is not neccessary here.
		//cout<<"test"<<endl;
		int low =0;
		//cout<<"test"<<endl;
		int high = numberofelements-1; //must be minus one because its from 0 to numberelements minus 1
		//cout<<"test"<<endl;
		int mid;
		bool avaluefound=false;
		while(low<=high){ //once this changes we don't want to keep looping
			mid = (low + high)/2;
			//cout<<"test"<<endl;
			if(searchnumbersarray[i]==list[mid]&&avaluefound==false){
				cout<<"Yes"<<endl;
				avaluefound=true;
				//cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
			}
			else if(searchnumbersarray[i]>list[mid]){
				low = mid+1;
			}
			else{
				high = mid-1;
			}
		} //must do for loop starting above int low statement then write code for binary search
		if(avaluefound==false){
			cout<<"No"<<endl;
			//cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
		}
	}
}

int main(){
	//begin first line

	int numberofelements,amountsearchnumbers;
	cin>>numberofelements>>amountsearchnumbers;
	//cout<<"numberofelements: "<<numberofelements<<"\t"<<"amount of search numbers: "<<amountsearchnumbers<<endl; //was used to make sure that I didn't need a scan for numbers
	int list[numberofelements];
	int searchnumbersarray[amountsearchnumbers];
	for(int i = 0; i<numberofelements;i++){ //this will create an array with each element inserted after space
		cin>>list[i];
	}
	for(int i = 0; i<amountsearchnumbers;i++){ //this will create an array with each search number inserted after space
		cin>>searchnumbersarray[i];
	}
	//sort(searchnumbersarray,searchnumbersarray + amountsearchnumbers);
	/*for(int i = 0; i<numberofelements;i++){ //was used to make sure array was being created correctly
		cout<<list[i]<<"  ";
		if(i==numberofelements-1){			
			cout<<endl;
			cout<<endl;
			cout<<endl;
			cout<<endl;
		}
	}
	for(int i = 0; i<amountsearchnumbers;i++){ //was used to make sure array was being created correctly
		cout<<searchnumbersarray[i]<<"  ";
		if(i==amountsearchnumbers-1){			
			cout<<endl;
		}
	}*/
	/*Searches searches;
	searches.LinearSearch();	// make sure that you do not have to delete anything for memory leaks!!!
	searches.BinarySearch();*/   //ended up not being necessary. can create functions outside of main without new class
	cout<<"number of elements: "<<numberofelements<<"\t"<<"amount search numbers: "<<amountsearchnumbers<<endl;
	clock_t startTime = clock(); //starting clock before i call linear search and printing time after. This should give me a realistic time for how long linear search takes
	LinearSearch(list,searchnumbersarray,numberofelements,amountsearchnumbers);	//these functions will be called in the right order to produce the output
	//cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;//will print out time taken to execute. no need to end as long as it is reset before binary search 
	//int sortedlist[numberofelements]=sort(list,list + numberofelements); //will sort the elements for binary search
	sort(list,list + numberofelements); //i will do this before starting the clock to not affect times
	clock_t startTime2 = clock(); //withll reset clock and start counting for binary search. sort is not included because we do not want it to add on to the computation time
	BinarySearch(list,searchnumbersarray,numberofelements,amountsearchnumbers);    
	//cout << double( clock() - startTime2 ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
		//delete[] list;
		//delete[] searchnumbersarray; //not necessary because program 
	return 0;
}
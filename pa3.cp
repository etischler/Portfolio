#include <iostream>
#include <cstdlib>
#include <string>
#include <stack>
#include <math.h>
using namespace std;




int main(){
	
	//create stacks
	stack<double> numberstack;
	stack<double> operatorstack;
	operatorstack.push(1.0);

	//begin with input of string
	string stringinput;
	getline(cin,stringinput);
	//variables for following for statement
	int leftparenthesiscount = 0;
	int rightparenthesiscount =0;
	int timetodooperation =0;
	int numbersback=0; //will help with doubles for input
	int operatorsinarow=0; // will help with doubles for input
	int logtracker=0;
	int sintracker=0;
	int costracker=0;
	int sqrtracker=0;
	int negnumcount=0; // will tack when to count negative sign and when not to
	string logstring = "log";
	string sinstring = "sin";
	string cosstring = "cos";
	string sqrtstring = "sqrt";
	string negnumstring = "(-"; 

	
		for(int i =0; i<stringinput.size(); i++){
			//poor input of ( or ) by user checking
			//cout<<logtracker<<endl;
			char stringinputchar = stringinput.at(i);
			double doublevaluestringinputchar = double(stringinputchar);

			if(stringinput.substr(i,2)==negnumstring){
				negnumcount=1;
			}
			
			if(doublevaluestringinputchar == 41.0){
				rightparenthesiscount+=1;

				
			}
			if(doublevaluestringinputchar==40.0){
				leftparenthesiscount+=1;
			}
			//stop the )( situation
			if((doublevaluestringinputchar == 41.0 || doublevaluestringinputchar == 40.0) && leftparenthesiscount<rightparenthesiscount){
				cout<<"Error: Unbalanced parenthesis!!!"<<endl;
				exit(0);
			}
			//fail safe for not equal parenthesis
			if(leftparenthesiscount!=rightparenthesiscount && i==stringinput.size()-1){
				cout<<"Error: Unbalanced Parenthesis!!!"<<endl;
				exit(0);

			}
			//determine how many numbers back is number
			if((doublevaluestringinputchar>47.0 && doublevaluestringinputchar<58.0) || doublevaluestringinputchar == 46.0 || doublevaluestringinputchar==32.0){ //for numbers or periods
				numbersback+=1;
				operatorsinarow=0;
			}
			if(doublevaluestringinputchar==48.0 && (stringinput.at(i-1)<=47.0|| stringinput.at(i-1)>=58.0) && (stringinput.at(i+1)<=47.0 || stringinput.at(i+1)>=58.0)){
				numberstack.push(0);
			}
			
			if(doublevaluestringinputchar==40.0 || doublevaluestringinputchar==41.0 || doublevaluestringinputchar == 43.e0 || doublevaluestringinputchar == 45.0 || doublevaluestringinputchar == 42.0 || doublevaluestringinputchar == 47.0 || doublevaluestringinputchar== 94.0 ){
				operatorsinarow++; 

				if(operatorsinarow==1){
				double d = atof(stringinput.substr(i-numbersback,i).c_str());
				
				
				if(d !=0){

				numberstack.push(d);
				
				
				}
			}
				numbersback=0;
			}

			//begin code for functions
			if((doublevaluestringinputchar == 43.0 || doublevaluestringinputchar == 45.0 || doublevaluestringinputchar == 42.0 || doublevaluestringinputchar == 47.0 || doublevaluestringinputchar== 94.0) && negnumcount==0){
				timetodooperation+=1;
				operatorstack.push(doublevaluestringinputchar);
			}
			
			if(stringinput.substr(i,3)==logstring){
				logtracker=1;
			}
			if(stringinput.substr(i,3)==sinstring){
				sintracker=1;
			}
			if(stringinput.substr(i,3)==cosstring){
				costracker=1;
			}
			if(stringinput.substr(i,4)==sqrtstring){
				sqrtracker=1;
			}
			
			if(doublevaluestringinputchar==41.0 && logtracker==1){
					logtracker=0;
					double x = numberstack.top();
					numberstack.pop();
					double logresult = log(x);
					numberstack.push(logresult);

			}
			if(doublevaluestringinputchar==41.0 && sintracker==1){
					sintracker=0;
					double x = numberstack.top();
					numberstack.pop();
					double y = ((x*3.14159265359)/180);
					double logresult = sin(y);
					//double finalresult = ((logresult/3.14159265359)*180);
					//numberstack.push(finalresult);
					numberstack.push(logresult);

			}
			if(doublevaluestringinputchar==41.0 && costracker==1){
					costracker=0;
					double x = numberstack.top();
					numberstack.pop();
					double y = ((x*3.14159265359)/180);
					double logresult = cos(y);
					//double finalresult = ((logresult/3.14159265359)*180);
					//numberstack.push(finalresult);
					numberstack.push(logresult);

			}
			if(doublevaluestringinputchar==41.0 && sqrtracker==1){
					
					
					sqrtracker=0;
					double x = numberstack.top();
					numberstack.pop();
					double logresult = sqrt(x);
					numberstack.push(logresult);
				
					

			}

			if(doublevaluestringinputchar == 41.0 && timetodooperation>0 && logtracker==0 && sintracker ==0 && costracker ==0 && sqrtracker ==0 && negnumcount==0){
				
				if(operatorstack.top()==43.0){
				double a = numberstack.top();
				numberstack.pop();
				double b = numberstack.top();
				numberstack.pop();
				double sum = a + b;
				
				numberstack.push(sum);
				timetodooperation-=1;
				operatorstack.pop();
				

				}
				if(operatorstack.top()==94.0){
				double a = numberstack.top();
				numberstack.pop();
				double b = numberstack.top();
				numberstack.pop();

				double sum = pow(b,a) ;
				
				numberstack.push(sum);
				timetodooperation-=1;
				operatorstack.pop();
				

				}
				if(operatorstack.top()==45.0){
				double a = numberstack.top();
				numberstack.pop();
				double b = numberstack.top();
				numberstack.pop();
				double sum = b - a;
				
				numberstack.push(sum);
				timetodooperation-=1;
				operatorstack.pop();
				
				}
				if(operatorstack.top()==47.0){
				double a = numberstack.top();
				numberstack.pop();
				double b = numberstack.top();
				numberstack.pop();
				if(a !=0){
				double sum = b / a;
				
				numberstack.push(sum);
				timetodooperation-=1;
				operatorstack.pop();
				}
				if(a == 0.0){
					cout<<"Error: Division by zero!!!"<<endl;
					exit(0);
				}

				}
				if(operatorstack.top()==42.0){
				double a = numberstack.top();
				numberstack.pop();
				double b = numberstack.top();
				numberstack.pop();
				double sum = b * a;
				
				numberstack.push(sum);
				timetodooperation-=1;
				operatorstack.pop();
				
				}

				if(i== stringinput.size()-1 && timetodooperation>0){
				if(operatorstack.top()==43.0){
				double a = numberstack.top();
				numberstack.pop();
				double b = numberstack.top();
				numberstack.pop();
				double sum = a + b;
				
				numberstack.push(sum);
				timetodooperation-=1;
				operatorstack.pop();
				

				}
				if(operatorstack.top()==94.0){
				double a = numberstack.top();
				numberstack.pop();
				double b = numberstack.top();
				numberstack.pop();

				double sum = pow(b,a) ;
				
				numberstack.push(sum);
				timetodooperation-=1;
				operatorstack.pop();
				

				}
				if(operatorstack.top()==45.0){
				double a = numberstack.top();
				numberstack.pop();
				double b = numberstack.top();
				numberstack.pop();
				double sum = b - a;
				
				numberstack.push(sum);
				timetodooperation-=1;
				operatorstack.pop();
				
				}
				if(operatorstack.top()==47.0){
				double a = numberstack.top();
				numberstack.pop();
				double b = numberstack.top();
				numberstack.pop();
				if(a!=0){
				double sum = b / a;
				
				numberstack.push(sum);
				timetodooperation-=1;
				operatorstack.pop();
				}
				if(a==0.0){
					cout<<"Error: Division by zero!!!"<<endl;
					exit(0);
				}
				
				}
				if(operatorstack.top()==42.0){
				double a = numberstack.top();
				numberstack.pop();
				double b = numberstack.top();
				numberstack.pop();
				double sum = b * a;
				
				numberstack.push(sum);
				timetodooperation-=1;
				operatorstack.pop();
				
				}
				
			}

			}
			if(doublevaluestringinputchar==41.0 && negnumcount==1){
				double b = numberstack.top();
				double c = 0-b;
				numberstack.pop();
				numberstack.push(c);
				negnumcount=0;
			}
			
			//being used to test num 1 and num 2
			if(i==stringinput.size()-1){
			cout<<"The result is: "<<numberstack.top()<<endl;
			}
			
		}
	return 0;
}
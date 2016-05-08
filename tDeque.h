#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;


template <typename T>
class Deque{
	public:
		Deque();
		virtual ~Deque();
		void grow();
		void shrink();
		void push_front(T item);
		void push_back(T item);
		T pop_front();
		T pop_back();
		int size();
		bool empty();
		bool full();
		void printq(int test);
		string toStr();
		void printallvaluesaftereverything();
		
	
	private:
		// your private stuff to implement the deque
		int capacity;
		int head;
		int rear;
		T *q;
		int numberelements; //this will help me keep track when there are no elements, and when expansions and shrinks are required

};
	template <typename T>
	Deque<T>::Deque() {
		//setting intial values and sizes
		q = new T [8]; //initial size of array
		head=0;
		rear=0;
		numberelements=0;
		capacity = 8; //0 to 7 but 8 spots all together

	}

	//Destructor
	template <typename T>
	Deque<T>::~Deque() {
		delete[] q;         // come back to this later
		/*delete[] qtemp;*/
	}
	template <typename T>
	void Deque<T>::printq(int i){
		
		cout<<q[i]<<endl;
		


	}
	template <typename T>
	void Deque<T>::printallvaluesaftereverything(){
		for(int i=0;i<capacity;i++){
			cout<<q[i]<<"\t"<<i<<endl;
		}
		cout<<"Head: "<<head<<endl;
		cout<<"Rear: "<<rear<<endl;
	}
	template <typename T>
	void Deque<T>::grow(){
		T* qtemp = new T[capacity]; //this will hold the values temporarily
		
		/*for(int i = 0; i<8; i++){
			cout<<q[i]<<endl;
		}*/
		 //head will move to zero once it is subtracted from itself. all other spaces will shift to their correct spots
		for(int i = 0; i <capacity;i++){ //
			if((head+i)==capacity){ //if head plus i is out of bounds put it back in bounds and continue
				head = -i;
			}
			qtemp[i] = q[(head)+i];//at beginning of array it will get value of head. it will then increment until wrap around and all values copied
		}
		
		delete[] q;
			try{
				q = new T[capacity*2]; // makes q blank and of double size
			}
			catch(exception e){
				throw runtime_error("You are out of memory. Cannot double size of array.");
			}
		
		
		for(int i = 0; i<capacity;i++){ //
			q[i] = qtemp[i]; //qtemp already formatted to have head and after at 0 and on
		}
	

		//placing head at front
		rear = capacity-1;//placing rear at last value in array
		head=0;

		capacity*=2;// this will do a final update of the size of the capacity before moving on
		
		delete [] qtemp;	
		/*for(int i=0;i<capacity/2;i++){
			cout<<q[i]<<endl;
			cout<<i<<endl;
			
			
		}*/

	}
	template <typename T>
	void Deque<T>::shrink(){
		T* qtemp = new T[capacity]; //this will hold the values temporarily
		
		
		 //head will move to zero once it is subtracted from itself. all other spaces will shift to their correct spots
		for(int i = 0; i <capacity;i++){ //
			if((head+i)==capacity){ //if head plus i is out of bounds put it back in bounds and continue
				head = -i;
			}
			qtemp[i] = q[(head)+i];//at beginning of array it will get value of head. it will then increment until wrap around and all values copied
		}

		delete[] q;
		q = new T[capacity/2]; // makes q blank and of double size
		for(int i = 0; i<capacity/2;i++){ //
			q[i] = qtemp[i]; //qtemp already formatted to have head and after at 0 and on
			
		}
				

		head=0;//placing head at front
		rear = (capacity/4)-2;//placing rear at last value in array but be minus 2 cuz it will be plus oned later on
		

		capacity/=2;// this will do a final update of the size of the capacity before moving on
		head=1;//it is gonna be minused later	

		delete [] qtemp;	
		

	}
	


	// Inserts the element at the front of the queue. 
	template <typename T>
	void Deque<T>::push_front(T item) {

		if(empty()==false){//there is a first 
			if(full()==true){//if the array is full it will begin the expansion process
				grow();
				//push_front(item);// after it grows they still need to push front
				
			}
			if(full()==false){//if the array is not full it will do other processes for placing element

				if(head!=0){//it is not at the beginning of the array. therefore, head will just shift one left and put element there
					head--;
					q[head]=item;
					numberelements++;
				}
				else/*(head==0)*/{//if it is at the begginning of the array and not first element to be placed it will wrap around.
					head = capacity-1;//it is minus one because the array begins at zero

					q[head] = item;
					numberelements++;				
				}
			}
		}
		if(empty()==true){ //this if statement will handle the first case when there is no first element
			q[head] = item; //it could be empty anywhere and therefore make it equal to head point
			numberelements++;

		}
		
		
		

	}
	// Inserts the element at the back of the queue
	template <typename T>
	void Deque<T>::push_back(T item) {
		
		if(empty()==false){//there is a first 
			if(full()==true){//if the array is full it will begin the expansion process
				grow();
				//push_back(item);// after it grows they still need to push front
			}
			if(full()==false){//if the array is not full it will do other processes for placing element

				if(rear!=(capacity-1)){//it is not at the beginning of the array. therefore, head will just shift one left and put element there
					rear++;
					q[rear]=item;
					numberelements++;
					
				}
				else/*(rear==(capacity-1))*/{//if it is at the end of the array and not first element to be placed it will wrap around.
					rear = 0;//it is minus one because the array begins at zero ^

					q[rear] = item;
					numberelements++;	
				}
				
			}
		}
		if(empty()==true){ //this if statement will handle the first case when there is no first element
			q[rear] = item; //it could be empty anywhere and therefore make it equal to head point
			numberelements++;
			

		}
		
		
	}

	// Removes and returns the element at the front of the queue.
	template <typename T> 
	T Deque<T>::pop_front() {
		if(empty()==true){ //exception will be thrown here
			throw runtime_error("Error: Tried to pop front with empty stack.");
		}

		if(empty()==false){ // in other case it will throw an exception
			if(head==capacity-1){		//it will pop and then go back to the front of the array
				if(numberelements-1!=0){ //this way it will not wrap around if array is made empty
				head = 0;
				}
				numberelements--;
				if(numberelements<(capacity/4&&capacity>8)){
					shrink();
					rear++;//necessary to make even again
					
				}

			}
			else{ //if not at front it will move back one
				if(numberelements-1!=0){ //this way it wont move head if its not an empty array
					head++;
				}
				numberelements--;
				if(numberelements<(capacity/4)&&capacity>8){
					head--;//necessary to print correct value
					shrink();
					rear++;//necessary to make even again
					
				}
			}
			if(numberelements!=0){
				if(head==0){
				cout<<q[capacity-1]<<endl;
				T c = q[capacity-1];
				//q[capacity-1]="";
				return c;
				}
		
				else{
					cout<<q[head-1]<<endl;
					T d = q[head-1];
					//q[head-1]="";
					return d;
				}
			}
			if(numberelements==0){
					cout<<q[rear]<<endl;
					return q[rear];
			}
			
		}
		

	}

		/*cout<<"before probable issue"<<endl;
		cout<<numberelements<<endl;
		cout<<q[rear+1]<<"\n";
		cout<<"after probable issue"<<endl;*/
		
		

	// Removes and returns the element at the back of the queue.
	template <typename T>
	T Deque<T>::pop_back() {
		if(empty()==true){ //exception will be thrown here
			throw runtime_error("Error: Tried to pop back with empty stack.");
		}
		if(empty()==false){ // in other case it will throw an exception

			if(rear==0){		//it will pop and then go back to the end of the array
				if(numberelements-1!=0){ // this way it will not wrap around if array made empty
					rear= (capacity-1);
				}
				numberelements--;
				if(numberelements<(capacity/4)&&capacity>8){
					shrink();
					head--; // necessary to make even
					
				}

			}
			else{ //if not at front it will move back one
				if(numberelements-1!=0){ //this way if made empty array it will not move rear
					rear--;
				}
				numberelements--;
				if(numberelements<(capacity/4)&&(capacity>8)){

					shrink();
					head--; // necessary to make even
					
				}
			}
			if(numberelements!=0){
				if(rear!=capacity-1){
					cout<<q[rear+1]<<"\n";
					T b = q[rear+1];
				
					//q[rear+1]="";
					return b;
					
				}
				if(rear==capacity-1){
					cout<<q[0]<<endl;
					T a = q[0];
					//q[0]="";
					return a;
				
				}
				/*else{
					return "";
				}*/
			}
			if(numberelements==0){
				cout<<q[rear]<<endl;
				return q[rear];
			}
		}

	}


	// Returns the number of elements in the queue.
	template <typename T>
	int Deque<T>::size() {

		return capacity;
	}
	template <typename T>
	bool Deque<T>::full(){
		if(numberelements==capacity){
			return true;
		}
		else{
			return false;
		}
	}

	// Tells whether the queue is empty or not.
	template <typename T>
	bool Deque<T>::empty() {
		if(numberelements==0){
			return true;
		}
		else{
			return false;
		}
	}

	/* Puts the contents of the queue from front to back into a 
retrun string with each string item followed by a newline
	 */
	template <typename T>
	std::string Deque<T>::toStr() {
		string x;
		stringstream stream;
		if(head<rear){
			for(int i=head; i<rear+1;i++){

				stream<<q[i];
				stream<<"\n";
			}
		}
		if(head>rear){
			for(int i=0; i<numberelements;i++){
				
				stream<<q[(i+head)%(capacity)];
				stream<<"\n";
			}
		}
		if(head==rear && numberelements==1){
			stream<<q[head];
				stream<<"\n";
		}
		
		x= stream.str();

		return x;
	}
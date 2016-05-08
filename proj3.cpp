#ifdef _WIN32
	#include <direct.h>
	#define getcd _getcwd
#else
	#include <unistd.h>
	#define getcd getcwd
#endif
#include <iostream>
#include <cstdlib>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
using namespace std;

char CWD[FILENAME_MAX];
#define CWD getcd(CWD, sizeof(CWD))

void encrypt(char* name){
	//get filename length
	int letters = strlen(name);

	//open file
	ifstream is(name);
	
	//check if file is open
	if(is.is_open()==false){
		cout<<"File not found. Exiting."<<endl;
		exit(0);
	}

	//create blank encypted file with original file name and .enc extension
    string encryptedName;
	encryptedName.assign(name, letters);

	//puf file into the "Encrypted" folder and add propper extension
	encryptedName = "./Encrypted/" + encryptedName;
	encryptedName += ".enc";
	
	//deliniate end of file name
	encryptedName += '\0';
	
	//change name from string to char array
	int i = 0;
	char* newName = new char[256];
	while(encryptedName[i] != '\0'){
		newName[i] = encryptedName[i];
		i++;
	}
	
	//create encrypted file stream
	ofstream encrypted(newName);
	
	//get password
	string password;
	cout <<"\n" << "Enter a password (no spaces): ";
	cin >> password;

	//write password (encrypted with itself) into encrypted file
	char c;
	int counter = 0;
	char shift;
	int passSize = password.size();
	for(int i = 0; i < passSize; i++){
		c = password[i];
		if(counter == passSize){
			
			counter=0;
		}
		if(password[counter]>64 && password[counter]<91){
			shift = (char)(password[counter]-64);
		}
		if(password[counter]>96 && password[counter]<123){
			shift = (char)(password[counter]-96);
		}
		c = (c + shift);
		encrypted.put(c);
		counter++;	
	}

	//put a new line to allow for ease of password checking during decryption
	encrypted.put('\n');

	//write rest of encrypted file
	while(is.get(c)){
		if(counter == passSize){
			
			counter=0;
		}
		if(password[counter]>64 && password[counter]<91){
			shift = (char)(password[counter]-64);
		}
		if(password[counter]>96 && password[counter]<123){
			shift = (char)(password[counter]-96);
		}	
		c = (c + shift);		
		encrypted.put(c);
		counter++;
	}

	//close file streams
	is.close();
	encrypted.close();
	
	//delete pointers
	delete [] newName;
}

void decrypt(char* name){
	//get file name length
	int letters = strlen(name);

	//check that file is encrypted
	string oldName;
	oldName.assign(name, letters);
	if(oldName.find(".enc") == string::npos){
		cout<<endl<<"The chosen file is not encrypted. Exiting"<<endl;
		exit(0);
	}

	//set counters for finding the file extension and directories
	int extension = 0;
	int extensionEnd = 0;
	int directory = 0;

	//set bools for determining if file extensions have been found
	bool done = false;
	bool done2 = false;

	//find extensions and manage directories
	for(int i = 0; i < letters; i++){
		if(i != 0 && name[i] == '.' && done && !done2){
			extensionEnd = i;
			done2 = true;
		}
		if(i != 0 && name[i] == '.' && !done){
			extension = i;
			done = true;
		}
		if(name[i] == '/'){
			directory = i+1;
		}
	}


	//create file will name decrypted, and previous extension, in "Decrypted" directory
	string newName = "decrypted_";
	newName.append(oldName.substr(directory, extension-directory));
	newName.append(oldName.substr(extension, extensionEnd-extension));
	newName = "./Decrypted/" + newName;

	int newLength = newName.length();
	char* newNameArray = new char[255];	
	for(int i = 0; i < newLength; i++){
		newNameArray[i] = newName[i];
	}
	
	//checks to see if file is in folder
	ifstream es(name);
	if(es.is_open()==false){
		cout<<"File not found. Exiting."<<endl;
		exit(0);
	}

	//get password
	string password;
	cout << "Enter the password (no spaces): ";
	cin >> password;
	

	//initialize decryption variables
	char c;
	int counter = 0;
	char shift;
	int passSize = password.size();

	//check password
	char* ePassArray = new char[256];
	es.getline(ePassArray, 256);
	int ePassSize = strlen(ePassArray);
	string dPass = "";
	for(int i = 0; i < ePassSize; i++){
		c = ePassArray[i];
		if(counter == passSize){
			counter=0;
		}
		if(password[counter]>64 && password[counter]<91){
			shift = (char)(password[counter]-64);
		}
		if(password[counter]>96 && password[counter]<123){
			shift = (char)(password[counter]-96);
		}	
		c = (c - shift);		
		dPass += c;
		counter++;
	}

	//quit if incorrect password
	if(dPass.compare(password) != 0){
		cout<<endl<<"The password you entered was incorrect."<<endl;
		exit(0);
		es.close();
	}

	//decrypt if password is correct
	ofstream ds(newNameArray);
	while(es.get(c)){
		if(counter == passSize){
			counter=0;
		}
		if(password[counter]>64 && password[counter]<91){
			shift = (char)(password[counter]-64);
		}
		if(password[counter]>96 && password[counter]<123){
			shift = (char)(password[counter]-96);
		}	
		c = (c - shift);		
		ds.put(c);
		counter++;
	}
	
	//close file streams
	es.close();
	ds.close();
	
	//delete pointers
	delete [] ePassArray;
	delete [] newNameArray;
}

int main(int argc, char* argv[]){
	//code for file input
	cout << "Enter the name of your file, or file path if not in the current direcotry: \n";
    char name_Array[256];
    cin.getline(name_Array, 256, '\n');

    //get user input
    cout<<endl<<"Would you like to encrypt (1) or decrypt (2); 0 to quit : ";
    int selection;
    cin>>selection;

    //procede as decided
    while(1){
    	if(selection == 0){
    		break;
    	}
    	if(selection == 1){
    		//make directory for encrypted files
    		mkdir("Encrypted", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    		encrypt(name_Array);
    		break;

    	}
    	else if(selection == 2){
    		//make directory for decrypted files
    		mkdir("Decrypted", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    		decrypt(name_Array);
    		break;

    	}
    		else{
    			cout<<endl<<"That is not a valid selection. Try again: ";
    			cin >> selection;
    		}
    }

    //allow cx to delete original file
    cout<<endl<<"Would you like to delete the original file? (1 = yes 0 = no): ";
    cin>>selection;
    while(1){
    	if(selection == 0){
    		break;
    	}
    	else if(selection == 1){
    		remove(name_Array);
    		break;
    	}
    		else{
    			cout<<endl<<"That is not a valid selection. Try again: ";
    			cin >> selection;
    		}
    }
    return 0;
}

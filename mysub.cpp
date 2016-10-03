#include <iostream>
#include <fstream>
#include <string>	//for string 
#include <cstring>	//for strlen
#include <array>
using namespace std;

//prototypes
void print(int ray[], int raySize);
bool addOne(int curPerm[], int size);
int sumVal(int curPerm[], int data[], int size);
void print(int perm[], int weight[], int value[], int itemID[], int size);


bool DEBUG_ON = false;

int main(int arg, char*argv[]){

	//attempt to open file
	ifstream fin;
	fin.open("tester.txt");
	if(!fin.good()){
		cout<<"File I/O Error. Terminating.\n";
		return 0;
	}
	
	//retrieve total number of elements in test case
	string line;
	getline(fin,line);
	int totalNumItems = stoi(line);
	if(DEBUG_ON) cout << "totalNumItems = " << totalNumItems << endl;
	
	//base 2 array to hold permutations
	int curPerm[totalNumItems] = {0};
	//array to hold value
	int value[totalNumItems] = {0};
	//array to hold weights
	int weight[totalNumItems] = {0};
	//array to hold item "id" of each index
	int itemID[totalNumItems] = {0};

	//retrieve max weight of knapsack
	getline(fin,line);
	int MAXWEIGHT = stoi(line);
	if(DEBUG_ON) cout << "maxweight = " << MAXWEIGHT << endl;

	//now populate value and weight arrays
	char buf[1000];		//buffer for strcpy
	int index = 0;
	int currentID = 0;
	char* token;
	const char* const comma = ",";
	while(fin.good()){
		getline(fin,line);
		strcpy(buf,line.c_str());
		const string itemCopies(token = strtok(buf, comma));
		const string itemValue(token = strtok(0, comma)); 
		const string itemWeight(token = strtok(0, comma));
		int numCop = stoi(itemCopies);
		int val = stoi(itemValue);
		int wght = stoi(itemWeight);
		//populate values and weight array
		for(int x = 0; x < numCop; x++){
			value[index] = val;
			weight[index] = wght;
			itemID[index] = currentID;
			index++;
		}
		currentID++;		
	}
	if(DEBUG_ON){
	cout << "printing curPerm array: " << endl;
	print(curPerm, totalNumItems);
	cout << "printing value array: "<< endl;
	print(value, totalNumItems);
	cout << "printing weight array: "<< endl;
	print(weight, totalNumItems);
	cout << "printing itemID array: "<< endl;
	print(itemID, totalNumItems);
	}

	//loop and work through all permutations
	int curBestValue = 0;
	int curBestWeight = 0;
	int curBestPerm[totalNumItems] = {0};
	bool incomplete = true;
	while(incomplete != false){ 
		//add one to binary rep of permutations (doing first ensures that will eventually exit)
		incomplete = addOne(curPerm, totalNumItems);
		//print(curPerm,totalNumItems);		
		//calculate this perms weight
		int tempWeight = sumVal(curPerm, weight, totalNumItems);
		//if calc'd weight exceeds limit
		if(tempWeight > MAXWEIGHT)
			continue;
		else{ // acceptable weight, is it better then our best?
			int tempValue = sumVal(curPerm, value, totalNumItems);
			if(tempValue > curBestValue){
				curBestValue = tempValue;	
				curBestWeight = tempWeight;
				//curBestPerm = curPerm;
				int t = sizeof curBestPerm;
				//cout << "SIZE OF CURBESTPERM = " << t << endl;
				memcpy(curBestPerm, curPerm, sizeof curBestPerm);
			}
		}
		
	}
	
	if(DEBUG_ON){
	cout << "printing curBestPerm array: " << endl;
	print(curBestPerm, totalNumItems);	
	cout << "bestValue = " << curBestValue << ", bestWeight = " << curBestWeight << endl;
	}

	//output result
	//ALMOST DONE, just need to fix printing the "item number" - fixed
	//print(curBestPerm, weight, value, itemID, totalNumItems);
	//cout << curBestValue << "," << curBestWeight;
	return 0;
	
}//end main

void print(int ray[], int raySize){
	for(int i =0; i < raySize; i++)
		cout << "[ " << ray[i] << " ] ";
	cout << endl;
	return;
}//end print

void print(int perm[], int weight[], int value[], int itemID[], int size){
	for(int i = 0; i < size; i++){
		if(perm[i] == 0) continue;
		for(int j = 0; j < perm[i]; j++){
			cout << itemID[i] << "," << value[i] << "," << weight[i] << endl;
		}
	}
}//end print multiple



bool addOne(int curPerm[], int size){ //pass by ref!
	for(int i = 0; i < size; i++){
		if(curPerm[i] == 1) //current position's value is 1
			curPerm[i] = 0;
		else{		 // current position's value is 0, able to add 1		
			curPerm[i] = 1;
			return true;
		}
	}
	return false; //unable to add 1, must have overflown
}//end overflow check

int sumVal(int curPerm[], int data[], int size){ //pass by ref
	int sum = 0;
	for(int i = 0; i < size; i++){
		sum += curPerm[i]*data[i];	
	}
	return sum;

}//end sumVal

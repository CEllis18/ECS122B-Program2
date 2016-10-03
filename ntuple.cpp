#include <iostream>	//for I/O purposes, and debugging
#include <fstream>	//for reading files
#include <vector>	//vector is useful and easy to manage
#include <cmath>	//for pow() function
#include <fstream> 	//for file I/O
#include <string>	//for string 
#include <cstring>	//for strlen

using namespace std;

bool DEBUG_ON = true;

void addOneMixedRadix(vector<int>&, vector<int>&);
void print(vector<int>);
void print(vector<int>, vector<int>, vector<int>);
bool overflowCheck(vector<int>); //legacy
int sum(vector<int>&, vector<int>&);

int main(int arg, char *argv[]){
		
	vector<int> A;
	vector<int> B;
	vector<int> weight;
	vector<int> value;
	string line;
	char buf[1000];
	const char* const comma = ",";
	char* token;
	ifstream fin; //For file I/O
	int maxWeight = 0;
	int bestValueSoFar = 0;
	int bestWeightSoFar = 0;
	vector<int> bestPerm;
	fin.open("tester.txt");
	if(!fin.good()){
		if(DEBUG_ON) cout<<"File I/O Error. Terminating.\n";
		return 0;
	}
	getline(fin, line); //we dgaf
	getline(fin, line); //this will have max Weight
	maxWeight = stoi(line);
	while(fin.good()){
		getline(fin, line); 
		strcpy(buf, line.c_str());
		const string itemCopies(token = strtok(buf, comma));
		const string itemValue(token = strtok(0, comma)); 
		const string itemWeight(token = strtok(0, comma));
		value.push_back(stoi(itemValue));
		weight.push_back(stoi(itemWeight));
		B.push_back(stoi(itemCopies) + 1);
		A.push_back(0);
	}
	 //Checks if # of args is 2, so that we can open the file that is the 2nd arg
	int numOfPermutations = 0;
	int totalIterations = 1;
	for(int i = 0; i < B.size(); i++){
		totalIterations *= B[i];
	}
	do{
		addOneMixedRadix(A, B);
		numOfPermutations++;
		int permWeight = sum(A, weight);
		int permValue;
		if(permWeight > maxWeight)
			continue;
		else{
			permValue = sum(A, value);
			if(permValue > bestValueSoFar){
				bestValueSoFar = permValue;
				bestWeightSoFar = permWeight;
				bestPerm = A;
			}
		}
	}while(numOfPermutations < totalIterations); //NOTE: We can also enumerate them out using pow function summation, this is just simpler for now.
	//print(bestPerm, weight, value);
	//cout<<bestValueSoFar<<","<<bestWeightSoFar;
	return 0;
	
}

/*
Specifically enumerates each possible permutation of our Array
TODO (Potentially): Pass as parameters the specifics of each enumeration,
	ex:	if only 500 gold bars are to be given in total, then check to make
		sure that the permutation uses exactly 500 gold bars	
*/
void addOneMixedRadix(vector<int>& a, vector<int>& b){ 
	if(a.size() != b.size()){
		cout<<"ERROR: Arrays of different size!\n";
		return;
	}
	for(int i = 0; i < a.size(); i++){
		if(a[i] + 1 == b[i]){
			a[i] = 0; //carry
		} else {
			a[i] = a[i] + 1; //successfully added
			break;
		}
	}
	return; //Check for completely 0'd out array. If zero'd out array we have overflow
}

/* Prints the contents of the vector */
void print(vector<int> printMe){
	for(int i = 0; i < printMe.size(); i++)
		cout<<"[ "<<printMe[i]<<" ] ";
	cout<<endl;
	return;
}

void print(vector<int> A, vector<int> weights, vector<int> values){
	for(int i = 0; i < A.size(); i++){
		if(A[i] == 0) continue;
		for(int j = 0; j < A[i]; j++){
			cout<<i<<","<<values[i]<<","<<weights[i]<<endl;
		}
	}
}

bool overflowCheck(vector<int> checkMe){ //legacy
	for(int i = 0; i < checkMe.size(); i++){
		if(checkMe[i] !=0)
			return false;
		else 
			continue;
	}
	return true; 
}

int sum(vector<int>& permVec, vector<int>& numVec){
	int sum = 0;
	for(int i = 0; i < permVec.size(); i++)
		sum += permVec[i]*numVec[i];

	return sum;
}

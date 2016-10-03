#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
using namespace std;
//first line is number of items
//second line is max weight of our bag
//output ot file is: #copies,item value,item weight
int main(int argc, char *argv[]){
	if(argc < 3){
		printf("datagenerator [number of items] [number of copies]");
		exit(1);
	}
	int filefd = open("tester.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(filefd < 0){
		perror("Couldn't create file.");
	}
	int values[atoi(argv[1])];
	int totalvalue = 0;
	int count = 0;
	srand(time(NULL));
	string result = "";
	int valuecount = 0;
	for( int counter = 0; counter < atoi(argv[1]) && valuecount < atoi(argv[1])*atoi(argv[2]); counter++ ){
		int weight = rand() % 100 + 1;
		srand(time(NULL)+count+rand());
		int copies = rand() % atoi(argv[2]) + 1;
		if(valuecount + copies > atoi(argv[1])*atoi(argv[2])){
			copies = atoi(argv[1])*atoi(argv[2]) - valuecount;
		}
		valuecount += copies;
		srand(time(NULL)+count+totalvalue+rand());
		int value = rand() % 100 + 1;
		totalvalue += value * copies;
		if(counter < atoi(argv[1]) - 1 && valuecount < atoi(argv[1])*atoi(argv[2])){
			result.append(to_string(copies) + "," + to_string(value) + "," + to_string(weight) + "\n");
		}else{
			result.append(to_string(copies) + "," + to_string(value) + "," + to_string(weight));
		}
	}
	result = to_string(valuecount) + "\n" + to_string(totalvalue/2) + "\n" + result;
	int size = write(filefd, result.c_str(), result.length());
	if(size < 0){
		perror("Couldn't write to file.");
	}
	close(filefd);
	return 0;
}
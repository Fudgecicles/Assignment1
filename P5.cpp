#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;



struct bucket{
	bool full = false;
	int* contents = NULL;
	int size= 0;
};

void put(bucket &buck, int* entry, int count,int spot){
	if (buck.full == true){
		cout << "bucket " << spot << " is not empty" << endl;
		delete[] entry;
		return;
	}
	delete[] buck.contents;
	buck.contents = entry;
	buck.size = count;
	buck.full = true;
}

void empty(bucket &buck){
	if (buck.full){
		delete[] buck.contents;
		buck.contents = NULL;
		buck.size = 0;
		buck.full = false;
	}
}

void output(bucket buck){
	if (!buck.full){
		cout << "empty";
	}
	else{
		for (int k = 0; k < buck.size; k++){
			cout << buck.contents[k] << " ";
		}
	}
	
	cout << endl;
}

int* linetoarray(char* arr,int size){
	stringstream converter;
	converter << arr;
	int* contents = new int[size];
	for (int k = 0; k < size; k++){
		int num;
		converter >> num;
		if (converter.fail()){
			cout << "Not all values on Put command are integers" << endl;
			int* temp = NULL;
			return temp;
		}
		contents[k] = num;
	}
	return contents;
}

void invalidInput(){
	cout << "invalid input on vital information, press enter to continue";
	char temp[80];
	cin.getline(temp, 80);
	exit(EXIT_FAILURE);
}



int main(int argc, char** argv){
	if (argc == 1){
		cout << "Not enough arguments, press enter to exit";
		char temp[80];
		cin.getline(temp, 80);
		return 1;
	}
	fstream file;
	file.open(argv[1]);
	if (file.fail()){
		cout << "File does not exist, press enter to exit";
		char temp[80];
		cin.getline(temp, 80);
		return 1;
	}
	stringstream converter;
	char line[80];
	file.getline(line, 80);
	converter << line;
	int numbuckets;
	converter >> numbuckets;
	if (converter.fail()){
		cout << "Input for number of buckets is invalid, press enter to exit";
		char temp[80];
		cin.getline(temp, 80);
		return 1;
	}
	int numlines;
	converter >> numlines;
	if (converter.fail()){
		cout << "Input for number of commands is invalid, press enter to exit";
		char temp[80];
		cin.getline(temp, 80);
		return 1;
	}
	bucket* buckets = new bucket[numbuckets];
	
	for (int k = 0; k < numlines; k++){
		char line[80];
		file.getline(line, 80);
		converter.clear();
		converter << line;
		char command[80];
		converter.get(command, 80, ' ');

		if (strcmp(command, "PUT")==0){
			
			int index;
			converter >> index;
			if (converter.fail()){
				cout << "PUT";
				invalidInput();
			}
			if (index<1 || index>numbuckets){
				cout << "Bucket " << index << " does not exist" << endl;
				continue;
			}
			int nums;
			converter >> nums;
			if (converter.fail()){
				cout << "PUT";
				invalidInput();
			}
			
			converter.getline(line, 80);
			int* contents = linetoarray(line, nums);
			if (contents != NULL)
				put(buckets[index - 1], contents, nums, index);
			else
				delete[] contents;
		}
		else if (strcmp(command, "EMPTY")==0){
			int index;
			converter >> index;
			if (converter.fail()){
				cout << "EMPTY";
				invalidInput();
			}
			if (index<1 || index>numbuckets){
				cout << "Bucket " << index << " does not exist" << endl;
				continue;
			}
			empty(buckets[index-1]);
		}
		else if (strcmp(command, "OUTPUT")==0){
			int index;
			converter >> index;
			if (converter.fail()){
				cout << "OUTPUT";
				invalidInput();
			}
			if (index<1 || index>numbuckets){
				cout << "Bucket " << index << " does not exist" << endl;
				continue;
			}
			output(buckets[index-1]);
		}
		else{
			cout << command;
			cout << "Command does not exist, press enter to exit";
			char temp[80];
			cin.getline(temp, 80);
			return 1;
			
		}
	}
	char temp[80];
	cout << "Press enter to exit";
	cin.getline(temp, 80);
	for (int k = 0; k < numbuckets; k++){
		delete[] buckets[k].contents;
	}
	delete[] buckets;
	return 1;
}

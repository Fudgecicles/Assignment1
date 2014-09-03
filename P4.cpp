#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]){
	if (argc != 2){
		int i;
		cout << "incorrect number of arguments, press enter to continue";
		char temp[80];
		cin.getline(temp, 80);
		return 1;
	}
	ifstream file;
	stringstream converter;
	file.open(argv[1]);
	if (file.fail()){
		cout << "file does not exist";
		char temp[80];
		cin.getline(temp, 80);
		return 1;
	}
	int size;
	char temp[80];
	file.getline(temp, 80);
	converter << temp;
	converter >> size;
	if (converter.fail()){
		cout << "invalid input for number of lines";
		char temp[80];
		cin.getline(temp, 80);
		return 1;
	}
	char** lines;
	lines = new char*[size];
	for (int k = 0; k < size; k++){
		lines[k] = new char[80];
		file.getline(lines[k], 80);
	}
	int* results = new int[size];
	for (int k = 0; k < size; k++){
		int words = 0;
		converter.clear();
		converter << lines[k];
		/*while (converter.rdbuf()->in_avail() != 0){
			char temp[80];
			converter >> temp;
			cout << temp;
			words++;
		}*/
		char test[80];
		converter >> test;

		while (strlen(test) != 0){
			words++;
			converter >> test;
		}
		results[k] = words;
	}
	for (int k = size-1; k >=0; k--){
		cout << results[k] << endl;

	}
	cout << "Press enter to exit";
	char dumb[80];
	cin.getline(dumb, 80);
	for (int k = 0; k < size; k++){
		delete[] lines[k];
	}
	delete[] results;
	delete[] lines;
	return 1;
}
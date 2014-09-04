#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]){
	//Check that the correct number of arguments were passed and output an error if not
	if (argc <=1){
		int i;
		cout << "incorrect number of arguments, press enter to continue";
		char temp[80];
		cin.getline(temp, 80);
		return 1;
	}
	ifstream file;
	stringstream converter;
	//open the file specified and if it does not exist output an error
	file.open(argv[1]);
	if (file.fail()){
		cout << "file does not exist, press enter to exit";
		char temp[80];
		cin.getline(temp, 80);
		return 1;
	}
	int size;
	//get the line from the file and use a stringstream to convert it to an integer for the number of lines in the document
	char temp[80];
	file.getline(temp, 80);
	converter << temp;
	converter >> size;
	//if the number of lines inputed was not an integer then output an error and exit
	if (converter.fail()){
		cout << "invalid input for number of lines";
		char temp[80];
		cin.getline(temp, 80);
		return 1;
	}
	//create an array of c-string to store each line of the file in. 
	char** lines;
	lines = new char*[size];
	for (int k = 0; k < size; k++){
		lines[k] = new char[80];
		file.getline(lines[k], 80);
	}
	//create an array to store the number of words in each line
	int* results = new int[size];
	//go through each line and check how many words tehre are
	for (int k = 0; k < size; k++){
		//put the line into a stringstream which then takes out the words one by one until the word is empty meaning the line is empty
		int words = 0;
		converter.clear();
		converter << lines[k];
		char test[80];
		converter >> test;
		//checking if we are at the end of the file and if not taking in another word and incrementing counter
		while (!converter.eof()){
			words++;
			converter >> test;
		}
		//store the result
		results[k] = words;
	}
	//iterate through our results and output them in reverse order
	for (int k = size-1; k >=0; k--){
		cout << results[k] << endl;

	}
	//prompt the user for enter to exit the program
	cout << "Press enter to exit";
	char dumb[80];
	cin.getline(dumb, 80);
	//delete each c-string in line
	for (int k = 0; k < size; k++){
		delete[] lines[k];
	}
	//delete everything else
	delete[] results;
	delete[] lines;
	return 1;
}
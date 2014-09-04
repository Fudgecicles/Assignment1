#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;


//data structure to represent the bucket. Has an array of ints, an int to track how large that array is, and a bool for whether or not it has any contents
struct bucket{
	bool full = false;
	int* contents = NULL;
	int size = 0;
};

//Places the array of ints entry into the bucket buck, sets the bucket's size to count and sets full to treu afterwards. Spot is passed for outputting errors.
void put(bucket &buck, int* entry, int count, int spot){
	//If the bucket is already full output an error
	if (buck.full == true){
		cout << "bucket " << spot << " is not empty" << endl;
		//The array of ints must be deleted because the bucket's contents will not reference them now.
		delete[] entry;
		return;
	}
	// delete the bucket's contents just in case
	delete[] buck.contents;
	buck.contents = entry;
	buck.size = count;
	buck.full = true;
}
// Deletes the bucket's contents, resets size to 0 and sets full to false.
void empty(bucket &buck){
	if (buck.full){
		delete[] buck.contents;
		buck.contents = NULL;
		buck.size = 0;
		buck.full = false;
	}
}
// Prints each entry in the bucket's contents seperated by a space or "empty" if the bucket does not have any contents.
void output(bucket buck){
	//check for contents
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
// Function that converts a line of text stored in a c-string to an array of integers, size is passed in to tell it how many entries there are. 
// This is used for the PUT command after the bucket its being stored in and the number of entries is parsed
int* linetoarray(char* arr, int size){
	stringstream converter;
	converter << arr;
	int* contents = new int[size];
	for (int k = 0; k < size; k++){
		int num;
		converter >> num;
		// Error checking, will fail if any entry is not a number
		if (converter.fail()){
			cout << "Not all values on Put command are integers" << endl;
			// returns a null pointer which will be checked for and ignored if detected in the main function and delete any of the contents that were already created
			delete[] contents;
			int* temp = NULL;
			return temp;
		}
		contents[k] = num;
	}
	return contents;
}
// Function to output info for invalid input that the program cannot continue without and exits afterwards. 
void invalidInput(){
	cout << "invalid input on vital information, press enter to continue";
	char temp[80];
	cin.getline(temp, 80);
	exit(EXIT_FAILURE);
}



int main(int argc, char** argv){
	// check if atleast arguements were passed and if not exit
	if (argc <= 1){
		cout << "Not enough arguments, press enter to exit";
		char temp[80];
		cin.getline(temp, 80);
		return 1;
	}
	//open the file that was passed in when starting the program
	fstream file;
	file.open(argv[1]);
	//Check if the file exists and if not exit
	if (file.fail()){
		cout << "File does not exist, press enter to exit";
		char temp[80];
		cin.getline(temp, 80);
		return 1;
	}
	//Use stringstream to convert the first two entries into their integer counterparts
	stringstream converter;
	char line[80];
	file.getline(line, 80);
	converter << line;
	int numbuckets;
	converter >> numbuckets;
	//More error checking to see if the the input for the number of buckets to be used is actually a number
	if (converter.fail()){
		cout << "Input for number of buckets is invalid, press enter to exit";
		char temp[80];
		cin.getline(temp, 80);
		return 1;
	}
	int numlines;
	converter >> numlines;
	//More error checking to see if the input for the number of commands is actually a number
	if (converter.fail()){
		cout << "Input for number of commands is invalid, press enter to exit";
		char temp[80];
		cin.getline(temp, 80);
		return 1;
	}
	//Create our array of buckets after we know how many buckets we want
	bucket* buckets = new bucket[numbuckets];
	//-------------------Main work starts here!------------------------
	//Iterate through each command with if statements to check which command each line wants. 
	for (int k = 0; k < numlines; k++){
		char line[80];
		file.getline(line, 80);
		converter.clear();
		converter << line;
		char command[80];
		// Get the first word from the line and put it into a c-string then if statements to check which command it is
		converter.get(command, 80, ' ');
		// Check if the line is a PUT command
		// I'm doing weird stuff here because for some reason when I brought into GCC, it would add a white space in front of every char array
		// Checking the characters individually would somehow remove this space and then strcmp works correctly
		if (command[1] == 'P'&&command[2]=='U'&&command[3]=='T'||strcmp(command,"PUT")==0){
			// get the bucket index that the PUT command will be performed on
			int index;
			converter >> index;
			// if the value is not a number than print error and exit
			if (converter.fail()){
				cout << "PUT";
				invalidInput();
			}
			//Check if the bucket exists and if it does not print an error and go to the next line
			if (index<1 || index>numbuckets){
				cout << "Bucket " << index << " does not exist" << endl;
				continue;
			}
			//Get the number of integers that will be in the array
			int nums;
			converter >> nums;
			//if the value is not a number print error and exit
			if (converter.fail()){
				cout << "PUT";
				invalidInput();
			}
			//store the remainder of the line into a c-string and pass that to a function that converts the line into an array of ints
			converter.getline(line, 80);
			int* contents = linetoarray(line, nums);
			//if the function did not detect and values that were not integers then store the value in the bucket of the chosen array
			if (contents != NULL)
				//we use index-1 because the indexes do not start at 0 they start at 1
				put(buckets[index - 1], contents, nums, index);
			else
				// if we did find an error, delete what was returned anyways because we don't need it and we might as well be sure
				delete[] contents;
		}
		//check if the line is an EMPTY statement
		else if (command[1]=='E'||strcmp(command, "EMPTY") == 0){
			//get the index of what bucket we will be operating on
			int index;
			converter >> index;
			//Check that the entry was actually a number
			//It might have been a good idea to make this a function
			if (converter.fail()){
				cout << "EMPTY";
				invalidInput();
			}
			//Check that the index given exists and output an error if it does not
			if (index<1 || index>numbuckets){
				cout << "Bucket " << index << " does not exist" << endl;
				continue;
			}
			//Empty the bucket of the index, we use index -1 because indexes start at 1 not 0
			empty(buckets[index - 1]);
		}
		//check if the line is an OUTPUT statement
		else if (command[1]=='O'||strcmp(command, "OUTPUT") == 0){
			//get the index of what bucket we will be operating on
			int index;
			converter >> index;
			//Check that the entry was actually a number
			if (converter.fail()){
				cout << "OUTPUT";
				invalidInput();
			}
			//Check that the index given exists and output an error if it does not
			if (index<1 || index>numbuckets){
				cout << "Bucket " << index << " does not exist" << endl;
				continue;
			}
			//print out the contents of the chosen bucket with the output function, we use index -1 because the indexes start at 1 not 0
			output(buckets[index - 1]);
		}
		// Error checking for a command that does not exist and exit afterwards
		else{
			cout << command[1];
			cout << strcmp(command, "PUT");
			cout << "Command does not exist, press enter to exit";
			char temp[80];
			cin.getline(temp, 80);
			return 1;

		}
	}
	//create a dummy char array to let the user press enter to continue
	char temp[80];
	cout << "Press enter to exit";
	cin.getline(temp, 80);
	//iterate through each bucket and delete its contents
	for (int k = 0; k < numbuckets; k++){
		delete[] buckets[k].contents;
	}
	//delete each bucket
	delete[] buckets;
	return 1;
}

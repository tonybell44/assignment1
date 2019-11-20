#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void getInOutFile(string &inFile, string &outFile){
	cout << "Please type the name of the commands textfile:" << endl;
	cin >> inFile;
	cout << "Please type the name of the textfile you would like to output to:" << endl;
	cin >> outFile;
	return;
}


bool checkCommand(const string cm1) {
	if ((cm1 == "create") || (cm1 == "push")){
		return true;
	}
	else {return false;}
}

void runCommands (const string cm1, const string cm2, const string cm3 = "null"){
	
}


int main() {
	string cm1, cm2, cm3, commandFileName, outputFileName;

	getInOutFile(commandFileName, outputFileName);			// Asks for names of input and output files
	ifstream commands (commandFileName, ifstream::in);


	while(commands >> cm1 >> cm2) {
		if (checkCommand(cm1)){
			commands >> cm3;
			runCommands(cm1, cm2, cm3);
		}
		else {
			runCommands(cm1, cm2);
		}
	}

	commands.close();
	return 0;
}

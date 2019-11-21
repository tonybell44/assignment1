#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;

template <typename T>
class SimpleList {
	private:
		string name;
		int size;
		struct Node{
			T data;
			Node *next;
			Node (const T d , Node *n = nullptr) : data{d}, next{n} {}
			Node (Node *n = nullptr) : next{n} {}
		};
		Node *head;
		Node *tail;
	protected:
		void insertFront(T data);
		void insertEnd(T data);
		void removeFront();
	public:
		SimpleList (string n){
			name = n;
			size = 0;
			tail = new Node();
			head = new Node(tail);
		}
		void getName();
		void getSize();
		virtual void push(T data) = 0;
		virtual void pop() = 0;
				
};

void SimpleList::insertFront(T data){
	
}




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

void create(const string name, const string type){
	
}

void runCommands (const string cm1, const string cm2, const string cm3 = "null"){
	switch (cm1) {
		case "create":
			create(cm2, cm3);			//creates stack or queue based on name
		case "push":
			push(cm2, cm3);
		case "pop":
			pop(cm2);
	}
	return;
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

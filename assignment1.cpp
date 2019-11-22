#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;

//ABSTRACT BASE CLASS

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
		struct HeadNode{				//just head node
			Node *next;
			Node *last;
			HeadNode (Node *n, Node *l = nullptr) : next{n}, last{l} {}
		};
		HeadNode *head;
		Node *tail;
	protected:
		void insertFront(T data);
		void insertEnd(T data);
		T removeFront();
	public:
		SimpleList (string n){		//Maybe add outside of class :)
			name = n;
			size = 0;
			tail = new Node();
			head = new HeadNode(tail);
		}
		string getName();
		int getSize();
		virtual void push(T data) = 0;
		virtual T pop() = 0;
				
};

template <typename T>
void SimpleList<T>::insertFront(T data){	//check syntax
	Node *newNode = new Node(data, head.next);
	head.next = newNode;
	size++;
	return;
}

template <typename T>
void SimpleList<T>::insertEnd(T data){
	Node *newNode = new Node(data, tail);
	if (size == 0){
		head.next = newNode;
		head.last = newNode;
	}
	else if (size > 0){
		*(head.last).next = newNode;			//be careful
		head.last = newNode;
	}
	size++;
	return;
}

template <typename T>
T SimpleList<T>::removeFront(){			//make sure later code doesnt permit this if size == zero
	T object = *(head.next).data;
	Node *intermediateNode = *(head.next).next;
	delete head.next;
	head.next = intermediateNode;
	size--;
	return object;
}

template <typename T>
string SimpleList<T>::getName(){
	return name;
}

template <typename T>
int SimpleList<T>::getSize(){
	return size;
}

//DERIVED CLASSES

template <typename T>
class Stack : public SimpleList<T>{
	public:
		void push(T data);
		T pop();
		T removeFront();		//try commenting this out: why doesn't it work then?
		Stack(string n);
};

template <typename T>
void Stack<T>::push(T data){
	insertFront(data);
	return;
}

template <typename T>
T Stack<T>::pop(){
	return removeFront();
}

template <typename T>
Stack<T>::Stack(string n) : SimpleList<T>(n){      //correct syntax for using the base constructor as well :) thank https://stackoverflow.com/questions/18347474/shadows-a-parameter-when-single-parameter-on-constructor
}

template <typename T>
class Queue : public SimpleList<T>{
	public:
		void push(T data);
		T pop();
		T removeFront();
		Queue(string n);
};

template <typename T>
void Queue<T>::push(T data){
	insertEnd(data);
	return;
}

template <typename T>
T Queue<T>::pop(){
	return removeFront();
}

template <typename T>
Queue<T>::Queue(string n) : SimpleList<T>(n){
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

void runCommands (const string cm1, const string cm2, const string cm3 = "null"){    //handles reading the names and calling appropriate commands
	if (cm1 == "create"){
		create (cm2, cm3);
	}
	else if (cm1 == "push"){
		push (cm2, cm3);
	}
	else if (cm1 == "pop"){
		pop(cm2);
	}
	return;
}


int main() {
	string cm1, cm2, cm3, commandFileName, outputFileName;

	list<SimpleList<int> *> listSLi;
	list<SimpleList<double> *> listSLd;
	list<SimpleList<string> *> listSLs;

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

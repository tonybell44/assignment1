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
	Node *newNode = new Node(data, head->next);
	head->next = newNode;
	size++;
	return;
}

template <typename T>
void SimpleList<T>::insertEnd(T data){
	Node *newNode = new Node(data, tail);
	if (size == 0){
		head->next = newNode;
		head->last = newNode;
	}
	else if (size > 0){
		*(head->last)->next = newNode;			//be careful
		head->last = newNode;
	}
	size++;
	return;
}

template <typename T>
T SimpleList<T>::removeFront(){			//make sure later code doesnt permit this if size == zero
	T object = head->next->data;
	Node *intermediateNode = head->next->next;
	delete head->next;
	head->next = intermediateNode;
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
		Stack(string n);
};

template <typename T>
void Stack<T>::push(T data){
	this->insertFront(data);
	return;
}

template <typename T>
T Stack<T>::pop(){
	return this->removeFront();
}

template <typename T>
Stack<T>::Stack(string n) : SimpleList<T>(n){      //correct syntax for using the base constructor as well :) thank https://stackoverflow.com/questions/18347474/shadows-a-parameter-when-single-parameter-on-constructor
}

template <typename T>
class Queue : public SimpleList<T>{
	public:
		void push(T data);
		T pop();
		Queue(string n);
};

template <typename T>
void Queue<T>::push(T data){
	this->insertEnd(data);
	return;
}

template <typename T>
T Queue<T>::pop(){
	return this->removeFront();
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

template <typename T>
bool checkExistence(list<SimpleList<T> *> &SL, string name){			//true if name exists, false if name does not exist
	typename list<SimpleList<T> *>::iterator it;
	for (it = SL.begin(); it != SL.end(); it++){
		if ((*it)->getName() == name){
			return true;
		}
	}
	return false;
}

void create(const string name, const string type, list<SimpleList<int> *> &listSLi, list<SimpleList<double> *> &listSLd,  list<SimpleList<string> *> &listSLs){
	if (*(name.begin()) == 'i'){
		if (checkExistence(listSLi, name)){
			SimpleList<int> *pSLi;
			if (type == "stack"){
				pSLi = new Stack<int>(name);
				listSLi.push_front(pSLi);
			}
			else if (type == "queue"){
				pSLi = new Queue<int>(name);
				listSLi.push_front(pSLi);
			}
		}
	}
	else if (*(name.begin()) == 'd'){
		if (checkExistence(listSLd, name)){
			SimpleList<double> *pSLd;
			if (type == "stack"){
				pSLd = new Stack<double>(name);
				listSLd.push_front(pSLd);
			}
			else if (type == "queue"){
				pSLd = new Queue<double>(name);
				listSLd.push_front(pSLd);
			}
		}
	}
	else if (*(name.begin()) == 's'){
		if (checkExistence(listSLs, name)){
			SimpleList<string> *pSLs;
			if (type == "stack"){
				pSLs = new Stack<string>(name);
				listSLs.push_front(pSLs);
			}
			else if (type == "queue"){
				pSLs = new Queue<string>(name);
				listSLs.push_front(pSLs);
			}
		}
	}
	return;
}

void runCommands (const string commandFileName, const string outputFileName){    //handles reading the names and calling appropriate commands
	ifstream commands (commandFileName, ifstream::in);

        list<SimpleList<int> *> listSLi;
        list<SimpleList<double> *> listSLd;
        list<SimpleList<string> *> listSLs;

	string cm1, cm2, cm3;

	while(commands >> cm1 >> cm2){
		if (cm1 == "create"){
			commands >> cm3;
			create (cm2, cm3, listSLi, listSLd, listSLs);
		}
		else if (cm1 == "push"){
			commands >> cm3;
			push (cm2, cm3)
		}
		else if (cm1 == "pop"){
			pop (cm2);
		}
	}
	commands.close();
	return;
}


int main() {
	string commandFileName, outputFileName;

	getInOutFile(commandFileName, outputFileName);			// Asks for names of input and output files

	runCommands(commandFileName, outputFileName);

	return 0;
}

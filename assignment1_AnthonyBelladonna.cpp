#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;

/*Anthony Belladonna
 * Program takes input from a user-specified textfile and parses commands
 * from this textfile. It creates stacks and queues, can push, and can pop
 * from these stacks and queues based on the commands it parses. It outputs
 * to a specified textfile by diplaying the commands (line by line) it processed,
 * as well as the poppped values from stacks and queues where necessary. */

//ABSTRACT BASE CLASS

template <typename T>
class SimpleList {
	private:
		string name;
		int size;		//size exludes head and tail nodes when a SimpleList object is created. In Node constructor, size = 0
		struct Node{
			T data;
			Node *next;
			Node (const T d , Node *n = nullptr) : data{d}, next{n} {}
			Node (Node *n = nullptr) : next{n} {}
		};
		struct HeadNode{	//HeadNode is a special type of node with an extra pointer (Node *last;)
			Node *next;
			Node *last;	//the last pointer points to the Node before the tailnode if at least one exists
			HeadNode (Node *n, Node *l = nullptr) : next{n}, last{l} {}
		};
		HeadNode *head;
		Node *tail;
	protected:
		void insertFront(T data);
		void insertEnd(T data);
		T removeFront();
	public:
		SimpleList (string n){
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
void SimpleList<T>::insertFront(T data){
	Node *newNode = new Node(data, head->next);
	head->next = newNode;
	size++;
	return;
}

/*insertEnd inserts a new Node after the Node that the *last pointer points to (the *last pointer is exclusive to the HeadNode struct). The *last pointer
 * will now point to this new Node, and the node which was previosuly pointed to by *last will
 * have its own *next pointer point to this new Node as well. The new Node's *next pointer will point to the tail node.*/
template <typename T>
void SimpleList<T>::insertEnd(T data){
	Node *newNode = new Node(data, tail);
	if (size == 0){
		head->next = newNode;
		head->last = newNode;
	}
	else if (size > 0){
		(head->last)->next = newNode;
		head->last = newNode;
	}
	size++;
	return;
}

template <typename T>
T SimpleList<T>::removeFront(){			//implementation does not permit removal if size == 0 in order to assure the tail node is not deleted.
	T object = (head->next)->data;
	Node *intermediateNode = (head->next)->next;
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

//DERIVED CLASSES (Stack and Queue)

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
Stack<T>::Stack(string n) : SimpleList<T>(n){
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

/*checkExistence returns false if the SimpleList exists in a given list of SimpleList pointers (based off name)
 * and returns true if it does not exist*/
template <typename T>
bool checkExistence(list<SimpleList<T> *> &SL, string name){
        typename list<SimpleList<T> *>::iterator it;
        for (it = SL.begin(); it != SL.end(); it++){
                if ((*it)->getName() == name){
                        return false;
                }
        }
        return true;
}

/*getListPointer returns a SimpleList pointer if the SimpleList exists in a given list of SimpleList pointers (based off name)
 * returns a nullpointer if it does not exist*/
template <typename T>
SimpleList<T>* getListPointer(list<SimpleList<T> *> &SL, string name){
	typename list<SimpleList<T> *>::iterator it;
	for (it = SL.begin(); it != SL.end(); it++){
		if ((*it)->getName() == name){
			return *it;
		}
	}
	return nullptr;
}

/*commandMessage will be called every single time a command line from the input file is parsed,
 * and will print commands line by line to a given .txt file*/
template <typename T>
void commandMessage(int messageID, string cm1, string cm2, T cm3, ofstream &outFile){
	if (messageID == 0){
		outFile << "PROCESSING COMMAND: " << cm1 << " " << cm2 << " " << cm3 << "\n";
	}
	else if (messageID == 1){
		outFile << "PROCESSING COMMAND: " << cm1 << " " << cm2 << "\n";
	}
	return;
}

void errorMessage(int messageID, ofstream &outFile){
	if (messageID == 0){
		outFile << "ERROR: This name already exists!" << "\n";
	}
	else if (messageID == 1){
		outFile << "ERROR: This name does not exist!" << "\n";
	}
	else if (messageID == 2){
		outFile << "ERROR: This list is empty!" << "\n";
	}
}

template <typename T>
void popMessage(T data, ofstream &outFile){
	outFile << "Value popped: " << data << "\n";
	return;
}

/*The create function is called when the first word from a set of commands is "create". The rest of this set of commands is passed 
 * to this function. If the name does not already exist, a new stack or queue (depending on which was specified) is created and added
 * to the list. If the name already existed, nothing is created and an error message is output.*/
template <typename T>
void create(const string name, const string type, list<SimpleList<T> *> &listSLT, ofstream &outFile){
	if (checkExistence(listSLT, name)){
		SimpleList<T> *pSLT;
		if (type == "stack"){
			pSLT = new Stack<T>(name);
			listSLT.push_front(pSLT);
		}
		else if (type == "queue"){
			pSLT = new Queue<T>(name);
			listSLT.push_front(pSLT);
		}
		return;
	}
	errorMessage(0, outFile);
	return;
}

/*The push function is called when the first word from a set of commands is "push". The rest of this set is passed to this function.
 * The list is searched, and if the name exists, the pointer to this SimpleList is obtained and a value is pushed to it. If the name does
 * not exist, an error message is output and nothing gets pushed.*/
template <typename T>
void push(string name, T value, list<SimpleList<T> *> &listSLT, ofstream &outFile){
	if (!checkExistence(listSLT, name)){
		getListPointer(listSLT, name)->push(value);
		return;
	}
	errorMessage(1, outFile);
	return;
}

/*The pop function is called if the first word from a set of commands is "pop". The list is searched, and if the SimpleList exists, a pointer to it
 * is obtained. If the SimpleList's size is 0, then it has no nodes besides the head and tail nodes: a value cannot be popped and an error message is displayed.
 * If the size is above 0, the value is popped, and output to the textfile. If the SimpleList did not exist in the first place, an error message is output and 
 * no value is popped.*/
template <typename T>
void pop(string name, list<SimpleList<T> *> &listSLT, ofstream &outFile){
	SimpleList<T>* target;
	T poppedValue;
	if (!checkExistence(listSLT, name)){
		target = getListPointer(listSLT, name);
		if (target->getSize() <= 0){
			errorMessage(2, outFile);
			return;
		}
		else if (target->getSize() > 0){
			poppedValue = target->pop();
			popMessage(poppedValue, outFile);
			return;
		}
	}
	errorMessage(1, outFile);
	return;
}

/*Parses commands from the input file, runs create, push, and pull commands based on input.
 * Holds the lists of SimpleList Pointers and handles filestream as well.
 *
 * Continously reads input (in a loop) from a textfile of commands. The first word of a line of commands is evaluated
 * to be one of three cases ("create", "push", or "pop"). Next, the datatype that the SimpleList will deal with (the datatype
 * that is pushed or popped) is determined, and SimpleLists are created, pushed to, or popped from accordingly. */
void runCommands (const string commandFileName, const string outputFileName){
	ifstream commands (commandFileName, ifstream::in);
	ofstream outFile (outputFileName, ofstream::out);

        list<SimpleList<int> *> listSLi;
        list<SimpleList<double> *> listSLd;
        list<SimpleList<string> *> listSLs;

	string cm1, cm2, cm3 = "null";
	int cmi = 0;
	double cmd = 0.0;

	while(commands >> cm1 >> cm2){		//in the loop, the first letter in the stack or queue name is used to determine the datatype
		if (cm1 == "create"){
			commands >> cm3;
			commandMessage(0, cm1, cm2, cm3, outFile);
			if (*(cm2.begin()) == 'i'){
				create(cm2, cm3, listSLi, outFile);
                        }
                        else if (*(cm2.begin()) == 'd'){
				create(cm2, cm3, listSLd, outFile);
                        }
                        else if (*(cm2.begin()) == 's'){
				create(cm2, cm3, listSLs, outFile);
                        }
		}
		else if (cm1 == "push"){
			if (*(cm2.begin()) == 'i'){
				commands >> cmi;
				commandMessage(0, cm1, cm2, cmi, outFile);
				push (cm2, cmi, listSLi, outFile);
			}
			else if (*(cm2.begin()) == 'd'){
				commands >> cmd;
				commandMessage(0, cm1, cm2, cmd, outFile);
				push (cm2, cmd, listSLd, outFile);
			}
			else if (*(cm2.begin()) == 's'){
				commands >> cm3;
				commandMessage(0, cm1, cm2, cm3, outFile);
				push (cm2, cm3, listSLs, outFile);
			}
		}
		else if (cm1 == "pop"){
			if (*cm2.begin() == 'i'){
				commandMessage(1, cm1, cm2, cm3, outFile);
				pop (cm2, listSLi, outFile);
			}
			else if (*cm2.begin() == 'd'){
				commandMessage(1, cm1, cm2, cm3, outFile);
				pop (cm2, listSLd, outFile);
			}
			else if (*cm2.begin() == 's'){
				commandMessage(1, cm1, cm2, cm3, outFile);
				pop (cm2, listSLs, outFile);
			}
		}
	}
	commands.close();
	outFile.close();
	return;
}


int main() {
	string commandFileName, outputFileName;

	getInOutFile(commandFileName, outputFileName);			// Asks for names of input and output files

	runCommands(commandFileName, outputFileName);

	return 0;
}

// COMSC-210 | Midterm #2 | Anthony R. Sarabia
// IDE used: Visual Studio
#include <iostream>
#include <iomanip>
#include <cstdlib>   
#include <string>    
#include <vector>     
#include <fstream>    
#include <ctime>      
#include <functional> 

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int simulation_periods = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    } 

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;

        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return;

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1) {
            pop_front();
            return;
        }

        Node* temp = head;

        for (int i = 1; i < pos; i++) {
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next) {
            pop_back();
            return;
        }

        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl; 
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    //Seed the random generator
    srand(static_cast<unsigned int>(time(0)));

    //Initilaize line
    DoublyLinkedList list;

    //Read actual file before you create something to read each line
    string file = "names.txt";
    ifstream inFile(file);

    //Create a vector to store each customer/name
    vector<int> customers;

    //Variable to represent line
    string fileLine;

    //Let's create some more variables to represent each probability


    //Create something here to read each line from file. For this, let's use a while loop
    while(getline(inFile, fileLine)) { // error fixed: file->inFile. simple typo in my variable used..
        //and add each line to vector
        if (!fileLine.empty()) {
            int customer = stoi(fileLine);
            customers.push_back(customer); // this line adds our
        }
    }

    //When the store opens (i.e. in first time period), add 5 customers to the line right away. (i got this from assignment instructions)
    //We can add five customers using a simple for-loop
    cout << "STORE OPENS!: " << endl;

    for (int i = 0; i < 5; i++) {
        if (i < customers.size()) {
            int customer = customers[i];
            bool customerVip = rand() % 40 % < 4;
            if (customerVip) {
                list.push_back(customer);
            }
            else {
                list.push_back(customer);
            }
        }
    }

    //Dsipaly content (after opening)
    cout << "Resulting line" << endl;
    cout << endl;
    list.print();
    cout << endl;

    //run simulation (In subsequent time periods, the probability of...SEE BELOW!!!)


    //A customer being helped at the beginning of the line and ordering their coffee is 40 %

    
    //A new customer joining the end of the line is 60 %
    
    
    //The customer at the end of the line deciding they don't want to wait and leaving is 20%
    
    
    //Any particular customer can decide they don't want to wait and leave the line: 10%
    
    
    //A VIP(very important person) customer with a Coffee House Gold Card gets to skip the line and go straight to the counter and order: 10 %

    //Display final



    return 0;
}
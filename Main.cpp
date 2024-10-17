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
#include <map>        // For mapping customer IDs to names and VIP status

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

    // Initialize a vector to track the line order
    vector<int> line_order; 

    //Variable to represent line
    string fileLine;

    // Variable to assign unique IDs to customers
    int next_id = 1;

      //File check
    if (!inFile) {
        cerr << "Error: Unable to open file '" << file << "'." << endl;
        return 1; // Exit with error code if file reading fails
    }
     

    // Read each line from the file and add to the customers vector
    while (getline(inFile, fileLine)) {
        if (!fileLine.empty()) { // Ensure the line is not empty
            customers.push_back(fileLine);
        }
    }
    inFile.close(); // Close the file after reading

    // Map to associate each customer ID with their name and VIP status
    map<int, pair<string, bool>> id_to_name_vip;
   

    //When the store opens (i.e. in first time period), add 5 customers to the line right away. (i got this from assignment instructions)
    //We can add five customers using a simple for-loop

       // Add 5 customers to the line immediately as the store opens
    for (int i = 0; i < 5 && i < customers.size(); ++i) {
        string customer = customers[i]; // Get the customer name
        bool isVip = (rand() % 100) < 10; // 10% chance to be a VIP

        // Assign a unique ID to the customer
        int customer_id = next_id++;
        id_to_name_vip[customer_id] = make_pair(customer, vip_status); // Map ID to name and VIP status

        if (isVip) {
            list.push_front(customer_id); // VIPs join the front of the line
            cout << "    " << customer << " (VIP) joins the front of the line" << endl;
        }
        else {
            list.push_back(customer_id); // Regular customers join the end of the line
            cout << "    " << customer << " joins the line" << endl;
        }
    }

    cout << "resulting line" << endl;

    // Assuming the first 5 customers are already added abov, so Extracting customer IDs from the list is not possible without accessing private members

    for (int i = 0; i < 5 && i < customers.size(); ++i) {

        string customer = customers[i];
        bool vip_status = (rand() % 100) < 10;

    }
    line_order.clear();

    list = DoublyLinkedList();
    line_order.clear();

    for(int i = 0; i < 5 && i < customers.size(); ++i) {
        string customer = customers[i]; // Get the customer name
        bool vip_status = (rand() % 100) < 10; // 10% chance to be a VIP

        // Assign a unique ID to the customer
        int customer_id = next_id++;
        id_to_name_vip[customer_id] = make_pair(customer, vip_status); // Map ID to name and VIP status

        if (vip_status) {
            list.push_front(customer_id); // VIPs join the front of the line
            line_order.insert(line_order.begin(), customer_id); // Add to the front of the tracking vector
            cout << "    " << customer << " (VIP) joins the front of the line" << endl;
        }
        else {
            list.push_back(customer_id); // Regular customers join the end of the line
            line_order.push_back(customer_id); // Add to the end of the tracking vector
            cout << "    " << customer << " joins the line" << endl;
        }
    }

    cout << "resulting line" << endl;

    //Now, Traverse the line_order vector and print customer names in order (we'll use this to display at the end_)
    for (int id : line_order) {
        string name = id_to_name_vip[id].first;
        bool vip = id_to_name_vip[id].second;
        if (vip)
            cout << name << " (VIP)" << endl;
        else
            cout << name << endl;
    }
    cout << endl;


    // Run the simulation for the defined number of time periods

        // Run the simulation for the defined number of time periods
    for (int time_step = 1; time_step <= simulation_periods; ++time_step) {
        cout << "Time step #" << time_step << ":" << endl;

    // Event 1: 40% chance to serve a customer at the front
        int serve_prob = rand() % 100 + 1; // Generate a random number between 1 and 100
        if (serve_prob <= 40) { // 40% chance
            if (!line_order.empty()) { // Ensure the line is not empty
                int served_id = line_order.front(); // Get the first customer ID
                string served_name = id_to_name_vip[served_id].first; // Get the customer's name
                list.pop_front(); // Remove from the DoublyLinkedList
                line_order.erase(line_order.begin()); // Remove from the tracking vector
                cout << "    " << served_name << " is served" << endl;
            }
        }
    

    // Event 2: 60% chance for a new customer to join the end
        int join_prob = rand() % 100 + 1; // Generate a random number between 1 and 100
        if (join_prob <= 60) { // 60% chance
            if (customers.empty()) { // Ensure there are names available
                cout << "    No available names to add new customer." << endl;
            }
            else {
                int name_index = rand() % customers.size(); // Random index
                string new_customer = customers[name_index]; // Get the customer name

                bool vip_status = (rand() % 100) < 10; // 10% chance to be a VIP

                // Assign a unique ID to the new customer
                int new_id = next_id++;
                id_to_name_vip[new_id] = make_pair(new_customer, vip_status); // Map ID to name and VIP status


   // Event 3: 20% chance the last customer leaves the line
        int leave_end_prob = rand() % 100 + 1; // Generate a random number between 1 and 100
        if (leave_end_prob <= 20) { // 20% chance
            if (!line_order.empty()) { // Ensure the line is not empty
                int leaving_id = line_order.back(); // Get the last customer ID
                string leaving_name = id_to_name_vip[leaving_id].first; // Get the customer's name
                list.pop_back(); // Remove from the DoublyLinkedList
                line_order.pop_back(); // Remove from the tracking vector
                cout << "    " << leaving_name << " (at the rear) left the line" << endl;
            }
        }

    // Event 4: 10% chance any customer decides to leave the line
        int leave_any_prob = rand() % 100 + 1; // Generate a random number between 1 and 100
        if (leave_any_prob <= 10) { // 10% chance
            if (!line_order.empty()) { // Ensure the line is not empty
                // Select a random customer from the line
                int random_index = rand() % line_order.size();
                int leaving_id = line_order[random_index]; // Get the customer ID
                string leaving_name = id_to_name_vip[leaving_id].first; // Get the customer's name

                // Remove the customer from the DoublyLinkedList and tracking vector
                list.delete_val(leaving_id);
                line_order.erase(line_order.begin() + random_index);

                cout << "    " << leaving_name << " left the line" << endl;
            }
        }

        cout << "resulting line" << endl;

        //Dispaly final
        for (int id : line_order) {
            string name = id_to_name_vip[id].first;
            bool vip = id_to_name_vip[id].second;
            if (vip)
                cout << name << " (VIP)" << endl;
            else
                cout << name << endl;
        }
        cout << endl;
    }
        
    return 0;
}
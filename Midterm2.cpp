#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIM_TIME = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;

        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    int size() {
        int count = 0;
        Node* temp = head;
        while(temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(string v) {
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
        if (!head) return;
        Node* temp = head;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        } else
            head = tail = nullptr;

        delete temp;
    }

    void pop_back() {
        if (!tail) return;
        Node* temp = tail;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } else
            head = tail = nullptr;

        delete temp;
    }

    void delete_pos(int pos) {
    if (!head) return;

    Node* temp = head;
    int count = 1;

    while (temp && count < pos) {
        temp = temp->next;
        count++;
    }

    if (!temp) return;

    if (temp->prev) temp->prev->next = temp->next;
    else head = temp->next; // front node

    if (temp->next) temp->next->prev = temp->prev;
    else tail = temp->prev; // back node

    cout << "    " << temp->data << " left the line\n";
    delete temp;
}

    bool empty() { return head == nullptr; }

    string front() { return head ? head->data : ""; }
    string back() { return tail ? tail->data : ""; }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "     (empty)" << endl;
            return;
        }

        while (current) {
            cout << current->data << "    ";
            current = current->next;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    srand(time(0));

    // Load names
    vector<string> names;
    ifstream file("names.txt");
    if (!file) {
        cout << "Could not open names.txt" << endl;
        return 1;
    }
    string name;
    while (file >> name)
        names.push_back(name);
    file.close();

    // Coffee shop line
    DoublyLinkedList line;

    cout << "Store opens:" << endl;
    for (int i = 0; i < 5; i++) {
        string customer = names[rand() % names.size()];
        line.push_back(customer);
        cout << "     " << customer << " joins the line" << endl;
    }

    cout << "Resulting line:" << endl;
    line.print();

    // Simulation for 20 minutes
    for (int minute = 2; minute <= SIM_TIME; minute++) {
        cout << "Time step #" << minute << ":" << endl;
    
    // 40% chance: customer is served
        int prob = rand() % 100 + 1;
        if (prob <= 40 && !line.empty()) {
            cout << "     " << line.front() << " is served" << endl;
            line.pop_front();
        }

        // 60% chance: new customer joins
        prob = rand() % 100 + 1;
        if (prob <= 60) {
            string newCustomer = names[rand() % names.size()];
            cout << "     " << newCustomer << " joins the line" << endl;
            line.push_back(newCustomer);
        }

        // 20% chance: rear customer leaves
        prob = rand() % 100 + 1;
        if (prob <= 20 && !line.empty()) {
            cout << "     " << line.back() << " (at the rear) left the line" << endl;
            line.pop_back();
        }

        // 10% random customer leaves
        prob = rand() % 100 + 1;
        if (prob <= 10 && line.size() > 2) {
                int pos = rand() % (line.size() - 2) + 2;
                cout << "     Random customer: ";
                line.delete_pos(pos);
            }

        // 10% VIP skip line
        prob = rand() % 100 + 1;
        if (prob <= 10) {
            string vip = names[rand() % names.size()];
            cout << "     " << vip << " (VIP) joins the front of the line" << endl;
            line.push_front(vip);
        }

        // Show resulting line
        cout << "Resulting line:" << endl;
        line.print();
    }

        return 0;
}

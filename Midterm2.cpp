#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

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

    // Simulation for 20 mintes


        // 40% chance: customer is served


        // 60% chance: new customer joins


        // 20% chance: rear customer leaves


        // 10% random customer leaves


        // 10% VIP skip line


        // Show resulting line
        cout << "Resulting line:" << endl;
        line.print();

        return 0;
}

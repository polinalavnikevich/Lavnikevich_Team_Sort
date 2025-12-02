// Lavnikevich_Team_Sort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
Node<T>* readFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) return nullptr;

    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    T value;

    while (file >> value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) head = newNode;
        else tail->next = newNode;
        tail = newNode;
    }

    return head;
}

template <typename T>
bool isSorted(Node<T>* head) {
    while (head && head->next) {
        if (head->data > head->next->data) return false;
        head = head->next;
    }
    return true;
}

template <typename T>
void printList(Node<T>* head, int limit = 10) {
    int count = 0;
    while (head && count < limit) {
        cout << head->data << " ";
        head = head->next;
        count++;
    }
    if (head) cout << "...";
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");



    return 0;
}
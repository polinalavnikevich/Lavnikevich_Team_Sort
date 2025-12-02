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

template <typename T>
void freeList(Node<T>* head) {
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
Node<T>* copyList(Node<T>* head) {
    Node<T>* newHead = nullptr;
    Node<T>* tail = nullptr;

    while (head) {
        Node<T>* newNode = new Node<T>(head->data);
        if (!newHead) newHead = newNode;
        else tail->next = newNode;
        tail = newNode;
        head = head->next;
    }

    return newHead;
}

// Тестирование сортировки с замером времени
template <typename T>
void testSort(const string& name, Node<T>* (*sortFunc)(Node<T>*), Node<T>* head) {
    Node<T>* copy = copyList(head);

    auto start = high_resolution_clock::now();
    copy = sortFunc(copy);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    double time_ms = duration.count() / 1000.0;

    cout << name << ": " << time_ms << " мс";
    cout << " (Отсортирован: " << (isSorted(copy) ? "Да" : "Нет") << ")" << endl;

    freeList(copy);
}

//Aksinya

template <typename T>
Node<T>* merge(Node<T>* a, Node<T>* b) {
    if (!a) return b;
    if (!b) return a;

    Node<T>* result = nullptr;
    Node<T>* tail = nullptr;

    while (a && b) {
        Node<T>* smaller;
        if (a->data <= b->data) {
            smaller = a;
            a = a->next;
        }
        else {
            smaller = b;
            b = b->next;
        }

        smaller->next = nullptr;
        if (!result) result = smaller;
        else tail->next = smaller;
        tail = smaller;
    }

    if (a) tail->next = a;
    if (b) tail->next = b;

    return result;
}



//Aksinya


//Ира
template <typename T>
Node<T>* listInsertionSort(Node<T>* head) {
    if (!head || !head->next) return head;

    Node<T>* sorted = nullptr;

    while (head) {
        Node<T>* current = head;
        head = head->next;

        if (!sorted || current->data <= sorted->data) {
            current->next = sorted;
            sorted = current;
        }
        else {
            Node<T>* temp = sorted;
            while (temp->next && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    return sorted;
}
// Ира


// Анжелика

// Анжелика


// Даня

// Даня





int main() {
    setlocale(LC_ALL, "Russian");



    return 0;
}
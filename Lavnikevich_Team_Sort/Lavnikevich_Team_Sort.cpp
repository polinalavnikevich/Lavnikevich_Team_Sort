// Lavnikevich_Team_Sort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <limits>

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

template <typename T>
Node<T>* naturalMergeSort(Node<T>* head) {
    if (!head || !head->next) return head;

    while (true) {
        Node<T>* current = head;
        Node<T>* result = nullptr;
        Node<T>* tail = nullptr;

        while (current) {
            // Первый подсписок
            Node<T>* sub1 = current;
            Node<T>* prev = current;
            current = current->next;

            while (current && prev->data <= current->data) {
                prev = current;
                current = current->next;
            }
            prev->next = nullptr;

            if (!current) {
                if (!result) result = sub1;
                else tail->next = sub1;
                break;
            }

            // Второй подсписок
            Node<T>* sub2 = current;
            prev = current;
            current = current->next;

            while (current && prev->data <= current->data) {
                prev = current;
                current = current->next;
            }
            prev->next = nullptr;

            // Слияние
            Node<T>* merged = merge(sub1, sub2);

            if (!result) result = merged;
            else tail->next = merged;

            // Найти конец
            tail = merged;
            while (tail->next) tail = tail->next;
        }

        head = result;
        if (isSorted(head)) break;
    }

    return head;
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
        current->next = nullptr;

        if (!sorted) {
            sorted = current;
        }
        else if (current->data <= sorted->data) {
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

template <typename T>
Node<T>* polyphaseMergeSort(Node<T>* head) {
    if (!head || !head->next) return head;

    // Разделяем пополам
    Node<T>* slow = head;
    Node<T>* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node<T>* left = head;
    Node<T>* right = slow->next;
    slow->next = nullptr;

    // Рекурсивно сортируем
    left = polyphaseMergeSort(left);
    right = polyphaseMergeSort(right);

    // Сливаем
    return merge(left, right);
}
// Анжелика


// Даня

template <typename T>
Node<T>* strandSort(Node<T>* head) {
    if (!head || !head->next) return head;

    Node<T>* result = nullptr;

    while (head) {
        Node<T>* strand = head;
        Node<T>* strandTail = head;
        head = head->next;
        strandTail->next = nullptr;

        Node<T>* prev = strandTail;
        Node<T>* curr = head;
        Node<T>* prevCurr = nullptr;

        while (curr) {
            if (curr->data >= strandTail->data) {
                strandTail->next = curr;
                strandTail = curr;

                if (prevCurr) prevCurr->next = curr->next;
                else head = curr->next;

                curr = curr->next;
                strandTail->next = nullptr;
            }
            else {
                prevCurr = curr;
                curr = curr->next;
            }
        }

        if (!result) {
            result = strand;
        }
        else {
            result = merge(result, strand);
        }
    }

    return result;
}

// Даня

void showMenu() {
    cout << "\nТЕСТИРОВАНИЕ СОРТИРОВОК НА СПИСКАХ" << endl;
    cout << "1. Тестировать файл с любыми данными" << endl;
    cout << "2. Выход" << endl;
    cout << "Ваш выбор (1-2): ";
}

template<typename T>
void testAllSorts(const string& filename, Node<T>* head) {
    cout << "Первые 10 элементов: ";
    printList(head);

    cout << "\nРезультаты сортировок:" << endl;
    testSort("1. Natural Merge Sort", naturalMergeSort, head);
    testSort("2. Insertion Sort", listInsertionSort, head);
    testSort("3. Polyphase Merge Sort", polyphaseMergeSort, head);
    testSort("4. Strand Sort", strandSort, head);

    freeList(head);
}

template<typename T>
bool tryTestFile(const string& filename) {
    Node<T>* head = readFromFile<T>(filename);
    if (head) {
        cout << "\nФайл прочитан успешно." << endl;
        testAllSorts(filename, head);
        return true;
    }
    return false;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    do {
        showMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nОшибка ввода! Пожалуйста, введите число от 1 до 2." << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            string filename;
            cout << "\nВведите имя файла для тестирования: ";
            getline(cin, filename);

            if (tryTestFile<int>(filename) || tryTestFile<float>(filename) ||tryTestFile<string>(filename)) {
            }
            else {
                cout << "\nНе удалось прочитать файл." << endl;
            }

        }
        else if (choice == 2) {
            cout << "\nВыход из программы..." << endl;
        }
        else {
            cout << "\nНеверный выбор! Введите число от 1 до 2." << endl;
        }

    } while (choice != 2);

    return 0;
}
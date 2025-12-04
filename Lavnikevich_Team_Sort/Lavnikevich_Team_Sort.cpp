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


void generateDataFile(const string& filename, int type) {
    ofstream file(filename);
    srand(time(0));

    switch (type) {
    case 1:
        for (int i = 0; i < 1000; i++) {
            file << rand() % 10000 - 5000 << " ";
        }
        cout << "Создан файл data1.txt с 1000 целых чисел" << endl;
        break;

    case 2:
        for (int i = 0; i < 10000; i++) {
            file << rand() % 10000 - 5000 << " ";
        }
        cout << "Создан файл data2.txt с 10000 целых чисел" << endl;
        break;

    case 3:
    {
        for (int i = 0; i < 1000; i++) {
            char letter = 'a' + rand() % 26;
            file << letter << " ";
        }
        cout << "Создан файл data3.txt с 1000 английских букв" << endl;
        break;
    }

    case 4:
        for (int i = 1; i <= 1000; i++) {
            file << i << " ";
        }
        cout << "Создан файл data4.txt с 1000 чисел (уже отсортированный)" << endl;
        break;

    case 5:
        for (int i = 0; i < 1000; i++) {
            float val = (rand() % 10000 - 5000) / 100.0f;
            file << val << " ";
        }
        cout << "Создан файл data5.txt с 1000 дробных чисел" << endl;
        break;
    }

    file.close();
}

void showMenu() {
    cout << "\nТЕСТИРОВАНИЕ СОРТИРОВОК НА СПИСКАХ" << endl;
    cout << "1. 1000 целых чисел (data1.txt)" << endl;
    cout << "2. 10000 целых чисел (data2.txt)" << endl;
    cout << "3. 1000 букв (data3.txt)" << endl;
    cout << "4. 1000 чисел отсортирванные (data4.txt)" << endl;
    cout << "5. 1000 дробных чисел (data5.txt)" << endl;
    cout << "6. Выход" << endl;
    cout << "Ваш выбор (1-6): ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    do {
        showMenu();
        cin >> choice;

        if (choice >= 1 && choice <= 5) {
            string filenames[] = { "data1.txt", "data2.txt", "data3.txt", "data4.txt", "data5.txt" };
            string descriptions[] = { "1000 целых чисел", "10000 целых чисел",
                                    "1000 букв", "1000 чисел в обратном порядке",
                                    "1000 дробных чисел" };

            string filename = filenames[choice - 1];
            string desc = descriptions[choice - 1];

            cout << "\nТест: " << desc << endl;

            if (choice == 3) {
                Node<string>* head = readFromFile<string>(filename);
                if (!head) {
                    cout << "Файл не найден! Данные будут сгенерированы." << endl;
                    generateDataFile(filename, choice);
                    head = readFromFile<string>(filename);
                }
                cout << "Первые 10 элементов: ";
                printList(head);

                cout << "\nРезультаты сортировок:" << endl;
                testSort("1. Natural Merge Sort", naturalMergeSort, head);
                testSort("2. Insertion Sort", listInsertionSort, head);
                testSort("3. Polyphase Merge Sort", polyphaseMergeSort, head);
                testSort("4. Strand Sort", strandSort, head);
                
                freeList(head);
            }
            else if (choice == 5) {
                Node<float>* head = readFromFile<float>(filename);
                if (!head) {
                    cout << "Файл не найден! Данные будут сгенерированы." << endl;
                    generateDataFile(filename, choice);
                    head = readFromFile<float>(filename);
                }
                cout << "Первые 10 элементов: ";
                printList(head);

                cout << "\nРезультаты сортировок:" << endl;
                testSort("1. Natural Merge Sort", naturalMergeSort, head);
                testSort("2. Insertion Sort", listInsertionSort, head);
                testSort("3. Polyphase Merge Sort", polyphaseMergeSort, head);
                testSort("4. Strand Sort", strandSort, head);

                freeList(head);
            }
            else {
                Node<int>* head = readFromFile<int>(filename);
                if (!head) {
                    cout << "Файл не найден! Данные будут сгенерированы." << endl;
                    generateDataFile(filename, choice);
                    head = readFromFile<int>(filename);
                }
                cout << "Первые 10 элементов: ";
                printList(head);

                cout << "\nРезультаты сортировок:" << endl;
                testSort("1. Natural Merge Sort", naturalMergeSort, head);
                testSort("2. Insertion Sort", listInsertionSort, head);
                testSort("3. Polyphase Merge Sort", polyphaseMergeSort, head);
                testSort("4. Strand Sort", strandSort, head);

                freeList(head);
            }
        }
        else if (choice == 6) {
            cout << "\nВыход из программы..." << endl;
        }
        else {
            cout << "Неверный выбор! Введите число от 1 до 6." << endl;
        }

    } while (choice != 6);

    return 0;
}
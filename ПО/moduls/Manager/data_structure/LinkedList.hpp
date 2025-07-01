#pragma once

#include <iostream>
using namespace std;


template<typename dataType>
class DoubleLinkedList {
public:
    struct ListNode {
        ListNode* prev;
        dataType data;
        ListNode* next;

        ListNode(dataType _data) : prev(nullptr), data(_data), next(nullptr) {}
            
    };


    ListNode* head;
    DoubleLinkedList() {
        this->head = nullptr;
    }

    void add(dataType value) {
        ListNode* newNode = new ListNode(value);
        if (!head) {
            head = newNode;
            return;
        }

        ListNode* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }

    void print() {
        ListNode* current = head;
        while (current) {
            cout << current->data;
            if (current->next) {
                cout << ", ";
            }
            current = current->next;
        }
        cout << endl;
    }

    void deleteNodeByValue(dataType n) {
        if (head == nullptr) {
            return;
        }

        ListNode* current = head;
        while (current != nullptr && current->data != n) {
            current = current->next;
        }

        if (current == nullptr) {
            return;
        }
        if (current == head) {
            head = current->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
        }
        else {
            current->prev->next = current->next;
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }
        }
        delete current;
    }

    void clearList() {
        ListNode* current = head;
        while (current) {
            ListNode* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
    
    string toString() {
        string result = "";
        ListNode* current = head;
        while (current) {
            result += to_string(current->data);
            if (current->next) {
                result += ", ";
            }
            current = current->next;
        }
        return result;
    }


    bool isEmpty(){
        return head == nullptr;   
    }
};

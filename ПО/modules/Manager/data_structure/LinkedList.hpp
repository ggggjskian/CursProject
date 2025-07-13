#pragma once
#include <iostream>
#include <vector>
#include<optional>
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

    ~DoubleLinkedList() {
       clearList();
    }

    DoubleLinkedList(const DoubleLinkedList& other) : head(nullptr) {
    copy(other);}


    DoubleLinkedList& operator=(const DoubleLinkedList& other) {
        if (this != &other) {
            clearList();
            copyFrom(other);
        }
        return *this;
    }

    ListNode* getHead() const { return head; } 

    void copy(const DoubleLinkedList& other) {
        if (other.head == nullptr) {
            head = nullptr;
            return;
        }

        ListNode* currentOther = other.head;
        ListNode* prevNode = nullptr;

        head = new ListNode(currentOther->data);
        prevNode = head;
        currentOther = currentOther->next;

        while (currentOther) {
            ListNode* newNode = new ListNode(currentOther->data);
            prevNode->next = newNode;
            newNode->prev = prevNode;
            prevNode = newNode;
            currentOther = currentOther->next;
        }
    }

    void add(dataType value) {

        ListNode* newNode = new ListNode(value);
        if (head == nullptr){
            head = newNode;
            return;
        }

        if (value < head->data){
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            return;
        }

        ListNode* current = head;
        while (current->next && value > current->next->data){
            current = current->next;
        }
        
        if (current->next == nullptr){
            current->next = newNode;
            newNode->prev = current;
        
        } else {
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
        }

    }

    void print() {
        ListNode* current = head;
        while (current) {
            cout << " " << current->data << " ";
            current = current->next;
        }
    }

    optional<dataType> deleteNodeByValue(dataType n) {
        if (head == nullptr) {
            return nullopt;
        }

        ListNode* current = head;
        while (current != nullptr && current->data != n) {
            current = current->next;
        }

        if (current == nullptr) {
            return nullopt;
        }

        dataType deletedValue = current->data;
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

        return deletedValue;
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
    

    bool isEmpty() {
        return head == nullptr;   
    }


    string toString(){
        string temp = "[";
        ListNode* current = head;
        while (current) {
            temp += " " + to_string(current->data) + " ";
            current = current->next;
        }
        temp +="]";

        return temp;
    }

};
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <optional>
#include <sstream>
#include <iomanip>

using namespace std;

template <typename Key, typename OtherData>
class HashTable {
    
    private:
        struct Node {
            OtherData value;
            Key key;
            int status; // 0 - свободно, 1 - занято, 2 - удалено

            Node(Key _key, OtherData _value) : key(_key), value(_value), status(1) {}
            Node() : key(), value(), status(0) {}

            bool operator==(const Node& other) const {
                return key == other.key && value == other.value;
            }
        };

        int initialSize; // длина таблицы при инициализации
        int Ntable; // текущее длина таблицы
        Node* arrNode;
        int count; // количество элементов

        double max_a = 0.75;
        double min_a = 0.25;

        void rehash(int newSize) {

            Node* oldTable = arrNode;
            int oldSize = Ntable;
            arrNode = new Node[newSize];
            Ntable = newSize;
            count = 0;

            for (int i = 0; i < oldSize; i++) {
                if (oldTable[i].status == 1) {
                    insert(oldTable[i]);
                }
            }

            delete[] oldTable;
        }

        void resizeUP() {

            double new_a = (double)count / Ntable;
            if (new_a > max_a) {
                rehash(Ntable * 2);
            }
        }

        void resizeDOWN() {

            double new_a = (double)count / Ntable;
            if (new_a < min_a && Ntable > initialSize) {
                rehash(max(initialSize, Ntable / 2));
            }
        }

        size_t hash1(const string& tempString) const {

            size_t hash = 0;
            for (char c : tempString) {
                hash += c;
            }
            return hash % Ntable;
        }

        size_t hash2(const string& tempString) const {

            size_t hash_val = 0;
            for (char c : tempString) {
                hash_val = (hash_val * 31) + c;
            }
            size_t step = hash_val  % (Ntable - 1) + 1;
            return step;
        }

        size_t hashFunction(const string& tempString, int j) const {
            return (hash1(tempString) + j * hash2(tempString)) % Ntable;
        }

        bool insert(const Node& node) {

            int j = 0;
            size_t i;
            int first_deleted = -1;

            do {
                i = hashFunction(node.key.toString(), j);
                if (arrNode[i].status == 1) {
                    if (arrNode[i].key == node.key) {
                        return false;
                    }
                }
                else {
                    if (arrNode[i].status == 2) {
                        if (first_deleted == -1) {
                            first_deleted = i;
                        }
                    }
                    else { 
                        size_t insertIn;
                        if (first_deleted != -1){ 
                            insertIn = first_deleted;}
                        else insertIn = i;
                        arrNode[insertIn].value = node.value;
                        arrNode[insertIn].key = node.key;
                        arrNode[insertIn].status = 1;
                        count++;
                        resizeUP();
                        return true;
                    }
                }
                j++;
            } while (j < Ntable);

            if (first_deleted != -1) {
                arrNode[first_deleted].value = node.value;
                arrNode[first_deleted].key = node.key;
                arrNode[first_deleted].status = 1;
                count++;
                resizeUP();
                return true;
            }

            rehash(Ntable * 2); 
            return insert(node);
        }

        bool remove(const Node& node) { 

            int j = 0;
            size_t index;

            do {

                index = hashFunction(node.key.toString(), j);

                if (arrNode[index].status == 1 && arrNode[index] == node)  {
                    arrNode[index].status = 2;
                    count--;
                    resizeDOWN();
                    return true;
                }

                if (arrNode[index].status == 0) break;

                j++;
            } while (j < Ntable);

            return false;
        }




        

    public:

        HashTable(int N) : initialSize(N), Ntable(N), arrNode(new Node[N]), count(0) {}
        ~HashTable() {
            delete[] arrNode;
        }

        bool insert(const Key& key, OtherData data){
            Node newNode = Node(key,data);
            return insert(newNode);
        }

        bool remove(const Key& key, OtherData data){
            Node newNode = Node(key,data);
            return remove(newNode);
        }

        optional<OtherData> find(const Key& key) const {
            int j = 0;
            size_t index;
            do {
                index = hashFunction(key.toString(), j);
                if (arrNode[index].status == 1 && arrNode[index].key == key) {
                   return arrNode[index].value;
                }

                if (arrNode[index].status == 0) break;
                j++;

            } while (j < Ntable);
            return nullopt;
        }


        void print() {
            cout << "------Хэш-таблица--------" << endl;
            cout << "Текущая вместимость " << Ntable << endl;
            cout << " Текущий коэфицент сбалансированности " << (double)count / Ntable << endl;

            for (int i = 0; i < Ntable; i++) {
                cout << "[" << i << "] ";
                if (arrNode[i].status == 1) {
                    cout << arrNode[i].value << " | Первичный хэш: " << hash1(arrNode[i].key.toString());
                }
                else if (arrNode[i].status == 2) {
                    cout << "DELETED";
                }
                else {
                    cout << "-";
                }
                cout << endl;
            }
        }



        string toString() const {
            
            stringstream ss;

            ss << "------Хэш-таблица--------\n";
            ss << "Текущая вместимость: " << Ntable << "\n";
            
            double loadFactor = (Ntable > 0) ? static_cast<double>(count) / Ntable : 0.0;
            ss << "Текущий коэффициент заполнения: " << fixed << setprecision(2) << loadFactor << "\n\n";

            for (int i = 0; i < Ntable; i++) {
                ss << "[" << i << "] ";
                ss << left << setw(10);

                if (arrNode[i].status == 1) {
                    ss << arrNode[i].value;
                    ss << " | Первичный хэш: " << hash1(arrNode[i].key.toString());
                } else if (arrNode[i].status == 2) {
                    ss << "DELETED";
                } else {
                    ss << "-";
                }
                ss << "\n";
            }
            
            return ss.str();
        }


        void setInitialSize(int newSize) {
            if (this->count == 0 && newSize > 0) {
                rehash(newSize);
            this->initialSize = newSize; 
            }
        }

};

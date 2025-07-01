#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template <typename Key, typename OtherData>
class HashTable {
    
    private:
        struct Node {
            OtherData value;
            Key key;
            int status; // 0 - свободно, 1 - занято, 2 - удалено

            Node(OtherData _value, Key _key) :  value(_value), key(_key), status(1) {}
            Node() :  value(), key(), status(0) {}

            bool operator==(const Node& other) const {
                return key == other.key && value == other.value;
            }
        };

        struct HelpSearch {
            int index;
            int countTrySolve;
            OtherData value;
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
                cout << "Рехеш вверх" << endl;
                rehash(Ntable * 2);
            }
        }

        void resizeDOWN() {

            double new_a = (double)count / Ntable;
            if (new_a < min_a && Ntable > initialSize) {
                cout << "Рехеш вниз" << endl;
                rehash(max(initialSize, Ntable / 2));
            }
        }

        size_t hash1(const string& tempString) {

            size_t hash = 0;
            for (char c : tempString) {
                hash += c;
            }
            return hash % Ntable;
        }

        size_t hash2(const string& tempString) {

            size_t hash_val = 0;
            for (char c : tempString) {
                hash_val = (hash_val * 31) + c;
            }
            size_t step = hash_val  % (Ntable - 1) + 1;
            return step;
        }

        size_t hashFunction(const string& tempString, int j) {
            return (hash1(tempString) + j * hash2(tempString)) % Ntable;
        }

        bool insert(const Node& node) {

            int j = 0;
            size_t i;
            int first_deleted = -1;

            do {
                i = hashFunction(node.key, j);
                if (arrNode[i].status == 1) {
                    if (arrNode[i].key == node.key) {
                        cout << "Ключ уже существует в таблице " << endl;
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

                index = hashFunction(node.key, j);

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

        HelpSearch find(const Key& key) {

            int j = 0;
            size_t index;
            HelpSearch help;

            do {
                index = hashFunction(key, j);
                if (arrNode[index].status == 1 && arrNode[index].key == key) {
                    help.index = index;
                    help.countTrySolve = j;
                    help.value = arrNode[index].value;
                    return help;
                }

                if (arrNode[index].status == 0) break;
                j++;

            } while (j < Ntable);

            help.index = -1;
            help.countTrySolve = -1;
            return help;
        }

        int tryGetValueByKey(const Key& key){
            HelpSearch result = find(key);
            if (result.index != -1) return result.value;
            else return -1;
        
        }
};

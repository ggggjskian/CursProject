#include<iostream>
#include<vector>

#include "data_structure\AVLtree.hpp"
#include "data_structure\HashTable.hpp"
#include "data_structure\HelpRecords.hpp"

using namespace std;

class Manager{
    
    private:
        AVLTree<Key, int> tree;
        HashTable<Key, int> hashtable;
        vector<recordPet> Pets;
        vector<recordVisit> Visits ;


    public:
        Manager() : hashtable(10), tree(){}

        void readPetsFile(){}

        void readVisitsFile(){}

        bool addPet(const Key& key, string type){
            if (hashtable.insert(key, Pets.size()) != false){
                Pets.push_back(recordPet(key, type)); 
                return true;   
            }

            return false;
        }

        recordPet findPet(const Key& key){
          int value = hashtable.tryGetValueByKey(key);
          if (value != -1) return Pets[value];
            // я помню что должен вернуть при else
        }


        bool removePet(const Key& key, string type){
            recordPet tempPet = recordPet(key, type);
            int value = hashtable.tryGetValueByKey(key);
            if (value == -1) {
                return false;
            }
            
            if (Pets[value] == tempPet){
                hashtable.remove(key, value);
                tree.remove(key);

                return true;
            }

            return false;
        }


        void addVisit(const Key& key, string diagnos, Doctor doctor, Time time){
            if(hashtable.find(key).index != -1){
                tree.insert(key, Visits.size());
                Visits.push_back(recordVisit(key, diagnos, doctor, time)); 
            }

        }


        
        void findVisit(){}
        void removeVisit(){}



};
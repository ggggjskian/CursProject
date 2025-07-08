#include<iostream>
#include<vector>
#include <fstream> 
#include "data_structure\AVLtree.hpp"
#include "data_structure\HashTable.hpp"
#include "data_structure\HelpRecords.hpp"
#include "data_structure\LinkedList.hpp"
#include "..\HelpFunction.hpp"
#include "..\Validator.hpp"


using namespace std;

class Manager{
    
    private:
        AVLTree<Key, int> tree;
        HashTable<Key, int> hashtable;
        vector<recordPet> Pets;
        vector<recordVisit> Visits;
        Validator validator;


    public:

        Manager() : hashtable(10), tree(){}

        void readPetsFile(string filename){

            string line;
            ifstream file(filename);
            
            if (!file.is_open()) {
                cerr << "Ошибка: не удалось открыть файл " << filename << endl;
                return;
            }

            while (getline(file, line)) {
                if (line.empty()) continue;
        
                string* temp = splitstring(line);
                if (validator.checkPetName(temp[0]) && validator.checkFIO(temp[1]) && validator.checkType(temp[2])){
                    string* temp2 = splitstring(temp[1],' ');
                    Owner owner(temp2[0],temp2[1],temp2[2]);
                    Key key(temp[0], owner);
                    if (this->addPet(key, temp[2])){
                        cout << "Прочитана запись из файла" << endl;}
                    else cout <<  "Ключ уже существует в таблице" << endl; 
                
                    delete[] temp;
                    delete[] temp2;

                } else {

                    delete[] temp;
                }
            }

            file.close();

        }

        void readVisitsFile(string filename){
            string line;
            ifstream file(filename);
            
            if (!file.is_open()) {
                cerr << "Ошибка: не удалось открыть файл " << filename << endl;
                return;
            }

            while (getline(file, line)) {
                if (line.empty()) continue;
        
                string* temp = splitstring(line);
                if (validator.checkPetName(temp[0]) && validator.checkFIO(temp[1]) && validator.checkFIO(temp[3]) && validator.checkDate(temp[4])){
                    
                    string* temp2 = splitstring(temp[1],' ');
                    Owner owner(temp2[0],temp2[1],temp2[2]);
                    Key key(temp[0], owner);
                    string* temp3 = splitstring(temp[3],' '); 
                    Doctor doctor(temp3[0],temp3[1],temp3[2]);
                    string* temp4 = splitstring(temp[4],' ');
                    Time time(stoi(temp4[0]), temp4[1], stoi(temp4[2]));
                    if (this->addVisit(key, temp[2], doctor,time)){
                        cout << "Прочитана запись из файла" << endl;}
                    else cout <<  "Нет связной записи в справочнике1" << endl; 

                    delete[] temp;
                    delete[] temp2;
                    delete[] temp3;
                    delete[] temp4;
                
                } else {


                    delete[] temp;
                }

            }
            file.close();

        }

        bool addPet(const Key& key, string type){ 
            
            if (hashtable.insert(key, Pets.size())) {
                Pets.push_back(recordPet(key, type));
                return true;   
            }

            return false;
        }

        bool addVisit(const Key& key, string diagnos, Doctor doctor, Time time){
            
            if(hashtable.find(key)){
                tree.insert(key, Visits.size());
                Visits.push_back(recordVisit(key, diagnos, doctor, time));
                return true;
            }

            return false;
        }




        bool removePet(const Key& key, string type){

            auto value = hashtable.find(key);
            if (!value) {
                return false;
            }
            
            recordPet petToDel = recordPet(key, type);
            if (Pets[*value] == petToDel){
                hashtable.remove(key, *value);

                optional<DoubleLinkedList<int>> listNumbers = tree.searchList(key);
                if (listNumbers) {
                    auto* currentNode = listNumbers->getHead();
                    while (currentNode != nullptr) {
                        int temp = currentNode->data;
                        Visits[temp].isAct = false;
                        currentNode = currentNode->next;
                    }
                }

                tree.remove(key);
                Pets[*value].isAct = false;

                return true;

            }

            return false;
        }



        bool removeVisit(const Key& key, string diagnos, Doctor doctor, const Time& time) {
            
            optional<DoubleLinkedList<int>> listNumbers = tree.searchList(key);
            if (!listNumbers) {
                return false;
            }
            
            if (listNumbers->isEmpty()) {
                return false;
            }

            int indexToDel = -1;
            auto* currentNode = listNumbers->getHead();
            recordVisit visitToDel(key, diagnos, doctor, time);

            while (currentNode != nullptr) {
                int temp = currentNode->data;

                if (temp >= 0 && temp < Visits.size() && Visits[temp].isAct && Visits[temp] == visitToDel) {
                    indexToDel = temp;
                    break;
                }
                currentNode = currentNode->next;
            }

            if (indexToDel == -1) {
                return false;
            }

            Visits[indexToDel].isAct = false;
            
            return tree.remove(key, indexToDel);
        }

    optional<recordPet> findPet(const Key& key) const {
        optional<int> index_opt = hashtable.find(key);
    

        if (index_opt) {
            int index = *index_opt;
            

            if (index >= 0 && index < Pets.size() && Pets[index].isAct) {
                return Pets[index];
            }
        }
        
        return nullopt;
    }





    vector<ReportEntry> generateReport(
        const string& ownerFioFilter, 
        const string& diagnoseFilter, 
        const Time& startDate, 
        const Time& endDate) {
            vector<ReportEntry> results;
            vector<recordVisit> allActiveVisits = getAllActiveVisits();
            
            for (const auto& visit : allActiveVisits) {
                
                if (visit.time < startDate || visit.time > endDate) {
                    continue;
                }

                if (!ownerFioFilter.empty()) {
                    if (visit.key.owner.toStringView() != ownerFioFilter) {
                        continue;
                    }
                }
                
                if (!diagnoseFilter.empty()) {
                    if (visit.diagnos.find(diagnoseFilter) == string::npos) {
                        continue;
                    }
                }

                optional<recordPet> petInfo = findPet(visit.key);
                string petTypeStr = "НЕ НАЙДЕН";
                if (petInfo) {
                    petTypeStr = petInfo->type;
                }

                ReportEntry entry;
                entry.petName = visit.key.petName;
                entry.ownerFio = visit.key.owner.toStringView();
                entry.petType = petTypeStr;
                entry.diagnos = visit.diagnos;
                entry.doctorFio = visit.doctor.toStringView();
                entry.date = visit.time.toString();

                results.push_back(entry);
            }
            
                return results;
            }



        vector<recordPet> getAllActivePets () {
            vector<recordPet> temp;
            for (auto pet : Pets){
                if (pet.isAct == true){
                    temp.push_back(pet);
                }
                else continue;
            }

            return temp;
        }


        vector<recordVisit> getAllActiveVisits () {
            vector<recordVisit> temp;
            for (auto visit : Visits ){
                if (visit.isAct == true){
                    temp.push_back(visit);
                }
                else continue;
            }
            return temp;
        }

        void printPets() {

            cout << "Вывод таблицы:" << endl;
            hashtable.print();
        
        }

        void printVisits() {

            cout << "Вывод дерева:" << endl;
            tree.printTree();
        }



        string getStringDebugTree(){
            return tree.toString();
        }

        string getStringDebugTable(){
            return hashtable.toString();
        }


};

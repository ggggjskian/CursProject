#include<iostream>
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
        recordPet Pets[1000];
        recordVisit Visits[1000];
        Validator validator;

        int petsCount;
        int visitsCount;

        AVLTree<Time, int> sortTree; 


    public:

        Manager() : hashtable(10), tree(), sortTree(), petsCount(0), visitsCount(0) {}

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
            
            if (hashtable.insert(key, petsCount)) {
                Pets[petsCount] = recordPet(key, type);
                petsCount++;
                return true;   
            }

            return false;
        }

        bool addVisit(const Key& key, string diagnos, Doctor doctor, Time time){
            
            if(hashtable.find(key)){
                tree.insert(key, visitsCount);
                sortTree.insert(time, visitsCount);
                Visits[visitsCount] = recordVisit(key, diagnos, doctor, time);
                visitsCount++;
                return true;
            }

            return false;
        }


        void removeVisitsForPet(const Key& petKey) {

            
            while (true) {
                int step = 0;
                optional<DoubleLinkedList<int>> listNumbers = tree.searchList(petKey, step);

                if (!listNumbers || listNumbers->isEmpty()) {
                    break; 
                }

                int indexToDelete = listNumbers->getHead()->data;
                
                if (indexToDelete < 0 || indexToDelete >= visitsCount) {
                    tree.remove(petKey, indexToDelete);
                    continue;
                }
                
                recordVisit visit_to_delete = Visits[indexToDelete];

                removeVisit(visit_to_delete.key, visit_to_delete.diagnos, visit_to_delete.doctor, visit_to_delete.time);
            }
        }

        bool removePet(const Key& key, const std::string& type) {

            optional<int> index_opt = hashtable.find(key);
            if (!index_opt) {
                return false;
            }
            
            int indexToDelete = *index_opt;
            if (indexToDelete < 0 || indexToDelete >= petsCount) {
                return false;
            }

            recordPet petToRemove(key, type);
            if (!(Pets[indexToDelete] == petToRemove)) {
                return false;
            }

            removeVisitsForPet(key);

            if (!hashtable.remove(key, indexToDelete)) {
                return false;
            }

            if (indexToDelete < petsCount - 1) {
                int lastPetIndex = petsCount - 1;
                auto& lastPet = Pets[lastPetIndex];
                
                hashtable.remove(lastPet.key, lastPetIndex);
                hashtable.insert(lastPet.key, indexToDelete);
                
                Pets[indexToDelete] = lastPet;
            }
            
            petsCount--;

            return true;
        }

        bool removeVisit(const Key& key, string diagnos, Doctor doctor, const Time& time) {
            
            int step  = 0;
            optional<DoubleLinkedList<int>> listNumbers = tree.searchList(key, step);
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

                if (temp < visitsCount  && Visits[temp] == visitToDel) {
                    indexToDel = temp;
                    break;
                }
                currentNode = currentNode->next;
            }

            if (indexToDel == -1) {
                return false;
            }
            
            if (!(tree.remove(key, indexToDel) && sortTree.remove(time, indexToDel))){
                return false;
            }
            
            if (indexToDel == visitsCount - 1) {
                visitsCount--;
                return true;
            }

            auto temp = Visits[visitsCount - 1]; 
            tree.remove(temp.key, visitsCount - 1); 
            sortTree.remove(temp.time, visitsCount -1);
            
            tree.insert(temp.key, indexToDel); 
            sortTree.insert(temp.time, indexToDel); 

            Visits[indexToDel] = temp;

            visitsCount--;
            
            return true;
        }


        recordPet* getPetsArray () {
            return Pets;
        }


        recordVisit* getVisitsArray () {
            return Visits;
        }

        void printPets() {

            cout << "Вывод таблицы:" << endl;
            hashtable.print();
        
        }

        void printVisits() {

            cout << "Вывод дерева:" << endl;
            tree.printTree();
        }


        int getPetsCount(){ return petsCount;}
        int getVisitsCount(){ return visitsCount;}

        string getStringDebugTree(){
            return tree.toString();
        }

        string getStringDebugTable(){
            return hashtable.toString();
        }


        int findElementsInTree(const Key& key) const {
            int stepForSearch = 0;
            optional<DoubleLinkedList<int>> result = tree.searchList(key, stepForSearch);

            if (result){
                return stepForSearch;   
            }
            return -1;
        }



   int generateReport(const std::string& ownerFioFilter, const std::string& doctorFioFilter, const Time& startDate, const Time& endDate, ReportEntry* reportResults) {
        int reportCount = 0;
        int visitIndices[1000];
        int foundCount = sortTree.findInRange(startDate, endDate, visitIndices);

        for (int i = 0; i < foundCount; ++i) {
            int idx = visitIndices[i];
            const auto& visit = Visits[idx];
            
            if (!ownerFioFilter.empty() && visit.key.owner.toStringView() != ownerFioFilter) {
                continue;
            }
            
            if (!doctorFioFilter.empty() && visit.doctor.toStringView() != doctorFioFilter) {
                continue;
            }

            optional<int> tempIndex = hashtable.find(visit.key);
            optional<recordPet> petInfo = Pets[*tempIndex];
            string petTypeStr = petInfo ? petInfo->type : "НЕ НАЙДЕН";

            reportResults[reportCount].petName = visit.key.petName;
            reportResults[reportCount].ownerFio = visit.key.owner.toStringView();
            reportResults[reportCount].petType = petTypeStr;
            reportResults[reportCount].diagnos = visit.diagnos;
            reportResults[reportCount].doctorFio = visit.doctor.toStringView();
            reportResults[reportCount].date = visit.time.toString();

            reportCount++;
        }
                
        return reportCount;
    }


        

};
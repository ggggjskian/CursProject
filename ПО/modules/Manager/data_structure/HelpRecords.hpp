#pragma once
#include<iostream>

using namespace std;


struct Person {
            string surname;
            string name;
            string secondname;
            
            bool operator==(const Person& other) const {
                return name == other.name && surname == other.surname && secondname == other.secondname;
            }
            
            bool operator<(const Person& other) const {
                if (name != other.name) return name < other.name;
                if (surname != other.surname) return surname < other.surname;
                else return secondname < other.secondname;
            }
            
            bool operator>(const Person& other) const {
                return other < *this;
            }

            Person(string _surname, string _name, string _secondname ): surname(_surname), name(_name), secondname(_secondname){}
            Person( ): name(""), surname(""), secondname(""){}

            string toString() const {
                return surname + name + secondname;
            }

            string toStringView() const {
                return surname + " " + name + " " + secondname;
            }
};
        
struct Owner : Person {
    using Person::Person;
};

struct Doctor : Person {
    using Person::Person;
};

struct Time {
        int day;
        int month;
        int years;

        static string monthArr[12];
        bool operator==(const Time& other) const {
            return day == other.day && month == other.month && years == other.years;
        }

        bool operator<(const Time& other) const {

            if(years != other.years) return years < other.years;
            if (month != other.month) return month < other.month;
            return day < other.day;
        }

        bool operator>(const Time& other) const {
            return other < *this;
        }

        int monthToNumber(string month){

            for (int i = 0; i < 12; i++){
                if (month == monthArr[i]) return i;
            }
            throw invalid_argument("Invalid month name");
        }

        string numberToMonth(int number) const {
            return monthArr[number];
        }

        string toString() const {
            return to_string(day) + " " + numberToMonth(month) + " " + to_string(years);
        }

        Time(int _day, string _month, int _years){

            if (_years < 2000|| _years > 2025) {
                throw invalid_argument("Invalid year: " + to_string(_years));
            }

            this->years = _years;

            this->month = monthToNumber(_month);

            int max_days = 31;
            if (this->month == 3 || this->month == 5 || this->month == 8 || this->month == 10) { 
                max_days = 30;
            } else if (this->month == 1) { 
                bool isLeap = (_years % 4 == 0 && _years % 100 != 0) || (_years % 400 == 0);
                max_days = isLeap ? 29 : 28;
            }
            
            if (_day < 1 || _day > max_days) {
                throw invalid_argument("Invalid day: " + to_string(_day) + " for month " + _month);
            }
            this->day = _day;
        } 


        Time(): day(0), month(0), years() {}
};

inline string Time::monthArr[12] = {
        "январь", "февраль", "март",
        "апрель", "май", "июнь", 
        "июль", "август", "сентябрь", 
        "октябрь", "ноябрь", "декабрь"}; 


struct Key {
    string petName;
    Owner owner;
    
    bool operator==(const Key& other) const {
        return petName == other.petName && owner == other.owner;
    }

    bool operator<(const Key& other) const {
        if (petName != other.petName) return petName < other.petName;
        return owner < other.owner;
    }

    bool operator>(const Key& other) const {
       return other < *this;
    }

    
    Key(string _petName, Owner _owner): petName(_petName), owner(_owner){}
    Key(): petName(), owner(){}  

    string toString() const {
        return petName + owner.toString();
    }

    string toStringView() const {
        return petName + " " + owner.toStringView();
    }
};

struct recordPet {
    Key key;
    string type;
    bool isAct;

    recordPet(Key _key, string _type): key(_key), type(_type), isAct(true) {}
    recordPet(): key(), type(""){}

    bool operator==(const recordPet& other) const {
        return key == other.key && type == other.type;
    }

    string toString() {
        return key.toString() + " " + type;
    }

};

struct recordVisit {
    Key key;
    string diagnos;
    Doctor doctor;
    Time time;

    recordVisit(Key _key, string _diagnos, Doctor _doctor, Time _time) : 
                 key(_key), diagnos(_diagnos), doctor(_doctor), time(_time) {
    }

    recordVisit() : key(), diagnos(""), doctor(), time(){}


    bool operator==(const recordVisit& other) const {
        return key == other.key && diagnos == other.diagnos && doctor == other.doctor && time == other.time;
    }


    string toString() {
        return key.toString() + " " + diagnos + " " + doctor.toStringView() + " " + time.toString();
    }

};


struct ReportEntry {
    string petName;
    string ownerFio;
    string petType;
    string diagnos;
    string doctorFio;
    string date;
};
#pragma once
#include<iostream>

using namespace std;
struct Person {
            string name;
            string surname;
            string secondname;
            
            bool operator==(const Person& other) const {
                return name == other.name && surname == other.surname && secondname == other.secondname;
            }
            
            bool operator<(const Person& other) const {
                if (name != other.name) return name < other.name;
                if (surname != other.surname) return surname < other.surname;
                else return surname < other.secondname;
            }
            
            bool operator>(const Person& other) const {
                if (name != other.name) return name > other.name;
                if (surname != other.surname) return surname > other.surname;
                if (secondname != other.secondname) return surname > other.secondname;
            }

            Person(string _name, string _surname, string _secondname ): name(_name), surname(_surname), secondname(_secondname){}
            Person( ): name(""), surname(""), secondname(""){}
};
        
struct Owner : Person {};

struct Doctor : Person {};

struct Time{
    int day;
    int month;
    int years;

    bool operator==(const Time& other) const {
        return day == other.day && month == other.month && years == other.years;
    }

    Time(int _day, int _month, int _years): day(_day), month(_month), years(_years) 
    {} 
};

struct Key {
    string petName;
    Owner owner;
    
    bool operator==(const Key& other) const {
        return petName == other.petName && owner == other.owner;
    }

    bool operator<(const Key& other) const {
        if (petName != other.petName) return petName < other.petName;
        else owner < other.owner;
    }

    bool operator>(const Key& other) const {
        if (petName != other.petName) return petName > other.petName;
        else owner > other.owner;
    }

    
    Key(string _petName, Owner _owner): petName(_petName), owner(_owner){} 
};

struct recordPet {
    Key key;
    string type;

    recordPet(Key _key, string _type): key(_key), type(_type) {}

    bool operator==(const recordPet& other) const {
        return key == other.key && type == other.type;
    }

};

struct recordVisit {
    Key key;
    string diagnos;
    Doctor doctor;
    Time time;

    recordVisit(Key _key, string _diagnos, Doctor _doctor, Time _time) : 
                 key(_key), diagnos(_diagnos), doctor(_doctor), time(_time){}

    bool operator==(const recordVisit& other) const {
        return key == other.key && diagnos == other.diagnos && doctor == other.doctor && time == other.time;
    }

};
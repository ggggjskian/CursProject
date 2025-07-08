#pragma once

#include<iostream>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <string>

using namespace std;

class Validator {
    
    public:
    
        Validator() = default;

        static bool checkFIO(const string& fio) {

                QString q_fio = QString::fromUtf8(fio.c_str());
                QRegularExpression pattern(u8"^[А-ЯЁ][а-яё]+(?:-[А-ЯЁ][а-яё]+)? [А-ЯЁ][а-яё]+(?:-[А-ЯЁ][а-яё]+)? [А-ЯЁ][а-яё]+$");
                return pattern.match(q_fio).hasMatch(); 
        }

        static bool checkPetName(const string& petName) {

            QString q_petName = QString::fromUtf8(petName.c_str());
            QRegularExpression pattern(u8"^[А-ЯЁ][а-яё]+(?:-[А-ЯЁ][а-яё]+)*$");
            return pattern.match(q_petName).hasMatch();         
        }

        static bool checkType(const string& type) {

            QString q_type = QString::fromUtf8(type.c_str());
            QRegularExpression pattern(u8"^[а-яё]+$", QRegularExpression::CaseInsensitiveOption);
            return pattern.match(q_type).hasMatch();
        }

        static bool checkDate(const std::string& dateStr) {
            
            size_t firstSpace = dateStr.find(' ');
            if (firstSpace == string::npos) {
                return false;
            }
            
            size_t secondSpace = dateStr.find(' ', firstSpace + 1);
            if (secondSpace == string::npos) {
                return false;
            }

            string dayPart = dateStr.substr(0, firstSpace);
            string monthPart = dateStr.substr(firstSpace + 1, secondSpace - (firstSpace + 1));
            string yearPart = dateStr.substr(secondSpace + 1);

            try {
                Time testTime(stoi(dayPart), monthPart, stoi(yearPart));
            } catch (const exception& e) {
                return false;
            }

            return true;
        }

};
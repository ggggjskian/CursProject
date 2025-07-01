#pragma once
#include <iostream>
using namespace std;

string* splitstring(string text, char delimetr = ';') {

    int countDelimetr = 1;
    for (char c : text) {
        if (c == delimetr) {
            countDelimetr += 1;
        }
    }

    string* arr = new string[countDelimetr];
    size_t begin = 0;
    size_t end = text.find(delimetr);
    int indexArr = 0;

    while (end != (-1)) {
        arr[indexArr] = text.substr(begin, end - begin);
        begin = end + 1;
        end = text.find(delimetr, begin);
        indexArr += 1;
    }
    arr[indexArr] = text.substr(begin);

    return arr;
}


#include<iostream>
using namespace std;

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t capacity;
    size_t length;

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < length; ++i) {
            newData[i] = std::move(data[i]);
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArray() : data(nullptr), capacity(0), length(0) {}

    ~DynamicArray() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (length >= capacity) {
            resize(capacity ? capacity * 2 : 1);
        }
        data[length++] = value;
    }

    T& operator[](size_t index) {
        return data[index];
    }
};


int main(){
    DynamicArray<int> newArray;
}
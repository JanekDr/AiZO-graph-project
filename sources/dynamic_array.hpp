#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    DynamicArray(size_t initialCapacity=5) : size(0), capacity(initialCapacity) {
        data = new T[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    void resize(size_t newCapacity) {
        if (newCapacity == capacity) return;
        
        delete[] data;
        data = new T[newCapacity];
        capacity = newCapacity;
        size = 0;
    }    

    void add(T value) {
        if (size >= capacity){
            cout<<"Przekroczono pojemnosc tablicy"<<endl;
            return;
        }
        data[size++] = value;
    }

    void print() const {
        for (size_t i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    

    T get(size_t index) const {
        if (index >= size) {
            cerr << "Błąd: Indeks poza zakresem!" << endl;
            return T();
        }
        return data[index];
    }

    void set(size_t index, T value) {
        if (index >= size) {
            cerr << "Błąd: Indeks poza zakresem!" << endl;
            return;
        }
        data[index] = value;
    }

    void swap(size_t i, size_t j) {
        T temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }

    size_t getSize() const {
        return size;
    }    
};
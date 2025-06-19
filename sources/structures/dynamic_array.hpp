#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

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
    DynamicArray(size_t initialCapacity=5, T initialValue = T()) : size(0), capacity(initialCapacity) {
        data = new T[capacity];
        // for (size_t i = 0; i < capacity; ++i) {
        //     data[i] = initialValue;  // Inicjalizujemy wszystkie komórki tablicy
        // }
    }

    ~DynamicArray() {
        delete[] data;
    }

    void resize(size_t newCapacity) {
        if (newCapacity <= capacity) return;
        
        T* newData = new T[newCapacity];
        
        // Kopiuj istniejące dane
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        
        delete[] data;
        data = newData;
        capacity = newCapacity;
        // WAŻNE: NIE resetuj size = 0 !!!
    }
    

    void add(T value) {
        if (size >= capacity){
            cout<<"Przekroczono pojemnosc tablicy podczas dodawania"<<endl;
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
            cerr << "Blad: Indeks poza zakresem, podczas zwracania wartosci tablicy!" << endl;
            return T();
        }
        return data[index];
    }

    void set(size_t index, T value) {
        if (index >= size) {
            cerr << "Blad: Indeks poza zakresem, podczas ustawiania wartosci tablicy!" << endl;
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

#endif // DYNAMIC_ARRAY_HPP
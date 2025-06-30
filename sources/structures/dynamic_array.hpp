#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t size;
    size_t capacity;

    void grow() {
        size_t newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Konstruktor
    DynamicArray(size_t initialCapacity = 5) : size(0), capacity(initialCapacity) {
        if (capacity == 0) capacity = 1;
        data = new T[capacity];
    }
    DynamicArray(size_t initialCapacity, T initialValue)
        : size(initialCapacity), capacity(initialCapacity) {
        if (capacity == 0) capacity = 1;
        data = new T[capacity];
        for (size_t i = 0; i < capacity; ++i) {
            data[i] = initialValue;
        }
    }




    // Destruktor
    ~DynamicArray() {
        delete[] data;
    }

    // Zakaz kopiowania
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    // Dodawanie elementu
    void add(T value) {
        if (size >= capacity) {
            std::cerr << "[add] Przekroczono capacity!" << std::endl;
            throw std::overflow_error("Przepełnienie DynamicArray");
        }
        data[size++] = value;
    }


    // Odczyt elementu
    T get(size_t index) const {
        if (index >= size) {
            std::cerr << "[get] Błąd: indeks " << index << " poza zakresem (size = " << size << ")" << std::endl;
            throw std::out_of_range("Indeks poza zakresem");
        }
        return data[index];
    }

    // Ustawianie wartości
    void set(size_t index, T value) {
        if (index >= size) {
            std::cerr << "[set] Błąd: indeks " << index << " poza zakresem (size = " << size << ")" << std::endl;
            throw std::out_of_range("Indeks poza zakresem");
        }
        data[index] = value;
    }


    // Zamiana elementów miejscami
    void swap(size_t i, size_t j) {
        if (i >= size || j >= size) {
            std::cerr << "[swap] Błąd: indeks poza zakresem!" << std::endl;
            throw std::out_of_range("Indeks poza zakresem");
        }
        T temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }

    // Wypisanie tablicy
    void print() const {
        for (size_t i = 0; i < size; ++i)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }

    // Rozmiar logiczny
    size_t getSize() const {
        return size;
    }

    // Pojemność
    size_t getCapacity() const {
        return capacity;
    }
};

#endif // DYNAMIC_ARRAY_HPP

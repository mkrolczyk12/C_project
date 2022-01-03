﻿#pragma once

#include <iostream>
using namespace std;

template<typename type> class Vector {

protected:
    type *data;
    size_t allocatedDataSize;
    size_t usingDataSize;

private:
    /**
     * Extend size of the vector - zmiana rozmiaru wektora
     * @param newSizeValue - new size for vector (nowy rozmiar wektora)
    */
    void changeVectorSize(size_t newSizeValue);

public:
    /**
     * Create empty vector - tworzenie pustego wektora
    */
    Vector();

    /**
     * Create vector with passed size - tworzenie wektora o podanym rozmiarze
     * @param usingDataSize - size of creating vector (rozmiar dla tworzonego wektora)
    */
    Vector(size_t usingDataSize);

    /**
     * Deallocating, do cleanings
     * Zwalnianie pamięci, robienie porządków
     */
    ~Vector();

    /**
     * Get element from specified index - pobieranie elementów spod przekazanego indeksu
     * @param index - index of element (indeks elementu)
     * @return reference to element (referencja do elementu)
    */
    type *at(size_t index);

    /**
     * Get address of first element - pobieranie adresu pierwszego elementu
     * @return address of first element (adres pierwszego elementu)
    */
    type *front();

    /**
     * Get address of last element - pobieranie adresu ostatniego używanego elementu
     * @return address of last element (adres ostatniego elementu)
    */
    type *back();

    /**
     * Get size of using data - pobieranie rozmiaru tablicy (uzywanej czesci)
     * @return size of using vector (rozmiar uzywanego wektora)
    */
    size_t size();

    /**
     * Add new element on the end of vector - dodaj nowy element na koniec wektora
     * @param newRecord - new value (nowa wartosc)
    */
    void pushBack(type newRecord);

    /**
     * Delete last element
     * Usuwanie ostatniego elementu
     */
    void popBack();

    /**
     * Check vector is empty - sprawdzanie, czy wektor jest pusty
     * @return true if vector is empty, false if not empty (prawda jezeli pusty, falsz jezeli niepusty)
    */
    bool isEmpty();

    /** Dodatkowe
     * Delete all elements
     * Usuwanie wszystkich elementów z wektora
     */
    void clear();
    
    /** Dodatkowe
     * Reallocate data to fit allocated data to using data
     * Realokowanie pamięci, aby dopasować rozmiar zaalokowanej tablicy do używanej
     */
    void shrinkToFit();
    
    /**
     * Delete element on passed index
     * Usuwanie elementu pod wskazanym indeksem
     * @param index - index of element to erase (indeks wskazanego elementu do usuniecia)
    */
    void erase(size_t index);
};

// Implementation

template<typename type>
inline Vector<type>::Vector() {
    data = new type[1];
    allocatedDataSize = 1;
    usingDataSize = 0;
}

template<typename type>
Vector<type>::Vector(size_t usingDataSize) {
    data = new type[usingDataSize];
    this->allocatedDataSize = usingDataSize;
    this->usingDataSize = 0;
}

template<typename type>
Vector<type>::~Vector() {
    delete[] data;
    data = nullptr;
}

template<typename type>
type* Vector<type>::at(size_t index) {
    if (index >= 0 && index < usingDataSize) return &data[index];
    else throw out_of_range("Index out of range");
}

template<typename type>
type* Vector<type>::front() {
    return size() >= 1 ? &data[0] : throw exception("Given vector is empty");
}

template<typename type>
type* Vector<type>::back() {
    return size() >= 1 ? &data[usingDataSize - 1] : throw exception("Given vector is empty");
}

template<typename type>
size_t Vector<type>::size() {
    return usingDataSize;
}

template<typename type>
void Vector<type>::pushBack(type newRecord) {
    if (usingDataSize >= allocatedDataSize) changeVectorSize(allocatedDataSize + 1);
    data[usingDataSize++] = newRecord;
}

template<typename type>
void Vector<type>::popBack() {
    data[usingDataSize].~type();
    --usingDataSize;
}

template<typename type>
bool Vector<type>::isEmpty() {
    return usingDataSize == 0 ? true : false;
}

template<typename type>
void Vector<type>::clear() {
    usingDataSize = allocatedDataSize = 0;
    data = nullptr;
}

template<typename type>
void Vector<type>::shrinkToFit() {
    changeVectorSize(usingDataSize);
}

template<typename type>
void Vector<type>::erase(size_t index) {
    type *i = &data[index];
    type *j = &data[index];
    ++i;

    for (; i != data + allocatedDataSize; ++i, ++j) *j = *i;

    usingDataSize--;
}

template<typename type>
void Vector<type>::changeVectorSize(size_t newSizeValue) {
    if (data == 0) {
        usingDataSize = 0;
        allocatedDataSize = 0;
    }

    type* buffer = new type[newSizeValue];
    allocatedDataSize = newSizeValue;

    size_t l_size = newSizeValue < usingDataSize ? newSizeValue : usingDataSize;

    for (size_t i = 0; i < l_size; i++) buffer[i] = data[i];

    delete[] data;
    data = buffer;
}


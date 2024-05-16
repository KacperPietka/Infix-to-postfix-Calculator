#pragma once

class DynamicArray {
private:
    char* data;
    int capacity;
    int size;

    void resize(int newCapacity) {
        char* newData = new char[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArray() : data(nullptr), capacity(0), size(0) {}


    // Copy constructor
    DynamicArray(const DynamicArray& other) : data(nullptr), capacity(0), size(0) {
        *this = other;
    }

    // Assignment operator (copy)
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            if (capacity < other.size) {
                resize(other.size);
            }
            for (int i = 0; i < other.size; ++i) {
                data[i] = other.data[i];
            }
            size = other.size;
        }
        return *this;
    }

    void add(char value) {
        if (size >= capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            resize(newCapacity);
        }
        data[size++] = value;
    }

    int getSize() const {
        return size;
    }

    char& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void clear() {
        delete[] data;
        data = nullptr;
        capacity = 0;
        size = 0;
    }

    ~DynamicArray() {
        delete[] data;
    }
};

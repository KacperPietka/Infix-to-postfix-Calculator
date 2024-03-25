#pragma once

class Node_int {
public:
    int Value;
    Node_int* Next;
    Node_int* Prev;

    Node_int(int val) : Value(val), Next(nullptr), Prev(nullptr) {}
};


#pragma once

class Node {
public:
    char Value;
    Node* Next;
    Node* Prev;

    Node(char val) : Value(val), Next(nullptr), Prev(nullptr) {}
};

#pragma once
#include "Node.h"
#include <iostream>

class Stack_char
{
private:
    Node_char* head_stack;
    int stack_size;
public:
    Stack_char() : head_stack(nullptr), stack_size(0) {}

    void push(char val) {
        Node_char* newNode = new Node_char(val);
        newNode->Next = head_stack;
        head_stack = newNode;
        stack_size++;
    }
    void pop() {
        if (!empty()) {
            Node_char* temp = head_stack;
            head_stack = head_stack->Next;
            delete temp;
            stack_size--;
        }
        else {
            std::cout << "Stack underflow! Cannot pop element." << std::endl;
        }
    }
    char top() const {
        if (!empty()) {
            return head_stack->Value;
        }
        std::cout << "Stack is empty! No top element." << std::endl;
        return -1;
    }

    int size() const {
        return stack_size;
    }

    bool empty() const {
        return head_stack == nullptr;
    }
    ~Stack_char() {
        while (!empty()) {
            pop();
        }
    }
};


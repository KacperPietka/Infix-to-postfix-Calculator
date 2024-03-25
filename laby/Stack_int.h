#pragma once
#include "Node_int.h"
#include <iostream>

class Stack_int
{
private:
    Node_int* head_stack;
    int stack_size;
public:
    Stack_int() : head_stack(nullptr), stack_size(0) {}

    Stack_int(const Stack_int& other) : head_stack(nullptr), stack_size(0) {
        // Copy constructor to initialize from another stack
        Node_int* temp = other.head_stack;
        while (temp != nullptr) {
            push(temp->Value);
            temp = temp->Next;
        }
    }

    void push(int val) {
        Node_int* newNode = new Node_int(val);
        newNode->Next = head_stack;
        head_stack = newNode;
        stack_size++;
    }
    void pop() {
        if (!empty()) {
            Node_int* temp = head_stack;
            head_stack = head_stack->Next;
            delete temp;
            stack_size--;
        }
        else {
            std::cout << "Stack underflow! Cannot pop element." << std::endl;
        }
    }
    int top() const {
        if (!empty()) {
            return head_stack->Value;
        }
        std::cout << "Stack is empty! No top element." << std::endl;
        return -1;
    }

    int size()  const {
        return stack_size;
    }

    bool empty() const {
        return head_stack == nullptr;
    }

    Stack_int& operator=(const Stack_int& other) {
        if (this == &other) // self-assignment check
            return *this;

        // Copy elements from other stack in reverse order
        Node_int* temp = other.head_stack;
        Stack_int tempStack;
        while (temp != nullptr) {
            tempStack.push(temp->Value);
            temp = temp->Next;
        }

        // Reversing the order while pushing into this stack
        while (!tempStack.empty()) {
            push(tempStack.top());
            tempStack.pop();
        }

        return *this;
    }

    ~Stack_int() {
        while (!empty()) {
            pop();
        }
    }
};

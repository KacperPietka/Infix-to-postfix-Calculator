#include <iostream>
#include "Stack_char.h"
#include "DynamicArray.h"
#include "Stack_int.h"
#include "Node.h"
#include "Node_int.h"


#define MAX 'X'
#define MIN 'Y'
#define IF 'F'
#define N 'N'
#define MULTIPLICATION '*'
#define ADDITION '+'
#define SUBSTRACTION '-'
#define DIVISION '/'



void insert(Node*& head, char Value) {
    auto* temp = new Node(Value);

    if (head == nullptr) {
        head = temp;
    }
    else {
        Node* current = head;
        while (current->Next != nullptr) {
            current = current->Next;
        }
        current->Next = temp;
        temp->Prev = current;
    }
}


bool IS_DIGIT(char number)
{
    if (number >= '0' && number <= '9')
    {
        return true;
    }
    else
    {
        return false;
    }
}

void cleanList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->Next;
        delete temp;
    }
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == N)
        return 3;
    if (op == IF)
        return 4;
    if (op == MIN || op == MAX)
        return 5;
    return 0;
}


void Push_char_Postfix(Stack_int* Count_stack, Stack_char* Simple_operations, Node*& Postfix)
{
    if (!Count_stack->empty()) {
        if (Simple_operations->top() == MAX || Simple_operations->top() == MIN) {
            int number = Count_stack->top();
            char number_to_insert = ' ';
            while (number > 0) {
                int digit = number % 10;
                number_to_insert = '0' + digit;
                insert(Postfix, number_to_insert);
                number /= 10;
            }
            Count_stack->pop();
        }
    }
}

void CountStackOperations(Stack_int* Count_stack, char current_operation)
{
    if (!Count_stack->empty()) {
        if (current_operation == IF)
        {
            int count = Count_stack->top();
            Count_stack->pop();
            Count_stack->push(count - 2);
        }
        else if (current_operation == N)
        {
            int count = Count_stack->top();
            Count_stack->pop();
            Count_stack->push(count);
        }
        else if (current_operation == 'M')
        {
            int count = Count_stack->top();
            Count_stack->pop();
            Count_stack->push(count + 1);
        }
        else if (current_operation == '+' || current_operation == '/' || current_operation == '*' || current_operation == '-')
        {
            int count = Count_stack->top();
            Count_stack->pop();
            Count_stack->push(count - 1);
        }

    }
}

int Evaluation(Node*& Postfix)
{
    std::cout << std::endl;
    Stack_int Nums;
    Stack_int OutStack;
    DynamicArray Current_Num;

    int op1 = 0;
    //int op2 = 0;
    int op3 = 0;
    int number = 0;
    int min = 0, max = 0;
    Node* current = Postfix;
    while (current != nullptr && current->Value != '.') {
        if (current->Prev != nullptr && (current->Prev->Value == MIN || current->Prev->Value == MAX))
        {
            if (IS_DIGIT(current->Value))
            {
                current = current->Next;
                continue;
            }
        }
        if (!IS_DIGIT(current->Value) && current->Value == ' ' && Current_Num.getSize() > 0)
        {
            int result = 0;
            int multiplier = 1;

            for (int i = Current_Num.getSize() - 1; i >= 0; i--) {
                int digit_value = Current_Num[i] - '0';
                result += digit_value * multiplier;
                multiplier *= 10;
            }
            Nums.push(result);
            Current_Num.clear();
        }
        if (IS_DIGIT(current->Value))
        {
            Current_Num.add(current->Value);
        }
        else if (current->Value != ' ' && (!Nums.empty()))
        {
            int op2 = Nums.top();
            Nums.pop();
            if (current->Value != N && current->Value != MAX && current->Value != MIN) { op1 = Nums.top();  Nums.pop(); }
            if (current->Value == IF)
            {
                op3 = Nums.top(); Nums.pop();
            }
            switch (current->Value)
            {
                case MAX:
                    number = (current->Next->Value - '0');
                    max = op2;
                    if ((!Nums.empty()))
                    {
                        OutStack = Nums;

                        std::cout << "MAX" << number << " " << op2 << " ";
                        while (!OutStack.empty())
                        {
                            std::cout << OutStack.top() << " ";
                            OutStack.pop();
                        }
                        std::cout << std::endl;
                    }
                    else {
                        std::cout << "MAX" << number << " " << op2 << std::endl;
                    }
                    while ((!Nums.empty()) && number > 1)
                    {
                        if (max < Nums.top())
                        {
                            max = Nums.top();
                        }
                        number--;
                        Nums.pop();

                    }
                    Nums.push(max);
                    break;
                case MIN:
                    number = (current->Next->Value - '0');
                    if ((!Nums.empty()))
                    {
                        OutStack = Nums;
                        std::cout << "MIN" << number << " " << op2 << " ";
                        while (!OutStack.empty())
                        {
                            std::cout << OutStack.top() << " ";
                            OutStack.pop();
                        }
                        std::cout << std::endl;
                    }
                    else {
                        std::cout << "MIN" << number << " " << op2 << std::endl;
                    }
                    min = op2;
                    while ((!Nums.empty()) && number > 1)
                    {
                        int curr = Nums.top();
                        if (min > curr)
                        {
                            min = curr;
                        }
                        Nums.pop();
                        number--;
                    }
                    Nums.push(min);
                    break;
                case ADDITION:
                    if ((!Nums.empty()))
                    {
                        OutStack = Nums;
                        std::cout << ADDITION << " " << op2 << " " << op1 << " ";
                        while (!OutStack.empty())
                        {
                            std::cout << OutStack.top() << " ";
                            OutStack.pop();
                        }
                        std::cout << std::endl;
                    }
                    else { std::cout << ADDITION << " " << op2 << " " << op1 << " " << std::endl; }
                    Nums.push(op1 + op2);
                    break;
                case MULTIPLICATION:
                    if ((!Nums.empty()))
                    {
                        OutStack = Nums;
                        std::cout << MULTIPLICATION << " " << op2 << " " << op1 << " ";
                        while (!OutStack.empty())
                        {
                            std::cout << OutStack.top() << " ";
                            OutStack.pop();
                        }
                        std::cout << std::endl;

                    }
                    else { std::cout << MULTIPLICATION << " " << op2 << " " << op1 << " " << std::endl; }
                    Nums.push(op1 * op2);
                    break;
                case DIVISION:
                    if ((!Nums.empty()))
                    {
                        OutStack = Nums;
                        std::cout << DIVISION << " " << op2 << " " << op1 << " ";
                        while (!OutStack.empty())
                        {
                            std::cout << OutStack.top() << " ";
                            OutStack.pop();
                        }
                        std::cout << std::endl;
                    }
                    else { std::cout << DIVISION << " " << op2 << " " << op1 << " " << std::endl; }
                    if (op2 == 0) { std::cout << "ERROR"; return 0; }

                    Nums.push(op1 / op2);
                    break;
                case SUBSTRACTION:
                    if ((!Nums.empty()))
                    {
                        OutStack = Nums;
                        std::cout << SUBSTRACTION << " " << op2 << " " << op1 << " ";
                        while (!OutStack.empty())
                        {
                            std::cout << OutStack.top() << " ";
                            OutStack.pop();
                        }
                        std::cout << std::endl;
                    }
                    else {
                        std::cout << SUBSTRACTION << " " << op2 << " " << op1 << " " << std::endl;
                    }
                    Nums.push(op1 - op2);
                    break;
                case N:
                    if ((!Nums.empty()))
                    {
                        OutStack = Nums;
                        std::cout << N << " " << op2 << " ";
                        while (!OutStack.empty())
                        {
                            std::cout << OutStack.top() << " ";
                            OutStack.pop();
                        }
                        std::cout << std::endl;
                    }
                    else {
                        std::cout << N << " " << op2 << " " << std::endl;
                    }
                    Nums.push(op2 * (-1));
                    break;

                case IF:
                    if ((!Nums.empty()))
                    {
                        OutStack = Nums;
                        std::cout << "IF" << " " << op2 << " " << op1 << " " << op3 << " ";
                        while (!OutStack.empty())
                        {
                            std::cout << OutStack.top() << " ";
                            OutStack.pop();
                        }
                        std::cout << std::endl;
                    }
                    else {
                        std::cout << "IF" << " " << op2 << " " << op1 << " " << op3 << std::endl;
                    }
                    if (op3 > 0)
                    {
                        Nums.push(op1);
                    }
                    else
                    {
                        Nums.push(op2);
                    }
                    break;
                default:
                    break;
            }

        }
        current = current->Next;
    }
    std::cout << Nums.top();
    Nums.pop();
    cleanList(Postfix);
    Current_Num.clear();
    return 0;

}



void postfix_notation(char current_operation, char previous_operation, Stack_char* Simple_operations, Node*& Postfix, DynamicArray* Current_Num, Stack_int* Count_stack)
{
    if (!IS_DIGIT(current_operation) && (*Current_Num).getSize() > 0)
    {
        int result = 0;
        int multiplier = 1;

        for (int i = (*Current_Num).getSize() - 1; i >= 0; i--) {
            int digit_value = (*Current_Num)[i] - '0';
            result += digit_value * multiplier;
            multiplier *= 10;
        }
        insert(Postfix, ' ');
        if (!Count_stack->empty()) {
            int count = Count_stack->top();
            Count_stack->pop();
            Count_stack->push(count + 1);
        }
        (*Current_Num).clear();
    }
    if (IS_DIGIT(current_operation))
    {
        (*Current_Num).add(current_operation);
        insert(Postfix, current_operation);

    }
    else if (current_operation == '(')
    {
        (*Simple_operations).push(current_operation);
    }
    else if (current_operation == ',' && (!Simple_operations->empty()) && (*Simple_operations).top() != '(')
    {
        while ((*Simple_operations).top() != '(')
        {
            insert(Postfix, Simple_operations->top());
            Push_char_Postfix(Count_stack, Simple_operations, Postfix);
            insert(Postfix, ' ');
            (*Simple_operations).pop();
        }
    }
    else if (current_operation == ')')
    {
        while (!(*Simple_operations).empty() && (*Simple_operations).top() != '(') {
            insert(Postfix, Simple_operations->top());
            Push_char_Postfix(Count_stack, Simple_operations, Postfix);
            insert(Postfix, ' ');
            (*Simple_operations).pop();
        }
        (*Simple_operations).pop();
    }
    else if ((current_operation == N && previous_operation == N))
    {
        (*Simple_operations).push(N);
    }
    else if (previous_operation == 'I' && current_operation == 'N')
    {
        (*Simple_operations).push(MIN);
        Count_stack->push(0);
    }
    else if (previous_operation == 'A' && current_operation == 'X')
    {
        (*Simple_operations).push(MAX);
        Count_stack->push(0);
    }
    else if ((previous_operation == 'I' && current_operation == 'F') || current_operation == N || current_operation == '+' || current_operation == '/' || current_operation == '*' || current_operation == '-') {
        while (!(*Simple_operations).empty() && precedence((*Simple_operations).top()) >= precedence(current_operation)) {

            insert(Postfix, Simple_operations->top());
            Push_char_Postfix(Count_stack, Simple_operations, Postfix);
            insert(Postfix, ' ');
            (*Simple_operations).pop();
        }
        if (previous_operation == 'I' && current_operation == 'N')
        {
            (*Simple_operations).push(MIN);
        }
        else { (*Simple_operations).push(current_operation); }

        if ((previous_operation == 'I' && current_operation == 'N') || (previous_operation == 'A' && current_operation == 'X'))
        {
            Count_stack->push(0);
        }
    }
    CountStackOperations(Count_stack, current_operation);
}

void ClearSimpleOperations(Stack_char* Simple_operations, Node*& Postfix, Stack_int* Count_stack)
{
    while ((!Simple_operations->empty()))
    {
        insert(Postfix, Simple_operations->top());
        Push_char_Postfix(Count_stack, Simple_operations, Postfix);
        insert(Postfix, ' ');
        (*Simple_operations).pop();
    }
}

void printPostfix(Node* Postfix)// Prints linked list conetent
{
    while (Postfix != nullptr) {
        if (Postfix->Value == IF) {
            std::cout << "IF";
        }
        else if (Postfix->Value == MAX) {
            std::cout << "MAX";

        }
        else if (Postfix->Value == MIN) {
            std::cout << "MIN";
        }
        else {
            std::cout << Postfix->Value;

        }
        Postfix = Postfix->Next;
    }

}

void HandleOperations(Stack_char* Simple_operations, Node*& Postfix, Stack_int* Count_stack, DynamicArray* Current_Num)// Handles each char in all operations(formulas)
{
    char current_operation = ' ';
    int NumberOfCalculations = 0;
    std::cin >> NumberOfCalculations;

    for (int i = 0; i < NumberOfCalculations; i++) {
        char previous_operation = current_operation;
        while (current_operation != '.') {
            previous_operation = current_operation;
            std::cin >> current_operation;
            if (current_operation != ' ')
            {
                postfix_notation(current_operation, previous_operation, Simple_operations, Postfix, Current_Num, Count_stack);
            }
        }
        ClearSimpleOperations(Simple_operations, Postfix, Count_stack);
        printPostfix(Postfix);
        Evaluation(Postfix);
        cleanList(Postfix);
        std::cout << std::endl;
        std::cout << std::endl;
        current_operation = ' ';
        while (!Count_stack->empty())
        {
            Count_stack->pop();
        }
    }
}


int main() {

    Node* head = nullptr;
    Node* Postfix = nullptr;
    auto* Current_Num = new DynamicArray();
    auto* Simple_operations = new Stack_char();
    auto* Count_stack = new Stack_int();

    HandleOperations(Simple_operations, Postfix, Count_stack, Current_Num);

    return 0;

}
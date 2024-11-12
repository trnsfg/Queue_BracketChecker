#include <iostream>

class Queue {
private:
    int* data;
    int capacity;
    int front;
    int rear;
    int count;

public:
    Queue(int size) : capacity(size), front(0), rear(-1), count(0) {
        data = new int[capacity];
    }

    ~Queue() {
        delete[] data;
    }

    void enqueue(int value) {
        if (count == capacity) {
            std::cout << "Queue overflow\n";
            return;
        }
        rear = (rear + 1) % capacity;
        data[rear] = value;
        count++;
    }

    int dequeue() {
        if (count == 0) {
            std::cout << "Queue underflow\n";
            return -1;
        }
        int value = data[front];
        front = (front + 1) % capacity;
        count--;
        return value;
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == capacity;
    }

    int peek() const {
        if (isEmpty()) {
            std::cout << "Queue is empty\n";
            return -1;
        }
        return data[front];
    }
};

class BracketChecker {
private:
    char* stack;
    int top;
    int capacity;

public:
    BracketChecker(int size) : top(-1), capacity(size) {
        stack = new char[capacity];
    }

    ~BracketChecker() {
        delete[] stack;
    }

    void push(char ch) {
        if (top < capacity - 1) {
            stack[++top] = ch;
        }
    }

    char pop() {
        if (top >= 0) {
            return stack[top--];
        }
        return '\0';
    }

    char peek() const {
        if (top >= 0) {
            return stack[top];
        }
        return '\0';
    }

    bool isEmpty() const {
        return top == -1;
    }

    bool checkBrackets(const std::string& str) {
        for (char ch : str) {
            if (ch == '(' || ch == '{' || ch == '[') {
                push(ch);
            }
            else if (ch == ')' || ch == '}' || ch == ']') {
                if (isEmpty()) {
                    std::cout << "Error: Unexpected closing bracket '" << ch << "'\n";
                    return false;
                }
                char open = pop();
                if (!((open == '(' && ch == ')') || (open == '{' && ch == '}') || (open == '[' && ch == ']'))) {
                    std::cout << "Error: Mismatched brackets '" << open << "' and '" << ch << "'\n";
                    return false;
                }
            }
        }

        if (!isEmpty()) {
            std::cout << "Error: Unmatched opening bracket '" << peek() << "'\n";
            return false;
        }

        std::cout << "The bracket placement is correct.\n";
        return true;
    }
};

int main() {
    Queue queue(5);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    std::cout << "Dequeued: " << queue.dequeue() << "\n";
    std::cout << "Front of queue: " << queue.peek() << "\n";

    BracketChecker checker(100);
    std::string expression = "({x-y-z}*[x+2y]-(z+4x));";
    checker.checkBrackets(expression);

    return 0;
}

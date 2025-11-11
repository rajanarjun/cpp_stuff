#include <iostream>

class Widget {
    int* data;
public:
    Widget(int size) {
        data = new int[size]; // heap allocation inside the class
        std::cout << "Widget constructed, allocated " << size << " ints\n";
    }

    // Try commenting out this destructor, and compile again
    // If we use valgrind and check we will see that we leaked some heap memory
    // Since we didn't free data
    ~Widget() {
        delete[] data; // clean up
        std::cout << "Widget destroyed, memory freed\n";
    }

    void setValue(int index, int value) {
        data[index] = value;
    }

    void printValue(int index) const {
        std::cout << "data[" << index << "] = " << data[index] << '\n';
    }
};

int main() {
    Widget* w = new Widget(5); // dynamically allocate object itself
    w->setValue(0, 42);
    w->printValue(0);
    delete w; // destroy object, call ~Widget()

    // accessing freed memory, undefined behaviour
    w->printValue(0);

    // "double free", undefined behaviour, 
    // the memory block was returned to the heap manager when we previously 
    // used delete w. Now its again receiving the same address, and it may
    // corrupt internal data structures leading to program crash
    delete w;
}


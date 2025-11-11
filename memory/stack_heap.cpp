#include <iostream>

using namespace std;


int global_var = 42;


void func() {

    int local_var = 10; // stored on the stack
    int* heap_var = new int(20); // stored on the heap

    cout << local_var << endl;
    cout << *heap_var << endl; // need to dereference pointer to access value

    delete heap_var;
}



int* get_pointer() {
  // This will throw an warning at compilation since this is undefined behavior.
  //  and get a Seg Fault.
  //  Since x is a local variable it is stored on the stack.
  //  Whatever is stored on the stack is deleted after it goes out of scope.

  int x = 100;
  return &x;
}



void store_large_array_in_stack() {
    // Seg Fault for storing a large array in stack.
    // ulimit -s in linux will tell u the stack limit

    int arr[3000000]; // 3 million ints ≈ 12 MB (4 bytes * 3,000,000)
    arr[0] = 42;
    cout << "arr[0] = " << arr[0] << endl;
}


void store_large_array_in_heap() {
    // Storing a large array in heap doesnt cause problems.

    int* arr = new int[30000000]; // 30 million ints ≈ 120 MB
    arr[0] = 42;
    arr[29999999] = 99;

    std::cout << "arr[0] = " << arr[0] << '\n';
    std::cout << "arr[last] = " << arr[29999999] << '\n';

    delete[] arr;
}


int main() {

    func();

    int* p = get_pointer();
    cout << *p << endl;

    store_large_array_in_stack();
    store_large_array_in_heap();

    return 0;
}


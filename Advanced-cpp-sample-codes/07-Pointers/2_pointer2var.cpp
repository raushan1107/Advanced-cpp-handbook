// Pointers to a variable, and pointer arithmetic over an array.
//
// Compile: g++ -std=c++17 2_pointer2var.cpp -o pointer2var
// Run:     pointer2var.exe   (Windows)   or   ./pointer2var   (Linux/macOS)

#include<iostream>
using namespace std;

int main()
{
    // int a=11;
    // int * p = &a; // pointer variable p holds the address of variable a
    // cout << "Value of a: " << a << endl;
    // cout << "Address of a: " << &a << endl;
    // cout << "Value of pointer p (Address of a): " << p << endl;
    // a = 15; // changing value of a
    // cout << "New value of a: " << a << endl;
    // cout << "Value of pointer p (Address of a): " << p << endl; //
    // cout << "Value pointed by pointer p: " << *p << endl; //


    int arr[3] = {10, 20, 30};
    // int *ptr = arr
    // An array's NAME, used in an expression like this, automatically
    // "decays" into a pointer to its FIRST element — so `ptr` now holds
    // the address of arr[0], exactly as if you'd written `&arr[0]`.
    int *ptr = arr; // pointer variable ptr holds the address of first element of array arr
    cout << "Array elements using pointer: " << endl;
    cout << "Address of first element of array arr: " << ptr << endl;
    for(int i = 0; i < 3; i++)
    {
        // *(ptr + i)
        //   ptr + i - POINTER ARITHMETIC: this does NOT add `i` to the
        //             raw address by 1 byte at a time. Because ptr is an
        //             int*, adding i moves the address forward by
        //             i * sizeof(int) bytes — the compiler automatically
        //             scales the offset by the pointed-to type's size, so
        //             ptr+1 lands exactly on arr[1], ptr+2 on arr[2], etc.
        //   *(...)  - dereferences that computed address, reading the int
        //             stored there.
        cout << *(ptr + i) << " "; // accessing array elements using pointer arithmetic
    }
    return 0;
}

// Explanation:
// In this code, we demonstrate the use of pointers in C++. We declare an integer variable
// `a` and a pointer variable `p` that holds the address of `a`. We print the value of `a`, its address,
// and the value of the pointer `p`. We then change the value of `a` and show that the pointer still
// holds the same address, but the value it points to has changed.
// We also demonstrate how to use pointers with arrays. We declare an array `arr` and a
// pointer `ptr` that points to the first element of the array. We use pointer arithmetic to
// access and print the elements of the array.
// Note: The output of the program will show the value of `a`, its address, the value of
// the pointer `p`, and the elements of the array accessed through the pointer `ptr`.
// Real-world scenario: Pointers are often used in dynamic memory allocation, data structures
// like linked lists, and for efficient array manipulation. Understanding pointers is crucial for
// low-level programming and performance optimization in C++.
// Analogy: Think of a pointer as a signpost that points to a specific location (memory address)
// where data is stored. Just like a signpost can point to different locations, a pointer can point
// to different variables or array elements in memory.
// Note: Always ensure that pointers are initialized before use and avoid dereferencing null or
// uninitialized pointers to prevent undefined behavior.

// --------------------------------------------------------------------------
// Step-by-step execution trace (the ACTIVE code below the commented-out
// section — the comment block above never executes, it's illustrative
// only, describing what `p`/`a` WOULD do if uncommented)
// --------------------------------------------------------------------------
// STEP 1  arr = {10, 20, 30}; ptr is set to arr's address, which is the
//         SAME address as &arr[0].
// STEP 2  "Address of first element of array arr: " prints ptr's value —
//         some hexadecimal address (will differ every run, same reason as
//         1_Checkmemoryaddress.cpp).
// STEP 3  i=0: *(ptr + 0) is *(ptr), the address itself unchanged ->
//         dereferences to arr[0] = 10. Prints "10 ".
// STEP 4  i=1: *(ptr + 1) computes ptr's address PLUS 1*sizeof(int) (4
//         bytes on virtually all modern systems) -> lands exactly on
//         arr[1] -> dereferences to 20. Prints "20 ".
// STEP 5  i=2: *(ptr + 2) lands on arr[2] -> dereferences to 30. Prints
//         "30 ".
// STEP 6  Final printed line: "10 20 30 ". main() returns 0.
//
// If the commented-out block above were uncommented instead: a starts at
// 11, p holds &a; printing *p gives 11. After `a = 15;`, p's OWN value
// (the address it holds) is completely unchanged — but *p now reads 15,
// because p still points at the SAME memory location, and that location's
// contents changed.

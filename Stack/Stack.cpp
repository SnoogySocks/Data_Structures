/*
* A take on the stack class to get exponentially faster results than its STL counterpart.
*/

#include <iostream>
#include <stack>
#include "Benchmarker.h"

template<class T, const size_t Size> class Stack {
private:
    T arr[Size];    // The size of arr must be known before instantiating
    int top_i;      // top_i keeps track of the top in arr

public:
    Stack() : arr(), top_i(-1) {}     // The stack is empty when top_i = -1
    
    // Push an element onto the stack
    void push (T n) {
        arr[++top_i] = n;
    }
    /*
        Example:
        [el1, el2, el3, el4, el5]
                   ^top_i
        > a_stack.push(new);
        [el1, el2, el3, el4, el5]
                        ^top_i
        [el1, el2, el3, new, el5]
                        ^top_i
        Notice that even though el4 and el5 exist, they are never going to be accessed
        because their value will be replaced with new.
    */
    
    // Decrementing top_i simulates a "pop."
    void pop() {
        top_i--;
    }
    T top() {
        return arr[top_i];
    }
    T bottom() {
        return arr[0];
    }
    // Since top_i is zero indexed relative to the stack, add 1 to get the size
    int size() {
        return top_i+1;
    }
};

const int mxN = 1e4;

int main() {
    
    Stack<int, mxN> s1;
    stack<int> s2;
    puts("Homemade vs STL Speed Test - Test Size of 10000 Operations");
    puts("\nPush");
    printf("Homemade stack: ");
    {
        Benchmarker timer;
        for (int i = 0; i<mxN; ++i) {
            s1.push(i);
        }
    }
    printf("STL stack: ");
    {
        Benchmarker timer;
        for (int i = 0; i<mxN; ++i) {
            s2.push(i);
        }
    }

    puts("\nPop");
    printf("Homemade stack: ");
    {
        Benchmarker timer;
        for (int i = 0; i<mxN; ++i) {
            s1.pop();
        }
    }
    printf("STL stack: ");
    {
        Benchmarker timer;
        for (int i = 0; i<mxN; ++i) {
            s2.pop();
        }
    }
    
    return 0;
    
    /*
        Output:
        -----------------------------------------------------------
        Homemade vs STL Speed Test - Test Size of 10000 Operations

        Push
        Homemade stack: 1309us (1.309ms)
        STL stack: 39641us (39.641ms)

        Pop
        Homemade stack: 1426us (1.426ms)
        STL stack: 28009us (28.009ms)
        -----------------------------------------------------------
        Results (Ratio of Homemade to STL)
        Push: ~0.033
        Pop: ~0.051
        
        Note: The speed times will vary, but the ratio will approximately remain the same.
    */

}

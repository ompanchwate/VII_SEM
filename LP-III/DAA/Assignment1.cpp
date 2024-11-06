#include <iostream>
using namespace std;

int fibonacci_recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

int fibonacci_iterative(int n) {
    if (n <= 1) {
        return n;
    }
    
    int a = 0, b = 1, fib = 0;
    for (int i = 2; i <= n; i++) {
        fib = a + b;
        a = b;
        b = fib;
    }
    return b;
}

int main() {
    int n;
    cout << "Enter the position (0-indexed) of the Fibonacci number: ";
    cin >> n;

    cout << "Fibonacci number at index " << n << " (recursive) is " << fibonacci_recursive(n) << endl;
    cout << "Fibonacci number at index " << n << " (iterative) is " << fibonacci_iterative(n) << endl;

    return 0;
}

/* Recursive : 
TC : O(2^n)
SC : O(n)  Recursion stack */

/* Iterative : 
TC : O(n)
SC : O(1) */

// 0 1 1 2 3 5 8
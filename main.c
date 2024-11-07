#include <stdio.h>
#include "main.h"

int main(int argc, char* argv[]) {

    // Check if the correct number of command-line arguments is provided.
    if (argc != 2) {
        printf("%s \n", "Wrong number of args! Ex: ./SquareRoot0.exe 10048");
        return 1;
    }
    int N = 0; // Initialize variable to store input value.

    // Convert the single command-line argument into an integer.
    sscanf_s(argv[1], "%d", &N); 

    // Call SquareRoot0 function and print result.
    printf("SquareRoot0 = %i \n", SquareRoot0(N));

    return 0;
}

int SquareRoot0(int a) {

    int lzcs = CountZeros(a); // Calculate the number of leading zeros in 'a'.
    if (lzcs == 32) { // Special case: all bits are zero.
        return 0;
    }

    // Adjust count to exclude most significant bit.
    lzcs &= 0xfffffffe; 

    int idx;
    if ((lzcs - 24) < 0) { // Shift 'a' right by the adjusted count.
        idx = a >> (24 - lzcs); 
    }
    else { // Shift 'a' left by the adjusted count.
        idx = a << (lzcs - 24); 
    }

    // Return square root value from precomputed array.
    return SQRT[idx - 64] << (31 - lzcs >> 1) >> 12; 
}

int CountZeros(unsigned int idx) {

    int total_bits = sizeof(idx) * 8;
    int res = 0;

    while (!(idx & (1 << (total_bits - 1)))) {
        idx = (idx << 1); // Shift 'x' left by one bit.
        res++; // Increment the count of leading zeros.
    }

    return res;
}

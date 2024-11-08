# SquareRoot0
SquareRoot0 is an function used in Castlevania Symphony of the Night to make Square Root without a floating-point unit.

The way the devs made this code generates a mathematical anomaly that is quite difficult to understand when playing the game,
one of these cases is the Muramasa calculation, which is the sum of several variables with the square root of the number of times it absorbed blood from enemies with Muramasa.

I reimplemented this SquareRoot function with the help of sotn-decomp project, making it possible to perform this calculation with the same anomalies on any computer.

You can also find in this project a command-line tool.

```c
// Precomputed array of square roots (192 elements).
short SQRT[] = {
    0x1000, 0x101f, 0x103f, 0x105e, 0x107e, 0x109c, 0x10bb, 0x10da, 0x10f8,
    0x1116, 0x1134, 0x1152, 0x116f, 0x118c, 0x11a9, 0x11c6, 0x11e3, 0x1200,
    0x121c, 0x1238, 0x1254, 0x1270, 0x128c, 0x12a7, 0x12c2, 0x12de, 0x12f9,
    0x1314, 0x132e, 0x1349, 0x1364, 0x137e, 0x1398, 0x13b2, 0x13cc, 0x13e6,
    0x1400, 0x1419, 0x1432, 0x144c, 0x1465, 0x147e, 0x1497, 0x14b0, 0x14c8,
    0x14e1, 0x14f9, 0x1512, 0x152a, 0x1542, 0x155a, 0x1572, 0x158a, 0x15a2,
    0x15b9, 0x15d1, 0x15e8, 0x1600, 0x1617, 0x162e, 0x1645, 0x165c, 0x1673,
    0x1689, 0x16a0, 0x16b7, 0x16cd, 0x16e4, 0x16fa, 0x1710, 0x1726, 0x173c,
    0x1752, 0x1768, 0x177e, 0x1794, 0x17aa, 0x17bf, 0x17d5, 0x17ea, 0x1800,
    0x1815, 0x182a, 0x183f, 0x1854, 0x1869, 0x187e, 0x1893, 0x18a8, 0x18bd,
    0x18d1, 0x18e6, 0x18fa, 0x190f, 0x1923, 0x1938, 0x194c, 0x1960, 0x1974,
    0x1988, 0x199c, 0x19b0, 0x19c4, 0x19d8, 0x19ec, 0x1a00, 0x1a13, 0x1a27,
    0x1a3a, 0x1a4e, 0x1a61, 0x1a75, 0x1a88, 0x1a9b, 0x1aae, 0x1ac2, 0x1ad5,
    0x1ae8, 0x1afb, 0x1b0e, 0x1b21, 0x1b33, 0x1b46, 0x1b59, 0x1b6c, 0x1b7e,
    0x1b91, 0x1ba3, 0x1bb6, 0x1bc8, 0x1bdb, 0x1bed, 0x1c00, 0x1c12, 0x1c24,
    0x1c36, 0x1c48, 0x1c5a, 0x1c6c, 0x1c7e, 0x1c90, 0x1ca2, 0x1cb4, 0x1cc6,
    0x1cd8, 0x1ce9, 0x1cfb, 0x1d0d, 0x1d1e, 0x1d30, 0x1d41, 0x1d53, 0x1d64,
    0x1d76, 0x1d87, 0x1d98, 0x1daa, 0x1dbb, 0x1dcc, 0x1ddd, 0x1dee, 0x1e00,
    0x1e11, 0x1e22, 0x1e33, 0x1e43, 0x1e54, 0x1e65, 0x1e76, 0x1e87, 0x1e98,
    0x1ea8, 0x1eb9, 0x1eca, 0x1eda, 0x1eeb, 0x1efb, 0x1f0c, 0x1f1c, 0x1f2d,
    0x1f3d, 0x1f4e, 0x1f5e, 0x1f6e, 0x1f7e, 0x1f8f, 0x1f9f, 0x1faf, 0x1fbf,
    0x1fcf, 0x1fdf, 0x1fef };

int CountZeros(unsigned int idx) {

    int total_bits = sizeof(idx) * 8;
    int res = 0;

    while (!(idx & (1 << (total_bits - 1)))) {
        idx = (idx << 1); // Shift 'x' left by one bit.
        res++; // Increment the count of leading zeros.
    }

    return res;
}

int SquareRoot0(int a) {

    if (a == 0){
        return 0;
    }

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
```

This anomaly was fixed in the PSP version found in Castlevania: The Dracula X Chronicles and derivatives of it.

# Special Thanks
[sotn-decomp](https://github.com/Xeeynamo/sotn-decomp)

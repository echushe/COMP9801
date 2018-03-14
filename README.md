# Programs and algorithms of COMP9801
> This repository includes homemade C++ source code of some algorithms on behalf of subject COMP9801
## You can download this repository as a Visual Studio 2017 solution
## Multiplication
**Multiplication** is a program to implement Karatsuba algorithm dealing with multiplications of long integral numbers.
Time complexity of Karatsuba algorithm is roughly O(n^1.585).
A super integral type named **Integer** is defined in this program.
Theoretically, length of this integer can be up to 2^63 - 1 bytes which is far larger than 8-byte or 4-byte integers.

Operations implemented for this super integer:
- **left shift**
- **right shift**
- **summation**
- **subtraction**
- **multiplication**

## Stable Matching
**Problem description:**

Assume that you are running a dating agency and have n men and n women as customers;
They all attend a dinner party; after the party

- every man gives you a list with his ranking of all women present, and
- every woman gives you a list with her ranking of all men present;

Design an algorithm which produces a stable matching:
a set of n pairs p = (m; w) of a man m and a woman w so that
the following situation never happens:

for two pairs p = (m; w) and p0 = (m0; w0):
- man m prefers woman w0 to woman w, and
- woman w0 prefers man m to man m0.

Solution: **Gale - Shapley algorithm.**
- Produces pairs in stages, with possible revisions;
- A man who has not been paired with a woman will be called free.
- Men will be proposing to women.Women will decide if they accept a
proposal or not.
- Start with all men free;

While there exists a free man who has not proposed to all women


    pick such a free man m and have him propose to the highest
    ranking woman w on his list to whom he has not proposed yet;
    
    If no one has proposed to w yet
    
        she always accepts and a pair p = (m, w) is formed;

    Else

        she is already in a pair p0 = (m0, w);
        If m is higher on her preference list than m0

            the pair p0 = (m0, w) is deleted;
            m0 becomes a free man;
            a new pair p = (m, w) is formed;

        Else

            m is lower on her preference list than m0;
            the proposal is rejected and m remains free.





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
- Men will be proposing to women.Women will decide if they accept a proposal or not.
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





## Assignment1
**Assignment1** is the first homework of this course (COMP9801 or COMP9101, Algorithm design).
Specification of this homework and my answers are both uploaded here.

## Assignment2
**Assignment2** is the second homework of this course (COMP9801 or COMP9101, Algorithm design).
Specification of this homework and my answers are both uploaded here.

## Assignment3
**Assignment3** is the third homework of this course (COMP9801 or COMP9101, Algorithm design).
Specification of this homework and my answers are both uploaded here.

## ass2_ques4
Source code of assignment 2 question 4

## ass2_ques5
Source code of assignment 2 question 5

## ass3_ques1
Source code of assignment 3 question 1

## ass3_ques2
Source code of assignment 3 question 2

## ass3_ques3
Source code of assignment 3 question 3

## ass3_ques4
Source code of assignment 3 question 4

## ass3_ques6
Source code of assignment 3 question 6-1

## ass3_ques6_2
Source code of assignment 3 question 6-2

## frog_flies
The problem that a frog jumps over lily pads to catch as many flies as possible.

## stick_cut
The cost to cut a stick into 2 pieces is proportional to length of the stick.
What is the minimum cost to cut a stick into unit pieces?

## operator_max
How can I add operators ( +, -, * ) and brackets to array of numbers so that I can
get maximum calculation result?
For example, solution to get maximum result of -9 -8 7 6 5 4 -3 2 1 0
is (((-9)*(-8))*(7*(6*(5*(4-(((-3)*2)+(1+0)))))))

## sample_ques1
This source code is to solve the problem that how can I get a contiguous sub array
where sum of elements in this sub array is maximized.






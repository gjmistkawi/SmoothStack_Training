# Day 2 - Overflow

## 1. Fibonacci series and recursion
The only issue I ran into was the interger values eventually being too long and running over the buffer for int, and thereby flipping to extremely large negative values.
The program ran without issues and there were no warnings that something had gone wrong, I had to visually inspect the results to see the issue.
To solve this, I changed all my instances of int to long.

## 2. Interger Overflow
By setting the nth fibonacci calculation to 2^n and solving for n. The eventual equation was used to solve for n given a b-bit value.

# Day 4 Answers

## 1. Arithmetic Expressions
The only assertion that fails consistently is the final one, where Null == 0.
This fails because while setting a pointer value to 0 will make it a null pointer, the null is being compared to the interger number 0.
The x == 3.1 can fail sometimes because of drift of the float value of x.
The others work because of implicit casting, the strangest of which is the a == 97, but this works because 97 is the bit value equivalent to a.

## 2 Truth Table for Cast Operators

| | int | float | bool | char |
| int | int | float | int | int |
| float | float | float | float | float |
| bool | int | float | int | int |
| char | int | float | int | int |

## 3. Operators

## 4. Increment Operators

## 5. More Truth Tables

# Day 4 Answers

## 1. Arithmetic Expressions
The only assertion that fails consistently is the final one, where Null == 0.
This fails because while setting a pointer value to 0 will make it a null pointer, the null is being compared to the interger number 0.
The x == 3.1 can fail sometimes because of drift of the float value of x.
The others work because of implicit casting, the strangest of which is the a == 97, but this works because 97 is the bit value equivalent to a.

## 2 Truth Table for Cast Operators

| | int | float | bool | char |
|---|---|---|---|---|
| int | int | float | int | int |
| float | float | float | float | float |
| bool | int | float | int | int |
| char | int | float | int | int |

## 3. Operators
### 3.1 Unary
\+ &nbsp;&nbsp;&nbsp; Make positive

\- &nbsp;&nbsp;&nbsp; Make negative

\! &nbsp;&nbsp;&nbsp; The not operator, reverses true and false. if\(!true\)

\~ &nbsp;&nbsp;&nbsp; Bitwise-not operator, flips the bits of a variable.

\* &nbsp;&nbsp;&nbsp; Indirection, used to derefernce a pointer to get the value at that address. int x = *y;

\& &nbsp;&nbsp;&nbsp; Address of, gets the address of a variable. int* y = \&x;

\-\- &nbsp;&nbsp;&nbsp; The decrement operator and reduces the variable by 1, example: x--;

\+\+ &nbsp;&nbsp;&nbsp; The increment operator and increases the variable by 1, example: x++;

### 3.2 Binary
\+ &nbsp;&nbsp;&nbsp; The addition operator, adds 2 variables and returns the that value, 3 == 1 + 2;

\- &nbsp;&nbsp;&nbsp; The subtraction operator, sutracts the second variable from the first, 2 == 3 - 1;

\* &nbsp;&nbsp;&nbsp; The multiplication operator, multiplies the 2 values together and returns that value, 6 == 2 * 3;

\/ &nbsp;&nbsp;&nbsp; The division oeprator, divides the second value from the first, 3 == 9 / 3;

\% &nbsp;&nbsp;&nbsp; The remainder operator, divides 2 values and returns the remained, 1 == 3 % 2;

\=\= &nbsp;&nbsp;&nbsp; The equal to operator, returns true if both values are equal

\!\= &nbsp;&nbsp;&nbsp; The not equal to operator, returns true if the values are not equal

\< &nbsp;&nbsp;&nbsp; The less than operator, returns true if the left side is less than the right side

\> &nbsp;&nbsp;&nbsp; The greator than operator, returns true if the left side is greater than the right side

\<\= &nbsp;&nbsp;&nbsp; The less than or equal to operator, returns true if the left side is less than or equal to the right side

\>\= &nbsp;&nbsp;&nbsp; The greater than or equal to operator, returns true if the left side is greater than or equal to the right side

\&\& &nbsp;&nbsp;&nbsp; The logical and operator, returns true if both the left and right expressions are true

\|\| &nbsp;&nbsp;&nbsp; The logical or operator, returns true if either the left or right expressions are true

\& &nbsp;&nbsp;&nbsp; The bitwise and operator, applies the and operator at the bit level between 2 variables

\| &nbsp;&nbsp;&nbsp; The bitwise or operator, applies the or operator at the bit level between 2 variables

\^ &nbsp;&nbsp;&nbsp; The bitwise xor operator, applies the xor operator at the bit level between 2 variables

\<\< &nbsp;&nbsp;&nbsp; The bitwise left shift, shifts all bits in a variable to the left 1 space

\>\> &nbsp;&nbsp;&nbsp; The bitwise right shift, shifts all bits in a variable to the right 1 space

\= &nbsp;&nbsp;&nbsp; The assignment variable, sets the variable on the left to the value of the expression on the right

\+\= &nbsp;&nbsp;&nbsp; The addition assignment variable, sets the variable on the left to the value of the expression on the right plus the variable itself

\-\= &nbsp;&nbsp;&nbsp; The subtraction assignment variable, sets the variable on the left to the value of the expression on the right minus the variable itself

\*\= &nbsp;&nbsp;&nbsp; The multiplication assignment variable, sets the variable on the left to the value of the expression on the right mulitplied by the variable itself

\/\= &nbsp;&nbsp;&nbsp; The division assignment variable, sets the variable on the left to the value of the expression on the right divided by the variable itself

\%\= &nbsp;&nbsp;&nbsp; The remainder assignment variable, sets the variable on the left to the remainder of the value of the expression on the right divided by the variable itself 

\&\= &nbsp;&nbsp;&nbsp; Bitwise and assignment operator, applies the bitwise operator on the variable by the expression on the right, and then assigns that value to the variable

\|\= &nbsp;&nbsp;&nbsp; Bitwise or assignment operator, applies the bitwise operator on the variable by the expression on the right, and then assigns that value to the variable

\^\= &nbsp;&nbsp;&nbsp; Bitwise xor assignment operator, applies the bitwise operator on the variable by the expression on the right, and then assigns that value to the variable

\<\<\= &nbsp;&nbsp;&nbsp; Bitwise left shift assignment operator, applies the bitwise operator on the variable by the expression on the right, and then assigns that value to the variable

\>\>\= &nbsp;&nbsp;&nbsp; Bitwise right shift assignment operator, applies the bitwise operator on the variable by the expression on the right, and then assigns that value to the variable

### 3.3 Ternary
\? &nbsp;&nbsp;&nbsp; The conditional operator and is used to determine which expression to execute based on the first expression evaluated, example: \(x == 0\) ? \(y = 2\) : \(y = 3\);


## 4. Increment Operators
The expressions works because \(y = x+++2\); adds 2 to x and then assigns that value to y, and then once the expression is complete, x is incremented. If the expression was \(y = ++x+2\), then you would end up with y = 7 because you would increment x before the rest of the expression takes place.
## 5. More Truth Tables
| x | y | AND | OR |
| -- | -- | -- | --- |
| true | true | true | true |
| true | false | false | true |
| false | true | false | true |
| false | false | false | false |

| x | NOT |
|---|-----|
|true|false|
|false|true|
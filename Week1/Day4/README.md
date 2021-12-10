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
+ &nbsp;&nbsp;&nbsp; The addition operator, adds 2 variables and returns the that value, x = 1 + 2;
- &nbsp;&nbsp;&nbsp; The subtraction operator, sutracts the second variable from the first, x = 3 - 1;
* &nbsp;&nbsp;&nbsp; The multiplication operator, multiplies the 2 values together and returns that value, x = 2 * 3;
/ &nbsp;&nbsp;&nbsp; The division oeprator, divides the second value from the first, x = 9 % 3;
% &nbsp;&nbsp;&nbsp; 
== &nbsp;&nbsp;&nbsp; 
!= &nbsp;&nbsp;&nbsp; 
\< &nbsp;&nbsp;&nbsp; 
> &nbsp;&nbsp;&nbsp; 
<= &nbsp;&nbsp;&nbsp; 
>= &nbsp;&nbsp;&nbsp; 
&& &nbsp;&nbsp;&nbsp; 
|| &nbsp;&nbsp;&nbsp; 
& &nbsp;&nbsp;&nbsp; 
| &nbsp;&nbsp;&nbsp; 
^ &nbsp;&nbsp;&nbsp; 
<< &nbsp;&nbsp;&nbsp; 
>> &nbsp;&nbsp;&nbsp; 
= &nbsp;&nbsp;&nbsp; 
+= &nbsp;&nbsp;&nbsp; 
-= &nbsp;&nbsp;&nbsp; 
*= &nbsp;&nbsp;&nbsp; 
/= &nbsp;&nbsp;&nbsp; 
%= &nbsp;&nbsp;&nbsp; 
&= &nbsp;&nbsp;&nbsp; 
|= &nbsp;&nbsp;&nbsp; 
^= &nbsp;&nbsp;&nbsp; 
<<= &nbsp;&nbsp;&nbsp; 
>>= &nbsp;&nbsp;&nbsp; 
### 3.3 Ternary
? &nbsp;&nbsp;&nbsp; The conditional operator and is used to determine which expression to execute based on the first expression evaluated, example: \(x == 0\) ? \(y = 2\) : \(y = 3\);


## 4. Increment Operators

## 5. More Truth Tables

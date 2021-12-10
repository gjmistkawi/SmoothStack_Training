# Day 3 Answers

## 2. Mixed Arrays
### 2.1 Dissimilar Arrays
You can have elements of dissimlar types in a single array by making the array an array of void pointers. 
The void pointers can then be cast to the specific type of pointer, and then dereferenced.

### 2.2 Types in Array
You cannot automatically detect what type a void* is in c++.
You would have to manually hard-cast the type and hope/assume you were casting the void pointer correctly.

## 3. Array vs Vector
The real difference for arrays and vectors, from my understanding, is in changing the sizing.
If you know that your dataset will not be growing or shrinking, then use an array.
They are dependable and fast, if simple in their uses.
Vectors are the option to go with if your dataset will be changing in size because they are more optimized for that.

## 4. Vector Performance
Inserting elements at a particular position runs at time complexity O\(N+M\), where N is the number of elements inserted and M is the number of elements moved after the new insertions.
So worst case, you are inserting at the first element and moving the entire vector worth of elements.
Best case, you are inserting at the end and not moving anything.

Pushback is almost always more efficient because you are simply adding on an element to the rear of the vector.
It has a time complexity of O\(1\).
The only time where this is not the case is when the vector runs out of space in its current memory location.
When this happens, the entire vector needs to be moved to a new location in memory, which takes up a lot of time, relatively speaking.
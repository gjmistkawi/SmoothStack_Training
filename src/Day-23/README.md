# Day 23

## Race Conditions and Deadlocks
### Race Condition - hailtsone.cpp
There is a race condition in the code here where both threads try to access the vector at the same time. This is resolved by giving the sequence object a mutex and then locking/unlocking said mutex when it is time to compute the next element in the sequence.


### Deadlock - country.cpp
When you call the lock on 2 mutex, one after the other, even with lock_gaurd, there is an opportunity for a deadlock if each thread call the mutex on their respective objects before they check the mutex of the object owned by the opposite thread. 
By using a scoped lock, calling on both mutex at the same time, the deadlock is fixed.
I checked this by running a large sample size of tests, and no deadlock occured where before a deadlock would occur fairly frequently.
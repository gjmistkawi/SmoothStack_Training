# Day 14

## 1. Copy Assignable
Class A is not copy constructible because the copy constructor is explicitly deleted.

Class B is copy constructible because the array of strings is not applicable because it is an aggregate type with no constructor/destructor.

Class C is is copy constructible, both trivially and nothrow because it constains only a primative data type.

Class D is copy constructible, but not trivially or nothrow because it has a non-primative, non-aggregate data type.

Class E is copy constructible, both trivially and nothrow beacuse their are no other base members to the class and the copy constructor is set to default.


## 2. Polymorphism with Shapes

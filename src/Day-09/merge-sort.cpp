#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

struct Student {
    string studentId; // studentId is unique
    int score; // between [1..100]
    Student(string id, int s) { studentId = id; score = s;};
    Student() {};
    bool comparator(Student x, Student y) { // returns true if score of x is less than score of y
        return x.score < y.score;
    }
};

class MergeSort {
    private:
        typedef bool (Student::*memfn)(Student x, Student y);
        memfn lessfn;
        Student* s;

        void register_comparator(Student* s, memfn ptr) {
            lessfn = ptr;
            this->s = s;
        }

        bool compare(Student x, Student y) {
            return (s->*lessfn)(x,y);
        }

        void mergeSort(vector<Student>& students, const int&& left, const int&& right) {
            if(left >= right)    //stop if group is only 1 element
                return;

            const int mid = left + (right - left) / 2;

            //left half
            mergeSort(students, (const int)left, (const int)mid);

            //right half
            mergeSort(students, (const int)(mid + 1), (const int)right);

            //merge them pieces back together
            int leftSize = mid - left + 1;
            Student* leftArr = new Student[leftSize];
            for(int i = 0; i < leftSize; i++)
                leftArr[i] = students.at(left + i);

            int rightSize = right - mid;
            Student* rightArr = new Student[rightSize];
            for(int i = 0; i < rightSize; i++)
                rightArr[i] = students.at(mid + 1 + i);

            int l = 0, r = 0;   //indeces for left and right array
            int m = left;       //index of merged

            //merge arrays back into students vector
            while(l < leftSize && r < rightSize) {
                if(compare(leftArr[l], rightArr[r])) {
                    students.at(m) = leftArr[l];
                    l++;
                }

                else {
                    students.at(m) = rightArr[r];
                    r++;
                }

                m++;
            }

            //copy remaineders over
            while(l < leftSize) {
                students.at(m) = leftArr[l];
                l++;
                m++;
            }

            while(r < rightSize) {
                students.at(m) = rightArr[r];
                r++;
                m++;
            }
        }

        

    public:
        void sort(vector<Student>& students) {  // don't use recursion directly here!
            register_comparator(&(*s), &Student::comparator);

            mergeSort(students, 0, students.size()-1);
        }
};

int main() {
    string names [10] = {"Larry", "Gary", "Bob", "Tom", "Lee", "Steve", "Jill", "Nancy", "Mike", "El"};
    int scores [10] = {60, 50, 40, 21, 38, 70, 80, 78, 100, 10};

    vector<Student> students;
    for(int i = 0; i < 10; i++) {
        students.push_back(Student(names[i], scores[i]));
    }

    cout << "Pre-sorted vector: " << endl;
    for(auto &student : students) 
        cout << "Student: " << student.studentId << ",  Score: " << student.score << endl;

    MergeSort ms;
    ms.sort(students);

    cout << endl << "Post-sorted vector: " << endl;
    for(auto &student : students) 
        cout << "Student: " << student.studentId << ",  Score: " << student.score << endl;

    //check to make sure order is smallest to largest
    Student *s1, *s2;
    s1 = &students.at(0);
    for(int i = 1; i < students.size(); i++) {
        s2 = &students.at(i);
        assert(s1->score <= s2->score);
        s1 = s2;
    }

    return 0;
}
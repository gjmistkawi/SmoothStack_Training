#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>

using namespace std;

vector<vector<int>>* generateMatrix();
vector<vector<int>>* multiplyMatrices(vector<vector<int>>*, vector<vector<int>>*);
void printMatrix(vector<vector<int>>*);


int main() {
    srand(time(0));

    vector<vector<int>>* matrix_1 = generateMatrix();
    vector<vector<int>>* matrix_2 = generateMatrix();

    cout << "Matrix 1" << endl;
    printMatrix(matrix_1);
    cout << endl << "Matrix 2" << endl;
    printMatrix(matrix_2);


    if(matrix_1->at(0).size() != matrix_2->size()) {
        cout << endl << "The matrices did not have the correct dimensions for multiplication." << endl;
        return 0;
    }

    vector<vector<int>>* result = multiplyMatrices(matrix_1, matrix_2);

    cout << endl << endl << "Multiplication Result" << endl;
    printMatrix(result);

    return 0;
}


vector<vector<int>>* generateMatrix() {
    int rows = (rand() % 5) + 1;
    int cols = (rand() % 5) + 1;

    vector<vector<int>>* matrix = new vector<vector<int>>();

    for(int i = 0; i < rows; i++) {
        vector<int> row = vector<int>();
        for(int j = 0; j < cols; j++) {
            row.push_back(rand() % 9 + 1);  // random int from 1-10
        }
        matrix->push_back(row);
    }

    return matrix;
}


void printMatrix(vector<vector<int>>* M) {
    int rows = M->size();
    int cols = M->at(0).size();

    for(int i = 0; i < rows; i++) {
        cout << "[ ";
        for(int j = 0; j < cols; j++) {
            cout << M->at(i).at(j) << " ";
        }
        cout << "]" << endl;
    }
}

vector<vector<int>>* multiplyMatrices(vector<vector<int>>* M1, vector<vector<int>>* M2) {
    vector<vector<int>>* result = new vector<vector<int>>();
    int rows = M1->size();
    int cols = M2->at(0).size();
    int elements = M1->at(0).size(); //the number of items to be multiplied

    for(int i = 0; i < rows; i++) {
        vector<int> row = vector<int>();
        for(int j = 0; j < cols; j++) {
            int value = 0;
            for( int k = 0; k < elements; k++) {
                value += M1->at(i).at(k) * M2->at(k).at(j);
            }
            row.push_back(value);
        }
        result->push_back(row);
    }
    
    return result;
}

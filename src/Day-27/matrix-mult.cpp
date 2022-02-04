#include <cassert>
#include <iostream>
#include <vector>
#include <thread>
#include <omp.h>
#include <random>

using std::vector;


vector<vector<int>*>* generateMatrix(int rows, int cols) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,10);

    vector<vector<int>*>* matrix = new vector<vector<int>*>();
    for(int i = 0; i < rows; i++) {
        matrix->push_back(new vector<int>());
        for(int j = 0; j < cols; j++)
            matrix->at(i)->push_back(dist(rng));
    }

    return matrix;
}

double parallelMatrixMult(vector<vector<int>*>* m1, vector<vector<int>*>* m2, vector<vector<int>*>* res, int threadCount) {
    // m1 = a x b
    // m2 = b x c
    int c = m2->at(0)->size();
    int b = m2->size();
    int a = m1->size();

    // Check for OpenMP
    #ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported - sorry!\n");
        return 1;
    #endif

    omp_set_num_threads(threadCount);

    std::cout << "hello" << std::endl;
    double start = omp_get_wtime();
    std::cout << start << std::endl;

    #pragma omp parallel for
    for(int i = 0; i < a; i++) {
        for(int j = 0; j < c; j++) {
            res->at(i)->at(j) = 0;
            for(int k = 0; k < b; k++)
                res->at(i)->at(j) += m1->at(i)->at(k) * m2->at(k)->at(j);
        }
    }

    double finish = omp_get_wtime();

    return (finish - start);
}

void cleanVector(vector<vector<int>*>* v) {
    for(auto ptr : *v)
        delete ptr;
    delete v;
}

int main(void) {
    int a = 1000;
    int b = 700;
    int c = 900;

    int threadCount = 6;

    vector<vector<int>*>* m1 = generateMatrix(a,b);
    vector<vector<int>*>* m2 = generateMatrix(b,c);
    vector<vector<int>*>* res = generateMatrix(a,c);

    double time = parallelMatrixMult(m1, m2, res, threadCount);
    std::cout << "time elapsed: " << time << std::endl;

    cleanVector(m1);
    cleanVector(m2);
    cleanVector(res);

    return 0;
}
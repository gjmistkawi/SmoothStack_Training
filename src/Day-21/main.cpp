#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <thread>
#include "body.cpp"
#include "../../../graph/matplotlib-cpp/matplotlibcpp.h"

namespace plt = matplotlibcpp;

double G = 6.673e-11; // Gravitational Constant    
int max_distance = 10000;
int numBodies[] = {10, 20, 50, 100, 200, 500, 1000, 2000};
int numThreads[] = {1, 2, 3, 4, 8};
double timeSegment = 5.;
int segmentCount = 5;



std::pair<long,long> simulate(std::vector<Body*>* b, double t, int k);
std::vector<Body*>* generateBodies(int n, double m);
void averageData(std::vector<std::vector<std::pair<long,long>>*>* data, int index);

void perThread(std::vector<std::pair<long,long>>* v);
void graphData(std::vector<std::vector<std::pair<long,long>>*>* data);

template<typename T>
void cleanVector(std::vector<T*>* b);


int main(void) {
    std::vector<std::vector<std::pair<long,long>>*>* data = new std::vector<std::vector<std::pair<long,long>>*>();

    // for each numThreads
    for(int m = 0; m < sizeof(numThreads)/sizeof(int); m++) {
        std::vector<std::thread> mThreads;


        // for each numThreads
        for(int i = 0; i < numThreads[m]; i++) {
            std::vector<std::pair<long,long>>* temp = new std::vector<std::pair<long,long>>();
            data->push_back(temp);
            mThreads.push_back(std::thread(perThread, temp));
        }

        // bring threads back
        for(std::thread &t : mThreads)
            t.join();

        // average the data from each thread
        averageData(data, m);
    }

    graphData(data);
    cleanVector(data);
}


// Simulate 2D N-body interactions
std::pair<long, long> simulate(std::vector<Body*>* b, double t, int k) {
    auto start = std::chrono::high_resolution_clock::now();

    auto distance = [] (R p1, R p2) {
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    };

    auto angle = [] (R p1, R p2) {
        return atan2((p2.y - p1.y), (p2.x - p1.x));
    };

    // for each time step
    for(int count = 0; count < k; count++) {
        // for each body
        for(int i = 0; i < b->size(); i++) {
            // for each interaction not calculated
            for(int j = i+1; j < b->size(); j++) {
                // calculate the force between 2 bodies
                [distance, angle] (Body* b1, Body* b2) {
                    double force = G * b1->mass * b2->mass * pow(distance(b1->position, b2->position), 2);
                    F f1(force * cos(angle(b1->position, b2->position)), force * sin(angle(b1->position, b2->position)));
                    F f2(-f1.f_x, -f1.f_y);

                    b1->forceVector.push_back(f1);
                    b2->forceVector.push_back(f2);
                } (b->at(i), b->at(j));
            }

            // sum the total force on the current body
            b->at(i)->totalForce = accumulate(b->at(i)->forceVector.begin(), b->at(i)->forceVector.end(), F(0,0), 
                [] (F total, F f) { return total += f; });
        }
 
        // for each body
        for_each(b->begin(), b->end(), [t] (Body* bod) {
            // calculate acceleration
            bod->acceleration = A(bod->totalForce.f_x / bod->mass, bod->totalForce.f_y / bod->mass);
            
            // update velocity
            [&] (A acc, double t) {
                bod->velocity += V(acc.a_x * t, acc.a_y * t);
            } (bod->acceleration, t);

            // update position
            [&] (V vel, double t) {
                bod->position.x += vel.v_x * t;
                bod->position.y += vel.v_y * t;
            } (bod->velocity, t);
        });
    }

    auto end = std::chrono::high_resolution_clock::now();


    auto interactions = [&] () -> std::pair<long,long> {
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
        float d = duration.count();
        long interactions = (b->size() * b->size() * k) / d;
        if(interactions < 0)
            interactions = 0;
        return std::pair<long,long>(b->size(), interactions);
    };

    return interactions();
}


// generate the bodies with come randoms
std::vector<Body*>* generateBodies(int n, double m) {
    std::vector<Body*>* bodies = new std::vector<Body*>();
    srand(time(0));

    for(int i = 0; i < n; i++)
        bodies->push_back(new Body(i, (rand() % max_distance), (rand() % max_distance), (rand() % 1000 * m)));

    return bodies;
}

// average the vectors, set to indexed position, remove the leftover data
void averageData(std::vector<std::vector<std::pair<long,long>>*>* data, int index) {
    // for each pair of data points
    for(int i = 0; i < data->at(index)->size(); i++) {
        // add interactions to indexed vector
        for(int j = index+1; j < data->size(); j++) {
            data->at(index)->at(i).second +=  data->at(j)->at(i).second;
        }

        data->at(index)->at(i).second /= (data->size() - index);
    }

    // if the vector 
    if(data->size() > index)
        data->erase(data->begin()+index+1, data->end());
}


// the simulation running in each thread
void perThread(std::vector<std::pair<long,long>>* v) {    
    for(int n : numBodies) {
        std::vector<Body*>* bodies = generateBodies(n, 100.);
        v->push_back(simulate(bodies, timeSegment, segmentCount));
        cleanVector(bodies);
    }
}


// graph the data, each line represents a different number of threads
void graphData(std::vector<std::vector<std::pair<long,long>>*>* data) {
    std::vector<long>* xs;
    std::vector<long>* ys;


    plt::figure_size(1200, 780);
    plt::title("Interactions by N");
    plt::xlabel("N Bodies");
    plt::ylabel("Interactions per millisecond");

    // for each vector of data
    //for(auto v : *data) {
    for(int i = 0; i < data->size(); i++) {
        xs = new std::vector<long>();
        ys = new std::vector<long>();

        for(auto p : *(data->at(i))) {
            xs->push_back(p.first);
            ys->push_back(p.second);
        }

        plt::named_plot(std::to_string(numThreads[i]),*xs, *ys);

        delete xs;
        delete ys;
    }

    plt::legend();
    plt::save("./plot.png");
}


// used to cleanup multiple types of vectors
template<typename T>
void cleanVector(std::vector<T*>* b) {
    for(T* t : *b)
        delete t;
    delete b;
}
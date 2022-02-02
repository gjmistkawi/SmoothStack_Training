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

// b -> vector of bodies
// t -> timestep
// k -> number of time steps
std::pair<long, long> simulate(std::vector<Body*>* b, double t, int k);
std::pair<long, long> threadSimulate(std::vector<Body*>* b, double t, int k);

// n -> number of bodies to create
// m -> mass multiplier
std::vector<Body*>* generateBodies(int n, double m);

void updateForceVector(std::vector<Body*>* b, int index);
void updatePosition(Body* b, double t);

void cleanBodies(std::vector<Body*>* b);
void graphData(std::vector<std::pair<long,long>>* v1, std::vector<std::pair<long,long>>* v2);



int main(void) {
    std::vector<std::pair<long, long>>* threadInteractions = new std::vector<std::pair<long, long>>();
    std::vector<std::pair<long, long>>* interactions = new std::vector<std::pair<long, long>>();

    for(int n : numBodies) {
        std::vector<Body*>* bodies = generateBodies(n, 100.);
        interactions->push_back(simulate(bodies, 5, 2));
        cleanBodies(bodies);
    }

    for(int n : numBodies) {
        std::vector<Body*>* bodies = generateBodies(n, 100.);
        threadInteractions->push_back(threadSimulate(bodies, 5, 2));
        cleanBodies(bodies);
    }

    graphData(interactions, threadInteractions);

    return 0;
}


std::vector<Body*>* generateBodies(int n, double m) {
    std::vector<Body*>* bodies = new std::vector<Body*>();
    srand(time(0));

    for(int i = 0; i < n; i++)
        bodies->push_back(new Body(i, (rand() % max_distance), (rand() % max_distance), (rand() % 1000 * m)));

    return bodies;
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
            for(int j = 0; j < b->size(); j++) {
                // calculate the force between 2 bodies
                [distance, angle] (Body* b1, Body* b2) {
                    double force = G * b1->mass * b2->mass * pow(distance(b1->position, b2->position), 2);
                    F f1(force * cos(angle(b1->position, b2->position)), force * sin(angle(b1->position, b2->position)));
                    //F f2(-f1.f_x, -f1.f_y);

                    b1->forceVector.push_back(f1);
                    //b2->forceVector.push_back(f2);
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


// Simulate 2D N-body interactions with N-threads running the calculations
std::pair<long, long> threadSimulate(std::vector<Body*>* b, double t, int k) {
    auto start = std::chrono::high_resolution_clock::now();

    auto distance = [] (R p1, R p2) {
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    };

    auto angle = [] (R p1, R p2) {
        return atan2((p2.y - p1.y), (p2.x - p1.x));
    };

    std::vector<std::thread> threads;

    
    for(int i = 0; i < k; i++) {
        // Calculate force vectors
        for(int j = 0; j < b->size(); j++) {
            threads.push_back(std::thread(updateForceVector, b, j));
        }

        for(std::thread &t: threads)
            t.join();
        threads.clear();

        // Calculate new positions
        for(Body* bod: *b)
            threads.push_back(std::thread(updatePosition, bod, t));

        for(std::thread &t: threads)
            t.join();
        threads.clear();
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

    
void cleanBodies(std::vector<Body*>* b) {
    // Clean-up bodies
    for(int i =0; i < b->size(); i++) {
        delete b->at(i);
    }
    delete b;
}


void graphData(std::vector<std::pair<long,long>>* v1, std::vector<std::pair<long,long>>* v2) {
    std::vector<long>* xs1 = new std::vector<long>();
    std::vector<long>* ys1 = new std::vector<long>();
    std::vector<long>* xs2 = new std::vector<long>();
    std::vector<long>* ys2 = new std::vector<long>();

    for(std::pair<long,long> p : *v1) {
        xs1->push_back(p.first);
        ys1->push_back(p.second);
    }

    for(std::pair<long,long> p : *v2) {
        xs2->push_back(p.first);
        ys2->push_back(p.second);
    }

    plt::figure_size(1200, 780);
    plt::named_plot("Threadless", *xs1, *ys1);
    plt::named_plot("N-Threads", *xs2, *ys2);
    plt::title("Interactions by N");
    plt::xlabel("N Bodies");
    plt::ylabel("Interactions per millisecond");
    plt::legend();
    //plt::draw();
    //plt::show();
    plt::save("./plot.png");

}


void updateForceVector(std::vector<Body*>* b, int index) {
    auto distance = [] (R p1, R p2) {
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    };

    auto angle = [] (R p1, R p2) {
        return atan2((p2.y - p1.y), (p2.x - p1.x));
    };

    Body* b1 = b->at(index);

    for(Body* b2: *b) {
        // calculate the force between 2 bodies
        [distance, angle] (Body* b1, Body* b2) {
            double force = G * b1->mass * b2->mass * pow(distance(b1->position, b2->position), 2);
            F f1(force * cos(angle(b1->position, b2->position)), force * sin(angle(b1->position, b2->position)));
            //F f2(-f1.f_x, -f1.f_y);

            b1->forceVector.push_back(f1);
            //b2->forceVector.push_back(f2);
        } (b1, b2);
    }

    // sum the total force on the current body
    b1->totalForce = accumulate(b1->forceVector.begin(), b1->forceVector.end(), F(0,0), 
        [] (F total, F f) { return total += f; });
}


void updatePosition(Body* b, double t) {
    // calculate acceleration
    b->acceleration = A(b->totalForce.f_x / b->mass, b->totalForce.f_y / b->mass);
    
    // update velocity
    [&] (A acc, double t) {
        b->velocity += V(acc.a_x * t, acc.a_y * t);
    } (b->acceleration, t);

    // update position
    [&] (V vel, double t) {
        b->position.x += vel.v_x * t;
        b->position.y += vel.v_y * t;
    } (b->velocity, t);
}
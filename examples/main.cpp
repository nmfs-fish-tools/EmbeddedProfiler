/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: mattadmin
 *
 * Created on January 6, 2022, 8:52 AM
 */

#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>
#include "EmbeddedProfiler/Profiler.hpp"
using namespace std;

void DoStuff1() {
    PROFILER_START_SCOPE("DoStuff2");
    double* d = new double[1000000000];
    for (size_t i = 0; i < 1000000000; i++) {
        double d = 1.0 * 3.1459;
        d++;
        d *= d;
    }
    PROFILER_END_SCOPE("DoStuff2");
}

void DoStuff2() {
    PROFILER_START_SCOPE("DoStuff");
    double* d = new double[1000000000];
    for (size_t i = 0; i < 1000000000; i++) {
        double d = 1.0 * 3.1459;
        d++;
        d *= d;
    }
    PROFILER_END_SCOPE("DoStuff");
}

std::atomic<bool> keep_sampling_g(true);

void Sample() {
    while (keep_sampling_g) {
        PROFILER_SAMPLE_MEMORY("memory sample");
        PROFILER_SAMPLE_CPU("cpu sample");
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }
}

/*
 *
 */
int main(int argc, char** argv) {
    PROFILER_START_APP("my application");
    std::thread sampler(Sample);
    double* d = new double[1000000000];
    PROFILER_SAMPLE_MEMORY("line 25");
    PROFILER_SAMPLE_CPU("line 26");
    DoStuff1();
    DoStuff2();
    DoStuff1();
    DoStuff1();
    DoStuff2();
    DoStuff1();
    delete[] d;
    
    keep_sampling_g = false;
    sampler.join();
    
    PROFILER_END_APP("my application");
    std::cout << tools::DumpToString();
    return 0;
}


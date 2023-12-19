#include <stdio.h>
#include <time.h>
#include "headers/runtime.h"
#include "headers/arsinh_lookup.h"
#include "headers/arsinh_series.h"
#include "headers/arsinh_comp.h"


double calculateRunTimeArsinh(double x, int rep, short argument){
    double time = 0.0;
    switch (argument)
    {
        case 1:
            time = calculateRunTimeArsinh_lookup(x,rep);
        break;
        case 2:
            time = calculateRunTimeArsinh_comp(x,rep);
        break;
        default:
            time = calculateRunTimeArsinh_series(x,rep);
        break;
    }
    return time;
}

double calculateRunTimeArsinh_series(double x, int rep){
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC_RAW,&start);
    double res=0.;
    for(int i=0;i<rep;i++){
        res = approxArsinh_series(x);
    }
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC_RAW,&end);
    double time=end.tv_sec-start.tv_sec+ 1e-9 * (end.tv_nsec-start.tv_nsec);
    return time;
}

double calculateRunTimeArsinh_lookup(double x, int rep){
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC_RAW,&start);
    double res=0.;
    for(int i=0;i<rep;i++){
        res = approxArsinh_lookup(x);
    }
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC_RAW,&end);
    double time=end.tv_sec-start.tv_sec+ 1e-9 * (end.tv_nsec-start.tv_nsec);
    return time;
}

double calculateRunTimeArsinh_comp(double x, int rep){
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC_RAW,&start);
    double res=0.;
    for(int i=0;i<rep;i++){
        res = approxArsinh_comp(x);
    }
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC_RAW,&end);
    double time=end.tv_sec-start.tv_sec+ 1e-9 * (end.tv_nsec-start.tv_nsec);
    return time;
}
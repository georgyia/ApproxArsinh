#include <stdio.h>
#include <math.h>
#include <time.h>
#include "headers/arsinh_comp.h"

//Es werden keine Kommentare hinzugefügt, da die Vergleichsimplementierung nach dem gleichen Prinzip abläuft wie die Hauptimplementierung
double arsinhComp(double x) {

    double nominator = 1;
    double denominator = 2;
    double exponent = 3;
    double res = 0.;

    for (int i = 0; i < 122; i++) {

        if (i>=2 && i % 2 == 0) {
            res -= nominator * pow(x, exponent) / (denominator * exponent);
        } else { res += nominator * pow(x, exponent) / (denominator * exponent); }
       nominator *= exponent;
        denominator *= exponent+1;
        exponent += 2;

        if (i == 0)res = x - res;

    }


    return res;
}


double arcoshComp(double x){
    double nominator=1.;
    double denominator=2.;
    double exponent=2.;
    double res=0.;



    for(int i=0;i<144;i++){


        res+=(nominator/denominator)* (powf(x,-exponent)/exponent);

        nominator *= (exponent+1);
        denominator *= (exponent+2);//Variablen umbenennen
        exponent += 2.;
    }

    if(x<0)return - (log(2*x)-res);
    return (log(2*x)-res);
}
double approxArsinh_comp(double x){
    if (x>=1.0)return arcoshComp(sqrt(powf(x,2)+1.));
    if (x<=-1) return -arcoshComp(sqrt(powf(x,2)+1.));
    if(x<0.){
        x*=-1;
        return -(arsinhComp(x));
    }
    return arsinhComp(x);
}
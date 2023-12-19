#include <stdio.h>
#include <time.h>
#include "headers/arsinh_series.h"


double squareRoot(double x){
    double former = 1;
    double latter = 2;
    while (former != latter){
        former = latter;
        latter = ((x / latter) + latter ) / 2;}
    return latter;
}

//Reihendarstellung des Logarithmus für 1<=|x|<12
double lnSeries(double x, int n) {
    x=1.0/x;//Umkehrwert von x wird berechnet und das Ergebnis negiert, damit die Double Grenze nicht überschritten wird
    double nominator = x - 1;
    double nomPow = nominator*nominator;
    double scalar = 1.0;
    double denominator = x + 1;
    double denomPow= denominator*denominator;
    double ln = nominator/(scalar*denominator);//x-1/x+1

    for (int k = 1; k < n; k++) {
        nominator *= nomPow;//pow(nominator,k+2)
        scalar += 2.0;
        denominator *= denomPow;//pow(denominator,k+2)
        ln += nominator/(scalar*denominator); //pow(x-1,k+2)/scalar*pow(denominator,k+2)

    }
    return 2*ln;
}

//rekursive Logarithmusfunktion für |x|>=12
double ln(double x, double base)
{


    double  newX = x;
    double count = 0.0;
    while (newX >= base)
    {
        newX /= base;
        count++; //Im ersten Rekursionsschritt gibt Count nach der Iteration die Vorkommastelle an
    }
    if (newX >= 1.0&&newX<=1.0+1e-4)
    {
        return count;
    }

    return  count + (1.0 / ln(base, newX)); /*Durch das Vertauschen von Basis und Eingabe nähern sich beide Werte gegen 1.
 * Da der rekursive Aufruf durch 1 geteilt wird und count immer >=1 ist, werden in den
 * darauf folgenden Rekursionsebenen die Nachkommastellen approximiert*/
}



//Reihendarstellung für |x|<1
double arsinh(double x) {
double pow1=x;
    double nominator = 1.;
    double denominator = 2.;
    double exponent = 3.;
    double res = 0.;
    for (int i = 0; i < 122; i++) {

            pow1 *= x;  //pow1= pow(x, exponent)
        pow1*=x;
        if (i>=2 && i % 2 == 0) {
            res -= nominator * pow1 / (denominator * exponent); // (nominator/denominator)*(pow(x,exponent)/exponent)
        } else { res += nominator * pow1 / (denominator * exponent); }
nominator*=exponent;
        denominator*=exponent+1;
        exponent+=2;

        if (i == 0)res = x - res;
    }
    return res;
}

//Reihendarstellung für |x|>=1
double arcosh(double x,int boolean){
    double power=2.;
    double pow1=1.;
    double nominator=1.;
    double denominator=2.;
    double res=0.;
 double ln1=0.;
    if(boolean){
        double e=2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274;

        ln1= ln(2.0*x,e);
    }

    else  ln1= -lnSeries(2.0*x,x*15);
    for(int i=0;i<144;i++){


            pow1 *= 1 / x;  //pow1= pow(x, -power)
            pow1 *= 1 / x;

         res+=(nominator/denominator)* (pow1/power);

        nominator *= (power+1);
        denominator *= (power+2);
        power += 2.; //power=Exponent von x
    }

    return ln1-res;
}

double approxArsinh_series(double x){
    int boolean=0;
    if (x>=1.){
        if(x>=12){
            boolean=1;
        }
        x=squareRoot(x*x+1.);
        return arcosh(x,boolean);
    }
    if (x<=-1.) {
        x*=-1.;
        if(x>=12){
            boolean=1;
        }
        x=squareRoot(x*x+1.);
        return -(arcosh(x,boolean));
    }
    if(x<0.){
        x*=-1;
        return -(arsinh(x));
    }
    return arsinh(x);
}


int calculateRunTimeArsinhSeries(double x, int rep){
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC_RAW,&start);
    double res=0.;
    for(int i=0;i<rep;i++){
        res = approxArsinh_series(x);
    }
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC_RAW,&end);
    double time=end.tv_sec-start.tv_sec+ 1e-9 * (end.tv_nsec-start.tv_nsec);
    printf("Laufzeit: %0.19lf\n",time/rep);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <float.h>
#include <string.h>
#include <ctype.h>
#include "headers/framework.h"
#include "headers/arsinh_lookup.h"
#include "headers/arsinh_series.h"
#include "headers/arsinh_comp.h"
#include "headers/runtime.h"

// die Flags aus Terminal werden gelesen, nach der Richtigkeit geprüft und dann ausgeführt.
void run(int argc, char *argv[]){
    // für --help
    // 1 - der Name der langen Option
    // 2 - die Akzeptanz des Argumentes. 0 bedeutet kein Argument.
    // 3 - der Speicherort für den Wert. 0 bedeutet, dass die Option boolesch ist, und der Wert wird im Flag gespeichert.
    // 4 - der Wert, der zurückgegeben werden soll, wenn diese Option ausgewählt ist.
    static struct option long_options[] = {
            {"help", 0, 0, 0}
    };
    double x = searchNumber(argv);
    // für Standartwerte
    if(argc == 1 || argc == 2 && (x || strcmp(argv[1], "0") == 0)){
        printf("Der berechnete Wert: %0.19lf\n", approxArsinh_series(*(&x)));
        printf("Die Laufzeit wird gemessen und ausgegeben \"die Anzahl der Wiederholungen = %d\"\n", 1);
        printf("Laufzeit: %0.19lf Sekunden\n",(double)(calculateRunTimeArsinh(x,0,0)));
    }
    int rez = 0;
    // keine automatische Fehlermeldungen
    opterr = 0;
    int option_index = 0;
    // somit lässt es sich die passende Laufzeitberechnung bei -B bestimmen
    int argument_V = 0;
    // falls nicht nur ./arsin.out wird überprüft, ob der nächste Befehl richtig ist
    int temp = 0;

    while ((rez = getopt_long(argc, argv, "V::B::h::",long_options ,&option_index)) != -1){
        switch (rez) {
            case 0:


                // Fall mit langer Option
                if(strcmp(argv[optind-1], "--help") == 1){
                    // es gibt nur eine richtige lange Option --help , alle anderen sind falsch
                    fprintf(stderr, "Ungültiges Flag\n");
                    exit(1);
                }

                print_help_flag();
                exit(0);
            case 'V':
                if (optarg)
                {

                    switch (atoi(optarg))
                    {
                        case 0:

                            // Hauptimplementierung, also Reihendarstellung
                            printf("Der berechnete Wert: %0.19lf\n", approxArsinh_series(*(&x)));
                            argument_V = 0;
                            break;
                        case 1:
                            // Lookup Tabellen Implementierung
                            printf("Der berechnete Wert: %0.19lf\n",approxArsinh_lookup(x));
                            argument_V = 1;
                            break;
                        case 2:
                            // Vergleichsimplementierung
                            printf("Der berechnete Wert: %0.19lf\n",approxArsinh_comp(x));
                            argument_V = 2;
                            break;
                        default:
                            // nur bestimmte oder keine Argumente bei diesem Flag, hier ist, wenn das optionale Argument falsch ist
                            fprintf(stderr, "Dieses optionale Argument von flag -V<int> existiert nicht\n");
                            exit(1);
                    }
                }else{
                    // ohne Argument
                    // Hauptimplementierung, also Reihendarstellung
                    printf("Der berechnete Wert: %0.19lf\n", approxArsinh_series(*(&x)));
                    argument_V = 0;
                    break;
                }
                break;
            case 'B':
                if(optarg){

                    if (atof(optarg)<0)
                    {
                        // wenn das optionale Argument negativ ist
                        fprintf(stderr, "Das falsche optionale Argument vom Flag -B<int> .\nDie Anzahl der Wiederholungen des Funktionsaufrufs darf nicht negativ sein. \n");
                        exit(1);
                    }else if (atof(optarg)>2147483647){
                        // wenn das optionale Argument für int außerhalb der Grenzen liegt
                        fprintf(stderr, "Das falsche optionale Argument vom Flag -B<int> .\nDie Anzahl der Wiederholungen des Funktionsaufrufs kann nicht so groß sein \n");
                        exit(1);
                    }else if (atof(optarg)== 0){
                        // wenn es keine Wiederholung gibt
                        printf("Bei 0 Wiederholungen wird die Laufzeit nicht gemessen\n");
                    }else{
                        // wenn alles stimmt
                        printf("Die Laufzeit wird gemessen und ausgegeben \"die Anzahl der Wiederholungen = %d\"\n", atoi(optarg));
                        printf("Laufzeit: %0.19lf\n",(double)(calculateRunTimeArsinh(x,atoi(optarg),argument_V)));
                    }
                } else{
                    // wenn es kein optionales Argument gibt, führen wir dies nur einmal aus
                    printf("Die Laufzeit wird gemessen und ausgegeben \"die Anzahl an Wiederholungen = %d\"\n", 1);
                    printf("Laufzeit: %0.19lf Sekunden\n",(double)(calculateRunTimeArsinh(x,0,argument_V)));
                }
                break;
            case 'h':
                if(optarg){
                    // bei -h gibt es keine optionale Argumente, hier ist optarg, damit wir die Fälle fangen können, bei welchen das Argument angegeben ist
                    fprintf(stderr, "Ungültiges Flag %s\n",argv[optind-1]);
                    exit(1);
                }
                print_help_flag();
                exit(0);
            case '?':
                // der Dateiname und die Zahlen sind gültig hier, alles andere nicht
                if(strcmp(argv[optind-1], "--help") == 1){
                    // es gibt nur eine richtige lange Option --help , alle anderen sind falsch
                    fprintf(stderr, "Ungültiges Flag\n");
                    exit(1);
                }
        } // switch

    } // while
}


// hier wird überprüft, ob es ein e im Befehlh gibt
short includes_e(char* input){
    for (int i = 0; i < strlen(input); i++)
    {
        if(input[i] == 'e'){
            return 1;
        }
    }
    return 0;
}

// überprüft, ob angegebene Zahl dezimal ist
short isDecimal(char* input){
    int i = 0;
    for (i = 0; i < strlen(input); i++)
    {
        if (isdigit(input[i])-1)
        {
            // wenn es keine Ziffer ist
            if (input[i] == '.')
            {
                return 1;
            }
        }
    }
    return 0;
}

// gibt die Informationen von -h und --help aus
void print_help_flag(){
    printf(
            "\n   Flags:\n\n"
            "   -V<int> - Mit diesem Flag kann man die Implementierung wählen, die verwendet werden soll. Hierbei soll mit -V0 die Hauptimplementierung(Reihendarstellung), mit -V1 die Lookup Tabellen Implementierung und mit -V2 die Vergleichsimplementierung verwendet werden. Wenn die Option nicht gesetzt wird, wird ebenfalls die Hauptimplementierung a>"
            "   -B<int> - Falls gesetzt, wird die Laufzeit der angegebenen Implementierung gemessen und ausgegeben. Das optionale Argument dieser Option gibt die Anzahl an Wiederholungen des Funktionsaufrufs an. Falls kein Argument gesetzt wurde, wird nur eine Wiederholung durchgeführt. Falls keine Implementierung davor gewählt wurde, wird die Hauptim>"
            "   <float> - Positional Argument: Der vorgegebene Wert für x.\n\n"
            "   -h - Eine Beschreibung aller Optionen des Programms und Verwendungsbeispiele werden ausgegeben und das Programm danach beendet.\n\n"
            "   --help - Eine Beschreibung aller Optionen des Programms und Verwendungsbeispiele werden ausgegeben und das Programm danach beendet.\n\n"
            "   Verwendungsbeispiele:\n\n"
            "   Eingabe: -V \n"
            "   Ausgabe: \n"
            "   Der berechnete Wert: 0.0000000000000000000 \n\n"
            "   Eingabe: -B \n"
            "   Ausgabe: \n"
            "   Die Laufzeit wird gemessen und ausgegeben \"die Anzahl an Wiederholungen = 1\"\n"
            "   Laufzeit: 0.0000000420000000000 Sekunden \n\n"
            "   Eingabe: 0.2 \n"
            "   Ausgabe: \n"
            "   Der berechnete Wert: 0.1986901103492414444\n"
            "   Die Laufzeit wird gemessen und ausgegeben \"die Anzahl an Wiederholungen = 1\"\n"
            "   Laufzeit: 0.0000000420000000000 Sekunden \n\n"
            "   Eingabe: -V1 -B3 3.5 \n"
            "   Ausgabe: \n"
            "   Der berechnete Wert: 1.9654253360883138235\n"
            "   Die Laufzeit wird gemessen und ausgegeben \"die Anzahl an Wiederholungen = 3\"\n"
            "   Laufzeit: 0.0000015000000000000 Sekunden \n\n"
            "   Eingabe: -V2 -230 \n"
            "   Ausgabe: \n"
            "   Der berechnete Wert: -6.1312312153470971410 \n\n"
    );
}

// gibt die gefundene Zahl zurück
double searchNumber(char *argv[]){
    // 1, da als erstes immer ./filename
    int i = 1;
    char *endptr;
    double x = 0;
    short number_count = 0;
    while(argv[i]){
        if (strtod(argv[i], &endptr))
        {
            int ind;

            if (number_count)
            {
                fprintf(stderr,"Zu viele Werte für x");
                exit(1);
            }
            if (argv[i][ind] == '.')
            {
                printf("Die Zahl ist nicht ganz korrekt mit dem Punkt am Ende, sie wird als eine ganze Zahl betrachtet.\n");
            }else if(argv[i][0] == '.'){
                printf("Die Zahl ist nicht ganz korrekt mit dem Punkt am Anfang, sie wird als eine Dezimalzahl betrachtet.\n");
            }
            // strtof() liest den Float-Wert, ist aber nicht genau genug
            // die Verwendung von strtod(), das double liest und die Validierung der Nummer genauso sicher macht, ist präziser
            x = (double)strtod(argv[i], &endptr);
            validateNumber(x);
            number_count = 1;
        }
        i++;
    }
    // wenn es keine Zahl gibt, dann als Standardwert - 0
    return x;
}



// prüft, ob die Zahl im Float-Intervall liegt
void validateNumber(double num){
    if(num < (-1)*FLT_MAX || num > FLT_MAX){
        fprintf(stderr,"Der Wert für x außerhalb der Grenzen.\nDie Zahl muss zwischen -%e und %e liegen\n",(double)FLT_MAX, (double)FLT_MAX);
        exit(1);
    }
}

// prüft ob es eine Zahl ist und gibt den Index des Elementes
int getIndex_number(char* input)
{
    int i = 0;
    short decimal_flag = 0, negative_flag = 0, e_flag = 0, plus_flag = 0;

    if (input[0] == '-')
    {
        // es darf nur ein Strich am Anfang sein, was dann die Zahl als negativ definiert
        negative_flag = 1;
    }

    for (i = negative_flag; i < strlen(input); i++)
    {
        if (isdigit(input[i])-1)
        {
            // wenn es keine Ziffer ist
            if (input[i] == '.' && decimal_flag == 0)
                // darf nur ein Punkt sein, was dann die Zahl dezimal macht
                decimal_flag = 1;
        }else if(input[i] == 'e' && e_flag == 0){
            e_flag = 1;
        }else if(input[i] == '+' && plus_flag == 0 && input[i-1] == 'e'){
            plus_flag = 1;
        }
        else
        {
            return -1;
        }
    }
    return i;
}

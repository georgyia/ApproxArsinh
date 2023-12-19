# Project Overview

This project, conducted as part of the Basic Computer Architecture Internship, focuses on the approximation of the hyperbolic arcsin function (arsinh), the inverse function of the hyperbolic sine (sinh), and the analysis of the implemented calculations. The project is divided into two main parts: the theoretical conception and the practical implementation.

## Theoretical Conception

The theoretical part involves the mathematical derivation, which forms the basis for the approximation formula of arsinh as a series representation and the logic for the method of lookup tables. The details of this derivation and the mathematical concepts used are explained in the Ausarbeitung.tex file.

## Practical Implementation

The practical part involves the implementation of the derived formulas in C. The implementation is divided into three versions: the main implementation (series representation), the lookup table implementation, and the comparison implementation. The framework program allows the use of different implementations and runtime calculations.

## Compilation and Execution

The project includes a Makefile for easy compilation and execution of the program. To compile the program, use the make command. To clean up the generated files, use make clean.

## Performance Analysis

The performance of the different implementations is analyzed using the clock_gettime() function. The Wall Time and CPU Time are the two most commonly used times for measuring the execution time of a routine. The Monotonic Time is used to guarantee the exact difference between the start and end of a specific routine.

## Documentation

The project is thoroughly documented. The README file provides an overview of the project and instructions for compiling and running the program. The Ausarbeitung.tex file provides a detailed explanation of the mathematical concepts used and the implementation of the arsinh function.

## Conclusion

The project successfully approximates the arsinh function using different methods and analyzes their performance. The results of the project are summarized in the Ausarbeitung.tex file.

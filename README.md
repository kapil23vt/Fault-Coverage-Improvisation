# Fault-Coverage-Improvisation
The objective of this project is to repeatedly add and remove vectors to a given circuit with the goal of attaining a test set that achieves highest coverage.

Compile Instructions: You can use the following command to compile your code: 
g++ -Iinclude include/verilated.cpp Vtop__Syms.cpp Vtop.cpp (your file)

The program will generate set of vectors which when applied will give the maximum possible fault coverage of given circuit.

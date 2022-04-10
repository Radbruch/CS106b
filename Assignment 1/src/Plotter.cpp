#include "Plotter.h"
#include "strlib.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void runPlotterScript(istream& input) {
    /* TODO: Delete this line and the one after it, then implement this function. */
    /*Initialize*/
    int upordown = 0; // up:0, down:1, initialize to up.
    double positionx = 0;
    double positiony = 0; // Initialize (x,y) to (0,0), center of picture.
    double destinationx = 0;
    double destinationy = 0;
    PenStyle style = {1, "black"}; // Initialize style to defalt value.

    /* Loop */
    for (string line; getline(input, line); ) {
        /* ... do something with line ... */
        Vector<string> command = stringSplit(line, " ");
        int commandsize = command.size();
        if (commandsize == 1) { // penup or pendown.
            if (toLowerCase(command[0]) == "penup"){
                upordown = 0;
            }
            else {
                upordown = 1;
            }
            continue;
        }
        if (commandsize == 2) { // pencolor or penwidth.
            if (toLowerCase(command[0]) == "pencolor") {
                style.color = toLowerCase(command[1]);
            }
            else {
                style.width = stringToReal(command[1]);
            }
            continue;
        }
        else {
            if (toLowerCase(command[0]) == "moveabs" && upordown == 0) {
                positionx = stringToReal(command[1]);
                positiony = stringToReal(command[2]);
                continue;
            }
            if (toLowerCase(command[0]) == "moveabs" && upordown == 1) {
                destinationx = stringToReal(command[1]);
                destinationy = stringToReal(command[2]);
                drawLine(positionx, positiony, destinationx, destinationy, style);
                positionx = destinationx;
                positiony = destinationy;
                continue;
            }
            if (toLowerCase(command[0]) == "moverel" && upordown == 0) {
                positionx += stringToReal(command[1]);
                positiony += stringToReal(command[2]);
                continue;
            }
            else {
                destinationx = positionx + stringToReal(command[1]);
                destinationy = positiony + stringToReal(command[2]);
                drawLine(positionx, positiony, destinationx, destinationy, style);
                positionx = destinationx;
                positiony = destinationy;
                continue;
            }
        }
    }
}


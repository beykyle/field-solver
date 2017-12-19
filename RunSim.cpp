/*
 * Author: Kyle Beyer
 * Last Updated: 12/19/2017
 *
 * This holds the main function for the field solving simulation
 * It reads inputs according to paths set in command line
 * Creates a Simulation object with a Cavity and Mesh for each input file
 * Runs the Simulation
 */

#include <iostream>

#include "Simulation.h"

int main(int argc , char** argv) {
    

    // parse command line argument to get input file paths
    vector<std::string> filenames;
    
    for (int i=1; i< argc; i++) {
        filenames.push_back( argv[i]);
    }
    
    // create simulation object
    Simulation mySim;
    
    // setup simulation according to filenames
    mySim.setupFromInputFiles(filenames);

    // run simulation
    // mySim.run()
    
    return(0);
};


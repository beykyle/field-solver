/*
 * Author: Kyle Beyer
 * Last Updated: 12/11/2017
 *
 * This class holds arrays containing pointers to cavity and mesh objects,
 * which together make up an entire field solving simulation
 */

#ifndef _SIMULATION_HEADER_
#define _SIMULATION_HEADER_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "pugixml.hpp"
#include "Cavity.h"
#include "Mesh.h"

using std::vector;
using std::string;
using pugi::xml_node;

typedef std::shared_ptr<Cavity>  Cavity_Ptr;
typedef std::shared_ptr<Mesh>    Mesh_Ptr;

class Simulation {
    private:
        vector<Cavity_Ptr>      cavitySet;
        vector<Mesh_Ptr>        meshSet;
        vector<std::string>     methodSet;

    public:
        Simulation() {};
       ~Simulation() {};

       void run();

        bool readInput(std::string XML_FILE_PATH , vector<int> &bins, vector<double> &boundaryPotentials , 
                vector <bool> &holdPotentials , vector <double> &cavityDimensions , std::string &shape , 
                std::string &name , std::string &method);

        bool setupFromInputFiles( vector <std::string> paths); 
};

#endif

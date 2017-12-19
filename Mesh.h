/*
 * Author: Kyle Beyer
 * Last Updated: 12/11/2017
 * 
 * This class runs multiple 3D field solver algorithms on a Cavity
 */

#ifndef _MESH_HEADER_
#define _MESH_HEADER_

#include <cmath>
#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include "Utilities.h"
#include "Cavity.h"

using std::vector;
using std::string;

typedef std::shared_ptr<Cavity> Cavity_ptr;

class Mesh {
    private:
        Cavity_ptr cavity;

        vector <int> bins;

        vector <double> binWidths;

        vector <double> potential;
        vector <double> Ey;
        vector <double> Ex;
        vector <double> Ez;

        vector <bool> onBoundary;  // bins where potential is held by boundar condition
        vector <bool> geoBoundary; // bins at the geometric boundary of the cavity

    public:
        // constructor
        Mesh(Cavity_ptr cavIn , vector <int> binsi , vector<double> binwidths);

        // destructor
       ~Mesh() {}; 
        
       // get name of associated cavity
        string getName() { return(cavity->getName() ); };
        
        // running function
        void solve(string method); 
        // allowed methods: 'relax', 'fft', 'matrix', 
        //'Green', 'fmm' , 'finite_element', 'monte_carlo'
        
        // solvers
        void relax();

        // Electric field
        void calculateE();

        // functions for operations on grid
        int ijk2n(int i , int j, int k);

        vector <int> n2ijk(int n);

        vector <double> getNeighbors(int n);

        // writers
        void writeE();
        void writePotential();


};

#endif

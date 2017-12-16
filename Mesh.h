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

typedef std::shared_ptr<RectangularCavity> RectangularCavity_ptr;

class Mesh {
    private:
        RectangularCavity_ptr cavity;

    public:
        Mesh(RectangularCavity cavIn ): cavity( std::make_shared<RectangularCavity>(cavIn)) {};
       ~Mesh() {}; 
        
        string getName() { return(cavity->getName() ); };
        
        // running function
        void solve(string method); 
        // allowed methods: 'relax', 'fft', 'matrix', 
        //'Green', 'fmm' , 'finite_element', 'monte_carlo'
        
        // solvers
        void relax();

        // Electric field
        void getField();

};

#endif

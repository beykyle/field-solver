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

#include "Cavity.h"

using std::vector;
using std::string;

typedef std::shared_ptr<RectangularCavity> Cavity_ptr;

class Mesh {
    private:
        Cavity_ptr cavity;

    public:
        Mesh(RectangularCavity cavityi): cavity( std::make_shared< RectangularCavity >( cavityi ) ) {};
       ~Mesh() {}; 

        // running function
        void solve(string method); // allowed methods: 'relax', 'fft', 'matrix', 'Green', 'fmm' , 'finite_element', 'monte_carlo'
        
        // solvers
        void relax();

};

#endif

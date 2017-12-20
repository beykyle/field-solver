/*
 * Author: Kyle Beyer
 * Last Updated: 12/11/2017
 *
 * These classes define 3D cavities for EM field solving.
 * A Cavity has dimensions and boundary conditions,
 * and a 3D mesh covering the inside 
 */

#ifndef _CAVITY_HEADER_
#define _CAVITY_HEADER_

#include <cmath>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>

using std::vector;
using std::string;

class Cavity {
    protected:
        string name;
        
        vector <double> dimensions;
        vector <double> boundaryPotentials;
        vector <bool>   holdPotentials;

    public:
        Cavity(string namei , vector <double> lens , vector <double> pots , vector <bool> hold): 
            name(namei), dimensions(lens), boundaryPotentials(pots), holdPotentials(hold) {};
       ~Cavity() {};

        // get/set
        string getName() { return(name); }; 
       
        vector <double>  getLens() { return(dimensions);               };
        vector <double>  getPots() { return(boundaryPotentials); };
        vector <bool>    getHold() { return(holdPotentials);     };

        void setDims( vector <double> lens) { dimensions         = lens; };
        void setPots( vector <double> pots) { boundaryPotentials = pots; };
        void setHold( vector <bool>   hold) { holdPotentials     = hold; };

        // interface with mesh
        virtual void boundaries2Mesh(vector <int> bins , vector <bool> &geoBoundaries , vector <bool> &boundaries, 
                             vector <double> &potential);
};

class RectangularCavity : public Cavity {
    public:
        // constructors
        RectangularCavity(string namei , vector <double> lens , vector <double> pots , vector <bool> hold): 
            Cavity(namei , lens, pots, hold) {};

        // destructor
        ~RectangularCavity() {};
     
        // sets boundary conditions on mesh
        void boundaries2Mesh(vector <int> bins , vector <bool> &geoBoundaries , vector <bool> &boundaries, 
                             vector <double> &potential);
        
};

class CylindricalCavity : public Cavity {
    public:
        // constructors
        CylindricalCavity(string namei , vector <double> lens , vector <double> pots , vector <bool> hold): 
            Cavity(namei , lens, pots, hold) {};

        // destructor
        ~CylindricalCavity() {};
     
        // sets boundary conditions on mesh
        void boundaries2Mesh(vector <int> bins , vector <bool> &geoBoundaries , vector <bool> &boundaries, 
                             vector <double> &potential);
        
};

#endif

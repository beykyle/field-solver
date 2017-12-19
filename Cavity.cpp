#include "Cavity.h"

/* Cavity
 *
 */

// constructor


// functions
void Cavity::boundaries2Mesh(vector <int>  bins        , vector <bool> &geoBoundaries , 
                                        vector <bool> &boundaries , vector <double> &potentials) {};

/* Rectagular Cavity
 *
 */

// constructor


// functions

void RectangularCavity::boundaries2Mesh(vector <int>  bins        , vector <bool> &geoBoundaries , 
                                        vector <bool> &boundaries , vector <double> &potentials) {
    
    int n;


    for (int i = 0; i < bins.at(0); ++i){
        for (int j = 0; j < bins.at(1); ++j) {
            for (int k = 0; k < bins.at(2); ++k) {

                n = k * bins.at(0) * bins.at(1) + j * bins.at(1) + i;

                
                if (i == 0 or i == bins.at(0) - 1 or
                    j == 0 or j == bins.at(1) - 1 or  
                    k == 0 or k == bins.at(2) - 1 ) {
                    geoBoundaries.at(n) = true;
                }

                if (i == 0               and holdPotentials.at(0) == true) {
                    boundaries.at(n)    = true; 
                    potentials.at(n)    = boundaryPotentials.at(0);
                }
                if (i == bins.at(0) - 1 and holdPotentials.at(1)  == true) {
                    boundaries.at(n)    = true; 
                    potentials.at(n)    = boundaryPotentials.at(1);
                }
                if (j == 0              and holdPotentials.at(2) == true) {
                    boundaries.at(n)    = true; 
                    potentials.at(n)    = boundaryPotentials.at(2);
                }
                if (j == bins.at(1) - 1 and holdPotentials.at(3)  == true) {
                     boundaries.at(n)    = true; 
                     potentials.at(n)    = boundaryPotentials.at(3);
                }
                if (k == 0              and holdPotentials.at(4)   == true) {
                     boundaries.at(n)    = true; 
                     potentials.at(n)    = boundaryPotentials.at(4);
                }
                if (k == bins.at(1) - 1 and holdPotentials.at(5)    == true) {
                     boundaries.at(n)    = true; 
                     potentials.at(n)    = boundaryPotentials.at(5);
                }

            }
        }
    }

};



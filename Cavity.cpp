#include "Cavity.h"


/* Rectagular Cavity
 *
 */


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

                if (i == 0               and leftPotentialHold   == true) {
                    boundaries.at(n)    = true; 
                    potentials.at(n)    = leftPotential;
                }
                if (i == bins.at(0) - 1 and rightPotentialHold  == true) {
                    boundaries.at(n)    = true; 
                    potentials.at(n)    = rightPotential;
                }
                if (j == 0              and bottomPotentialHold == true) {
                    boundaries.at(n)    = true; 
                    potentials.at(n)    = bottomPotential;
                }
                if (j == bins.at(1) - 1 and topPotentialHold    == true) {
                     boundaries.at(n)    = true; 
                     potentials.at(n)    = topPotential;
                }
                if (k == 0              and nearPotentialHold   == true) {
                     boundaries.at(n)    = true; 
                     potentials.at(n)    = nearPotential;
                }
                if (k == bins.at(1) - 1 and farPotentialHold    == true) {
                     boundaries.at(n)    = true; 
                     potentials.at(n)    = farPotential;
                }

            }
        }
    }

};



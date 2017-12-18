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
    private:
        string name;

    public:
        Cavity(string namei ): name(namei) {};
       ~Cavity() {};

       // get/set
       string getName() { return(name); }; 

       // interface with mesh
       virtual void boundaries2Mesh(vector <int> bins , vector <double> &boundaries , vector <double> &potential) {};
           
};

class RectangularCavity : public Cavity {
    private:
        // rectangle side lengths
        vector <double> lens;

        // boundary conditions
        double topPotential;
        double bottomPotential;
        double leftPotential;
        double rightPotential;
        double nearPotential;
        double farPotential;
        
        bool topPotentialHold;
        bool bottomPotentialHold;
        bool leftPotentialHold;
        bool rightPotentialHold;
        bool nearPotentialHold;
        bool farPotentialHold;
        
    public:
        // constructors
        RectangularCavity(string namei, vector <double> lensi): Cavity(namei) , lens(lensi) {};

        // destructor
        ~RectangularCavity() {};
     
        // sets boundary conditions on mesh
        void boundaries2Mesh(vector <int> bins , vector <bool> &geoBoundaries , vector <bool> &boundaries, 
                             vector <double> &potential);
        
        // get/set functions
            // get/set rectangle side lengths
        vector <double>  getLens() { return(lens); };

            // get/set boundary conditions
        void setTopPotential(double in)     { topPotential    = in; topPotentialHold     = true;   };
        void setBottomPotential(double in)  { bottomPotential = in; bottomPotentialHold  = true;  };
        void setLeftPotential(double in)    { leftPotential   = in; leftPotentialHold    = true;  };
        void setRightPotential(double in)   { rightPotential  = in; rightPotentialHold   = true;  };
        void setNearPotential(double in)    { nearPotential   = in; nearPotentialHold    = true;  };
        void setFarPotential(double in)     { farPotential    = in; farPotentialHold     = true;  };

        double getTopPotential()            { return(topPotential);    };
        double getBottomPotential()         { return(bottomPotential); };
        double getLeftPotential()           { return(leftPotential);   };
        double getRightPotential()          { return(rightPotential);  };
        double getNearPotential()           { return(nearPotential);   };
        double getFarPotential()            { return(farPotential);    };
        
};
#endif

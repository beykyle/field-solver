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

using std::vector;
using std::string;

class Cavity {
    private:
        string name;

    public:
        Cavity(string namei): name(namei) {};
       ~Cavity() {};

       string getName() { return(name); }; 


};

class RectangularCavity : public Cavity {
    private:
        static constexpr double x0 = 0.0;
        static constexpr double y0 = 0.0;
        static constexpr double z0 = 0.0;
       
        const double xf    , yf    , zf;
        const double xbins , ybins , zbins;

        double topPotential;
        double bottomPotential;
        double leftPotential;
        double rightPotential;
        double nearPotential;
        double farPotential;

        vector <double> Potential;

    public:
        // constructors
        RectangularCavity(string namei, double length , double width, double height );
        RectangularCavity(string namei, double length , double width, double height , int i , int j , int k);
        RectangularCavity(string namei, double length , double width, double height , 
                vector <double> boundaryPotentiali);
        RectangularCavity(string namei, double length , double width, double height , int i , int j , int k, 
                vector <double> boundaryPotentiali);

        // destructor
        ~RectangularCavity() {};
     
        // sets boundary conditions on mesh
        void updateBoundaries();

        // helper function for accesing mesh
        int ijk2n(int i , int j , int k);
        vector <int>  n2ijk(int n);

        // get/set functions
        double getLength() { return(xf); };
        double getWidth()  { return(yf); };
        double getHeight() { return(zf); };

        void setTopPotential(double in)     { topPotential    = in;  updateBoundaries(); };
        void setBottomPotential(double in)  { bottomPotential = in;  updateBoundaries(); };
        void setLeftPotential(double in)    { leftPotential   = in;  updateBoundaries(); };
        void setRightPotential(double in)   { rightPotential  = in;  updateBoundaries(); };
        void setNearPotential(double in)    { nearPotential   = in;  updateBoundaries(); };
        void setFarPotential(double in)     { farPotential    = in;  updateBoundaries(); };

        double getTopPotential()            { return(topPotential); };
        double getBottomPotential()         { return(topPotential); };
        double getLeftPotential()           { return(topPotential); };
        double getRightPotential()          { return(topPotential); };
        double getNearPotential()           { return(topPotential); };
        double getFarPotential()            { return(topPotential); };
 
        vector <double> getPotentials();
        void setPotentials( vector <double> potentials);
        
};
#endif

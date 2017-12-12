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

    protected:
        vector <double> potential;

    public:
        Cavity(string namei ): name(namei) {};
       ~Cavity() {};

       virtual string getName() { return(name); }; 
       
       vector <double> getPotential() {return(potential); };

       double getNthPotential(int n)          {return(potential.at(n)); };
       void setPotential(int n , double val)  { potential.at(n) = val;  };
       
       // utility functions for accesing mesh 
       virtual  int ijk2n(int i , int j , int k);
       virtual  vector <int>  n2ijk(int n);
       virtual  bool isBoundary(int n) { return(false); };
       virtual  vector <double> getNeighbors(int n);
       virtual  vector <int>  getBins();
        
       // writer
       virtual void writePotential();
};

class RectangularCavity : public Cavity {
    private:
        // origin
        static constexpr double x0 = 0.0;
        static constexpr double y0 = 0.0;
        static constexpr double z0 = 0.0;
       
        // other corner of 
        const double xf    , yf    , zf;
        const int xbins , ybins , zbins;

        double topPotential;
        double bottomPotential;
        double leftPotential;
        double rightPotential;
        double nearPotential;
        double farPotential;
        
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
        
        // writer
        void writePotential();

        // utility functions
        int ijk2n(int i , int j , int k);
        vector <int>  n2ijk(int n);
        bool isBoundary(int n);
        vector <double> getNeighbors(int n);

        // get/set functions
        double getLength() { return(xf); };
        double getWidth()  { return(yf); };
        double getHeight() { return(zf); };

        vector <int>  getBins();
     
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
        
        vector <double> getBoundPotentials();
        void setBoundPotentials(vector <double> potentials );
};
#endif

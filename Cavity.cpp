#include "Cavity.h"

/*  Cavity
 *
 */

// Constructors

// Functions
int Cavity::ijk2n(int i , int j , int k) { return(0); };
vector <int>  Cavity::n2ijk(int n) { return(vector<int>()); };

/* Rectagular Cavity
 *
 */

// Constructors
RectangularCavity::RectangularCavity(string namei, double l , double w, double h ): 
    Cavity(namei) , xf(l) , yf(w) , zf(h) , xbins(100) , ybins(100) , zbins(100) {
        vector <double> pots = {0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0};
        setPotentials(pots);
};

RectangularCavity::RectangularCavity(string namei, double l, double w, double h, int i , int j ,  int k): 
    Cavity(namei) , xf(l) , yf(w) , zf(h) , xbins(i)   , ybins(j)   , zbins(k) {
        vector <double> pots = {0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0};
        setPotentials(pots);
};

// Functions
RectangularCavity::RectangularCavity(string namei, double l , double w, double h , vector<double> boundaryPotentiali): 
    Cavity(namei) , xf(l) , yf(w) , zf(h) , xbins(100) , ybins(100) , zbins(100) {
        setPotentials(boundaryPotentiali);
};

RectangularCavity::RectangularCavity(string namei, double l , double w, double h,  int i , int j ,  int k , vector <double> boundaryPotentiali):
    Cavity(namei) , xf(l) , yf(w) , zf(h) , xbins(i)   , ybins(j)   , zbins(k)   {
        setPotentials(boundaryPotentiali);    
};



vector <double> RectangularCavity::getPotentials() {
    vector <double> potentials = { topPotential  , bottomPotential ,
                                   leftPotential , rightPotential  ,
                                   nearPotential , farPotential    , 
                                 };
    return(potentials);
};


void RectangularCavity::setPotentials(vector <double> potentials) {
    topPotential     = potentials.at(0);
    bottomPotential  = potentials.at(1);
    leftPotential    = potentials.at(2);
    rightPotential   = potentials.at(3);
    nearPotential    = potentials.at(4);
    farPotential     = potentials.at(5);
};

int RectangularCavity::ijk2n(int i , int j , int k) {
// bins are indexed from 0
    return(k * xbins * ybins + j * xbins + i);
};

vector <int>  RectangularCavity::n2ijk(int n) {
// bins are indexed from 0

    vector <int> ijk;
    ijk.push_back(n / xbins);
    ijk.push_back((n -ijk.at(0)) / ybins);
    ijk.push_back((n - ijk.at(0) - ijk.at(1)) / zbins);

    return(ijk);
};

void RectangularCavity::updateBoundaries() {

    for (int n = 0; n < potential.size(); ++n) {
        vector <int> bin = n2ijk(n);
        if (bin.at(0) == xbins - 1 ) { potential.at(n) = farPotential;    }
        if (bin.at(0) == 0         ) { potential.at(n) = nearPotential;   }
        if (bin.at(1) == ybins - 1 ) { potential.at(n) = rightPotential;  }
        if (bin.at(1) == 0         ) { potential.at(n) = leftPotential;   }
        if (bin.at(2) == zbins - 1 ) { potential.at(n) = topPotential;    }
        if (bin.at(2) == 0         ) { potential.at(n) = bottomPotential; }
    }
};


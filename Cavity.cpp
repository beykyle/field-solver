#include "Cavity.h"

/*  Cavity
 *
 */

// Constructors

// Functions
int Cavity::ijk2n(int i , int j , int k) { 
    std::cout<<" Somethnig has gone awry. " << std::endl;
    return(0); 
};

vector <int>  Cavity::n2ijk(int n) { 
    std::cout<<" Somethnig has gone awry. " << std::endl;
    return(vector<int>()); 
};

vector <double> Cavity::getNeighbors(int n) {
    std::cout<<" Somethnig has gone awry. " << std::endl;
    vector <double> neighbors;
    return(neighbors);
};

vector <int>  Cavity::getBins() {
    std::cout<<" Somethnig has gone awry. " << std::endl;
    return(vector<int>());
};

void Cavity::writePotential() {
    std::cout<<" Somethnig has gone awry. " << std::endl;
};



/* Rectagular Cavity
 *
 */

// Constructors
RectangularCavity::RectangularCavity(string namei, double l , double w, double h ): 
    Cavity(namei) , xf(l) , yf(w) , zf(h) , xbins(100) , ybins(100) , zbins(100) {
        vector <double> pots = {0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0};
        setBoundPotentials(pots);
        potential.resize(xbins * ybins * zbins );
        updateBoundaries();
};

RectangularCavity::RectangularCavity(string namei, double l, double w, double h, int i , int j ,  int k): 
    Cavity(namei) , xf(l) , yf(w) , zf(h) , xbins(i)   , ybins(j)   , zbins(k) {
        vector <double> pots = {0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0};
        setBoundPotentials(pots);
        potential.resize(xbins * ybins * zbins);
        updateBoundaries();
};

RectangularCavity::RectangularCavity(string namei, double l , double w, double h , vector<double> boundaryPotentiali): 
    Cavity(namei) , xf(l) , yf(w) , zf(h) , xbins(100) , ybins(100) , zbins(100) {
        setBoundPotentials(boundaryPotentiali);
        potential.resize(xbins * ybins * zbins);
        updateBoundaries();
};

RectangularCavity::RectangularCavity(string namei, double l , double w, double h,  int i , int j ,  int k , vector <double> boundaryPotentiali):
    Cavity(namei) , xf(l) , yf(w) , zf(h) , xbins(i)   , ybins(j)   , zbins(k)   {
        setBoundPotentials(boundaryPotentiali);    
        potential.resize(xbins * ybins * zbins);
        updateBoundaries();
};

// Functions
vector <double> RectangularCavity::getBoundPotentials() {
    vector <double> boundPotentials = { topPotential  , bottomPotential ,
                                        leftPotential , rightPotential  ,
                                        nearPotential , farPotential    , 
                                      };
    return(boundPotentials);
};


void RectangularCavity::setBoundPotentials(vector <double> potentials) {
    topPotential     = potentials.at(0);
    bottomPotential  = potentials.at(1);
    leftPotential    = potentials.at(2);
    rightPotential   = potentials.at(3);
    nearPotential    = potentials.at(4);
    farPotential     = potentials.at(5);
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

// Utility  functions
bool RectangularCavity::isBoundary(int n) {
    
    vector <int> bin = n2ijk(n);

    if (   bin.at(0) == xbins-1   or bin.at(0) == 0
       or  bin.at(1) == ybins-1   or bin.at(1) == 0  
       or  bin.at(2) == zbins-1   or bin.at(2) == 0 ) {return(true); }
    else { return(false); }
};

int RectangularCavity::ijk2n(int i , int j , int k) {
// bins are indexed from 0
    return(k * xbins * ybins + j * xbins + i );
};

vector <int>  RectangularCavity::n2ijk(int n) {
// bins are indexed from 0

    vector <int> ijk;
    ijk.push_back(n % xbins);
    ijk.push_back( (n % (xbins*ybins) ) / xbins);
    ijk.push_back(n / (xbins * ybins) );

    return(ijk);
};

vector <double> RectangularCavity::getNeighbors(int n) {
    vector<int> bins = n2ijk(n);
    
    int i = bins.at(0);
    int j = bins.at(1);
    int k = bins.at(2);

    int nfor= ijk2n(i+1,j,k);
    int nback= ijk2n(i-1,j,k);
    int nright= ijk2n(i,j+1,k);
    int nleft =ijk2n(i,j-1,k);
    int nup = ijk2n(i,j,k+1);   
    int ndown = ijk2n(i,j,k-1);

    
    vector<double> neighbors;
    neighbors.push_back( potential.at(nfor) );
    neighbors.push_back( potential.at(nback) );
    neighbors.push_back( potential.at(nright) );
    neighbors.push_back( potential.at(nleft) );
    neighbors.push_back( potential.at(nup) );
    neighbors.push_back( potential.at(ndown) );

    
    return(neighbors);
};

vector <int> RectangularCavity::getBins() {
    vector <int> bins = {xbins , ybins , zbins};
    std::cout << "size of bins: " << bins.size() << std::endl;
    return(bins);
};


void RectangularCavity::writePotential() {
    
    std::cout << "Writing results to file "  << std::endl;
//    std::cout << "xbins " << xbins  << std::endl;
//    std::cout << "ybins " << ybins  << std::endl;
//    std::cout << "zbins " << zbins  << std::endl;

//    vector <double> potyy = getPotential();

//    std::cout << "potsize " << potyy.size()  << std::endl;

    std::ofstream pot;
    pot.open(getName().append(".out"));

    int n;

    for (int i = 0; i < xbins; ++i) {
        for (int j = 0; j < ybins; ++j) {
            for(int k = 0; k < zbins; ++k) {
//    std::cout << "i " << i  << std::endl;
//    std::cout << "j " << j  << std::endl;
//    std::cout << "k " << k  << std::endl;
                n = ijk2n(i,j,k);
//                std::cout << "n " << n  << std::endl;
//                std::cout << "pot(n) " << getNthPotential(n) << std::endl;

                pot << i << "," << j << "," << k << "," << getNthPotential(n) << std::endl;
            }
        }
    }
};

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

void Cavity::calculateE() {
    std::cout<<" Somethnig has gone awry. " << std::endl;
};

void Cavity::writeE() {
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

    vector<double> neighbors;
    neighbors.push_back( getNthPotential( ijk2n(i+1,j  ,k  ) ) );
    neighbors.push_back( getNthPotential( ijk2n(i+1,j+1,k  ) ) );
    neighbors.push_back( getNthPotential( ijk2n(i+1,j-1,k  ) ) );
    neighbors.push_back( getNthPotential( ijk2n(i-1,j  ,k  ) ) );
    neighbors.push_back( getNthPotential( ijk2n(i-1,j+1,k  ) ) );
    neighbors.push_back( getNthPotential( ijk2n(i-1,j-1,k  ) ) );
    neighbors.push_back( getNthPotential( ijk2n(i  ,j+1,k  ) ) );
    neighbors.push_back( getNthPotential( ijk2n(i  ,j-1,k  ) ) );
    neighbors.push_back( getNthPotential( ijk2n(i+1,j  ,k+1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i+1,j+1,k+1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i+1,j-1,k+1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i-1,j  ,k+1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i-1,j+1,k+1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i-1,j-1,k+1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i  ,j+1,k+1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i  ,j-1,k+1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i+1,j  ,k-1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i+1,j+1,k-1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i+1,j-1,k-1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i-1,j  ,k-1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i-1,j+1,k-1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i-1,j-1,k-1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i  ,j+1,k-1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i  ,j-1,k-1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i  ,j  ,k+1) ) );
    neighbors.push_back( getNthPotential( ijk2n(i  ,j  ,k-1) ) );
 
    return(neighbors);
};

vector <int> RectangularCavity::getBins() {
    vector <int> bins = {xbins , ybins , zbins};
    std::cout << "size of bins: " << bins.size() << std::endl;
    return(bins);
};


void RectangularCavity::calculateE() {
    
    int i , j , k;
    
    double delx = (xf - x0)/xbins;
    double dely = (yf - y0)/ybins;
    double delz = (zf - z0)/ybins;
    
    vector <int> tmpijk;

    for (int n = 0; n < potential.size() ; ++n) {
        tmpijk = n2ijk(n);

        i = tmpijk.at(0);
        j = tmpijk.at(1);
        k = tmpijk.at(2);


        if (isBoundary(n) == false) {
            Ex.push_back( -0.5 * ( potential.at(ijk2n(i+1,j,k)) - potential.at(ijk2n(i-1,j,k)) ) / delx );
            Ey.push_back( -0.5 * ( potential.at(ijk2n(i,j+1,k)) - potential.at(ijk2n(i,j-1,k)) ) / dely );
            Ez.push_back( -0.5 * ( potential.at(ijk2n(i,j,k+1)) - potential.at(ijk2n(i,j,k-1)) ) / delz );
        }
        else {
            Ex.push_back(0.0);
            Ey.push_back(0.0);
            Ez.push_back(0.0);
        }
    };
};


void RectangularCavity::writePotential() {
    
    std::cout << "Writing potential to file "  << std::endl;
    std::ofstream pot;
    pot.open(getName().append("_V.out"));

    int n;

    for (int i = 0; i < xbins; ++i) {
        for (int j = 0; j < ybins; ++j) {
            for(int k = 0; k < zbins; ++k) {
                n = ijk2n(i,j,k);
                pot << i << "," << j << "," << k << "," << getNthPotential(n) << std::endl;
            }
        }
    }

    pot.close();
};

void RectangularCavity::writeE() {

    std::cout << "Writing E field to file "  << std::endl;
    std::ofstream pot;
    pot.open(getName().append("_E.out"));

    int n;

    for (int i = 0; i < xbins; ++i) {
        for (int j = 0; j < ybins; ++j) {
            for(int k = 0; k < zbins; ++k) {
                n = ijk2n(i,j,k);
                pot << i << "," << j << "," << k << "," << Ex.at(n) << "," << Ey.at(n) << "," << Ez.at(n)  << std::endl;
            }
        }
    }

    pot.close();
};



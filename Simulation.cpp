#include "Mesh.h"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */


int main() {
    clock_t t;

    
    vector <double> binWidths;
    vector <double> cavityDimensions = { 1.0  , 1.0 , 1.0 }; // rectangular cavity
    vector <int>    bins             = { 50   , 50 , 50 }; // number of bins in each dimension
    
    binWidths.push_back(cavityDimensions.at(0) / double(bins.at(0)) );
    binWidths.push_back(cavityDimensions.at(1) / double(bins.at(1)) );
    binWidths.push_back(cavityDimensions.at(2) / double(bins.at(2)) );

    RectangularCavity myCavity( "cCav" , cavityDimensions);

//    myCavity.setFarPotential(100.0);
//    myCavity.setNearPotential(100.0);
    myCavity.setLeftPotential(100.0);
    myCavity.setRightPotential(-100.0);
    
    RectangularCavity_ptr myCavityPtr = std::make_shared<RectangularCavity>(myCavity);
    
    Mesh mesh( myCavityPtr , bins );

    t = clock();
    mesh.solve("relax");
    t = clock() - t;
    
    std::cout<<"Solved for Phi in " << ((float)t)/CLOCKS_PER_SEC << " seconds" << std::endl;
    
    mesh.calculateE(binWidths);
    mesh.writeE();
    mesh.writePotential();

    return(0);
};


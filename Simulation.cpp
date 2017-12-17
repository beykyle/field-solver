#include "Mesh.h"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */


int main() {
    clock_t t;

    RectangularCavity myCavity( "cCav" , 1 , 1 , 1 , 50 , 50 , 50);
    myCavity.setTopPotential(100.00);
    myCavity.setLeftPotential(100.00);
    
    Mesh mesh(myCavity );

    t = clock();
    mesh.solve("relax");
    t = clock() - t;
    
    std::cout<<"Solved for Phi in " << ((float)t)/CLOCKS_PER_SEC << " seconds" << std::endl;
    


  //  myCavity.writePotential();
  //  myCavity.writeE();
};


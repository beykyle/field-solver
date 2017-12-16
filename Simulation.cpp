#include "Mesh.h"

int main() {
    
    RectangularCavity myCavity( "my_rectangular_cavity2" , 10 , 2 , 2 , 100 , 20 , 20);
    myCavity.setBottomPotential(10.0);
    myCavity.setLeftPotential(50.0);

    
    Mesh mesh(myCavity );
    mesh.solve("relax");
};


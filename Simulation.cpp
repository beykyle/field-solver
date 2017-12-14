#include "Mesh.h"

int main() {
    
    RectangularCavity cavity( "my_rectangular_cavity2" , 10 , 2 , 2 , 100 , 20 , 20);
    cavity.setBottomPotential(10.0);
    cavity.setFarPotential(50.0);
    cavity.setLeftPotential(50.0);

    
    Mesh mesh(cavity);
    mesh.solve("relax");
};


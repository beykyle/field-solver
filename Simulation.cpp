#include "Mesh.h"

int main() {
    
    RectangularCavity cavity( "my_rectangular_cavity2" , 10 , 5 , 5 , 100 , 50 , 50);
    cavity.setTopPotential(1.0);
    cavity.setBottomPotential(1.0);
    cavity.setLeftPotential(0.5);
    
    Mesh mesh(cavity);
    mesh.solve("relax");
};


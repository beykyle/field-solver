#include "Mesh.h"

int main() {
    RectangularCavity cavity( "washing_machine" , 10 , 4 , 4 , 10 , 4 , 4);
    Mesh wash_mesh(cavity);
    wash_mesh.solve("relax");
};

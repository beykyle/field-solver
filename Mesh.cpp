#include "Mesh.h"

// Utilities
enum string_code {
        eRelax,
        eFFT,
        eMatrix,
        eGreen,
        eFMM,
        eFinite,
        eMonte
};

string_code hashit (std::string const& inString) {
        if (inString == "relax"          )   return eRelax;
        if (inString == "fft"            )   return eFFT;
        if (inString == "matrix"         )   return eMatrix;
        if (inString == "green"          )   return eGreen;
        if (inString == "fmm"            )   return eFMM;
        if (inString == "finite_element" )   return eFinite;
        if (inString == "monte_carlo"    )   return eMonte;
}

double mean(vector <double> values) {
    double sum = 0.0;
    for (auto v : values) {
        sum += v;
    };

    return(sum / double(values.size()) );
};

// Constructrs


// Functions

void Mesh::solve(string method) {
// allowed methods: 'relax', 'fft', 'matrix', 'green', 'fmm' , 'finite_element', 'monte_carlo'
    std::cout << "Running " << method << " on " << cavity->getName() << std::endl;
    bool write = true;

    switch( hashit(method)) {
        case eRelax :
            relax();
            break;
        case eFFT :
            break;
        case eMatrix :
            break;
        case eGreen :
            break;
        case eFMM :
            break;
        case eFinite :
            break;
        case eMonte :
            break;
        default:
            write = false;
            std::cerr << method <<" is not a recognized solve method for Mesh.solve()" << std::endl;
            break;
    }

    if(write == true) {
        cavity->writePotential();
    }
};
        
void Mesh::relax() {
    bool converge = false;
    int  count    = 0;
    vector<double> neighbors;
    vector<double> oldPotential;
    vector<double> diff;

    // while the simulation hasn't converged
    while (converge == false) {
        std::cout << "Doing relaxation..." << std::endl;
        // iterate over non-boundary bins
        for (int n = 0; n < cavity->getPotential().size(); ++n) {
            if (cavity->isBoundary(n) == false) {
                // do relaxation on this bin
                neighbors = cavity->getNeighbors(n);
                cavity->setPotential(n , mean(neighbors));               
            }
        }
        count++;
        
        // every 5 steps re-evaluate convergence
        if (count % 10 == 0) {
                converge = true; 
        }
    } 
};
